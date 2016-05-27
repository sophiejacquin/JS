#ifndef MOEO_JS_DECODER_H_
#define MOEO_JS_DECODER_H_

#include <core/MOEO.h>
#include <eoFunctor.h>
#include "moeoJobShopEvalFuncS.h"
#include <addToParadisEO/moeo/core/moeoDecoder.h>
#include "Timing.h"

template < class MOEOT, class MOEOTX >
class moeoJSDecoder : public moeoDecoder<MOEOT, MOEOTX>
{
 public:
	
	typedef typename MOEOT::ObjectiveVector ObjectiveVector;
	moeoJSDecoder(Timing<MOEOTX> & t, int Nb_lambda_, moeoJSEvalFunc<MOEOTX> eval_)
	{
		timer=t;
		nb_lambda=Nb_lambda_;
		eval=eval_;
	}
	void operator () (MOEOT & eo, eoPop<MOEOTX> & popX)
	{
		int N=eo.getN();
		vector<int> jobs=eo.getListeJobs();
		for(unsigned int i=0; i<nb_lambda+1;i++)
		{
			MOEOTX eoX;
			eoX.setN(N);
			eoX.setListeJobs(jobs);
			vector<double> time;
			timer.timing(jobs,time,double(i)/double(nb_lambda));
			eoX.setCompletionTime(time);
			eval(eoX);
			popX.push_back(eoX);	
		}	
	}
private :
	Timing<MOEOTX> timer;
	int nb_lambda;
	moeoJSEvalFunc<MOEOTX> eval;

};
#endif
