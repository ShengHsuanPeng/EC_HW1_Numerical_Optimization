#include "Genetic_Algorithm.h"
#include <iostream>
//using namespace std;
#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);  

double Schwefel_Function(int* bits, Individual::chromo_typ size)
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
        fsch -= x_i*sin(sqrt(fabs(x_i)));
    }
    return fsch;
}

class Binary_GA: public Genetic_Algorithm
{
    public:
        Binary_GA(int population_size, double (*fitnessFn)(int *, Individual::chromo_typ))
        : Genetic_Algorithm(population_size, fitnessFn){}

        void Initial(int N_X, int len)
        {
            _gene_length = N_X*len;
            for (int i = 0; i < _population_size; i++)
            {
                population[i] = new Individual::individual(N_X, len, _fitnessFn, false);
                population[i+_population_size] = new Individual::individual(N_X, len, _fitnessFn, true);
                std::cout << i << std::endl;
                population[i]->print(Individual::fitness);
            }
        }
};

int main(){
	srand(time(NULL));
    clock_t t1, t2;
    Binary_GA biGA(10, Schwefel_Function);
    biGA.Initial(5, 10);
    std::cout << "Initial\n";
    biGA.Print(whole);
    t1=clock();
    for(int generation=0;generation<=5;generation++)
    {
        std::cout << "================Gen: " << generation << "================\n";
        
        biGA.Crossover(0.9, 2);
        std::cout << "Crossover\n";
        biGA.Print(whole);
        biGA.Mutation(0.1);
        std::cout << "Mutation\n";
        biGA.Print(whole);
        biGA.Survivor();
        std::cout << "Survivor\n";
        biGA.Print(whole);
    }
    t2 = clock();

    PAUSE
}