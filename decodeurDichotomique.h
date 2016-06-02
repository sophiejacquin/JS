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
	moeoJSDecoderDichotmique(Timing<MOEOTX> & t, int Nb_lambda_, moeoJSEvalFunc<MOEOTX> eval_)
	{
		timer=t;
		nb_lambda=Nb_lambda_;
		eval=eval_;
	}
	void operator () (MOEOT & eo, eoPop<MOEOTX> & popX)
	{
		vector<vector<int>>points;
		int N=eo.getN();
		vector<int> jobs=eo.getListeJobs();

		MOEOTX eoX0;
		eoX0.setN(N);
		eoX0.setListeJobs(jobs);
		vector<double> time0;
		timer.timing(jobs,time0, 0, 1);
		eoX0.setCompletionTime(time);
		eval(eoX0);
		popX.push_back(eoX0);
		vector<int> point0;
		point0.push_back(eoX0.objectiveVector()[0],eoX0.objectiveVector()[1]);
		points.push_back(point0);
		

		MOEOTX eoX1;
		eoX1.setN(N);
		eoX1.setListeJobs(jobs);
		vector<double> time1;
		timer.timing(jobs,time1, 1, 0);
		eoX1.setCompletionTime(time);
		eval(eoX1);
		popX.push_back(eoX1);
		vector<int> point1;
		point1.push_back(eoX1.objectiveVector()[0],eoX1.objectiveVector()[1]);
		points.push_back(point1);
		popX.push_back(eoX1);
		vector<bool> censure(nb_lambda,false);
		if(point1[0]==point0[0])
			censure[0]=true;
		for(unsigned int i=1; i<nb_lambda;i++)
		{

	   		int dmax=0;
	   		int ptselec=-1;
	   		for(int pt=0; pt<points.size()-1;pt++)
	   		{
		
				int dpts=(points[pt][0]-points[pt+1][0])*(points[pt][0]-points[pt+1][0])+(points[pt][1]-points[pt+1][1])*(points[pt][1]-points[pt+1][1]);
		
				if(dpts>=dmax && not(censure(pt)))
				{
					dmax=dpts;
					ptselec=pt;
				}
	   		}
		
           		if(ptselect==-1)
				break;
			
	   		int alpha1=(points[ptselec+1][1]-points[ptselec][1])
			int alpha2((points[ptselec][0]-points[ptselec+1][0]);
			MOEOTX eoX;
			eoX.setN(N);
			eoX.setListeJobs(jobs);
			vector<double> time;
			timer.timing(jobs,time, alpha1, alpha2);
			eoX.setCompletionTime(time);
			eval(eoX);
			popX.push_back(eoX);

			vector<int> point;
			point.push_back(eoX.objectiveVector()[0],eoX.objectiveVector()[1]);
			if(point[0]==points[ptselec][0]|| point[0]==points[ptselec+1][0])
				censure[ptselect]=true;
			else
				points.insert(points.begin()+ptselec+1,point);
			
				
		}	
	}
private :
	Timing<MOEOTX> timer;
	int nb_lambda;
	moeoJSEvalFunc<MOEOTX> eval;

};
#endif
