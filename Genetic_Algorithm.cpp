#include "genetic_algorithm.h"

#include <iomanip>
#include <algorithm>

namespace genetic_algorithm {

GeneticAlgorithm::GeneticAlgorithm(int population_size, 
    double (*fitnessFn)(int *, individual::ChromoTyp)) {
    _population_size = population_size;
    _fitnessFn = fitnessFn;
    max_fitness = 0;
    population.reserve(population_size * 2);
}

void GeneticAlgorithm::Initial(int len) {
    _gene_length = len;
    for (int i = 0; i < _population_size; i++) {
        population[i] = new individual::Individual();
        population[i+_population_size] = new individual::Individual();
    }
}

void GeneticAlgorithm::Print() {
    std::cout << "Best: " << std::endl;
    population[0]->print();
}

void GeneticAlgorithm::Print(PrintMode mode) {
    switch (mode) {
      case whole:
        std::cout << "---------------------\nParent: " << std::endl;
        for (int i = 0; i < _population_size; i++) {
            std::cout << i << ": ";
            population[i]->print(individual::oneline);
        }
        std::cout << "---------------------\nChild: " << std::endl;
        for (int i = _population_size; i < _population_size*2; i++) {
            std::cout << i << ": ";
            population[i]->print(individual::oneline);
        }
        std::cout << "---------------------\n";
        break;
      case children:
        std::cout << "---------------------\nChild: " << std::endl;
        for (int i = _population_size; i < _population_size*2; i++) {
            std::cout << i << ": ";
            population[i]->print(individual::oneline);
        }
        std::cout << "---------------------\n";
        break;
      case best:
        std::cout << "Best: " << std::endl;
        population[0]->print();
        break;
      case best_fitness:
        std::cout << "Best: ";
        population[0]->print(individual::fitness);
        break;
      case summary:
        Summary();
    }
    
}


void GeneticAlgorithm::Crossover(double p_c, int n_tnmt) {
    TwoPtCrossover(p_c, n_tnmt);
    for (int i = 0; i < _population_size * 2;i++) {
        population[i]->CalcFitness();
    }
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
    for (int i=0;i<_population_size/2;i++) {
        individual::Individual* parent1 = TnmtSelection(n_tnmt);
        individual::Individual* parent2 = TnmtSelection(n_tnmt);
        while (parent1 == parent2){
            parent2 = TnmtSelection(n_tnmt);
        }
        int point1 = rand() % (_gene_length);
        int point2 = rand() % (_gene_length);
        double pc = (rand()/(double)RAND_MAX);
        if (pc < p_c) {
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
    for (int i=0; i<_population_size/2; i++) {
        individual::Individual* parent1 = TnmtSelection(n_tnmt);
        individual::Individual* parent2 = TnmtSelection(n_tnmt);
        while (parent1 == parent2) {
            parent2 = TnmtSelection(n_tnmt);
        }
        
        for(int j=0; j<_gene_length; j++) {
            double pc = (rand()/(double)RAND_MAX);
            if(pc < p_c) {
                *(population[i*2+_population_size]->bits+j) = *(parent1->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent2->bits+j);
            } else  {
                *(population[i*2+_population_size]->bits+j) = *(parent2->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent1->bits+j);
            }
        }
    }
}

void GeneticAlgorithm::Mutation(double p_m) {
    for (int i=0; i<_population_size; i++) {
        for (int j=0;j<_gene_length;j++) {
            double pm = (rand()/(double)RAND_MAX);
            if (pm<p_m) {
                *(population[i+_population_size]->bits+j)
                     = 1-*(population[i+_population_size]->bits+j);
            }
        }
    }
    for (int i = 0; i < _population_size * 2;i++) {
        population[i]->CalcFitness();
    }
}


void GeneticAlgorithm::Survivor() {
    for(int i=0;i<_population_size;i++) {
        population[i + _population_size]->CalcFitness();
    }
    sort(population.begin(), population.begin()+_population_size*2, utility::FitnessCmp);
    max_fitness = population[0]->fitness;
}
void GeneticAlgorithm::Summary() {
    double sum = 0;
    double mean = 0;
    double var = 0;
    for (int i = 0; i < _population_size * 2; i++) {
        sum += population[i]->fitness;
    }
    mean = sum / double(_population_size);
    for (int i = 0; i < _population_size * 2; i++) {
        var += pow((population[i]->fitness - mean), 2);
    }
    var /= double(_population_size);
    std::cout  << "Summary: " << std::endl
        << std::setw(7) << std::fixed << std::setprecision(2) 
        << "\tBest:  " << population[0]->fitness << std::endl
        << "\tMean: " << mean << std::endl
        << "\tvar:  " << var << std::endl;
}

GeneticAlgorithm::~GeneticAlgorithm() {
    for (int i = 0; i < _population_size*2; i++) {
        delete[] population[i]->bits;
        delete population[i];
    }
}

} // namespace genetic_algorithm