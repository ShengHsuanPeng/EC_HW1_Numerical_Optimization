#include "individual.h"

#include <iomanip>

namespace individual {

Individual::Individual(int n_of_x, double (*fitness_fn)(double *, ChromoTyp), bool child) {
    gene_size = {n_of_x, n_of_x, 1};
    fitnessFN = fitness_fn;
    bits = new double[n_of_x];
   
    for (int i = 0; i < n_of_x; i++) {
        if(child == false)
            *(bits + i) = (rand()/(double)RAND_MAX)*1023-512;
        else
            *(bits + i) = 0.0;
    }
    
    fitness = fitnessFN(bits, gene_size);
}
void Individual::CalcFitness() {
    fitness = fitnessFN(bits, gene_size);
}
void Individual::print() {
    std::cout << "----------------" << std::endl;
    for (int i = 0; i < gene_size.n_of_x; i++) {
            std::cout << *(bits + i) << ", ";
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
                std::cout << *(bits + i);
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