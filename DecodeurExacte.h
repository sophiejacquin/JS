#ifndef MOEO_JS_DECODEREXACTE_H_
#define MOEO_JS_DECODEREXACTE_H_

#include <core/MOEO.h>
#include <eoFunctor.h>
#include "moeoJobShopEvalFuncS.h"
#include <addToParadisEO/moeo/core/moeoDecoder.h>
#include "Data.h"
template < class MOEOT, class MOEOTX >
typedef struct
   {
   	int Jobdeb;
	int derAvance;
	int Jobfin;
	double val;
	int earli;
	int tardi;
	bool bloque;
   } Bloc;
class moeoJSDecoderExacte : public moeoDecoder<MOEOT, MOEOTX>
{
 public:
	moeoJSDecoderExacte(Data & data_, moeoJSEvalFunc<MOEOTX> eval_)
	{
		data=data_;
		eval=eval_;
	}
	MOEOTX initSol_et_blocs(vector<int> & ordre,vector< Bloc> & blocs)
	{
		MOEOTX eoX;
		eoX.setN(data.getN());
		eoX.setListeJobs(ordre);
		vector<double> completionTime;
		int r0=data.getJob(ordre[0]).getR();
		int p0=data.getJob(ordre[0]).getP();
		int d0=data.getJob(ordre[0]).getD();
		Bloc b;
		b.Jobdeb=0;
		b.Jobfin=0;
		b.derAvance=0;
		b.earli=data.getJob(ordre[0]).getalpha();
		if(d0<r0+p0)
		{
			completionTime.push_back(r0+p0);
			b.tardi=data.getJob(ordre[0]).getBeta();
			b.bloque=true;
		}
		else
		{
			completionTime.push_back(d0);
			b.tardi=0;
			b.bloque=false;
		}
		b.val=b.tardi/b.earli;
		blocs.push_back(b);
		for(unsigned int i=1; i<ordre.size();i++)
		{
			int r=data.getJob(ordre[i]).getR();
			int p=data.getJob(ordre[i]).getP();
			int d=data.getJob(ordre[i]).getD();
			double C=completionTime[i-1];
			if(d>C+p and d > r+p)
			{
				Bloc b;
				b.Jobdebut=i;
				b.Jobfin=i;
				b.derAvance=i;
				b.earli=data.getJob(ordre[i]).getalpha();
				b.tardi=0;
				blocs.push_bach(b);
				completionTime.push(d);
				b.bloque=false;
				blocs.push_back(b);
			}
			else if(C+p > r+p)
			{
				blocs[blocs.size()-1].Jobfin=i;
				if(C+p==d)
				{
					blocs[blocs.size()-1].earli+=data.getJob(ordre[i]).getalpha();
					blocs[blocs.size()-1].derAvance=i;
					
				}
				else
				{
					blocs[blocs.size()-1].tardi+=data.getJob(ordre[i]).getBeta();
				}
				blocs[blocs.size()-1].val=blocs[blocs.size()-1].tardi/blocs[blocs.size()-1].earli;
				completionTime.push(C+p);
			}
			else //creation d'un nouveau bloc bloqué
			{
				Bloc b;
				b.Jobdebut=i;
				b.Jobfin=i;
				b.derAvance=i;
				b.bloque=true;
				b.early=1;
				b.tardy=0;
				b.val=0;
				blocs.push_back(b);
				completionTime.push(r+p);
				
					
			}
		}
		eoX.setCompletionTime(completionTime);
		
		int nbGrosBlocs=blocs.size();
		int gap=0;
		int taillePred=nbGrosBlocs;
		for(i=0;i<nbGrosBlocs;i++)
		{
			construire_sous_blocs(i+gap, blocs[i+gap].Jobdeb, blocs, eoX);
			gap=blocs.size()-taillePred;
			taillePred=blocs.size();
		}
		
		
		
		return eoX;
		
	}
	void bougerBloc(vector< Bloc> & blocs, MOEOTX & eoX, int numBloc)
	{
		int blocPred=blocPred( blocs, numBloc);
		int t =calculT( blocs, eoX, numBloc, blocPred);
		
		//decolage du bloc de droite si besoin
		if(numBloc<blocs.size()-1 && blocs[numBloc].Jobdeb=blocs[numBloc+1].Jobdeb)
		{
			blocs[numBloc+1].Jobdeb=blocs[numBloc].Jobfin+1;
			blocs[numBloc+1].derAvance=blocs[numBloc+1].Jobdeb;
			int i =blocs[numBloc+1].Jobdeb;
			while(i<=blocs[numBloc+1].Jobfin && eoX.getCompletionTime(i) -data.getJob(eoX.getJob(i)).getD()<=0)
			{
				blocs[numBloc+1].derAvance=i;
				i++;
			}
		}
		//fusion bloc gauche si necessaire
		
		for(unsigned int i=blocs[numBloc].Jobdeb; i <=blocs[numBloc].Jobfin;i++)
		{
			int C=eoX.getCompletionTime(i)-t;
			eoX.setCompletionTime(i,C);
			
			
		}
		erase_sous_blocs(numBloc,blocs);
		if(eoX.getCompletionTime(blocs[blocPred].Jobfin)==eoX.getCompletionTime(blocs[numBloc].Jobdeb)-data.getJob(eoX.getJob(blocs[numBloc].Jobdeb)).getP())
		{
			if(blocs[blocPred].bloque)
			{
				blocs[blocPred].Jobfin=blocs[numBloc].Jobfin;
				blocs.erase (blocs.begin()+numBloc);
				numBloc--;
			}
			else if(blocs[blocPred].val==0 )
			{
				blocs[blocPred].bloque=blocs[numBloc].bloque;
				blocs[blocPred].Jobfin=blocs[numBloc].Jobfin;
				blocs.erase (blocs.begin()+numBloc);
				numBloc--;
			}
			else if(not(blocs[numBloc].bloque) && blocs[numBloc-1].val>0)
			{
				blocs[blocPred].Jobfin=blocs[numBloc].Jobfin;
				blocs[numBloc].Jobdeb=blocs[blocPred].Jobdeb;
			}
			
		}
		construire_sous_blocs(numBloc, deb,blocs);
		
		//TODO :calcul valeurs des blocs!!!!
	}
	void erase_sous_blocs(int & num,vector< Bloc> & blocs)
	{
		int i=0;
		while(blocs[i].Jobdeb<=blocs[num].Jobdeb and i<num)
		{
			if(blocs[i].Jobdeb==blocs[num].Jobdeb)
			{
				blocs.erase (blocs.begin()+i);
				num--;
			}
		}
	}
	void construire_sous_blocs(int num, int deb, vector< Bloc> & blocs, MOEOTX & eoX)
	{
		int place=num;
		int fin=blocs[num].Jobfin;
		int i =deb
		bool bloque=false;
		while(i<fin)
		{
			Bloc b;
			b.Jobdeb=i;
			derAvance=i;
			while(not(bloque) && (eoX.getCompletionTime(derAvance)-data.getJob(eoX.getJob(derAvance)).getD())<=0)
			{
				
				if(eoX.getCompletionTime(derAvance)-data.getJob(eoX.getJob(derAvance)).getR()==0)
					bloque=true;
				else derAvance++;
			}
			b.derAvance=derAvance;
			i=derAvance+1;
			if (bloque){
				b.Jobfin=fin;
				b.bloque=true;
				i=fin;
			}
			else{
				while(i<data.getN() && not((eoX.getCompletionTime(i)-data.getJob(eoX.getJob(i)).getD())<=0) or not(eoX.getCompletionTime(i)-data.getJob(eoX.getJob(i)).getR()) )
				{
					i++;
				
				}
				b.Jobfin=i-1;
			}
			blocs.insert(blocs.begin()+place,b); place+=1;
		}
	}
	int calculT(vector< Bloc> & blocs, MOEOTX & eoX, int numBloc, int blocPred)
	{
		int tempsDebBloc= eoX.getCompletionTime(blocs[numBloc].Jobdeb)-data.getJob(eoX.getJob(blocs[numBloc].Jobdeb)).detP();
		int t=tempsDebBloc;
		if( blocPred>-1)
			t=t-eoX.getCompletionTime(blocs[blocPred].Jobfin);
		for(unsigned i=0; i<blocs[numBloc].jobfin+1; i++)
		{
			int ecartD=eoX.getCompletionTime(i)-data.getJob(eoX.getJob(i)).detP()-data.getJob(eoX.getJob(i)).detD();
			if (ecartD<t)
				t=ecartD;
		
		
			int ecartR=eoX.getCompletionTime(i)-data.getJob(eoX.getJob(i)).detP()-data.getJob(eoX.getJob(i)).detR();
			if (ecartR<t){
				t=ecartR;
				if (i<=blocs[numBloc].derAvance)
					 blocs[numBloc].bloque=true;
			}
		}
		return t;
		
			
	}
	int choixBloc(vector< Bloc> & blocs)
	{
		double valMax= 0;
		int choix=-1;
		int s=blocs.size();

		for ( unsigned i =0; i<s;i++)
		{

			if (not(blocs[i].bloque) && blocs[i].val>valMax)
			{
				valMax=blocs[i].val;
				choix=i;
			}
		}
		
		return choix;
	}
	int blocPred(vector< Bloc> & blocs, int numBloc)
	{
		int numPred=numBloc -1;
		while(numPred>=0 && blocs[numPred].Jobdeb==blocs[numBloc].Jobdeb)
		{
			numPred -=1;
		}
		return numPred;
	}
	void operator () (MOEOT & eo, eoPop<MOEOTX> & popX)
	{
	}
	
 private:
	Data data;
	moeoJSEvalFunc<MOEOTX> eval;
};

#endif
