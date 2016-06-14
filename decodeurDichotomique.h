#ifndef MOEO_JS_DECODERDICO_H_
#define MOEO_JS_DECODERDICO_H_

#include <core/MOEO.h>
#include <eoFunctor.h>
#include "moeoJobShopEvalFuncS.h"
#include <addToParadisEO/moeo/core/moeoDecoder.h>
#include "Timing.h"

template < class MOEOT, class MOEOTX >
class moeoJSDecoderDichotomique : public moeoDecoder<MOEOT, MOEOTX>
{
 public:
	
	typedef typename MOEOT::ObjectiveVector ObjectiveVector;
	moeoJSDecoderDichotomique(Timing<MOEOTX> & t, int Nb_lambda_, moeoJSEvalFunc<MOEOTX> eval_)
	{
		timer=t;
		nb_lambda=Nb_lambda_;
		eval=eval_;
	}
	void operator () (MOEOT & eo, eoPop<MOEOTX> & popX)
	{
		vector< vector<double> >points;
		int N=eo.getN();
		vector<int> jobs=eo.getListeJobs();

		MOEOTX eoX0;
		eoX0.setN(N);
		eoX0.setListeJobs(jobs);
		vector<double> time0;
		timer.timing(jobs,time0, 0, 1);
		eoX0.setCompletionTime(time0);
		eval(eoX0);
		popX.push_back(eoX0);
		vector<double> point0;
		point0.push_back(eoX0.objectiveVector()[0]);
		point0.push_back(eoX0.objectiveVector()[1]);
		points.push_back(point0);
		

		MOEOTX eoX1;
		eoX1.setN(N);
		eoX1.setListeJobs(jobs);
		vector<double> time1;
		timer.timing(jobs,time1, 1, 0);
		eoX1.setCompletionTime(time1);
		eval(eoX1);
		vector<double> point1;
		point1.push_back(eoX1.objectiveVector()[0]);
		point1.push_back(eoX1.objectiveVector()[1]);
		points.push_back(point1);
		popX.push_back(eoX1);
		vector<bool> censure(1,false);
		if(point1[0]==point0[0])
		{
			censure[0]=true;
			cout<<"sol unique"<<endl;
		}
		unsigned int i=1;
		while( i<nb_lambda)
		{

	   		double dmax=0;
	   		int ptselec=-1;
	   		for(int pt=0; pt<points.size()-1;pt++)
	   		{
		
				double dpts=((points[pt][0]-points[pt+1][0])/10000)*((points[pt][0]-points[pt+1][0])/10000)+((points[pt][1]-points[pt+1][1])/10000)*((points[pt][1]-points[pt+1][1])/10000);
				cout<<dpts<<endl;
				if(dpts>=dmax && not(censure[pt]))
				{
					dmax=dpts;
					ptselec=pt;
				}
	   		}
		
           		if(ptselec==-1)
				break;
			cout<<"pt select"<<ptselec<< " "<<points[ptselec][0]<<endl;
			double a1=(points[ptselec+1][1]-points[ptselec][1]);
			double a2=(points[ptselec][0]-points[ptselec+1][0]);
	   		double alpha1=(points[ptselec+1][1]-points[ptselec][1])/(a1+a2);
			double alpha2=(points[ptselec][0]-points[ptselec+1][0])/(a1+a2);
			MOEOTX eoX;
			eoX.setN(N);
			eoX.setListeJobs(jobs);
			vector<double> time;
			timer.timing(jobs,time, alpha1, alpha2);
			eoX.setCompletionTime(time);
			eval(eoX);
			

			vector<double> point;
			point.push_back(eoX.objectiveVector()[0]);
			point.push_back(eoX.objectiveVector()[1]);
			if(point[0]==points[ptselec][0]|| point[0]==points[ptselec+1][0])
				{
					if(points[ptselec][0]==36758)
						cout<<point[0]<<"  "<<points[ptselec+1][0]<<endl;
					censure[ptselec]=true;
					cout<<"ici on censure"<<endl;
				}
			else{
				points.insert(points.begin()+ptselec+1,point);
				censure.insert(censure.begin()+ptselec+1,false);
				i++;
				popX.push_back(eoX);
			}
			
				
		}
		for(int i=0;i<points.size();i++)
			cout<<points[i][0]<<"   ";
		cout<<endl;
	}
private :
	Timing<MOEOTX> timer;
	int nb_lambda;
	moeoJSEvalFunc<MOEOTX> eval;

};
#endif
