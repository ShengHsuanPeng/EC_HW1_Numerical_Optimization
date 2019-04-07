#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>
//#include <functional>
#include "Individual.h"
#include "utility.h"

//using namespace std;

class Genetic_Algorithm
{
    private:
        void TwoPtCrossover(double p_c, int n_tnmt);
        void UniformCrossover(double p_c, int n_tnmt);
        individual* TnmtSelection(int n_tnmt);

      protected:
        vector<individual> population;
        int _population_size;
        int _gene_length;
        double (*_fitnessFn)(int *, chromo_typ);

    public:
        double max_fitness;
        Genetic_Algorithm(int, double (*fitnessFn)(int *, chromo_typ));
        void Initial(int len);
        void Selection();
        void Crossover(double p_c, int n_tnmt);
        void Mutation(double p_m);
        void Survivor();
        void Print();
};

#endif