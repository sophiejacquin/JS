#ifndef eoJobShopQuadCrossover_H
#define eoJobShopQuadCrossover_H

#include <eoOp.h>

template<class EOT>
class eoJobShopQuadCrossover: public eoQuadOp<EOT>
{
public:

  eoJobShopQuadCrossover()
  {
    
  }

  /// The class name. Used to display statistics
  string className() const { return "eoJobShopQuadCrossover"; }


  bool operator()(EOT & eo1, EOT& eo2)
  { //2points
	//////cout<<"enter crossover"<<endl;
        bool oneAtLeastIsModified(true);
	unsigned int N = eo1.getN();
	unsigned int p1, p2; //random int;
	eoUniformGenerator<int> rdm(0,N);
	
	p1 =  rdm(); // rng.random(N);
	p2 =  rdm(); // rng.random(N);
	//////cout <<"p1, p2 " <<p1<<" "<<p2<<endl;
	// vérifie et corrige point1 < point2
	if (p1 > p2)
		std::swap(p1, p2);
	
	if (p1 !=p2)
	{
		vector< EOT > offspring;
		
		offspring.push_back(generateOffspring(eo1, eo2, p1, p2));
		offspring.push_back(generateOffspring(eo2, eo1, p1, p2));
		eo1 = offspring[0];
		eo2 = offspring[1];
		oneAtLeastIsModified = true;
	}
	else
	{
		oneAtLeastIsModified = false;
	}

    return oneAtLeastIsModified;
  }
	
  EOT generateOffspring( EOT& parent1, EOT & parent2, unsigned int p1, unsigned int p2)
{
	EOT result = eoJobShop();
	
	result.setN(parent1.getN());
	
	std::vector<bool> taken_values(N, false);
	vector<int> var;
	vector<int> liste;
	

	
	for (unsigned int i =0; i < N; i++)
	{
		if (i>p1 && i<p2)
		{
			liste.push_back(0);
		} 
		else
		{
			var = parent1[i];
			taken_values[var[0]] = true; 
			liste.push_back(var);
		}
	}

	unsigned int i = p1 + 1;
	unsigned j = 0;
	while (i < p2 && j < N)
	{
		if (!taken_values[parent2[j]])
		{
			liste[i]= parent2[j];
			i++;
		}
		j++;
	}
	
	
	

	result.setListeJobs(liste);
	return result;	
}
  

};

#endif
