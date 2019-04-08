#include <iostream>
#include <fstream>

#include "real_valued_ga.h"

#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);  



int main(){
    int population = 100;
    int n_of_x = 100;
    int generation = 100;
    int num_of_trials = 30;
    srand(time(NULL));
    std::vector<double> log(generation, 0.0);
    double sum_of_time=0;

    for (int trial = 0; trial < num_of_trials; trial++) {
        std::cout << "================Trial: " << trial+1 << "================\n";
        real_valued_ga::RealValuedGa realGA(population, real_valued_ga::Schwefel_Function);
        realGA.Initial(n_of_x);
        clock_t t1 = clock();
        for (int gen=0; gen<generation; gen++) {
            //std::cout << "================Gen: " << generation << "================\n";
            realGA.Crossover(genetic_algorithm::two_pt, 0.9, 2);
            realGA.Mutation(0.1);
            realGA.Survivor();
            log[gen] += realGA.max_fitness;
        }
        clock_t t2 = clock();
        double duration_sec = double(t2-t1)/CLOCKS_PER_SEC;
        sum_of_time += duration_sec;
        std::cout << "took: " << duration_sec << " s" << std::endl;
        //biGA.Print(genetic_algorithm::summary);
    }
    double avg_time = sum_of_time / double(num_of_trials);
    std::cout << "---------------\naverage time: " << avg_time << std::endl;

    std::ofstream log_file;
    log_file.open ("real_ga.csv");

    for (int gen=0; gen<generation; gen++) {
        log_file << log[gen]/double(num_of_trials)
                 << ", \n";
    }
    log_file.close();
    PAUSE
}