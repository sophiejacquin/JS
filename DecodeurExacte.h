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
	}
	void bougerBloc(vector< Bloc> & blocs, MOEOTX & eoX, int numBloc)
	{
		
	}
	int calculT(vector< Bloc> & blocs, MOEOTX & eoX, int numBloc, int blocPred)
	{
		
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
