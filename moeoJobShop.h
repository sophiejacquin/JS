#ifndef _eoJobShop_h
#define _eoJobShop_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <addToParadisEO/moeo/core/Origin.h>
#include "eoJobShopObjectiveVector.h"
class moeoJobShop : public moeoRealVector < eoJobShopObjectiveVector >, public Origin{
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
      
     	 	moeoRealVector<eoJobShopObjectiveVector>::printOn(os);
      	 	os << ' ';
    
    	}

  
    	void readFrom(istream& is)
      	{
	
	moeoRealVector<eoJobShopObjectiveVector>::readFrom(is);
    
      	}
	int operator [](unsigned int i)
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
	vector<int> & getListeJobs()
	{
		return listeJobs;
	}
 private :
 	std::vector<int> listeJobs;
	int N;
};
#endif
