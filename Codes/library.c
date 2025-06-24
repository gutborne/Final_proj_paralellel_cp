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

int mov(int value, int x){
    return value; // x is not used, but kept for signature consistency
}

int increment(int reg, int x){
    return reg++; // x is not used, but kept for signature consistency
}

int decrement(int reg, int x){
    return reg--; // x is not used, but kept for signature consistency
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

int and_function(int regA, int regB){
    int result = (regA == 1 && regB == 1)? 1: 0;
    return result;
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

void fitness_func(Population* population, Chromosome* validation_chrom){

}
void genetic_alg(Population* population){
    
}

void initialize_population(Population* population, int chrom_size) {
    srand((unsigned) time(NULL));
    population->chromosomes->size = chrom_size;
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
