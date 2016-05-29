#ifndef _eoJobShopInit_h
#define _eoJobShopInit_h

// include the base definition of eoInit
#include <eoInit.h>
#include "moeoJobShop.h"
#include "Parser.h"
#include "Timing.h"
#include "Data.h"

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * There is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO (e.g. to initialize
 *    atoms of an eoVector you will need an eoInit<AtomType>)
 */
template <class eoJobShop>
class moeoJobShopInit: public eoInit<eoJobShop> {
 public:
	moeoJobShopInit(Data data_)
	{
		data = data_;
		N = data.getN();
  	}
	void operator () (eoJobShop & eo)
	{
   		eo.setN(N);
		 std::srand ( unsigned ( std::time(0) ) );
		vector<int> order ;
		for (int i = 0; i < N; i++)
		{
			order.push_back(i);
		}
	
		random_shuffle ( order.begin(), order.end() );
		
		eo.setListeJobs(order);
		eo.invalidate();
	}
 private:
 	Data data;
	int N;
};
#endif
