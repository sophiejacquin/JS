#ifndef MOEO_JS_DECODEREXACTE_H_
#define MOEO_JS_DECODEREXACTE_H_

#include <core/MOEO.h>
#include <eoFunctor.h>
#include "moeoJobShopEvalFuncS.h"
#include <addToParadisEO/moeo/core/moeoDecoder.h>
#include "Data.h"
#define INF 100000
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

template < class MOEOT, class MOEOTX >
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
		cout<<ordre[0]<<" "<<data.getN()<<endl;
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
		b.earli=data.getJob(ordre[0]).getAlpha();
		int nR=0;
		int nB=0;
		//cout<<"debug0"<<endl;
		if(d0<r0+p0)
		{
			completionTime.push_back(r0+p0);
			b.tardi=data.getJob(ordre[0]).getBeta();
			b.bloque=true;
			nB++;
		}
		else
		{
			completionTime.push_back(d0);
			b.tardi=0;
			b.bloque=false;
		}
		if (b.earli==0)
		{
			if(b.tardi==0)
				b.val=0;
			else b.val=INF;
		}
		else
			b.val=(double)b.tardi/b.earli;
		blocs.push_back(b);
		for(unsigned int i=1; i<ordre.size();i++)
		{
			int r=data.getJob(ordre[i]).getR();
			int p=data.getJob(ordre[i]).getP();
			int d=data.getJob(ordre[i]).getD();
			double C=completionTime[i-1];
			if(d>C+p and d > r+p)
			{
				if(data.getJob(ordre[i]).getAlpha()==0)
				{
					blocs[blocs.size()-1].Jobfin=i;
					if(blocs[blocs.size()-1].derAvance==i-1)
						blocs[blocs.size()-1].derAvance=i;
					completionTime.push_back(C+p);
				}
				else{
				Bloc b;
				b.Jobdeb=i;
				b.Jobfin=i;
				b.derAvance=i;
				b.earli=data.getJob(ordre[i]).getAlpha();
				b.tardi=0;
				completionTime.push_back(d);
				b.bloque=false;
				
				if (b.earli==0)
				{
					if(b.tardi==0)
						b.val=0;
					else b.val=INF;
				}
				else{
					

					b.val=(double)b.tardi/b.earli;
				 }
				blocs.push_back(b);}
			}
			else if(C > r)
			{
				blocs[blocs.size()-1].Jobfin=i;
				if(C+p==d)
				{
					blocs[blocs.size()-1].earli+=data.getJob(ordre[i]).getAlpha();
					if(blocs[blocs.size()-1].derAvance==i-1)
						blocs[blocs.size()-1].derAvance=i;
					
				}
				else
				{
					blocs[blocs.size()-1].tardi+=data.getJob(ordre[i]).getBeta();
					nR++;
				}
				if(blocs[blocs.size()-1].earli>0)
					blocs[blocs.size()-1].val=(double)blocs[blocs.size()-1].tardi/blocs[blocs.size()-1].earli;
				else{
					if(blocs[blocs.size()-1].tardi==0)
						blocs[blocs.size()-1].val=0;	
					else blocs[blocs.size()-1].val=INF;
				}
				completionTime.push_back(C+p);
			}
			else //creation d'un nouveau bloc bloqué
			{
				Bloc b;
				b.Jobdeb=i;
				b.Jobfin=i;
				b.derAvance=i;
				b.bloque=true;
				b.earli=1;
				b.tardi=0;
				b.val=0;
				blocs.push_back(b);
				completionTime.push_back(r+p);
				nB++;	
			}
		}
		eoX.setCompletionTime(completionTime);
		cout<<"nR="<<nR<<" nB="<<nB<<endl;
		int nbGrosBlocs=blocs.size();
		int gap=0;
		int taillePred=nbGrosBlocs;
		for(unsigned int i=0;i<nbGrosBlocs;i++)
		{

			construire_sous_blocs(i+gap, blocs[i+gap].Jobdeb, blocs, eoX);
			gap=blocs.size()-taillePred;
			//cout<<"gap="<<gap<<endl;
			taillePred=blocs.size();
		}
		
		
		
		return eoX;
		
	}
	void bougerBloc(vector< Bloc> & blocs, MOEOTX & eoX, int numBloc)
	{
		//cout<<"deb bouger blocs"<<endl;
		int blocPred=get_blocPred( blocs, numBloc);
		int t =calculT( blocs, eoX, numBloc, blocPred);
		// cout<<" t "<<t<<endl;
		int deb= blocs[numBloc].Jobdeb;
		//decollage du(ou DES) bloc de droite si besoin + recalculer earli , tardi et val..
		int j=1;
		while(numBloc+j<blocs.size() && blocs[numBloc].Jobdeb==blocs[numBloc+j].Jobdeb)
		{
			blocs[numBloc+j].Jobdeb=blocs[numBloc].Jobfin+1;
			blocs[numBloc+j].derAvance=blocs[numBloc+j].Jobdeb;
			int i =blocs[numBloc+j].Jobdeb;
			while(i<=blocs[numBloc+j].Jobfin && eoX.getCompletionTime(i) -data.getJob(eoX.getJob(i)).getD()<=0)
			{
				blocs[numBloc+j].derAvance=i;
				i++;
			}
			blocs[numBloc+j].tardi-=blocs[numBloc].tardi;
			blocs[numBloc+j].earli-=blocs[numBloc].earli;
			if(blocs[numBloc].earli>0)
				blocs[numBloc+j].val=(double)blocs[numBloc+j].tardi/blocs[numBloc+j].earli;
			else
			{
				if(blocs[numBloc+j].tardi==0)
					blocs[numBloc+j].val=0;
				else
					blocs[numBloc+j].val=INF;
			}
			j++;
		}
		
		
		for(unsigned int i=blocs[numBloc].Jobdeb; i <=blocs[numBloc].Jobfin;i++)
		{
			int C=eoX.getCompletionTime(i)-t;
			eoX.setCompletionTime(i,C);
			
			
		}
		erase_sous_blocs(numBloc,blocs);
		
		blocPred=numBloc-1;
		//fusion bloc gauche si necessaire 
		if(blocPred>=0 && eoX.getCompletionTime(blocs[blocPred].Jobfin)==eoX.getCompletionTime(blocs[numBloc].Jobdeb)-data.getJob(eoX.getJob(blocs[numBloc].Jobdeb)).getP())
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
			else if(not(blocs[numBloc].bloque) && blocs[numBloc-1].val>0)//peut etre probleme au découpage ici
			{
				//blocs[blocPred].Jobfin=blocs[numBloc].Jobfin;
				blocs[numBloc].Jobdeb=blocs[blocPred].Jobdeb;
				
			}
			
		}
		if(numBloc<0)
	       {
			 cout<< numBloc<<endl;
			exit(0);
		}
		construire_sous_blocs(numBloc, deb,blocs,eoX);
		//cout<<"fin bouger blocs"<<endl;
		
	}
	void erase_sous_blocs(int & num,vector< Bloc> & blocs)
	{
		//cout<<"deb erase sous blocs"<<endl;
		int i=0;
		while(blocs[i].Jobdeb<=blocs[num].Jobdeb and i<num)
		{
			if(blocs[i].Jobdeb==blocs[num].Jobdeb)
			{
				blocs.erase (blocs.begin()+i);
				num--;
			}
			else i++;
		}
		//cout<<"fin erase sous blocs"<<endl;
	}
	void construire_sous_blocs(int num, int deb, vector< Bloc> & blocs, MOEOTX & eoX)
	{
		//cout<<"deb construire sous bloc"<<endl;
		int place=num;
		int fin=blocs[num].Jobfin;
		int da=blocs[num].derAvance;
		int i =deb;
		int debut=blocs[num].Jobdeb;
		bool bloque=false;
		int earli=0;
		int tardi=0;
		double val;//attentioon div int -> int??
		while(i<=fin and not(bloque))
		{
			Bloc b;
			b.Jobdeb=debut;
			int derAvance=i;
			if(eoX.getCompletionTime(derAvance)-data.getJob(eoX.getJob(derAvance)).getP()-data.getJob(eoX.getJob(derAvance)).getR()==0)
				bloque=true;
			while(derAvance<=fin && not(bloque) && (eoX.getCompletionTime(derAvance)-data.getJob(eoX.getJob(derAvance)).getD())<=0)
			{
				earli+=data.getJob(eoX.getJob(derAvance)).getAlpha();
				if(eoX.getCompletionTime(derAvance)-data.getJob(eoX.getJob(derAvance)).getP()-data.getJob(eoX.getJob(derAvance)).getR()==0)
					bloque=true;
				 derAvance++;
			}
			// cout<<"derAvance "<<derAvance-1<<" "<<eoX.getCompletionTime(derAvance)-data.getJob(eoX.getJob(derAvance)).getD()<<" D "<<data.getJob(eoX.getJob(derAvance)).getD()<< " R "<<data.getJob(eoX.getJob(derAvance)).getR()<<" P "<<data.getJob(eoX.getJob(derAvance)).getP()<<" C "<<eoX.getCompletionTime(derAvance)<<" i : "<<i<<" fin : "<<fin<<endl;

			
			b.derAvance=da;
			
			if (bloque){
				b.Jobfin=fin;
				b.bloque=true;
				b.Jobdeb=i;
				blocs[place]=b;
				
			}
			else{
				i=derAvance;
				b.bloque=false;
				while(i<fin+1 && not((eoX.getCompletionTime(i)-data.getJob(eoX.getJob(i)).getD())<=0) and not(eoX.getCompletionTime(i)-data.getJob(eoX.getJob(i)).getP()-data.getJob(eoX.getJob(i)).getR()==0) )			
				{
					tardi+=data.getJob(eoX.getJob(i)).getBeta();
					i++;
				
				}
				b.Jobfin=i-1;
			
				if (i<fin+1){
					
					b.earli=earli;
					b.tardi=tardi;
					if(earli>0)
						b.val=(double)(tardi)/earli;
					else
					{
						if(tardi==0)
							b.val=0;
						else b.val=INF;
					}
					blocs.insert(blocs.begin()+place,b);
					 place+=1;
				}
				else
				{
					blocs[place].earli=earli;
					blocs[place].tardi=tardi;
					if(earli>0)
						blocs[place].val=(double)tardi/earli;
					else
					{
						if(tardi==0)
							blocs[place].val=0;
						else blocs[place].val=INF;
					}
				}
			}		
			
		}
		//cout<<"fin construire sous bloc"<<endl;
	}
	int calculT(vector< Bloc> & blocs, MOEOTX & eoX, int numBloc, int blocPred)
	{
		//cout<<"deb calcul T"<<endl;

		bool bloque=false;
		int tempsDebBloc= eoX.getCompletionTime(blocs[numBloc].Jobdeb)-data.getJob(eoX.getJob(blocs[numBloc].Jobdeb)).getP();
		int t=tempsDebBloc;
		if( blocPred>-1)
			t=t-eoX.getCompletionTime(blocs[blocPred].Jobfin);
		for(unsigned i=blocs[numBloc].Jobdeb; i<blocs[numBloc].Jobfin+1; i++)
		{
			int ecartD=eoX.getCompletionTime(i)-data.getJob(eoX.getJob(i)).getD();
			if (ecartD>0 && ecartD<t){
				t=ecartD;
				bloque=false;}

		
		
			int ecartR=eoX.getCompletionTime(i)-data.getJob(eoX.getJob(i)).getP()-data.getJob(eoX.getJob(i)).getR();
			if (ecartR<t){
				
				t=ecartR;
				if (i<=blocs[numBloc].derAvance)
				  bloque=true;
				else
					bloque=false;
			}
		}
		//cout<<"fin calcul T"<<endl;
		return t;
		
			
	}
	int choixBloc(vector< Bloc> & blocs)
	{
		//cout<<"deb choixBloc"<<endl;
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
		//cout<<" valmax="<<valMax<<" earli "<<blocs[choix].earli<<" tardi "<<blocs[choix].tardi<<" numbloc "<<choix<<endl;
		/*if(blocs[choix].earli==0 && (not(blocs[choix].bloque) and valMax!=0)){
			 
			cout<<choix<<" LISTE BLOCS :"<<endl;
			for(unsigned i=0;i<blocs.size();i++)
			{
				cout<<blocs[i].Jobdeb<<" "<<blocs[i].Jobfin<<" "<<blocs[i].bloque<<" earli : "<<blocs[i].earli<<" tardi : "<<blocs[i].tardi<<endl;
			}
			exit(0);
		}*/
		return choix;
	}
	int get_blocPred(vector< Bloc> & blocs, int numBloc)
	{
		//cout<<"deb bloc pred"<<endl;
		int numPred=numBloc -1;
		while(numPred>=0 && blocs[numPred].Jobdeb==blocs[numBloc].Jobdeb)
		{
			numPred -=1;
		}
		//cout<<"fin bloc pred"<<endl;
		return numPred;
	}
	void operator () (MOEOT & eo, eoPop<MOEOTX> & popX)
	{
		//cout<<"dans deco exacte"<<endl;
		vector<int> ordre=eo.getListeJobs();
		vector<Bloc> blocs;
		//cout<<"av init"<<endl;
		MOEOTX eoX = initSol_et_blocs(ordre, blocs);
		//cout<<"apres init"<<endl;
		/*cout<<"LISTE BLOCS :"<<endl;
		for(unsigned i=0;i<blocs.size();i++)
		{
			cout<<blocs[i].Jobdeb<<" "<<blocs[i].Jobfin<<" "<<blocs[i].bloque<<" earli : "<<blocs[i].earli<<" tardi : "<<blocs[i].tardi<<endl;
		}*/
		eval(eoX);
		popX.push_back(eoX);
		eoX.invalidate();
		int numBloc=choixBloc(blocs);
		while(numBloc>=0)
		{

			bougerBloc( blocs, eoX, numBloc);
			eval(eoX);
			popX.push_back(eoX);
			eoX.invalidate();
			numBloc=choixBloc(blocs);

			
			
			
		}
	}
	
 private:
	Data data;
	moeoJSEvalFunc<MOEOTX> eval;
};

#endif
