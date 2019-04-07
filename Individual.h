#ifndef INDIVIDUAL
#define INDIVIDUAL
#include <iostream>
using namespace std;

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
        individual(int N_X, int len, double (*fitness_fn)(int *, chromo_typ))
        {
            gene_size = {N_X*len, N_X, len};
            fitnessFN = fitness_fn;
            bits = new int[N_X * len];
            for (int i = 0; i < N_X; i++)
            {
                int index = i * len;
                for (int j = 0; j < len; j++)
                    *(bits + index + j) = (rand() >= 0.5 * (double)RAND_MAX) ? 1 : 0;
            }
            fitness = fitnessFN(bits, gene_size);
        }
        void print()
        {
            for (int i = 0; i < gene_size.N; i++) 
            {
                int index = i * gene_size.len;
                for (int j = 0; j < gene_size.len; j++)
                    cout << *(bits + index + j);
                cout << endl;
            }
            cout << "----------------" << endl;
            cout << "fitness: " << fitness << endl;
        }
};

#endif