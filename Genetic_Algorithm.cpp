#include "Genetic_Algorithm.h"

Genetic_Algorithm::Genetic_Algorithm(int population_size, double (*fitnessFn)(int *, chromo_typ))
{
    _population_size = population_size;
    _fitnessFn = fitnessFn;
    population.resize(population_size * 2);
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

int Genetic_Algorithm::TnmtSelection(double fit[])
{
    int selection[N_TOURNAMENT] = {};
    int i = N_TOURNAMENT;
    int max_fit_sel=0;
    while(i>0)
    {
        int sel = rand()%POPULATION;
        for(int j=N_TOURNAMENT-i;j>0;)
        {
            if(sel==selection[N_TOURNAMENT-j]){
                j=N_TOURNAMENT-i;
                sel = rand()%POPULATION;
            }
            else
                j--;
        }
        selection[i-1] = sel;
        if(i==N_TOURNAMENT)
            max_fit_sel = sel;
        else
            max_fit_sel = (fitness[sel]>fitness[max_fit_sel])? sel:max_fit_sel;
        i--;
    }
    return max_fit_sel;
}

void Genetic_Algorithm::Crossover()
{
    for(int i=0;i<POPULATION/2;i++)
    {
        int parent1 = TnmtSelection(fitness);
        int parent2 = TnmtSelection(fitness);
        int point1=0, point2=0;
        double pc = (rand()/(double)RAND_MAX);
        if( pc < PROBABILITY_CROSSOVER)
        {
            while(point1 == point2){
                point1 = rand()%(GENE_LEN);
                point2 = rand()%(GENE_LEN);
                if(point1>point2){
                    int tmp = point1;
                    point1 = point2;
                    point2 = tmp;
                } 
            }
        }
        for(int j=0;j<GENE_LEN;j++)
        {
            if(j<point1)
            {
                child[i*2][j] = chromo[parent1][j];
                child[i*2+1][j] = chromo[parent2][j];
            }
            else if(j<point2)
            {
                child[i*2][j] = chromo[parent2][j];
                child[i*2+1][j] = chromo[parent1][j];
            }
            else
            {
                child[i*2][j] = chromo[parent1][j];
                child[i*2+1][j] = chromo[parent2][j];
            }
        }
        
    }
}

void Genetic_Algorithm::Mutation()
{
    for(int i=0;i<POPULATION;i++)
    {
        for(int j=0;j<GENE_LEN;j++)
        {
            double pm = (rand()/(double)RAND_MAX);
            if(pm<PROBABILITY_MUTATION)
            {
                child[i][j] = 1-child[i][j];
            }
        }
    }
}


void Genetic_Algorithm::Survivor(){
    double fitness_child[POPULATION];
    int sort[POPULATION*2][2];
    double fit[POPULATION*2];;
    Fitness(child,fitness_child,-1);
    for(int i=0;i<POPULATION;i++)
    {
        sort[i][0]=0;
        sort[i][1]=i;
        fit[i]=fitness[i];
        sort[i+POPULATION][0]=1;
        sort[i+POPULATION][1]=i;
        fit[i+POPULATION]=fitness_child[i];
    }
    double tmp,t1,t2;
    int j;
    for(int i=0;i<POPULATION*2;i++)
    {
        tmp = fit[i];
        t1=sort[i][0];
        t2=sort[i][1];
        for(j=i; j>0 && fit[j-1]<tmp; j--)
        {
            sort[j][0]=sort[j-1][0];
            sort[j][1]=sort[j-1][1];
            fit[j]=fit[j-1];
        }
        sort[j][0]=t1;
        sort[j][1]=t2;
        fit[j]=tmp;
    }
    for(int i=0;i<POPULATION;i++)
    {
        if(sort[i][0]==0)
            for(int j=0;j<GENE_LEN;j++)
            {
                newchromo[i][j] = chromo[sort[i][1]][j];
            }
        else 
            for(int j=0;j<GENE_LEN;j++)
            {
                newchromo[i][j] = child[sort[i+POPULATION][1]][j];
            }   
    }
    for(int i=0;i<POPULATION;i++)
    {
        for(int j=0;j<GENE_LEN;j++)
        {
            chromo[i][j] = newchromo[i][j];
        } 
    }
}