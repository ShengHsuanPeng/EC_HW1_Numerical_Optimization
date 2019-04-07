#include "Genetic_Algorithm.h"
#include <iostream>
//using namespace std;

double Schwefel_Function(int* bits, chromo_typ size)
{
    int N = size.N;
    int len = size.len;
    
    double fsch=418.98291*N;
    for(int j=0; j<N; j++)
    {
        int index = j * len;
        double x_i=0;
        for(int k=0;k<len;k++)
        {
            x_i+=double(*(bits + index + k))*pow(2, len-k-1);
        }
        x_i-=512;
        fsch -= x_i*sin(sqrt(abs(x_i)));
    }
    return fsch;
}

class Binary_GA: public Genetic_Algorithm
{
    public:
        Binary_GA(int population_size, double (*fitnessFn)(int *, chromo_typ))
        : Genetic_Algorithm(population_size, fitnessFn){}

        void Initial(int N_X, int len)
        {
            _gene_length = N_X*len;
            for (int i = 0; i < _population_size; i++)
            {
                population[i] = individual(N_X, len, _fitnessFn);
            }
        }
};

int main(){
	srand(time(NULL));
    clock_t t1, t2;
    Binary_GA biGA(100, Schwefel_Function);
    biGA.Initial(10, 10);
    t1=clock();
    for(int generation=0;generation<=10;generation++)
    {
        cout << "================Gen: " << generation << "================\n";
        biGA.Crossover(0.9, 5);
        biGA.Mutation(0.1);
        biGA.Survivor();
        biGA.Print();
    }
    t2 = clock();
    
}