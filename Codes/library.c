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
void mutation(Chromosome* chromosome_n, int n_instructions){
    srand((unsigned) time(NULL));
    int index_bit_change = rand() % n_instructions * 4;
    if(chromosome_n->bin_arr[index_bit_change] == 0) 
        chromosome_n->bin_arr[index_bit_change] = 1;
    else 
        chromosome_n->bin_arr[index_bit_change] = 0;  
}

Chromosome crossover(Chromosome* parent1, Chromosome* parent2, int n_instructions){
    Chromosome chrom;
    chrom.bin_arr = malloc(sizeof(int) * parent1->size);
    chrom.double_arr = malloc(sizeof(double) * parent1->size);
    // a * 4 = 4a/2 = 2a
    // 1 0 1 0 0 0 0 0
    // 1 1 1 1 0 1 0 1
    int j = n_instructions * 2;
    for(int i = 0; i < n_instructions * 2; i++){
        chrom.bin_arr[i] = parent1->bin_arr[i];
        chrom.bin_arr[j] = parent2->bin_arr[j];
        j++;
    }
    j = n_instructions * 2;
    for(int i = 0; i < n_instructions * 2; i++){
        chrom.double_arr[i] = parent1->double_arr[i];
        chrom.double_arr[j] = parent2->double_arr[j];
        j++;
   }
    for(int i = 0; i < parent1->size; i++){
        printf("%d\n ", parent1->bin_arr[i]);
    }
    printf("\n ");
    for(int i = 0; i < parent1->size; i++){
        printf("%d\n ", parent2->bin_arr[i]);
    }
    printf("\n ");
    for(int i = 0; i < parent1->size; i++){
        printf("%d\n ", chrom.bin_arr[i]);
    }
    printf("\n ");
    return chrom;
}

Chromosome helper_selection(Chromosome chosen_chrom, int size){
    Chromosome new_chrom;
    new_chrom.bin_arr = malloc(sizeof(int) * size);
    new_chrom.double_arr = malloc(sizeof(double) * size);
    new_chrom.fitness = chosen_chrom.fitness;
    new_chrom.size = size;
    for(int i = 0; i < size; i++){
        new_chrom.bin_arr[i] = chosen_chrom.bin_arr[i];
        new_chrom.double_arr[i] = chosen_chrom.double_arr[i];
    }
    return new_chrom;
}

Chromosome selection(Population* pop){
    srand((unsigned)time(NULL));
    int max_pop = pop->size;
    int num_instructions = pop->e->num_instructions;
    int index_chosen_parent = rand() % max_pop; //index chosen parent(from 1 to 10)
    while(pop->chromosomes[index_chosen_parent].fitness <= (2 * num_instructions)){
        index_chosen_parent = rand() % max_pop;
        printf("\nindex_parent: %d chosen_parent_fitness: %d \n", index_chosen_parent, pop->chromosomes[index_chosen_parent].fitness);
    }

    Chromosome chrom = helper_selection(pop->chromosomes[index_chosen_parent], pop->chromosomes->size);
    /*for(int i = 0; i < pop->chromosomes->size; i++){
        printf("%d  ", chrom.bin_arr[i]);
    }
    printf("\n");
    for(int i = 0; i < pop->chromosomes->size; i++){
        printf("%.2lf ", chrom.double_arr[i]);
    }*/
    printf("\n");
    return chrom;
} 
void print_pop_with_fitness(Population* population){
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
        printf("fitness: %d\n", population->chromosomes[i].fitness);
    }
    printf("\nbest Chromosome: \n");
    for(int i = 0; i < population->chromosomes->size; i++){
        printf("%d ", population->best_chromosome.bin_arr[i]);
    }
    printf("\nbest fitness: %d", population->best_fitness);
    printf("\n");
    for(int i = 0; i < population->chromosomes->size; i++){
        printf("%.2lf ", population->best_chromosome.double_arr[i]);
    }
    printf("\n");
}
void fitness_func(Population* pop){
    printf("inside fitness\n");
    Chromosome* chrom_pop = pop->chromosomes;
    int num_pop = pop->size;
    int num_instructions = pop->e->num_instructions;
    char* perfect_indiv = malloc(sizeof(char) * (num_instructions * 4 + 1));
    printf("inside fitness before the first for\n");
    for(int i = 0; i < num_instructions; i++){
        if(i == 0)
        sprintf(perfect_indiv, "%s", pop->e->Instruc_arr[i].code);
        else
        sprintf(perfect_indiv + (4 * i), "%s", pop->e->Instruc_arr[i].code);          
    }
    printf("inside fitness after the first for\n");
    printf("inside fitness before the second for\n");
    for(int i = 0; i < num_pop; i++){
        chrom_pop[i].fitness = 4 * num_instructions;
        for(int j = 0; j < num_instructions * 4; j++) {
            if((chrom_pop[i].bin_arr[j] + '0') != perfect_indiv[j]){
                chrom_pop[i].fitness -= 1;
            }
        }
    }
    printf("inside fitness after the second for\n");
    printf("inside fitness before the third and forth for\n");
    pop->best_fitness = pop->chromosomes[0].fitness;
    for(int i = 1; i < pop->size; i++){
        pop->best_fitness = (pop->best_fitness < pop->chromosomes[i].fitness)? pop->chromosomes[i].fitness: pop->best_fitness;
    }
    pop->best_chromosome = pop->chromosomes[0];
    for(int i = 1; i < pop->size; i++){
        if(pop->best_chromosome.fitness < pop->chromosomes[i].fitness)
        pop->best_chromosome = pop->chromosomes[i];
    }
    printf("inside fitness after the third and forth for\n");
}

void genetic_alg(Population* pop){
    printf("inside genetic algorithm\n");
    int flag = TRUE;
    Chromosome* new_pop = malloc(sizeof(Chromosome) * pop->size);
    double crossover_rate = rand()/RAND_MAX;
    double mutation_rate = rand()/RAND_MAX;
    while(flag){
        printf("inside while\n");
        fitness_func(pop);
        print_pop_with_fitness(pop);
        if(pop->best_fitness == pop->chromosomes->size){
            printf("\n A perfect chromosome was found!!\n");
            flag = FALSE;
        }else{
            for(int i = 0; i < pop->size; i++){
                printf("parent 1\n");
                Chromosome parent1 = selection(pop);
                printf("parent 2\n");
                Chromosome parent2 = selection(pop);
                if(crossover_rate > 0.6 && crossover_rate < 1.0){
                    new_pop[i] = crossover(&parent1, &parent2, pop->e->num_instructions);
                }else{
                    //we will choose the chromosome with better fitness to the new population
                    new_pop[i] = (parent1.fitness > parent2.fitness)? parent1: parent2;
                }
                if(mutation_rate > 0.1 && mutation_rate < 0.3){
                    mutation(&new_pop[i], pop->e->num_instructions);
                }
            }
            pop->chromosomes = new_pop;
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
