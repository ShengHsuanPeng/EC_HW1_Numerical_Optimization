#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>
//#include <functional>
#include "define.h"
#include "Individual.h"

using namespace std;

class Genetic_Algorithm
{
    protected:
        vector<individual> population;
        int _population_size;

        FILE* out;
        
        void Print();
        double (*_fitnessFn)(int *, chromo_typ);
    public:
        Genetic_Algorithm(int, double (*fitnessFn)(int *, chromo_typ));
        void Initial(int len);
        void Selection();
        void Crossover();
        void Mutation();
        void Survivor();
};

#endif