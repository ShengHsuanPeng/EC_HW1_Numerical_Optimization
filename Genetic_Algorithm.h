#ifndef GENETIC_ALGORITHM_H_
#define GENETIC_ALGORITHM_H_

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <vector>
//#include <functional>

#include "individual.h"
#include "utility.h"

namespace genetic_algorithm {

typedef enum {
    whole,
    children,
    best,
    best_fitness,
    summary
} PrintMode;

// GeneticAlgorithm
class GeneticAlgorithm {
    private:
        void TwoPtCrossover(double p_c, int n_tnmt);
        void UniformCrossover(double p_c, int n_tnmt);
        individual::Individual* TnmtSelection(int n_tnmt);
        void Summary();

      protected:
        std::vector<individual::Individual*> population;
        int _population_size;
        int _gene_length;
        double (*_fitnessFn)(int *, individual::ChromoTyp);

    public:
        double max_fitness;
        GeneticAlgorithm(int, double (*fitnessFn)(int *, individual::ChromoTyp));
        ~GeneticAlgorithm();
        void Initial(int len);
        void Selection();
        void Crossover(double p_c, int n_tnmt);
        void Mutation(double p_m);
        void Survivor();
        void Print();
        void Print(PrintMode);
};

} // namespace genetic_algorithm 

#endif // GENETIC_ALGORITHM_H_