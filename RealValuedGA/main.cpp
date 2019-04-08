#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

#include "real_valued_ga.h"

#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);  

int main(int argc, char *argv[]){
    int population = 100;
    int n_of_x = 10;
    int x_len = 10;
    int generation = 100;
    int num_of_trials = 30;
    int n_tnmt = 2;
    double a = 0.3;
    double p_c = 0.9;
    double p_m = 0.1;
    genetic_algorithm::CrossoverMethod method = genetic_algorithm::two_pt;
    int title = 0;
    char titlename[64];

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
        } else if (strcmp(argv[i], "-a") ==0) {
            a = atof(argv[i + 1]);
        } else if (strcmp(argv[i], "-method") ==0) {
            if (strcmp(argv[i], "2pt") ==0) {
                method = genetic_algorithm::two_pt;
            } else if (strcmp(argv[i], "uni") ==0) {
                method = genetic_algorithm::uniform;
            } else if (strcmp(argv[i], "whole") ==0) {
                method = genetic_algorithm::whole_arithmetic;
            }
        } else if (strcmp(argv[i], "-title") ==0) {
            title = 1;
            strcpy(titlename, argv[i + 1]);
        }
    }

    srand(time(NULL));
    std::vector<double> log(generation, 0.0);
    double sum_of_time=0;

    for (int trial = 0; trial < num_of_trials; trial++) {
        real_valued_ga::RealValuedGa realGA(population, real_valued_ga::Schwefel_Function);
        realGA.Initial(n_of_x);
        clock_t t1 = clock();
        for (int gen=0; gen<generation; gen++) {
            realGA.Crossover(genetic_algorithm::two_pt, p_c, n_tnmt, a);
            realGA.Mutation(p_m);
            realGA.Survivor();
            log[gen] += realGA.max_fitness;
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
    double avg_time = sum_of_time / double(num_of_trials);

    std::ofstream log_file;
    log_file.open ("result.csv", std::ios::app);
    if (title==0) {
        log_file << "rGA:n" << n_tnmt << "-Pc" << p_c << "-Pm" << p_m << ", ";
    } else {
        log_file << titlename << ",";
    }
    for (int gen=0; gen<generation; gen++) {
        log_file << log[gen]/double(num_of_trials) << ", ";
    }
    log_file << std::endl;
    log_file.close();
    //PAUSE
}