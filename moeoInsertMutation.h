
#ifndef eoJobShopInsertMutation_H
#define eoJobShopInsertMutation_H


#include <eoOp.h>
#include <eoShiftMutation.h>
template<class eoJobShop>
class moeoInsertMutation: public eoMonOp<eoJobShop>
{
 public:
	moeoInsertMutation()
	{
		
	}
	virtual std::string className() const { return "moeoInsertMutation"; }
	bool operator() (eoJobShop & eo)
	{
		eoShiftMutation< vector<int> > mut(nbSwap);
		mut(eo.getListeJobs()); //si pb reflechir fonction qui renvoie ref...
		return true;
	}

 

};
