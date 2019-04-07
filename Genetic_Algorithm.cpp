#include "Genetic_Algorithm.h"
#include <algorithm>


Genetic_Algorithm::Genetic_Algorithm(int population_size, double (*fitnessFn)(int *, Individual::chromo_typ))
{
    _population_size = population_size;
    _fitnessFn = fitnessFn;
    max_fitness = 0;
    population.reserve(population_size * 2);
}
void Genetic_Algorithm::Initial(int len)
{
    _gene_length = len;
    for (int i = 0; i < _population_size; i++){
        population[i] = new Individual::individual();
        population[i+_population_size] = new Individual::individual();
    }
}

void Genetic_Algorithm::Print()
{
    std::cout << "Best: " << std::endl;
    population[0]->print();
}
void Genetic_Algorithm::Print(print_mode mode)
{
    switch(mode) 
    {
        case whole:
            std::cout << "---------------------\nParent: " << std::endl;
            for (int i = 0; i < _population_size; i++) 
            {
                std::cout << i << ": ";
                population[i]->print(Individual::oneline);
            }
            std::cout << "---------------------\nChild: " << std::endl;
            for (int i = _population_size; i < _population_size*2; i++) 
            {
                std::cout << i << ": ";
                population[i]->print(Individual::oneline);
            }
            std::cout << "---------------------\n";
            break;
        case children:
            std::cout << "---------------------\nChild: " << std::endl;
            for (int i = _population_size; i < _population_size*2; i++) 
            {
                std::cout << i << ": ";
                population[i]->print(Individual::oneline);
            }
            std::cout << "---------------------\n";
            break;
    }
    
}


void Genetic_Algorithm::Crossover(double p_c, int n_tnmt)
{
    TwoPtCrossover(p_c, n_tnmt);
    for (int i = 0; i < _population_size * 2;i++) 
    {
        population[i]->calc_fitness();
    }
}

Individual::individual* Genetic_Algorithm::TnmtSelection(int n_tnmt)
{
    std::vector<Individual::individual*> selected_population(n_tnmt);
    std::vector<int> selected(n_tnmt);
    int max_fit_index = 0;
    double max_fitness = 999999999.0;
    for (int i = 0; i < n_tnmt; i++)
    {
        selected[i] = rand()%_population_size;
        for (int j = 0; j < i; j++)
        {
            if(selected[j]==selected[i])
            {
                j = 0;
                selected[i] = rand() % _population_size;
                //cout << "same";
            }
        }
        if(population[selected[i]]->fitness < max_fitness)
        {
            max_fit_index = selected[i];
            max_fitness = population[selected[i]]->fitness;
        }
    }
    return population[max_fit_index];
}

void Genetic_Algorithm::TwoPtCrossover(double p_c, int n_tnmt)
{
    for(int i=0;i<_population_size/2;i++)
    {
        Individual::individual* parent1 = TnmtSelection(n_tnmt);
        Individual::individual* parent2 = TnmtSelection(n_tnmt);
        while(parent1 == parent2){
            parent2 = TnmtSelection(n_tnmt);
            std::cout << "same_tnmt_result";
        }
        int point1 = rand() % (_gene_length);
        int point2 = rand() % (_gene_length);
        double pc = (rand()/(double)RAND_MAX);
        if(pc < p_c)
        {
            while(point1 == point2){
                point2 = rand()%(_gene_length);
            }
            if(point1>point2){
                std::swap(point1, point2);
            } 
        }
        for(int j=0;j<_gene_length;j++)
        {
            if(j<point1)
            {
                *(population[i*2+_population_size]->bits+j) = *(parent1->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent2->bits+j);
            }
            else if(j<point2)
            {
                *(population[i*2+_population_size]->bits+j) = *(parent2->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent1->bits+j);
            }
            else
            {
                *(population[i*2+_population_size]->bits+j) = *(parent1->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent2->bits+j);
            }
        }
    }
}
void Genetic_Algorithm::UniformCrossover(double p_c, int n_tnmt)
{
    for(int i=0;i<_population_size/2;i++)
    {
        Individual::individual* parent1 = TnmtSelection(n_tnmt);
        Individual::individual* parent2 = TnmtSelection(n_tnmt);
        
        for(int j=0;j<_gene_length;j++)
        {
            double pc = (rand()/(double)RAND_MAX);
            if(pc < p_c)
            {
                *(population[i*2+_population_size]->bits+j) = *(parent1->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent2->bits+j);
            }
            else 
            {
                *(population[i*2+_population_size]->bits+j) = *(parent2->bits+j);
                *(population[i*2+1+_population_size]->bits+j) = *(parent1->bits+j);
            }
        }
    }
}

void Genetic_Algorithm::Mutation(double p_m)
{
    //int len = parent1.gene_size.gene_length;
    for(int i=0;i<_population_size;i++)
    {
        for(int j=0;j<_gene_length;j++)
        {
            double pm = (rand()/(double)RAND_MAX);
            if(pm<p_m)
            {
                *(population[i+_population_size]->bits+j) = 1-*(population[i+_population_size]->bits+j);
            }
        }
    }
    for (int i = 0; i < _population_size * 2;i++) 
    {
        population[i]->calc_fitness();
    }
}


void Genetic_Algorithm::Survivor(){
    for(int i=0;i<_population_size;i++)
    {
        population[i + _population_size]->calc_fitness();
    }
    sort(population.begin(), population.begin()+_population_size*2, utility::fitness_cmp);
    max_fitness = population[0]->fitness;
}

Genetic_Algorithm::~Genetic_Algorithm()
{
    for (int i = 0; i < _population_size*2; i++){
        delete[] population[i]->bits;
        delete population[i];
    }
}