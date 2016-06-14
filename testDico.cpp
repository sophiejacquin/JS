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
	int N=100;
	Parser p("../DataOneMachine/bky100/bky100_1.txt");
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
	int t[100]= { 46 , 50 , 45 , 57 , 73 , 61 , 6 , 11 , 75 , 54 , 19 , 38 , 34 , 64 , 81 , 89 , 1 , 0 , 17 , 78 , 37 , 41 , 12 , 13 , 8 , 67 , 88 , 93 , 51 , 55 , 53 , 24 , 94 , 72 , 77 , 47 , 40 , 9 , 10 , 68 , 74 , 71 , 36 , 35 , 20 , 23 , 31 , 33 , 65 , 76 , 58 , 70 , 44 , 16 , 98 , 60 , 25 , 99 , 22 , 95 , 28 , 39 , 7 , 21 , 18 , 26 , 48 , 15 , 3 , 91 , 69 , 29 , 52 , 49 , 80 , 43 , 56 , 62 , 66 , 83 , 90 , 14 , 27 , 30 , 4 , 32 , 87 , 63 , 84 , 5 , 79 , 96 , 85 , 82 , 2 , 86 , 97 , 42 , 59 , 92   };
	vector<int> o(&t[0],&t[0]+100);
	eo.setListeJobs(o);
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
