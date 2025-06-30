#include "final_proj.h"
#include <mpi.h>

//F1: D = A + B
const char* f1[2] = {"add", "mov"};

Instruction instruc_list[] = {
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

void print_population(Population* population){
    
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


void isMemoryAllocated(void* pointer){
    if(pointer != NULL){
        printf("memory alocated!\n");
    }else{
        printf("error in allocate memory!\n");
    }
}

Chromosome* generate_validation(int chromosome_size){
    Chromosome* validation_chrom = malloc(sizeof(Chromosome));
    validation_chrom->size = chromosome_size;
    isMemoryAllocated(validation_chrom);
    validation_chrom->double_arr = malloc(sizeof(double)*chromosome_size);
    validation_chrom->bin_arr = malloc(sizeof(int)*chromosome_size);
    isMemoryAllocated(validation_chrom->double_arr);
    isMemoryAllocated(validation_chrom->bin_arr);
    for(int i = 0; i < chromosome_size; i++){
        validation_chrom->double_arr[i] = (double) rand() / RAND_MAX;
    }
    double_to_bin(validation_chrom);
    return validation_chrom;
}

int count_instructions(){ 
    int number_instructions = sizeof(f1)/sizeof(f1[0]);
    printf("\nnumber of instructions: %d\n", number_instructions);
    return number_instructions;
}

void print_instruc_arr(Instruction* i, int limit){
    for(int j = 0; j < limit; j++){
        printf("Instruction %d -> name: %s | code: %s\n", j + 1, i[j].name, i[j].code);
    }
}
void populate_instruc_arr(Expression* exp, const char* instruc_input[]){
    int limit = exp->num_instructions;
    exp->Instruc_arr = malloc(sizeof(Instruction) * limit);
    isMemoryAllocated(exp->Instruc_arr);
    int index = 0;
    for(int i = 0; i < 10; i++){
        if(index == limit){ break; }
        if(strcmp(instruc_list[i].name, instruc_input[index]) == 0){
            exp->Instruc_arr[index].name = instruc_list[i].name;
            exp->Instruc_arr[index].code = instruc_list[i].code;
            index++;
        }
    }
    print_instruc_arr(exp->Instruc_arr, limit);
}

void populate_registers(int* registers, int A, int B, int C, int D){
    registers[0] = A, registers[1] = B, registers[2] = C, registers[3] = D;
    for(int i = 0; i < NUM_REG; i++){
        printf("&register[%d] = %p\n", i + 1, registers + i);
    }
}

void print_registers_address(Instruction* Instruc_arr, int num_instructions){
    for(int i = 0; i < num_instructions; i++){
        printf("instruction name: %s\n", Instruc_arr[i].name);
        printf("Input 1: %p\n", Instruc_arr[i].input_regs[0]);
        printf("Input 2: %p\n", Instruc_arr[i].input_regs[1]);
        printf("Ouput: %p\n", Instruc_arr[i].output_reg);
    }
}

//F1: D = A + B
//f1[2] = {"add", "mov"};
Expression* generate_f1(){
    //sum, mov 
    printf("\nInside generate_f1\n");
    const char** ptr_f1 = f1;
    Expression* exp = malloc(sizeof(Expression));
    isMemoryAllocated(exp);
    exp->num_instructions = count_instructions();
    exp->registers = malloc(sizeof(int) * NUM_REG);
    isMemoryAllocated(exp->registers);
    populate_registers(exp->registers, 2, 3, 4, 0); //A, B, C, D
    populate_instruc_arr(exp, ptr_f1);
    //sum
    exp->Instruc_arr[0].input_regs = malloc(sizeof(int*) * INPUTS);
    exp->Instruc_arr[0].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[0].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[0].output_reg = &exp->registers[0];
    
    //mov
    exp->Instruc_arr[1].input_regs = malloc(sizeof(int*) * INPUTS);
    exp->Instruc_arr[1].input_regs[0] = &exp->registers[0]; //registers[0] = regA
    exp->Instruc_arr[1].input_regs[1] = &exp->registers[1]; //registers[1] = regB
    exp->Instruc_arr[1].output_reg = &exp->registers[3];
    print_registers_address(exp->Instruc_arr, exp->num_instructions);
    return exp;
}

//F2: D = IF (A+B > C) THEN 1

//F3: D = A % B 

//F4: D = IF (A = B+1 && B=C+1) THEN 1

//F5: D = (A+B) - (B+C)

int main(){
    srand((unsigned)time(NULL));
    //Chromosome* validation_chrom = NULL;//will be used to measure the fitness
    Population pop; //Initial population
    pop.size = 50; 
    int chromosome_size = 16;
    //int is_memory_allocated;
    pop.chromosomes = malloc(sizeof(Chromosome) * pop.size);
    isMemoryAllocated(pop.chromosomes);
    initialize_population(&pop, chromosome_size);
    print_population(&pop);
    //validation_chrom = generate_validation(chromosome_size);
    //print_chromosome(validation_chrom);
    pop.e = generate_f1(); //sum, mov
    pop.e->result = pop.e->registers[0] + pop.e->registers[1];
    printf("\nresult of expression is: %d\n", pop.e->result);
    genetic_alg(&pop);
    return 0;
}


