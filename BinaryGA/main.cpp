#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#include "binary_ga.h"

#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);  

int main(int argc, char *argv[]){
    int population = 100;
    int n_of_x = 10;
    int x_len = 10;
    int generation = 100;
    int num_of_trials = 30;
    int n_tnmt = 2;
    double p_c = 0.9;
    double p_m = 0.1;

    for (int i = 1; i < argc-1; i++) { 

        if (strcmp(argv[i], "-popu")==0) {
            population = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-N") ==0) {
            n_of_x = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-len") ==0) {
            x_len = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-gen") ==0) {
            generation = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-trial") ==0) {
            num_of_trials = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-tnmt") ==0) {
            n_tnmt = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-pc") ==0) {
            p_c = atof(argv[i + 1]);
        } else if (strcmp(argv[i], "-pm") ==0) {
            p_m = atof(argv[i + 1]);
        }
    }

    srand(time(NULL));
    std::vector<double> log(generation, 0.0);
    double sum_of_time=0;
    int progress_bar = 100 / num_of_trials;

    for (int trial = 0; trial < num_of_trials; trial++) {
        binary_ga::BinaryGa biGA(population, binary_ga::Schwefel_Function);
        biGA.Initial(n_of_x, x_len);
        clock_t t1 = clock();
        for (int gen=0; gen<generation; gen++) {
            biGA.Crossover(genetic_algorithm::two_pt, p_c, n_tnmt);
            biGA.Mutation(p_m);
            biGA.Survivor();
            log[gen] += biGA.max_fitness;
        }
        clock_t t2 = clock();
        double duration_sec = double(t2-t1)/CLOCKS_PER_SEC;
        sum_of_time += duration_sec;
        
        int pos = 50*(1+trial) / num_of_trials;
        std::cout << "  " << 1+trial << "/" << num_of_trials << " [";
        for (int i = 0; i < 50; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] - " << sum_of_time << "s - fitness: " << log[generation-1]/double(trial+1) <<"\r";
        std::cout.flush();
    }
    std::cout << "\n";
    double avg_time = sum_of_time / double(num_of_trials);
    //std::cout << "---------------\naverage time: " << avg_time << std::endl;

    std::ofstream log_file;
    log_file.open ("binary_ga.csv", std::ios::app);
    log_file << "n" << n_tnmt << "-Pc" << p_c << "-Pm" << p_m << ", ";
    for (int gen=0; gen<generation; gen++) {
        log_file << log[gen]/double(num_of_trials) << ", ";
    }
    log_file << std::endl;
    log_file.close();
    //PAUSE
}