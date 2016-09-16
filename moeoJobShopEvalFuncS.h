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
  moeoJSEvalFunc(Data & data_)
  {
      data=data_;
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
         double tardiness =0;
	 double earliness=0;
          for(int i=0;i<data.getN(); i++)
          {
             
                  int job=_eo.getJob(i);
                  double e=0; double t=0;
                  double c=_eo.getCompletionTime(i);
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
      }
  }

 private:
    Data data;

};
#endif
