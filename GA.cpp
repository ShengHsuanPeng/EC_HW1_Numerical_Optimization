#include "Genetic_Algorithm.h"
#include <iostream>
using namespace std;
#define PRINT 0
#define FILENAME "BinaryGA_2points.csv"
#define TIMENAME "b2time.csv"

const int LENGTH = 10;
const int GENE_LEN = N_X*LENGTH;
const double PROBABILITY_MUTATION = (1.0/(GENE_LEN))*PARA_A+PARA_B;


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
            for (int i = 0; i < _population_size; i++)
            {
                population[i] = individual(N_X, len, _fitnessFn);
            }
        }
        void Selection();
        void Crossover();
        void Mutation();
        void Survivor();
};



int main(){
	srand(time(NULL));
    Binary_GA biGA(100, Schwefel_Function);
    clock_t t1, t2;
    t1=clock();
    for(int generation=0;generation<=GENERATION;generation++)
    {
        if(PRINT)cout << "================Gen: " << generation << "================\n";
        biGA.Fitness(generation);
        biGA.Print(generation);
        biGA.Crossover();
        biGA.Mutation();
        biGA.Survivor();
    }
    t2 = clock();
    if(fopen(TIMENAME,"rb+")==NULL)
    {
        FILE* timer = fopen(TIMENAME,"ab+");
        fprintf(timer,"time,N_X,n,pc,pm,gen,ppl\n");
        fprintf(timer,"%lf,%d,%d,%lf,%lf,%d,%d,\n",(t2-t1)/(double)(CLOCKS_PER_SEC),N_X,N_TOURNAMENT,PROBABILITY_CROSSOVER,PROBABILITY_MUTATION,GENERATION,POPULATION);
    }
    else
    {
        FILE* timer = fopen(TIMENAME,"ab+");
        fprintf(timer,"%lf,\n",(t2-t1)/(double)(CLOCKS_PER_SEC));
    }
}