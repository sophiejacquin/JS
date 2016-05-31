#include <iostream>
using namespace std;
#include <stdio.h>
#include <moeo>
#include <eo>
#include <metric/moeoHyperVolumeMetric.h>
#include "Data.h"
#include "moeoJobShopInit.h"
#include "eoJobShopQuadCrossover.h"
#include "moeoInsertMutation.h"
#include "moeoSwapMutation.h"
#include "Parser.h"
#include "eoJobShopObjectiveVectorTraits.h"
#include "eoJobShopObjectiveVector.h"
#include "moeoJobShop.h"
#include "moeoJobShopX.h"
#include "moeoJobShopEvalFuncS.h"//en fait X...
#include "decodeur.h"
#include<addToParadisEO/moeo/algo/moeoDecodedNSGAII.h>

typedef moeoJobShop Indi;
typedef moeoJobShopX IndiX;
#include <make_pop.h>
eoPop<Indi>&  make_pop(eoParser& _parser, eoState& _state, eoInit<Indi> & _init)
{
  return do_make_pop(_parser, _state, _init);
}

// checks for help demand, and writes the status file
// and make_help; in libutils
void make_help(eoParser & _parser);


// main
int main (int argc, char *argv[])
{
    eoParser parser(argc, argv);  // for user-parameter reading

    /** Lecture des informations d entree a partir du fichier mentionné dans le fichier "fichier.param" **/

    std::string inputFile = parser.createParam(std::string("../DataOneMachine/bky20/bky20_1.txt"), "inputFile", "File which describes input information", 'I', "Param" ).value();
    
   
    
    Parser p(inputFile);
    Data data = p();

    eoState state;                // to keep all things allocated*/

    // parameters
    unsigned int MAX_GEN = parser.createParam((unsigned int)(500), "maxGen", "Maximum number of generations",'G',"Param").value();
    unsigned int nb_lambda = parser.createParam((unsigned int)(5), "nb_lambda", "number of solutions of the sub problem",'l',"Param").value();
 
   
    // objective functions evaluation
    //moeoUCPEval eval;
    moeoJSEvalFunc<IndiX> plainEval(data);

    // turn that object into an evaluation counter
    eoEvalFuncCounter<IndiX> eval(plainEval);
    Timing<IndiX> timer(data);
    moeoJSDecoder<Indi,IndiX> decoder(timer,nb_lambda, plainEval);
    moeoJobShopInit<Indi> init(data);

    // A (first) crossover (possibly use the parser in its Ctor)
    eoJobShopQuadCrossover<Indi> cross;
    
  
    moeoSwapMutation<Indi> mut;
    moeoInsertMutation<Indi> mut1;
  
	  
    double pCross = parser.createParam(0.6, "pCross", "Probability of Crossover", 'C', "Variation Operators" ).value();
    //double pCross1 = parser.getORcreateParam(0.6, "pCross1", "Probability of Crossover", 'x', "Variation Operators" ).value();

    // minimum check
    if ( (pCross < 0) || (pCross > 1) )
      throw runtime_error("Invalid pCross");

    double pMut1 = parser.createParam(1., "pMut1", "Probability of Mutation", '1', "Variation Operators" ).value();


    // minimum check 
    if ( (pMut1 < 0) || (pMut1 > 1) )
      throw runtime_error("Invalid pMut1 ");


    
    double pMut = parser.createParam(1., "pMut", "Probability of Mutation", 'M', "Variation Operators" ).value();
    if ( (pMut < 0) || (pMut > 1) )
        throw runtime_error("Invalid pCross");
  
    eoPropCombinedMonOp<Indi> mutCombined(mut, pMut);
    mutCombined.add(mut1,pMut1);
    
    double pMutCombined = parser.createParam(0.1, "pMutCombined", "Probability of Mutation", 'W', "Variation Operators" ).value();
    
    // // initialize the population
    eoPop<Indi>& pop   = make_pop(parser, state, init);
    eoFileMonitor   *myFileMonitor;

    int maxtime=parser.createParam(100, "maxtime", "temps maximal", 't', "Algorithm").value();
    // printing of the initial population
    /*////cout << "Initial Population\n";
    pop.sortedPrintOn(////cout);
    ////cout << endl;*/
    
   
    eoTimeContinue< IndiX >  continuator(maxtime);
    //eoCheckPoint<IndiX> checkpoint (continuator);
    moeoUnboundedArchive < IndiX > arch;
    //moeoArchiveUpdater<Indi> updater(arch1, pop);
    //checkpoint.add(updater);
     //moeoSteadyHyperVolumeContinue<Indi> continuator( 0, 100, hyperVol);
     
    
   	 // build NSGA-II
        moeoDecodedNSGAII<Indi, IndiX> nsgaII(continuator, decoder, cross,pCross,mutCombined, pMutCombined);
        //moeoNSGAII < Indi > nsgaII (checkpoint, eval, op);
    	// run the algo
        
    	nsgaII (pop,arch);

    

    // help ?
    make_help(parser);

    // extract first front of the final population using an moeoArchive (this is the output of nsgaII)
	/* eoPop <IndiX> popX;
    decoder.decodePop(pop, popX);
    moeoUnboundedArchive < IndiX > arch;
    arch(popX);
    
	for(unsigned s=0; s<pop.size(); ++s)
        {
		 eoPop <IndiX> popX;
            decoder(pop[s], popX);
            for(unsigned x=0; x<popX.size(); ++x){
                popX[x].origin(pop[s].origin());
		popX[x].printOn(cout);}
           
        }*/
    // printing of the final population
    cout << "Final Population\n";
    arch.sortedPrintOn(cout);
    ////cout << endl;

    // printing of the final archive
    //std::////cout << "Final Archive " << std::endl;
    //std::////cout << "sans archive : ";
	eoJobShopObjectiveVector pointRef(2);
	pointRef[0]=0; pointRef[1]=1;
	moeoHyperVolumeMetric<eoJobShopObjectiveVector> hyperVol(false,pointRef);
	vector<eoJobShopObjectiveVector> res;
    for(int i=0;i<arch.size();i++)
        res.push_back(arch[i].objectiveVector());
   
     cout<<"air de l'hypervolume :"<<-1*hyperVol(res)<<endl;
    return EXIT_SUCCESS;
}
