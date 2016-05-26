#ifndef MOEO_JS_DECODER_H_
#define MOEO_JS_DECODER_H_

#include <core/MOEO.h>
#include <eoFunctor.h>
#include <moeoJobShopEvalFuncS.h>
#include <addToParadisEO/moeo/core/moeoDecoder.h>
#include "Timing.h"

template < class MOEOT, class MOEOTX >
class moeoJSDecoder : public moeoDecoder<MOEOT, MOEOTX>
{
 public:
	
	typedef typename MOEOT::ObjectiveVector ObjectiveVector;
	moeoJSDecoder(Timing & t, int Nb_lambda_)
	{
		timer=t;
		nb_lambda=Nb_lambda_;
	}
	void operator () (MOEOT & eo, eoPop<MOEOTX> & popX)
	{
		int N=eo.getN();
		vector<int> jobs=eo.getListeJobs();
		for(i=0; i<nb_lambda+1;i++)
		{
			MOEOTX eoX;
			eoX.setN(N);
			eoX.setListeJobs(jobs);
			vector<double> time;
			timer.timing(jobs,time,i/nb_lambda);
			eoX.setCompletionTime(time);
			popX.push_back(eoX);	
		}	
	}
private :
	Timing timer;
	nb_lambda;

};
#endif
