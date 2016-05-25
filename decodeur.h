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
	moeoJSDecoder(Timing & t)
	{
		timer=t;
	}
	void operator () (MOEOT & eo, eoPop<MOEOTX>& popX)
	{
	}
private :
	Timing timer;

};
#endif
