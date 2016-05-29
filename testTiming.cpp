#include <iostream>
using namespace std;
#include <stdio.h>
#include<numeric>
#include<moeo>
#include"Parser.h"
#include"Data.h"
#include"Timing.h"
#include "moeoJobShopX.h"
#include "moeoJobShopEvalFuncS.h"
main()
{
	Parser p("../DataOneMachine/bky100/bky100_1.txt");
     	Data data = p();
	int N=data.getN();
	 std::srand ( unsigned ( std::time(0) ) );
	vector<int> order;
	//int a[]={8, 34, 93, 11, 84, 90, 39, 35, 0, 85, 63, 73, 16, 58, 43, 88, 38, 72, 10, 1, 99, 67, 40, 4, 60, 61, 96, 2, 53, 95, 94, 66, 18, 14, 13, 46, 25, 62, 17, 9, 33, 26, 81, 20, 22, 65, 68, 86, 49, 52, 37, 6, 69, 41, 44, 74, 76, 29, 56, 64, 87, 75, 71, 30, 3, 24, 97, 42, 32, 82, 47, 78, 54, 27, 28, 80, 77, 19, 50, 23, 12, 92, 15, 83, 55, 89, 57, 31, 59, 98, 79, 36, 45, 51, 70, 21, 5, 7, 91, 48} ;
	//int a[]={29, 11, 14, 59, 10, 37, 57, 63, 23, 6, 51, 56, 79, 5, 32, 1, 90, 17, 74, 61, 44, 72, 95, 92, 77, 20, 0, 69, 26, 19, 88, 38, 39, 89, 41, 43, 48, 34, 83, 96, 87, 30, 18, 35, 53, 97, 16, 7, 46, 66, 64, 27, 21, 73, 62, 33, 67, 45, 71 ,82 ,42, 65, 36, 80, 70, 49, 52, 31, 81, 12, 28, 75, 98, 94, 13, 47, 25, 15, 8 ,24, 4, 68, 76, 3 ,55, 91, 9, 93, 84, 58, 50, 78, 99, 86, 40, 54, 22, 85, 60, 2 };{1, 4, 16, 12, 7, 37, 45, 71, 62, 48, 21, 30, 74, 35, 26, 50, 84, 41, 34, 64, 10, 49, 83, 51, 94, 22, 17, 24, 19, 97, 42, 76, 54, 99, 93, 92, 36, 65, 13, 6, 15, 53, 27, 95, 87, 77, 82, 68, 5, 88, 18, 20, 78, 47, 33, 89, 0, 67, 96, 61, 56, 79, 63, 32, 31, 46, 69, 81, 98, 39, 60, 57, 43, 44, 28, 66, 11, 14, 75, 86, 70, 52, 91, 73, 59, 72, 9, 23, 80, 2, 90, 3, 40, 58, 85, 25, 55, 38, 8, 29}//pb i0
	for (int i = 0; i < N; i++)
	{
		order.push_back(i);
	}
	std::random_shuffle ( order.begin(), order.end() );
	for (int i = 0; i < N; i++)
	{
		cout<<order[i]<<", ";
	}
	cout<<endl;
	moeoJobShopX eo;
	eo.setN(N);
	eo.setListeJobs(order);
	Timing<moeoJobShopX> timer(data);
	moeoJSEvalFunc<moeoJobShopX> eval(data);
	double i10, i11;
	for(unsigned int i=0; i<6;i++)
		{
			
			vector<double> time;
			timer.timing(order,time, i, 5-i);
			eo.setCompletionTime(time);
			eval(eo);
			std::cout<<"i="<<i<<" "<< eo.objectiveVector()[0]<<" ,"<<eo.objectiveVector()[1]<<std::endl;
			if (i==0) i10=eo.objectiveVector()[1];
			if (i==1) i11=eo.objectiveVector()[1];
			eo.invalidate();
			

		}
		cout<<i10-i11<<endl;
	
	
}
