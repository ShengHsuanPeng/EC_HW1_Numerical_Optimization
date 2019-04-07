#ifndef GENETIC_ALGORITHM_H_
#define GENETIC_ALGORITHM_H_

#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

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

typedef enum {
    two_pt,
    uniform
} CrossoverMethod;

//typedef std::chrono::high_resolution_clock::time_point TimeVar;

//#define timeNow() std::chrono::high_resolution_clock::now()

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
        void Crossover(CrossoverMethod, double p_c, int n_tnmt);
        void Mutation(double p_m);
        void Survivor();
        void Print();
        void Print(PrintMode);
};

} // namespace genetic_algorithm 

#endif // GENETIC_ALGORITHM_H_