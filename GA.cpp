#include <iostream>

#include "genetic_algorithm.h"

#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);  

double Schwefel_Function(int* bits, individual::ChromoTyp size) {
    int n_of_x = size.n_of_x;
    int x_len = size.x_len;
    
    double fsch=418.98291*n_of_x;
    for (int j=0; j<n_of_x; j++) {
        int index = j * x_len;
        double x_i=0;
        for (int k=0;k<x_len;k++) {
            x_i+=double(*(bits + index + k))*pow(2, x_len-k-1);
        }
        x_i-=512;
        fsch -= x_i*sin(sqrt(fabs(x_i)));
    }
    return fsch;
}

class BinaryGa: public genetic_algorithm::GeneticAlgorithm
{
    public:
        BinaryGa(int population_size, 
                double (*fitnessFn)(int *, individual::ChromoTyp))
        : GeneticAlgorithm(population_size, fitnessFn) {}

        // only for Schwefel_Function questions
        void Initial(int n_of_x, int x_len) {
            _gene_length = n_of_x*x_len;
            for (int i = 0; i < _population_size; i++)  {
                population[i] = new individual::Individual(n_of_x, x_len, _fitnessFn, false);
                population[i+_population_size]
                     = new individual::Individual(n_of_x, x_len, _fitnessFn, true);
                //std::cout << i << std::endl;
                //population[i]->print(Individual::fitness);
            }
        }
};

int main(){
    int population = 100;
    int n_of_x = 10;
    int x_len = 10;
    int generation = 100;
    srand(time(NULL));
    
    BinaryGa biGA(population, Schwefel_Function);
    biGA.Initial(n_of_x, x_len);
    clock_t t1 = clock();
    for (int gen=1; gen<=generation; gen++) {
        //std::cout << "================Gen: " << generation << "================\n";
        
        biGA.Crossover(0.9, 10);
        biGA.Mutation(0.1);
        biGA.Survivor();
    }
    clock_t t2 = clock();
    biGA.Print(genetic_algorithm::summary);
    PAUSE
}