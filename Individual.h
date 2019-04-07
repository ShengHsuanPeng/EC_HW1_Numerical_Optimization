#ifndef INDIVIDUAL
#define INDIVIDUAL
#include <iostream>
#include <string>

namespace Individual
{
typedef enum
{
    silent,
    fitness,
    whole,
    oneline
} print_mode;

struct chromo_typ {
    int gene_length;
    int N;
    int len;
};

class individual
{
    private:
        
        double (*fitnessFN)(int *, chromo_typ);

    public:
        int *bits;
        double fitness;
        chromo_typ gene_size;
        individual() : bits(NULL), fitness(0.0f){};
        individual(int N_X, int len, double (*fitness_fn)(int *, chromo_typ), bool child);
        void print();
        void print(print_mode);
        void calc_fitness();
};
}

#endif