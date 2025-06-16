#include "final_proj.h"

//================================Chromosome Instructions========================================


int add(int regA, int regB){
    return regA + regB;
}

int sub(int regA, int regB){
    return regA - regB;
}

int mult(int regA, int regB){
    return regA * regB;
}

void mov(int* reg, int value){
    *reg = value;
}

void increment(int* reg){
    *reg += 1;
}

void decrement(int* reg){
    *reg -= 1;
}

int greater_than(int regA, int regB){
    return (regA > regB)? TRUE: FALSE;  
}

int less_than(int regA, int regB){
    return (regA < regB)? TRUE: FALSE;
}

int module(int regA, int regB){
    return regA % regB;
}
//================================Chromosome Instructions========================================

//================================GA Functions================================================
void double_to_bin(Chromosome* chromosome){
    // Convert double to binary representation and store in chromosome
    for(int i = 0; i < chromosome->size; i++) {
        chromosome->bin_arr[i] = (chromosome->double_arr[i] > 0.5) ? 1 : 0;
    }
}
void mutation(Chromosome* chromosome_n){

}

void crossover(Chromosome* parent1, Chromosome* parent2){
    // Implement crossover logic here
}

void selection(Population* population){
    // Implement selection logic here
} 

void genetic_alg(Population* population, int gens){

}

void initialize_population(Population* population) {
    srand((unsigned) time(NULL));
    population->chromosomes->size = 16;
    double rand_val = 0;
    int chromosome_size = population->chromosomes->size;
    for(int i = 0; i < population->size; i++){
        population->chromosomes[i].double_arr = malloc(sizeof(double) * chromosome_size);
        for(int j = 0; j < chromosome_size; j++){
            rand_val = (double)rand() / RAND_MAX;
            population->chromosomes[i].double_arr[j] = rand_val;
        }
    }
}
//================================GA Functions================================================
