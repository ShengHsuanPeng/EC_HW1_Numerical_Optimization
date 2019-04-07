#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <iostream>
#include <string>

namespace individual {

typedef enum {
    silent,
    fitness,
    whole,
    oneline
} PrintMode;

struct ChromoTyp {
    int gene_length;
    int n_of_x;
    int x_len;
};

// define for each individual
class Individual {
    private:
        double (*fitnessFN)(int *, ChromoTyp);

    public:
        int *bits;
        double fitness;
        ChromoTyp gene_size;
        Individual() : bits(NULL), fitness(0.0f){};
        Individual(int n_of_x, int x_len, double (*fitness_fn)(int *, ChromoTyp), bool child);
        void print();
        void print(PrintMode);
        void CalcFitness();
};
} // namespace individual

#endif // INDIVIDUAL_H_