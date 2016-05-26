
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
		eoShiftMutation< eoVector<double, int> > mut;
		eoVector<double, int> x;
		x.value(eo.getListeJobs());
		mut(x); //si pb reflechir fonction qui renvoie ref...
		return true;
	}


 

};
#endif
