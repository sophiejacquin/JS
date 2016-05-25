
#ifndef eoJobShopMutation_H
#define eoJobShopMutation_H


#include <eoOp.h>
#include <eoSwapMutation.h>
template<class eoJobShop>
class moeoSwapMutation: public eoMonOp<eoJobShop>
{
 public:
	moeoSwapMutation(int nb)
	{
		nbSwap=nb;
	}
	virtual std::string className() const { return "moeoSwapMutation"; }
	bool operator() (eoJobShop & eo)
	{
		eoSwapMutation< vector<int> > mut(nbSwap);
		mut(eo.getListeJobs()); //si pb reflechir fonction qui renvoie ref...
		return true;
	}

 private:
	int nbSwap;

};
