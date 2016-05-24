#ifndef _eoJobShop_h
#define _eoJobShop_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <addToParadisEO/moeo/core/Origin.h>
class moeoJobShop : public moeoRealVector < moeoJobShopObjectiveVector >, public Origin{
 public :
	moeoJobShop()
	{
		N=0;
	}
	 virtual ~moeoJobShop()
  	{
  	}
	virtual string className() const { return "eoJobShop"; }

  
    	void printOn(ostream& os) const
    	{
      
     	 moeoIntVector<moeoJobShopObjectiveVector>::printOn(os);
      	os << ' ';
    
    	}

  
    	void readFrom(istream& is)
      	{
	
	moeoIntVector<eoJobShopObjectiveVector>::readFrom(is);
    
      	}
	int operator [](i)
	{
		return listeJobs[i];
	}
	void setN(int N_)
    	{
        	N=N_;
    	}
    	int getN() const
    	{
       	 	return N;
    	}
	void setListeJobs(std::vector<int> liste)
	{
		listeJobs=liste;
	}
 private :
 	std::vector<int> listeJobs;
	int N;
};
#endif
