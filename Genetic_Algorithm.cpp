#include "Genetic_Algorithm.h"
#include <algorithm>
//using namespace std;

Genetic_Algorithm::Genetic_Algorithm(int population_size, double (*fitnessFn)(int *, chromo_typ))
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
        population.at(i) = individual();
    }
}

void Genetic_Algorithm::Print()
{
    cout << "Best: " << endl;
    population.at(0).print();
}


void Genetic_Algorithm::Crossover(double p_c, int n_tnmt)
{
    TwoPtCrossover(p_c, n_tnmt);
}

individual* Genetic_Algorithm::TnmtSelection(int n_tnmt)
{
    vector<individual*> selected_population(5);
    vector<int> selected(5);
    int max_fit_sel=0, max_fitness=999999999;
    for (int i = 0; i < n_tnmt; i++)
    {
        selected.at(i) = rand()%_population_size;
        for (int j = 0; j < i; j++)
        {
            if(selected.at(j)==selected.at(i))
            {
                j = 0;
                selected.at(i) = rand() % 10;
                //cout << "same";
            }
        }
        if(population.at(selected.at(i)).fitness < max_fitness)
        {
            max_fit_sel = selected.at(i);
            max_fitness = population.at(selected.at(i)).fitness;
        }
    }
    return &population.at(selected.at(max_fit_sel));
}

void Genetic_Algorithm::TwoPtCrossover(double p_c, int n_tnmt)
{
    for(int i=0;i<_population_size/2;i++)
    {
        individual* parent1 = TnmtSelection(n_tnmt);
        individual* parent2 = TnmtSelection(n_tnmt);
        int point1 = rand() % (_gene_length);
        int point2 = rand() % (_gene_length);
        double pc = (rand()/(double)RAND_MAX);
        if(pc < p_c)
        {
            while(point1 == point2){
                point2 = rand()%(_gene_length);
            }
            if(point1>point2){
                swap(point1, point2);
            } 
        }
        for(int j=0;j<_gene_length;j++)
        {
            if(j<point1)
            {
                *(population.at(i*2).bits+j) = *(parent1->bits+j);
                *(population.at(i*2+1).bits+j) = *(parent2->bits+j);
            }
            else if(j<point2)
            {
                *(population.at(i*2).bits+j) = *(parent2->bits+j);
                *(population.at(i*2+1).bits+j) = *(parent1->bits+j);
            }
            else
            {
                *(population.at(i*2).bits+j) = *(parent1->bits+j);
                *(population.at(i*2+1).bits+j) = *(parent2->bits+j);
            }
        }
        
    }
}
void Genetic_Algorithm::UniformCrossover(double p_c, int n_tnmt)
{
    for(int i=0;i<_population_size/2;i++)
    {
        individual* parent1 = TnmtSelection(n_tnmt);
        individual* parent2 = TnmtSelection(n_tnmt);
        
        for(int j=0;j<_gene_length;j++)
        {
            double pc = (rand()/(double)RAND_MAX);
            if(pc < p_c)
            {
                *(population.at(i*2).bits+j) = *(parent1->bits+j);
                *(population.at(i*2+1).bits+j) = *(parent2->bits+j);
            }
            else 
            {
                *(population.at(i*2).bits+j) = *(parent2->bits+j);
                *(population.at(i*2+1).bits+j) = *(parent1->bits+j);
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
                *(population.at(i+_population_size).bits+j) = 1-*(population.at(i+_population_size).bits+j);
            }
        }
    }
}


void Genetic_Algorithm::Survivor(){
    sort(population.begin(), population.begin()+_population_size*2, utility::fitness_cmp);
    population.erase(population.begin() + _population_size + 1, population.begin() + _population_size * 2);
    population.reserve(_population_size * 2);
    max_fitness = population.at(0).fitness;
}