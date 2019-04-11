#include "genetic_algorithm.h"

#include <iomanip>
#include <algorithm>

namespace genetic_algorithm {

GeneticAlgorithm::GeneticAlgorithm(int population_size, 
    double (*fitnessFn)(double *, int)) {
    _population_size = population_size;
    _fitnessFn = fitnessFn;
    max_fitness = 0;
    population.reserve(population_size * 2);
}

// Generate initial population 
void GeneticAlgorithm::Initial(int len) {
    _gene_length = len;
    for (int i = 0; i < _population_size; i++) {
        population[i] = new individual::Individual();
        population[i+_population_size] = new individual::Individual();
    }
}

// parents selection and crossover
void GeneticAlgorithm::Crossover(CrossoverMethod method, double p_c, int n_tnmt) {
    Crossover(method, p_c, n_tnmt, 0.3);
}
void GeneticAlgorithm::Crossover(CrossoverMethod method, double p_c, int n_tnmt, double a) {
    switch(method){
      case two_pt:
        TwoPtCrossover(p_c, n_tnmt);
        break;
      case uniform:
        UniformCrossover(p_c, n_tnmt);
        break;
      case whole_arithmetic:
        WholeArithmeticCrossover(p_c, n_tnmt, a);
        break;
    }

}

//population mutation
void GeneticAlgorithm::Mutation(double p_m) {
    double threshold = p_m * (double)RAND_MAX;
    for (int i=0; i<_population_size; i++) {
        for (int j=0;j<_gene_length;j++) {
            if (rand() < threshold) {
                *(population[i+_population_size]->bits+j)
                     = (rand()/(double)RAND_MAX)*1023-512;
            }
        }
    }
}

// population survivor selection
void GeneticAlgorithm::Survivor() {
    for(int i=0;i<_population_size;i++) {
        population[i + _population_size]->CalcFitness();
    }
    sort(population.begin(), population.begin()+_population_size*2, utility::FitnessCmp);
    max_fitness = population[0]->fitness;
}

individual::Individual* GeneticAlgorithm::TnmtSelection(int n_tnmt) {
    std::vector<individual::Individual*> selected_population(n_tnmt);
    std::vector<int> selected(n_tnmt);
    int max_fit_index = 0;
    double max_fitness = 999999999.0;
    for (int i = 0; i < n_tnmt; i++) {
        selected[i] = rand()%_population_size;
        for (int j = 0; j < i; j++) {
            if(selected[j]==selected[i]) {
                j = 0;
                selected[i] = rand() % _population_size;
            }
        }
        if(population[selected[i]]->fitness < max_fitness) {
            max_fit_index = selected[i];
            max_fitness = population[selected[i]]->fitness;
        }
    }
    return population[max_fit_index];
}

void GeneticAlgorithm::TwoPtCrossover(double p_c, int n_tnmt) {
    double threshold = p_c * (double)RAND_MAX;
    for (int i=0;i<_population_size/2;i++) {
        individual::Individual* parent1 = TnmtSelection(n_tnmt);
        individual::Individual* parent2 = TnmtSelection(n_tnmt);
        while (parent1 == parent2){
            parent2 = TnmtSelection(n_tnmt);
        }
        int point1 = rand() % (_gene_length);
        int point2 = rand() % (_gene_length);
        double pc = (rand()/(double)RAND_MAX);
        if (rand() < threshold) {
            while (point1 == point2) {
                point2 = rand()%(_gene_length);
            }
            if (point1>point2) {
                std::swap(point1, point2);
            } 
        }
        for (int j=0; j<_gene_length; j++) {
            if (j<point1) {
                *(population[i*2+_population_size]->bits+j) = *(parent1->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent2->bits+j);
            } else if (j<point2) {
                *(population[i*2+_population_size]->bits+j) = *(parent2->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent1->bits+j);
            } else {
                *(population[i*2+_population_size]->bits+j) = *(parent1->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent2->bits+j);
            }
        }
    }
}
void GeneticAlgorithm::UniformCrossover(double p_c, int n_tnmt) {
    double threshold = (double)RAND_MAX * p_c;
    for (int i=0; i<_population_size/2; i++) {
        individual::Individual* parent1 = TnmtSelection(n_tnmt);
        individual::Individual* parent2 = TnmtSelection(n_tnmt);
        while (parent1 == parent2) {
            parent2 = TnmtSelection(n_tnmt);
        }
        
        for (int j=0; j<_gene_length; j++) {
            if (rand() < threshold) {
                *(population[i*2+_population_size]->bits+j) = *(parent1->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent2->bits+j);
            } else  {
                *(population[i*2+_population_size]->bits+j) = *(parent2->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent1->bits+j);
            }
        }
    }
}

void GeneticAlgorithm::WholeArithmeticCrossover(double p_c, int n_tnmt, double a) {
    double threshold = (double)RAND_MAX * p_c;
    for (int i=0; i<_population_size/2; i++) {
        individual::Individual* parent1 = TnmtSelection(n_tnmt);
        individual::Individual* parent2 = TnmtSelection(n_tnmt);
        while (parent1 == parent2) {
            parent2 = TnmtSelection(n_tnmt);
        }
        
        for (int j=0; j<_gene_length; j++) {
            if (rand() < threshold) {
                *(population[i*2+_population_size]->bits+j)
                     = a*(*(parent1->bits+j)) + (1-a)*(*(parent2->bits+j));
                *(population[i*2+1+_population_size]->bits+j)
                     = a*(*(parent2->bits+j)) + (1-a)*(*(parent1->bits+j));
            } else  {
                *(population[i*2+_population_size]->bits+j) = *(parent1->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent2->bits+j);
            }
        }
    }
}

GeneticAlgorithm::~GeneticAlgorithm() {
    for (int i = 0; i < _population_size*2; i++) {
        delete[] population[i]->bits;
        delete population[i];
    }
}

} // namespace genetic_algorithm