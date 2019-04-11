#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <iostream>
#include <string>

namespace individual {

// define for each individual
class Individual {
    private:
        double (*fitnessFN)(double *, int);

    public:
        double *bits;
        double fitness;
        int gene_size;
        Individual() : bits(NULL), fitness(0.0f){};
        Individual(int n_of_x, double (*fitness_fn)(double *, int), bool child);
        void CalcFitness();
};
} // namespace individual

#endif // INDIVIDUAL_H_