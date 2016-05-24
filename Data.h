//
//  Data.h
//  Project
//
//  Created by Sophie Jacquin on 13/04/15.
//  Copyright (c) 2015 __MyCompanyName__. All rights reserved.
//

#ifndef Project_Data_h
#define Project_Data_h
#include "Jobs.h"
#include<stdio.h>

class Data{
private:
    int N;
    vector<Jobs> jobs;
    int d_max;

    public :
    Data(vector<Jobs> Jobs_)
    {
        jobs=Jobs_;
        N=jobs.size();
	d_max = setMaxD();
    }
    Data()
    {
        N=0;
    }
    int getN()const
    {
        return N;
    }
    Jobs getJob(int i)
    {
        return jobs[i];
    }
    
    int getMaxD()
    {
	return d_max;
    }
    
  int setMaxD()
	{
		int max = 0;
		int d = 0;
		for (int i =0; i < N; i++)
		{
			d = jobs[i].getD();
			if (max < d)
				max = d;
		}
		return max;
	}
    
};


#endif
