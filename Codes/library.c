#include "final_proj.h"

//================================Chromosome Instructions========================================
Instruction instructions[] = {
    {"add", add, "0000"},
    {"sub", sub, "0001"},
    {"mult", mult, "0010"},
    {"mov", mov, "0011"},
    {"increment", increment, "0100"},
    {"decrement", decrement, "0101"},
    {"greater_than", greater_than, "0110"},
    {"less_than", less_than, "0111"},
    {"module", module, "1000"},
    {"and_function", and_function, "1001"}
}; 

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

void selection(Population* pop){
    // Implement selection logic here
} 

void fitness_func(Population* pop){
    Chromosome* chrom_pop = pop->chromosomes;
    int num_pop = pop->size;
    int num_instructions = pop->e->num_instructions;
    char* perfect_indiv = malloc(sizeof(char) * (num_instructions * 4 + 1));
    for(int i = 0; i < num_instructions; i++){
        if(i == 0)
            sprintf(perfect_indiv, "%s", pop->e->Instruc_arr[i].code);
        else
            sprintf(perfect_indiv + (4 * i), "%s", pop->e->Instruc_arr[i].code);          
    }
    
    for(int i = 0; i < num_pop; i++){
        chrom_pop[i].fitness = 4 * num_instructions;
        for(int j = 0; j < num_instructions * 4; j++) {
            if((chrom_pop[i].bin_arr[j] + '0') != perfect_indiv[j]){
                chrom_pop[i].fitness -= 1;
            }
        }
    }
}

void genetic_alg(Population* pop){
    int flag = TRUE;
    while(flag){
        for(int i = 0; i < pop->size; i++){
            
        }
    }    
}   

void initialize_population(Population* population, int chrom_size) {
    srand((unsigned) time(NULL));
    population->chromosomes->size = chrom_size;
    double rand_val = 0;
    int chromosome_size = population->chromosomes->size;
    for(int i = 0; i < population->size; i++){
        population->chromosomes[i].double_arr = malloc(sizeof(double) * chromosome_size);
        population->chromosomes[i].bin_arr = malloc(sizeof(int) * chromosome_size);
        for(int j = 0; j < chromosome_size; j++){
            rand_val = (double)rand() / RAND_MAX;
            if(rand_val > 0.5) 
                population->chromosomes[i].bin_arr[j] = 1;
            else 
                population->chromosomes[i].bin_arr[j] = 0;
            population->chromosomes[i].double_arr[j] = rand_val;
        }
    }
}
//================================GA Functions================================================
