#include <iostream>
using namespace std;
#include <stdio.h>
#include <moeo>
#include <eo>
#include "Data.h"
#include "moeoJobShopInit.h"
#include "Parser.h"
#include "decodeur.h"
#include"decodeurDichotomique.h"
#include"DecodeurExacte.h"
#include "moeoJobShop.h"
#include "moeoJobShopX.h"
typedef moeoJobShop Indi;
typedef moeoJobShopX IndiX;
main()
{
	int N=20;
	Parser p("../DataOneMachine/bky20/bky20_1.txt");
	int nb_lambda=25;
	Data data = p();
	moeoJSEvalFunc<IndiX> plainEval(data);
        Timing<IndiX> timer(data);
        moeoJSDecoderDichotomique<Indi,IndiX> decoderDicho(timer,nb_lambda, plainEval);
	moeoJSDecoderExacte<Indi,IndiX> decoderExacte(data, plainEval);
	moeoJSDecoder<Indi,IndiX> decoder(timer,nb_lambda, plainEval);
        moeoJobShopInit<Indi> init(data);
	
	Indi eo;
	init(eo);
	vector<int> jobs=eo.getListeJobs();
	eoPop <IndiX> popX;
        decoderDicho(eo, popX);
	cout<<"Decoder Dich : "<<endl;
	popX.sort();
        for(unsigned x=0; x<popX.size(); ++x){
              
	      popX[x].printOn(cout);
		cout<<endl;
	      if(popX[x].validity(data)==false)
			cout<<"PROBLEME DICO"<<endl;
		
	}
	eoPop <IndiX> popXbis;
        decoder(eo, popXbis);
	/*cout<<"Decoder normal : "<<endl;
        for(unsigned x=0; x<popXbis.size(); ++x){
         
	      popXbis[x].printOn(cout); cout<<endl;
		
	}*/
	cout<<"décodeur exacte :"<<endl;
	eoPop <IndiX> popXtierce;
        decoderExacte(eo, popXtierce);
	//popXtierce.sort();
        for(unsigned x=0; x<popXtierce.size(); ++x){
              
	      popXtierce[x].printOn(cout);
		cout<<endl;
	      if(popXtierce[x].validity(data)==false)
			cout<<"PROBLEME EXA"<<endl;
		
	}
	
	/*cout<<"test timing nombre non entier"<<endl;
	cout<<" 1 , 2 :"<<endl;
	IndiX eoX1;
	eoX1.setN(N);
	eoX1.setListeJobs(jobs);
	vector<double> time1;
	for(int i =0; i<N;i++)
	{
		time1.push_back(0.2*popX[1].getCompletionTime(i)+0.8*popX[2].getCompletionTime(i));
	}
	//timer.timing(jobs,time1, 1, 2);
	eoX1.setCompletionTime(time1);
	plainEval(eoX1);
	cout<<eoX1.objectiveVector()[0]<< " "<<eoX1.objectiveVector()[1]<< "   "<<eoX1.objectiveVector()[0]+ 2*eoX1.objectiveVector()[1]<<endl;
	/*cout<<" 1/4 , 2/4 :"<<endl;
	IndiX eoX2;
	eoX2.setN(N);
	eoX2.setListeJobs(jobs);
	vector<double> time2;
	timer.timing(jobs,time2, 0.2, 0.5);
	eoX2.setCompletionTime(time2);
	plainEval(eoX2);
	cout<<eoX2.objectiveVector()[0]<< " "<<eoX2.objectiveVector()[1]<< "   "<<eoX2.objectiveVector()[0]+ 2*eoX2.objectiveVector()[1]<<endl;*/
	
}
