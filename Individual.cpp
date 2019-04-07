#include "individual.h"

#include <iomanip>

namespace individual {

Individual::Individual(int n_of_x, int x_len, double (*fitness_fn)(int *, ChromoTyp), bool child) {
    gene_size = {n_of_x*x_len, n_of_x, x_len};
    fitnessFN = fitness_fn;
    bits = new int[n_of_x * x_len];
   
    for (int i = 0; i < n_of_x*x_len; i++) {
        if(child == false)
            *(bits + i) = (rand() >= 0.5 * (double)RAND_MAX) ? 1 : 0;
        else
            *(bits + i) = 0;
    }
    
    fitness = fitnessFN(bits, gene_size);
}
void Individual::CalcFitness() {
    fitness = fitnessFN(bits, gene_size);
}
void Individual::print() {
    std::cout << "----------------" << std::endl;
    for (int i = 0; i < gene_size.n_of_x; i++) {
        int index = i * gene_size.x_len;
        for (int j = 0; j < gene_size.x_len; j++)
            std::cout << *(bits + index + j);
        std::cout << std::endl;
    }
    std::cout << "----------------" << std::endl;
    std::cout << "fitness: " << std::setw(7) << std::fixed
              << std::setprecision(2) << fitness << std::endl;
}
void Individual::print(PrintMode mode) {
    switch(mode) {
      case PrintMode::silent:
        break;
      case PrintMode::fitness:
        std::cout << "fitness: " << std::setw(7) << std::fixed 
                  << std::setprecision(2) << fitness << std::endl;
        break;
      case PrintMode::whole:
        std::cout << "----------------" << std::endl;
        for (int i = 0; i < gene_size.n_of_x; i++) {
            int index = i * gene_size.x_len;
            for (int j = 0; j < gene_size.x_len; j++)
                std::cout << *(bits + index + j);
            std::cout << std::endl;
        }
        std::cout << "----------------" << std::endl;
        std::cout << "fitness: " << std::setw(7) << std::fixed 
                  << std::setprecision(2) << fitness << std::endl;
        break;
      case oneline:
        std::cout << "fitness: " << std::setw(7) << std::fixed 
                  << std::setprecision(2) << fitness << " | ";
        for (int i = 0; i < gene_size.gene_length; i++) {
            std::cout << *(bits + i);
        }
        std::cout << std::endl;
        break;
    }
}
} // namespace individual