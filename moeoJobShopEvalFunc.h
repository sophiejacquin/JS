#ifndef _eoJSEvalFunc_h
#define _eoJSEvalFunc_h

// include whatever general include you need
#include <stdexcept>
#include <fstream>

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

/**
  Always write a comment in this format before class definition
  if you want the class to be documented by Doxygen
*/
template <class EOT>
class moeoJSEvalFunc : public eoEvalFunc<EOT>
{
 public:
  moeoJSEvalFunc()
  {
      
  }
  moeoJSEvalFunc(Data & data_, int alpha_, int beta_, Timing<EOT> t)
  {
      timer=t;
      data=data_;
      lambda1=alpha_;
      lambda2=beta_;
  }

  /** Actually compute the fitness
   *
   * @param EOT & _eo the EO object to evaluate
   *                  it should stay templatized to be usable 
   *                  with any fitness type
   */
  void operator()(EOT & _eo)
  {
    // test for invalid to avoid recomputing fitness of unmodified individuals
    if (_eo.invalid())
      {
	//cout<<"deb eval"<<endl;
         int tardiness =0;
	 int earliness=0;
	 vector<int> jobs=_eo.getListeJobs();
	 vector<double> time;
	 timer.timing(jobs,time, lambda1, lambda2);
	 _eo.setCompletionTime(time);
          for(int i=0;i<data.getN(); i++)
          {
             
                  int job=_eo.getJob(i);
                  int e=0; int t=0;
                  int c=_eo.getCompletionTime(i);
                  int d=data.getJob(job).getD();
		  int alpha=data.getJob(job).getAlpha();
                  int beta =data.getJob(job).getBeta();
                  //cout<<alpha<<" "<<beta<<" c "<<c<<" "<<_eo.getEval(i)<<" d "<<d<<" fit "<<fit<<endl;
                  if(c<d)
                  {
                      e=alpha*(d-c);
                  }
                  else if(c>d)
                  {
                      t=beta*(c-d);
                  }
                  earliness+=e;
	          tardiness+=t;

              
          }
	eoJobShopObjectiveVector objVec;
	objVec[0]=earliness;
	objVec[1]=tardiness;
	_eo.objectiveVector(objVec);
	//cout<<"fin eval"<<endl;
      }
  }

 private:
    Timing<EOT> timer;
    Data data;
    double lambda1;
    double lambda2;

};
#endif
