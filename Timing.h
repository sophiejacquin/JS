#ifndef eoOneMachineTiming_H
#define eoOneMachineTiming_H
#include "Timing.h"

#include <eoOp.h>
template<class GenotypeT>
class Timing: public eoMonOp<GenotypeT>
{
public:
	Timing()
	{
		
	}
	Timing(Data _data)
	{
		data=_data;
	}
	bool operator()(GenotypeT & _genotype)
	{/*
		vector<int> ordre;
		vector<bool> dejaVus;
		vector<int>  temps;
		for(int i=0;i<data.getN();i++)
		{
			ordre.push_back(_genotype.getDernierVu(i));
			dejaVus.push_back(0);
		}
		timing(ordre,temps);
		miseAJour(0,data.getN()-1,temps,ordre,dejaVus,_genotype);
		return true;
		*/
	}

	void timing(const vector<int> & ordre, vector<double> & temps, int lambda, int lambda2)
	{
		
		
		int n=data.getN();
		vector<double> H;
		H.push_back(0);
		double ld=0;double lf=0;
		vector<double> gamma;
		gamma.push_back(0);
		vector<double> C ;
		C.push_back(0);
		int P=0;
		for(int k=1; k<n+1;k++)
		{
			
			int rk=data.getJob(ordre[k-1]).getR();
	
			int pk=data.getJob(ordre[k-1]).getP();
			int dk=data.getJob(ordre[k-1]).getD();
			int alphak=lambda*data.getJob(ordre[k-1]).getAlpha();
			int betak=(lambda2)*data.getJob(ordre[k-1]).getBeta();
			double x=C[k-1];
			if(x<rk)x=rk;
			x=x+pk-dk;
			if(rk>P) P=rk;
			P+=pk;
			double compressionMax=0;
			if(rk-C[k-1]<0) compressionMax=rk-C[k-1];
			
			if(H[lf]<compressionMax)
			{
				//cout<<"mise à jour H"<<endl;
				double diff=H[lf]-compressionMax;
				int l=lf;
				while(l>ld-1)
				{
					H[l]=H[l]-diff;
					if(H[l]>=0)
					{
						H[l]=0; ld=l;
					}
					l--;
				}

			}
			if(x<=0)
			{
				
				if(x<0)
				{	//cout<<"x<0"<<endl;
					lf=lf+1;
					double Hl=H[lf-1]+x;
					gamma.push_back(0);
					H.push_back(Hl);
				}
				gamma[lf]+=alphak;
				C.push_back(dk);
			}
			else
			{
				
				double Hnew=H[lf]+x;
				if(Hnew<0){
				
					int newP=lf;
					while(newP>ld && H[newP-1]<=Hnew)newP=newP-1;
					
					if(Hnew==H[newP])
					{
						gamma[newP]+=alphak+betak;
					}
					else
					{
						
						gamma.insert(gamma.begin()+newP,alphak+betak);
						
						H.insert(H.begin()+newP,Hnew);
						lf++;
					}
					
	
				} 
				gamma[lf]-=betak;
				int i=lf;
				C.push_back(P-H[i]);
				while(gamma[i]<=0 && i>ld)
				{
					gamma[i-1]=gamma[i-1]+gamma[i];
					C[k]=P-H[i];
					i=i-1;
					lf--;
				}
				
				while(lf>gamma.size())
				{
					gamma.pop_back(); H.pop_back();
				}
				//cout<<H[ld]<<endl;
			}
		}
		
		int avail=C[n];
		
		for(int k=n;k>0;k--)
		{
			if(C[k]>=avail)
				C[k]=avail;
			else avail=C[k];
			avail-=data.getJob(ordre[k-1]).getP();
		}
		C.erase(C.begin());
		temps=C;
		
	}


private:
 
    Data data;
};
#endif
