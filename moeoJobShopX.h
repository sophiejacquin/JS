#ifndef _eoJobShopX_h
#define _eoJobShopX_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <addToParadisEO/moeo/core/Origin.h>
class moeoJobShopX : public moeoRealVector < moeoJobShopXObjectiveVector >, public Origin{
 public:
	moeoJobShop()
	{
		N=0;
	}
	 virtual ~moeoJobShopX()
  	{
  	}
	virtual string className() const { return "eoJobShopX"; }

  
    	void printOn(ostream& os) const
    	{
      
     	 	moeoIntVector<moeoJobShopXObjectiveVector>::printOn(os);
      		os << ' ';
    
    	}
    	void readFrom(istream& is)
      	{
	
		moeoIntVector<eoJobShopXObjectiveVector>::readFrom(is);
    
      	}
	int getJob(i)
	{
		return listeJobs[i];
	}
	int getCompletionTime(i)
	{
		return completionTime[i];
	}
	void setCompletionTime(std::vector<int> time_)
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
	std::vector<int> completionTime;
	int N;
};
#endif
