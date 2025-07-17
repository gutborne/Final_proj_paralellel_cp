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

int is_equal(int regA, int regB){
    return (regA == regB)? TRUE: FALSE;
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
    //2 * a -> n_instruc = (a -> n_instruc * 4)/2
    //2a  = 4a/2
    //2a  = 2a
    //printf("Chromosome: \n");
    for(int i = 0; i < 2 * n_instructions; i++){
        int index_bit_mut = rand() % (n_instructions * NUM_BITS);
        //printf("%d: index_bit_mut: %d\n", i+1, index_bit_mut);
        if(chromosome_n->bin_arr[index_bit_mut] == 0) 
            chromosome_n->bin_arr[index_bit_mut] = 1;
        else 
            chromosome_n->bin_arr[index_bit_mut] = 0;
    }  
}

Chromosome crossover(Chromosome* parent1, Chromosome* parent2, int n_instructions, int index_curr_chrom){    
    Chromosome child;
    child.bin_arr = malloc(sizeof(int) * parent1->size);
    child.double_arr = malloc(sizeof(double) * parent1->size);
    // a * 4 = 4a/2 = 2a
    child.size = parent1->size;
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
    int attempts = 0;
    //a->n_instr * 4 * 3/4 = a->n_instr * 2 + a
    //12a/4 = 2a + a
    //3a = 3a
    while(pop->chromosomes[index_chosen_parent].fitness < (num_instructions * 3) && attempts < 50){
        index_chosen_parent = rand() % max_pop;
        //printf("index_chosen_parent: %d attempts: %d fitness_index_chosen_parent: %d\n", index_chosen_parent, attempts, pop->chromosomes[index_chosen_parent].fitness);
        attempts++;
    }
    Chromosome chrom = helper_selection(pop->chromosomes[index_chosen_parent], pop->chromosomes[index_chosen_parent].size);
    return chrom;
} 
void print_pop_with_fitness(Population* population){
    int chrom_size = population->chromosomes[0].size;
    for(int i = 0; i < population->size; i++){
        printf("%d chrom: ", i + 1);
        /*for(int j = 0; j < chrom_size; j++){
            printf("%.2lf ", population->chromosomes[i].double_arr[j]);
        }*/
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
    /*
    for(int i = 0; i < chrom_size; i++){
        printf("%.2lf ", population->best_chromosome.double_arr[i]);
    }
    */
    printf("\nbest fitness: %d\n", population->best_fitness);
}

int* generate_perfect_chrom(Expression* e){
    int num_instructions = e->num_instructions;
    char* perfect_indiv_char = malloc(sizeof(char) * (num_instructions * NUM_BITS));
    int* perfect_indiv_int = malloc(sizeof(int) * (num_instructions * NUM_BITS));
    for(int i = 0; i < num_instructions; i++){
        if(i == 0)
            sprintf(perfect_indiv_char, "%s", e->Instruc_arr[i].code);
        else
            sprintf(perfect_indiv_char + (NUM_BITS * i), "%s", e->Instruc_arr[i].code);          
    }
    for(int i = 0; i < num_instructions * NUM_BITS; i++){
        perfect_indiv_int[i] = perfect_indiv_char[i] - '0';
    }
    printf("PERFECT CHROM: ");
    for(int i = 0; i < num_instructions * NUM_BITS; i++){
        printf("%d ");
    }
    printf("\n");
    free(perfect_indiv_char);
    return perfect_indiv_int;
}

int fitness_func(Chromosome* chrom, Expression* e){
    int chrom_size = chrom->size, num_instructions = e->num_instructions;
    chrom->fitness = num_instructions * NUM_BITS;
    for(int j = 0; j < num_instructions * NUM_BITS; j++) {
        if(chrom->bin_arr[j] != e->perfect_chrom[j]){
            chrom->fitness -= 1;
        }
    }
    return chrom->fitness;
}

void find_best_fitness_of_pop(Population* pop){
    pop->best_fitness = pop->chromosomes[0].fitness;
    for(int i = 1; i < pop->size; i++){
        if(pop->best_fitness < pop->chromosomes[i].fitness){
            pop->best_fitness = pop->chromosomes[i].fitness;
        }
    }
}

void find_best_chrom_of_pop(Population* pop){
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
    printf("fitness: %d\n", chrom->fitness);
}

void genetic_alg(Population* pop){
    int flag = TRUE;
    double mutation_rate = (double)rand()/RAND_MAX;
    pop->generation = 1;
    while(pop->generation <= 10 && flag == TRUE){
        if(pop->best_fitness == NUM_BITS * pop->e->num_instructions){
            printf("\nPERFECT CHROMOSOME FOUND AT %dth GENERATION!\n", pop->generation);
            print_chromosome(&pop->best_chromosome);
            flag = FALSE;
        }else{
            int index = 0, chrom_size = NUM_BITS * pop->e->num_instructions, fitness = 0, n_instructions = pop->e->num_instructions;
            int my_rank;
            MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
            int total_n_process;
            MPI_Comm_size(MPI_COMM_WORLD, &total_n_process);
            MPI_Status stat;
            Chromosome parents[2];
            int remain_pop = pop->size % (total_n_process-1), j = 0, partition = pop->size / (total_n_process - 1), i_rank = 1;
            printf("                                GENERATION %dTH\n", pop->generation); 
            if(my_rank == 0){//master process
                for(int i = 0; i < pop->size; i++){
                    parents[0] = selection(pop);
                    parents[1] = selection(pop);
                    pop->chromosomes[i] = crossover(&parents[0], &parents[1], pop->e->num_instructions, i);
                    mutation_rate = (double)rand()/RAND_MAX;
                    if(mutation_rate > 0.1 && mutation_rate < 0.7){
                        mutation(&pop->chromosomes[i], pop->e->num_instructions);
                    }
                }
                if(remain_pop == 0){ //verify if the size of the pop is divisible by the numbers of slave processes
                    for(index; index < pop->size;){ 
                        if(j == partition){
                            i_rank++;
                            j = 0;
                        }
                        for(j; j < partition; j++){
                            MPI_Send(pop->chromosomes[index].bin_arr, NUM_BITS * pop->e->num_instructions, MPI_INT, i_rank % total_n_process, 0, MPI_COMM_WORLD);
                            MPI_Recv(&pop->chromosomes[index].fitness, 1, MPI_INT, i_rank % total_n_process, 0, MPI_COMM_WORLD, &stat);
                            index++;
                        }
                    }
                }else{//if not divisible
                    for(index; index < pop->size - remain_pop; index++){
                        if(j == partition){
                            i_rank++;
                            j = 0;
                        }
                        for(j; j < partition; j++){
                            MPI_Send(pop->chromosomes[index].bin_arr, NUM_BITS * pop->e->num_instructions, MPI_INT, i_rank % total_n_process, 0, MPI_COMM_WORLD);
                            MPI_Recv(&pop->chromosomes[index].fitness, 1, MPI_INT, i_rank % total_n_process, 0, MPI_COMM_WORLD, &stat);
                            index++;
                        }
                    }
                    i_rank = 1;
                    for(int i = 0; i < remain_pop; i++){//calculate the rest of the pop
                        MPI_Send(pop->chromosomes[index].bin_arr, pop->chromosomes->size, MPI_INT, i_rank % total_n_process, 0, MPI_COMM_WORLD);
                        MPI_Recv(&pop->chromosomes[index].fitness, 1, MPI_INT, i_rank % total_n_process, 0, MPI_COMM_WORLD, &stat);
                        i_rank++;
                    }
                }
                for (int rank = 1; rank < total_n_process; rank++) {
                    MPI_Send(NULL, 0, MPI_INT, rank, TAG_STOP, MPI_COMM_WORLD);
                }
            }else{//slaves
                int* buffer = malloc(sizeof(int) * chrom_size);
                MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);   
                if(stat.MPI_TAG == TAG_STOP) {
                    break;  // Master told this slave to stop
                }
                while(TRUE){
                    MPI_Recv(buffer, chrom_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &stat);
                    Chromosome chrom;
                    chrom.bin_arr = buffer;
                    chrom.size = chrom_size;
                    fitness = fitness_func(&chrom, pop->e);
                    MPI_Send(&fitness, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                }
            }
            find_best_fitness_of_pop(pop);
            find_best_chrom_of_pop(pop);
            //print_pop_with_fitness(pop);
        }
        pop->generation++;
    }
    if(flag) printf("A PERFECT CHROM WASNT FOUND!\n");    
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

//================================Instruction List================================================
/// @brief dont forget to create a function to count how many elements we have at runtime
Instruction instruc_list[] = {
    {"add", add, "0000"},
    {"sub", sub, "0001"},
    {"mult", mult, "0010"},
    {"mov", mov, "0011"},
    {"increment", increment, "0100"},
    {"greater_than", greater_than, "0101"},
    {"module", module, "0111"},
    {"and_function", and_function, "1000"},
    {"if_function", if_function, "1001"},
    {"is_equal", is_equal, "1010"}
}; 
//================================Instruction List================================================

//================================Utility Functions===============================================
void print_registers_address(Instruction* Instruc_arr, int num_instructions){
    for(int i = 0; i < num_instructions; i++){
        printf("instruction name: %s\n", Instruc_arr[i].name);
        printf("Input 1: %p\n", Instruc_arr[i].input_regs[0]);
        printf("Input 2: %p\n", Instruc_arr[i].input_regs[1]);
        printf("Ouput: %p\n", Instruc_arr[i].output_reg);
    }
}

void isMemoryAllocated(void* pointer){
    if(pointer != NULL){
        printf("memory alocated!\n");
    }else{
        printf("error in allocate memory!\n");
    }
}

void print_instruc_arr(Instruction* i, int limit){
    for(int j = 0; j < limit; j++){
        printf("Instruction %d -> name: %s | code: %s ptr_func: %p\n", j + 1, i[j].name, i[j].code, i->ptr_to_func);
    }
}

void populate_instruc_arr(Expression* exp, const char* instruc_input[]){
    int limit = exp->num_instructions;
    exp->Instruc_arr = malloc(sizeof(Instruction) * limit);
    isMemoryAllocated(exp->Instruc_arr);
    int index = 0;
    while(index < limit){
        //dont forget to create a function to count how many elements has instruc_list[] 
        for(int i = 0; i < 10; i++){// 10 is the current number of elements of instruc_list[]
            if(strcmp(instruc_list[i].name, instruc_input[index]) == 0){
                exp->Instruc_arr[index].name = instruc_list[i].name;
                exp->Instruc_arr[index].code = instruc_list[i].code;
                exp->Instruc_arr[index].ptr_to_func = instruc_list[i].ptr_to_func;
                index++;
                break;
            }
        }
    }
    print_instruc_arr(exp->Instruc_arr, limit);
}

void calc_fitness_first_pop(Population* pop){
    for(int i = 0; i < pop->size; i++){
        pop->chromosomes[i].fitness = fitness_func(&(pop->chromosomes[i]), pop->e);
    }
    find_best_fitness_of_pop(pop);
    find_best_chrom_of_pop(pop);
}
//================================Utility Functions================================================

//================================Expressions Names Arrays============================================
//F1: D = A + B
const char* f1[2] = {"add", "mov"};
//F2: D = A % B
const char* f2[2] = {"module", "mov"};
//F3: D = (A + B) - (B + C)
const char* f3[4] = {"add", "add", "sub", "mov"};
//F4: D = IF(A + B > C) THEN 1 ELSE 0
const char* f4[4] = {"add", "greater_than", "if_function", "mov"};
//F4: D = IF (A == B+1 && B == C+1) THEN 1 ELSE 0
const char* f5[7] = {"increment", "is_equal", "increment", "is_equal", "and_function", "if_function", "mov"};
//================================Expressions Names Arrays============================================



//================================Expression Generators============================================
//F1: D = A + B
//f1[2] = {"add", "mov"};
Expression* generate_f1(Population* pop){
    //sum, mov 
    printf("\nInside generate_f1\n");
    const char** ptr_f1 = f1;
    Expression* exp = malloc(sizeof(Expression));
    isMemoryAllocated(exp);
    exp->num_instructions = sizeof(f1) / sizeof(f1[0]);
    printf("num_instructions: %d\n", exp->num_instructions);
    exp->registers = malloc(sizeof(int) * NUM_REG);
    isMemoryAllocated(exp->registers);
    populate_instruc_arr(exp, ptr_f1);
    exp->perfect_chrom = generate_perfect_chrom(exp);
    calc_fitness_first_pop(pop);
    //sum
    exp->Instruc_arr[0].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[0].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[1].output_reg = &exp->registers[3];
    exp->Instruc_arr[0].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[0].output_reg = &exp->registers[0];
    
    //mov
    exp->Instruc_arr[1].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[1].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[1].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    print_registers_address(exp->Instruc_arr, exp->num_instructions);
    return exp;
}

//F2: D = A % B
//f2[2] = {"module", "mov"};
Expression* generate_f2(Population* pop){
    //sum, mov 
    const char** ptr_f2 = f2;
    Expression* exp = malloc(sizeof(Expression));
    isMemoryAllocated(exp);
    exp->num_instructions = sizeof(f2) / sizeof(f2[0]);
    printf("num_instructions: %d\n", exp->num_instructions);
    exp->registers = malloc(sizeof(int) * NUM_REG);
    isMemoryAllocated(exp->registers);
    populate_instruc_arr(exp, ptr_f2);
    exp->perfect_chrom = generate_perfect_chrom(exp);
    calc_fitness_first_pop(pop);
    //mod
    exp->Instruc_arr[0].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[0].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[0].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[0].output_reg = &exp->registers[0];
    
    //mov
    exp->Instruc_arr[1].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[1].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[1].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[1].output_reg = &exp->registers[3];
    print_registers_address(exp->Instruc_arr, exp->num_instructions);
    return exp;
}

//F3: D = (A + B) - (B + C)
//f3[2] = {"add", "add", "sub", "mov"};
Expression* generate_f3(Population* pop){
    //sum, mov 
    printf("\nInside generate_f3\n");
    const char** ptr_f3 = f3;
    Expression* exp = malloc(sizeof(Expression));
    isMemoryAllocated(exp);
    exp->num_instructions = sizeof(f3) / sizeof(f3[0]);
    printf("num_instructions: %d\n", exp->num_instructions);
    exp->registers = malloc(sizeof(int) * NUM_REG);
    isMemoryAllocated(exp->registers);
    populate_instruc_arr(exp, ptr_f3);
    exp->perfect_chrom = generate_perfect_chrom(exp);
    calc_fitness_first_pop(pop);
    //sum
    exp->Instruc_arr[0].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[0].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[0].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[0].output_reg = &exp->registers[0];
    
    //sum
    exp->Instruc_arr[1].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[1].input_regs[0] = &exp->registers[1]; //registers[0] = regA
    exp->Instruc_arr[1].input_regs[1] = &exp->registers[2]; //registers[1] = regB
    exp->Instruc_arr[1].output_reg = &exp->registers[1];
    
    //sub
    exp->Instruc_arr[2].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[2].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[2].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[2].output_reg = &exp->registers[0];
    
    //mov
    exp->Instruc_arr[3].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[3].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[3].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[3].output_reg = &exp->registers[3];
    print_registers_address(exp->Instruc_arr, exp->num_instructions);
    return exp;
}


Expression* generate_f4(Population* pop){
    printf("\nInside generate_f4\n");
    const char** ptr_f4 = f4;
    Expression* exp = malloc(sizeof(Expression));
    isMemoryAllocated(exp);
    exp->num_instructions = sizeof(f4) / sizeof(f4[0]);
    printf("num_instructions: %d\n", exp->num_instructions);
    exp->registers = malloc(sizeof(int) * NUM_REG);
    isMemoryAllocated(exp->registers);
    populate_instruc_arr(exp, ptr_f4);
    exp->perfect_chrom = generate_perfect_chrom(exp);
    calc_fitness_first_pop(pop);
    //add
    exp->Instruc_arr[0].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[0].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[0].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[0].output_reg = &exp->registers[0];

    //greather_than
    exp->Instruc_arr[1].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[1].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[1].input_regs[1] = &exp->registers[2]; //registers[1] = regB
    exp->Instruc_arr[1].output_reg = &exp->registers[0];
    
    //"if_function"
    exp->Instruc_arr[2].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[2].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[2].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[2].output_reg = &exp->registers[0];
    
    //mov
    exp->Instruc_arr[3].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[3].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[3].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[3].output_reg = &exp->registers[3];
    print_registers_address(exp->Instruc_arr, exp->num_instructions);
    return exp;
}

Expression* generate_f5(Population* pop){
    printf("\nInside generate_f5\n");
    const char** ptr_f5 = f5;
    Expression* exp = malloc(sizeof(Expression));
    isMemoryAllocated(exp);
    exp->num_instructions = sizeof(f5) / sizeof(f5[0]);
    printf("num_instructions: %d\n", exp->num_instructions);
    exp->registers = malloc(sizeof(int) * NUM_REG);
    isMemoryAllocated(exp->registers);
    populate_instruc_arr(exp, ptr_f5);
    exp->perfect_chrom = generate_perfect_chrom(exp);
    calc_fitness_first_pop(pop);
    //increment
    exp->Instruc_arr[0].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[0].input_regs[0] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[0].input_regs[1] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[0].output_reg = &exp->registers[1];
    
    //is_equal
    exp->Instruc_arr[1].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[1].input_regs[0] = &exp->registers[0]; //registers[1] = regA
    exp->Instruc_arr[1].input_regs[1] = &exp->registers[1]; //registers[0] = regB
    exp->Instruc_arr[1].output_reg = &exp->registers[0];
    
    //increment
    exp->Instruc_arr[2].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[2].input_regs[0] = &exp->registers[2]; //registers[1] = regB
    exp->Instruc_arr[2].input_regs[1] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[2].output_reg = &exp->registers[2];
    
    //is_equal
    exp->Instruc_arr[3].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[3].input_regs[0] = &exp->registers[1]; //registers[1] = regA
    exp->Instruc_arr[3].input_regs[1] = &exp->registers[2]; //registers[0] = regB
    exp->Instruc_arr[3].output_reg = &exp->registers[1];
    
    //and_function
    exp->Instruc_arr[4].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[4].input_regs[0] = &exp->registers[0]; //registers[1] = regA
    exp->Instruc_arr[4].input_regs[1] = &exp->registers[1]; //registers[0] = regB
    exp->Instruc_arr[4].output_reg = &exp->registers[0];
    
    //"if_function"
    exp->Instruc_arr[5].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[5].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[5].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[5].output_reg = &exp->registers[0];
    
    //mov
    exp->Instruc_arr[6].input_regs = malloc(sizeof(int*) * NUM_INPUTS);
    exp->Instruc_arr[6].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[6].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[6].output_reg = &exp->registers[3];//registers[3] = regD
    print_registers_address(exp->Instruc_arr, exp->num_instructions);
    return exp;
}
//================================Expression Generators============================================
