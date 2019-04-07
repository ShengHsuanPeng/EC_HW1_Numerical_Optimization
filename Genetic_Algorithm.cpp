#include "Genetic_Algorithm.h"
#include <algorithm>

Genetic_Algorithm::Genetic_Algorithm(int population_size, double (*fitnessFn)(int *, chromo_typ))
{
    _population_size = population_size;
    _fitnessFn = fitnessFn;
    population.reserve(population_size * 2);
}
void Genetic_Algorithm::Initial(int len)
{
    for (int i = 0; i < _population_size; i++){
        population[i] = individual();
    }
}

void Genetic_Algorithm::Print(int generation)
{
    if(PRINT)
    {
        cout << "Best: " << best_fitness[generation] << ", ";
        for(int j=0;j<GENE_LEN;j++)
        {
            cout << chromo[best_fitness[generation]][j];
            if(j%10==9) cout << " ";
        }
        cout << "\n";
        int x_i[N_X];
        for(int j=0; j<N_X;j++)
        {
            x_i[j]=0;
            for(int k=0;k<LENGTH;k++)
            {
                x_i[j]+=chromo[best_fitness[generation]][j*10+k]*pow(2,k);
            }
            x_i[j]-=512;
            cout << x_i[j] << " ";
        }
        cout << "\n";
    }
    
    if(generation<GENERATION)
        fprintf(out,"%lf,",1.0/fitness[best_fitness[generation]]);
    else
        fprintf(out,"%lf\n",1.0/fitness[best_fitness[generation]]);

}
void Genetic_Algorithm::_CalcFitness(int* bit){
    //int length = sizeof(bit)/sizeof(int);
    //int i = 0;
}
void Genetic_Algorithm::Fitness(int generation)
{
    Fitness(chromo,fitness, generation);
}
void Genetic_Algorithm::Fitness(int gene[][GENE_LEN], double fit[], int generation)
{
	int x_i[N_X] = {};
    double fitness_max=0,fitness_total=0,sum_square=0;
    double fitness_avg=0, fitness_std=0;
    for(int i=0;i<POPULATION;i++)
    {
        fit[i]=0;

        // convert from binary into integer
        for(int j=0; j<N_X;j++)
        {
            x_i[j]=0;
            for(int k=0;k<LENGTH;k++)
            {
                x_i[j]+=gene[i][j*10+k]*pow(2,k);
            }
            x_i[j]-=512;
        }

        // calculate Fsch
        double fsch=418.98291*N_X;
        for(int j=0; j<N_X; j++)
        {
            fsch -= x_i[j]*sin(sqrt(abs(x_i[j])));
        }
        fit[i] = (1.0/fsch);

        if(generation<0) continue;
        // statistic
        if(fit[i]>fitness_max)
        {
            fitness_max = fit[i];
            best_fitness[generation] = i;
        }
        fitness_total += fsch;
        sum_square += pow(fsch,2);
    }
    if(generation<0) return;
    fitness_avg = fitness_total/POPULATION;
    fitness_std = sqrt(sum_square/POPULATION - fitness_avg);

    if(PRINT)
    {
        printf("Average = %lf ",fitness_avg);
        printf("Std. deviation = %lf ",fitness_std);
        printf("Fitness Min = %lf ",1.0/fitness_max);
        printf("Fitness Sum = %lf\n",fitness_total);
    }
    
}

void Genetic_Algorithm::Crossover(int p_c)
{
    TwoPtCrossover(p_c);
}

individual* Genetic_Algorithm::TnmtSelection(int n_tnmt)
{
    vector<individual*> selected_population(5);
    vector<int> selected(5);
    int max_fit_sel=0, max_fitness=999999999;
    for (int i = 0; i < n_tnmt; i++)
    {
        selected[i] = rand()%_population_size;
        for (int j = 0; j < i; j++)
        {
            if(selected[j]==selected[i])
            {
                j = 0;
                selected[i] = rand() % 10;
                //cout << "same";
            }
        }
        selected_population[i] = &population[selected];
        if(selected_population[i].fitness < max_fitness)
        {
            max_fit_sel = selected;
            max_fitness = (*selected_population[i]).fitness;
        }
    }
    return selected_population[max_fit_sel];
}

void Genetic_Algorithm::TwoPtCrossover(int p_c)
{
    for(int i=0;i<_population_size/2;i++)
    {
        individual* parent1 = TnmtSelection(fitness);
        individual* parent2 = TnmtSelection(fitness);
        int len = parent1.gene_size.gene_length;
        int point1 = rand()%(len), 
        int point2 = rand()%(len);
        double pc = (rand()/(double)RAND_MAX);
        if(pc < p_c)
        {
            while(point1 == point2){
                point2 = rand()%(len);
            }
            if(point1>point2){
                swap(point1, point2);
            } 
        }
        for(int j=0;j<len;j++)
        {
            if(j<point1)
            {
                *(population[i*2].bits+j) = *(parent1.bits+j);
                *(population[i*2+1].bits+j) = *(parent2.bits+j);
            }
            else if(j<point2)
            {
                *(population[i*2].bits+j) = *(parent2.bits+j);
                *(population[i*2+1].bits+j) = *(parent1.bits+j);
            }
            else
            {
                *(population[i*2].bits+j) = *(parent1.bits+j);
                *(population[i*2+1].bits+j) = *(parent2.bits+j);
            }
        }
        
    }
}
void Genetic_Algorithm::NPtCrossover(int p_c, int n_pt)
{
    for(int i=0;i<_population_size/2;i++)
    {
        individual* parent1 = TnmtSelection(fitness);
        individual* parent2 = TnmtSelection(fitness);
        int len = parent1.gene_size.gene_length;
        
        for(int j=0;j<len;j++)
        {
            double pc = (rand()/(double)RAND_MAX);
            if(pc < p_c)
            {
                *(population[i*2].bits+j) = *(parent1.bits+j);
                *(population[i*2+1].bits+j) = *(parent2.bits+j);
            }
            else 
            {
                *(population[i*2].bits+j) = *(parent2.bits+j);
                *(population[i*2+1].bits+j) = *(parent1.bits+j);
            }
        }
    }
}

void Genetic_Algorithm::Mutation(int p_m)
{
    int len = parent1.gene_size.gene_length;
    for(int i=0;i<_population_size;i++)
    {
        for(int j=0;j<len;j++)
        {
            double pm = (rand()/(double)RAND_MAX);
            if(pm<p_m)
            {
                *(population[i+_population_size].bits+j) = 1-*(population[i+_population_size].bits+j);
            }
        }
    }
}


void Genetic_Algorithm::Survivor(){
    sort(population.begin().population.begin()+_population_size*2, utility::fitness_cmp);
    population.erase(population.begin() + _population_size + 1, population.begin() + _population_size * 2);
    population.reserve(_population_size * 2);
}