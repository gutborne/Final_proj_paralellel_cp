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
    {"greater_than", greater_than, "0101"},
    {"module", module, "0111"},
    {"and_function", and_function, "1000"}
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
        printf("Instruction %d -> name: %s | code: %s ptr_func: %p\n", j + 1, i[j].name, i[j].code, i->ptr_to_func);
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
            exp->Instruc_arr[index].ptr_to_func = instruc_list[i].ptr_to_func;
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
    populate_instruc_arr(exp, ptr_f1);
    //sum
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

//F2: D = IF (A+B > C) THEN 1

//F3: D = A % B 

//F4: D = IF (A = B+1 && B=C+1) THEN 1

//F5: D = (A+B) - (B+C)

int main(){
    srand((unsigned)time(NULL));
    Population pop; //Initial population
    pop.size = 50; 
    int chromosome_size;
    pop.chromosomes = malloc(sizeof(Chromosome) * pop.size);
    isMemoryAllocated(pop.chromosomes);
    printf("\n======================================================================================\n");
    printf("                            CHOOSE AN OPTION OF BENCHAMARK\n");
    printf("======================================================================================\n");
    int answer = 1;
    switch(answer){
        case 1:
            chromosome_size = 16;
            initialize_population(&pop, chromosome_size);
            print_population(&pop);
            pop.e = generate_f1(); //sum, mov
            int num_instructions = pop.e->num_instructions;
            genetic_alg(&pop);
            populate_registers(pop.e->registers, 2, 3, 4, 0); //A, B, C, D
            char* chrom_benchmark = malloc(sizeof(char) * (num_instructions * NUM_BITS+1));
            int index_chrom = 0;
            for(int i = 0; i < num_instructions; i++){
                for(int j = 0; j < NUM_BITS; j++){
                    chrom_benchmark[index_chrom] = pop.e->Instruc_arr[i].code[j];
                    index_chrom++;
                }
            }
            chrom_benchmark[index_chrom] = '\0';
            //printf("%s\n", chrom_benchmark);
            for(int i = 0; i < num_instructions * NUM_BITS; ){
                if(chrom_benchmark[i] == pop.best_chromosome.bin_arr[i] + '0'){
                    i++;
                }else{
                    printf("not equal!\n");
                    break;
                }
            }
            printf("Equal!\n");
            Expression* exp = pop.e;
            int* input1;
            int* input2;
            for(int i = 0; i < num_instructions; i++){
                input1 = exp->Instruc_arr[i].input_regs[0];
                printf("&input1: %p *input1: %d\n", exp->Instruc_arr[i].input_regs[0], *exp->Instruc_arr[i].input_regs[0]);
                input2 = exp->Instruc_arr[i].input_regs[1];
                printf("&input2: %p *input2: %d\n", exp->Instruc_arr[i].input_regs[1], *exp->Instruc_arr[i].input_regs[1]);
                *(exp->Instruc_arr[i].output_reg) = exp->Instruc_arr[i].ptr_to_func(*input1, *input2);
                printf("output[%d]: %p *output[%d]: %d\n", i, exp->Instruc_arr[i].output_reg, i, *(exp->Instruc_arr[i].output_reg));
            }
            printf("\nthe result of expression is: %d", *exp->Instruc_arr[1].output_reg);
            break;
        case 2:
            chromosome_size = 16;
            initialize_population(&pop, chromosome_size);
            genetic_alg(&pop);
            break;
        case 3:
            chromosome_size = 16;
            initialize_population(&pop, chromosome_size);
            genetic_alg(&pop);
            break;
        case 4:
            genetic_alg(&pop);
            initialize_population(&pop, chromosome_size);
            break;
        case 5:
            genetic_alg(&pop);
            initialize_population(&pop, chromosome_size);
            break;
        case 6:
    }
    return 0;
}


