#ifndef _eoJobShopX_h
#define _eoJobShopX_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <addToParadisEO/moeo/core/Origin.h>
#include "eoJobShopObjectiveVector.h"
class moeoJobShopX : public moeoRealVector < eoJobShopObjectiveVector >, public Origin{
 public:
	moeoJobShopX()
	{
		N=0;
	}
	 virtual ~moeoJobShopX()
  	{
  	}
	virtual string className() const { return "eoJobShopX"; }

  
    	void printOn(ostream& os) const
    	{
      
     	 	moeoRealVector<eoJobShopObjectiveVector>::printOn(os);
      		os <<this->origin()<< ' '<<endl;
    
    	}
    	void readFrom(istream& is)
      	{
	
		moeoRealVector<eoJobShopObjectiveVector>::readFrom(is);
    
      	}
	int getJob(unsigned int i)
	{
		return listeJobs[i];
	}
	double getCompletionTime(unsigned int i)
	{
		return completionTime[i];
	}
	void setCompletionTime(std::vector<double> time_)
	{
		completionTime=time_;
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
 private:
	std::vector<int> listeJobs;
	std::vector<double> completionTime;
	int N;
};
#endif
