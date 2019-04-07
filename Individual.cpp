#include "Individual.h"
#include <iomanip>

namespace Individual
{
individual::individual(int N_X, int len, double (*fitness_fn)(int *, chromo_typ), bool child)
{
    gene_size = {N_X*len, N_X, len};
    fitnessFN = fitness_fn;
    bits = new int[N_X * len];
   
    for (int i = 0; i < N_X*len; i++)
    {
        if(child == false)
            *(bits + i) = (rand() >= 0.5 * (double)RAND_MAX) ? 1 : 0;
        else
            *(bits + i) = 0;
    }
    
    fitness = fitnessFN(bits, gene_size);
}
void individual::calc_fitness() 
{
    fitness = fitnessFN(bits, gene_size);
}
void individual::print()
{
    std::cout << "----------------" << std::endl;
    for (int i = 0; i < gene_size.N; i++) 
    {
        int index = i * gene_size.len;
        for (int j = 0; j < gene_size.len; j++)
            std::cout << *(bits + index + j);
        std::cout << std::endl;
    }
    std::cout << "----------------" << std::endl;
    std::cout << "fitness: " << std::setw(7) << std::fixed << std::setprecision(2) << fitness << std::endl;
}
void individual::print(print_mode mode)
{
    switch(mode)
    {
        case print_mode::silent:
            break;
        case print_mode::fitness:
            std::cout << "fitness: " << std::setw(7) << std::fixed << std::setprecision(2) << fitness << std::endl;
            break;
        case print_mode::whole:
            std::cout << "----------------" << std::endl;
            for (int i = 0; i < gene_size.N; i++) 
            {
                int index = i * gene_size.len;
                for (int j = 0; j < gene_size.len; j++)
                    std::cout << *(bits + index + j);
                std::cout << std::endl;
            }
            std::cout << "----------------" << std::endl;
            std::cout << "fitness: " << std::setw(7) << std::fixed << std::setprecision(2) << fitness << std::endl;
            break;
        case oneline:
            std::cout << "fitness: " << std::setw(7) << std::fixed << std::setprecision(2) << fitness << " | ";
            for (int i = 0; i < gene_size.gene_length; i++) 
            {
                std::cout << *(bits + i);
            }
            std::cout << std::endl;
            break;
    }
}
}