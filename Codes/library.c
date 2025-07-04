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

int if_function(int regA, int regB){
    return (regA == 1)? TRUE: FALSE;
}
//================================Chromosome Instructions========================================

//================================GA Functions================================================
void double_to_bin(Chromosome* chromosome){
    // Convert double to binary representation and store in chromosome
    for(int i = 0; i < chromosome->size; i++) {
        chromosome->bin_arr[i] = (chromosome->double_arr[i] > 0.5) ? 1 : 0;
    }
}
void mutation(Chromosome* chromosome_n, int n_instructions){
    int index_bit_change = rand() % n_instructions * 4;
    if(chromosome_n->bin_arr[index_bit_change] == 0) 
        chromosome_n->bin_arr[index_bit_change] = 1;
    else 
        chromosome_n->bin_arr[index_bit_change] = 0;  
}

Chromosome crossover(Chromosome* parent1, Chromosome* parent2, int n_instructions){    
    Chromosome child;
    child.bin_arr = malloc(sizeof(int) * parent1->size);
    child.double_arr = malloc(sizeof(double) * parent1->size);
    // a * 4 = 4a/2 = 2a
    child.fitness = 8;
    child.size = parent1->size;
    if(parent1->fitness > parent2->fitness){
        for(int i = 0; i < parent1->size; i++){
            child.bin_arr[i] = parent1->bin_arr[i];   
            child.double_arr[i] = parent1->double_arr[i];   
        }
    }else{
        for(int i = 0; i < parent2->size; i++){
            child.bin_arr[i] = parent2->bin_arr[i];   
            child.double_arr[i] = parent2->double_arr[i];   
        }
    }
    int j = n_instructions * 2;
    for(int i = 0; i < n_instructions * 2; i++){
        child.bin_arr[i] = parent1->bin_arr[i];
        child.bin_arr[j] = parent2->bin_arr[j];

        child.double_arr[i] = parent1->double_arr[i];
        child.double_arr[j] = parent2->double_arr[j];
        j++;
    }
    return child;
}

Chromosome helper_selection(Chromosome chosen_chrom, int size_chrom){
    Chromosome new_chrom;
    new_chrom.bin_arr = malloc(sizeof(int) * size_chrom);
    new_chrom.double_arr = malloc(sizeof(double) * size_chrom);
    new_chrom.fitness = chosen_chrom.fitness;
    new_chrom.size = size_chrom;
    for(int i = 0; i < size_chrom; i++){
        new_chrom.bin_arr[i] = chosen_chrom.bin_arr[i];
        new_chrom.double_arr[i] = chosen_chrom.double_arr[i];
    }
    return new_chrom;
}

Chromosome selection(Population* pop){
    int max_pop = pop->size;
    int num_instructions = pop->e->num_instructions;
    int index_chosen_parent = rand() % max_pop; //index chosen parent(from 0 to 9)
    int attempts = 15;
    while(pop->chromosomes[index_chosen_parent].fitness <= (2 * num_instructions) && attempts < 50){
        index_chosen_parent = rand() % max_pop;
        attempts++;
    }
    Chromosome chrom = helper_selection(pop->chromosomes[index_chosen_parent], pop->chromosomes[index_chosen_parent].size);
    return chrom;
} 
void print_pop_with_fitness(Population* population){
    int chrom_size = population->chromosomes[0].size;
    printf("                            %dth GENERATION \n", population->generation);
    for(int i = 0; i < population->size; i++){
        printf("%d chrom: ", i + 1);
        for(int j = 0; j < chrom_size; j++){
            printf("%.2lf ", population->chromosomes[i].double_arr[j]);
        }
        printf("\n");
        for(int j = 0; j < chrom_size; j++){
            printf("%2d ", population->chromosomes[i].bin_arr[j]);
        }
        printf("\n");
        printf("fitness: %d\n", population->chromosomes[i].fitness);
    }
    printf("\nbest Chromosome: \n");
    for(int i = 0; i < chrom_size; i++){
        printf("%d ", population->best_chromosome.bin_arr[i]);
    }
    printf("\n");
    for(int i = 0; i < chrom_size; i++){
        printf("%.2lf ", population->best_chromosome.double_arr[i]);
    }
    printf("\nbest fitness: %d\n", population->best_fitness);
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
    pop->best_fitness = pop->chromosomes[0].fitness;
    for(int i = 1; i < pop->size; i++){
        if(pop->best_fitness < pop->chromosomes[i].fitness){
            pop->best_fitness = pop->chromosomes[i].fitness;
        }
    }
    pop->best_chromosome = pop->chromosomes[0];
    for(int i = 1; i < pop->size; i++){
        if(pop->best_chromosome.fitness < pop->chromosomes[i].fitness)
        pop->best_chromosome = pop->chromosomes[i];
    }    
}

void print_chromosome(Chromosome* chrom){
    printf("\n===============================================================Chromosome===========================\n");
    printf("Bin_arr: ");
    for(int i = 0; i < chrom->size; i++)
        printf("%6d", chrom->bin_arr[i]);
    printf("\n===============================================================Chromosome===========================\n");
}

void genetic_alg(Population* pop){
    int flag = TRUE;
    double mutation_rate = (double)rand()/RAND_MAX;
    pop->generation = 1;
    while(pop->generation < 40 && flag == TRUE){
        fitness_func(pop);
        //print_pop_with_fitness(pop);
        if(pop->best_fitness == NUM_BITS * pop->e->num_instructions){
            printf("\nPERFECT CHROMOSOME FOUND AT %dth GENERATION!\n", pop->generation);
            print_chromosome(&pop->best_chromosome);
            flag = FALSE;
        }else{
            Chromosome parents[2]; 
            for(int i = 0; i < pop->size; i++){
                parents[0] = selection(pop);
                parents[1] = selection(pop);
                pop->chromosomes[i] = crossover(&parents[0], &parents[1], pop->e->num_instructions);
                mutation_rate = (double)rand()/RAND_MAX;
                if(mutation_rate > 0.1 && mutation_rate < 0.7){
                    mutation(&pop->chromosomes[i], pop->e->num_instructions);
                }
            }
        }
        pop->generation++;
    }    
}   

void initialize_population(Population* population, int chrom_size) {
    double rand_val = 0;
    int chromosome_size = chrom_size;
    for(int i = 0; i < population->size; i++){
        population->chromosomes[i].double_arr = malloc(sizeof(double) * chromosome_size);
        population->chromosomes[i].bin_arr = malloc(sizeof(int) * chromosome_size);
        population->chromosomes[i].size = chromosome_size;
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

void print_pop(Population* population){
    for(int i = 0; i < population->size; i++){
        printf("%d chrom: ", i + 1);
        for(int j = 0; j < population->chromosomes->size; j++){
            printf("%.2lf ", population->chromosomes[i].double_arr[j]);
        }
        printf("\n");
        for(int j = 0; j < population->chromosomes->size; j++){
            printf("%2d ", population->chromosomes[i].bin_arr[j]);
        }
        printf("\n");
    }
}
//================================GA Functions================================================
