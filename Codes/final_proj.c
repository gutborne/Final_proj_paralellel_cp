#include "final_proj.h"
#include <mpi.h>
#include <locale.h>

//F1: D = A + B
const char* f1[2] = {"add", "mov"}; //num
//F2: D = A % B
const char* f2[2] = {"module", "mov"};
//F3: D = (A + B) - (B + C)
const char* f3[4] = {"add", "add", "sub", "mov"};
//F4: D = IF(A + B > C) THEN 1 ELSE 0
const char* f4[4] = {"add", "greater_than", "if_function", "mov"};
//F4: D = IF (A == B+1 && B == C+1) THEN 1 ELSE 0
const char* f5[7] = {"increment", "is_equal", "increment", "is_equal", "and_function", "if_function", "mov"};

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

int count_instructionsf1(){ 
    int number_instructions = sizeof(f1)/sizeof(f1[0]);
    printf("\nnumber of instructions: %d\n", number_instructions);
    return number_instructions;
}
int count_instructionsf2(){ 
    int number_instructions = sizeof(f2)/sizeof(f2[0]);
    printf("\nnumber of instructions: %d\n", number_instructions);
    return number_instructions;
}

int count_instructionsf3(){ 
    int number_instructions = sizeof(f3)/sizeof(f3[0]);
    printf("\nnumber of instructions: %d\n", number_instructions);
    return number_instructions;
}

int count_instructionsf4(){ 
    int number_instructions = sizeof(f4)/sizeof(f4[0]);
    printf("\nnumber of instructions: %d\n", number_instructions);
    return number_instructions;
}

int count_instructionsf5(){ 
    int number_instructions = sizeof(f5)/sizeof(f5[0]);
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
    while(index < limit){
        //dont forget to create a function to count how many elements has instruc_list[] 
        for(int i = 0; i < 10; i++){// 8 is the current number of elements of instruc_list[]
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

void populate_registers(int* registers, int A, int B, int C, int D){
    registers[0] = A, registers[1] = B, registers[2] = C, registers[3] = D;
    /*
    for(int i = 0; i < NUM_REG; i++){
        printf("&register[%d] = %p\n", i + 1, registers + i);
    }
    */
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
    exp->num_instructions = count_instructionsf1();
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

//F2: D = A % B
//f2[2] = {"module", "mov"};
Expression* generate_f2(){
    //sum, mov 
    const char** ptr_f2 = f2;
    Expression* exp = malloc(sizeof(Expression));
    isMemoryAllocated(exp);
    exp->num_instructions = count_instructionsf2();
    exp->registers = malloc(sizeof(int) * NUM_REG);
    isMemoryAllocated(exp->registers);
    populate_instruc_arr(exp, ptr_f2);
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
Expression* generate_f3(){
    //sum, mov 
    printf("\nInside generate_f3\n");
    const char** ptr_f3 = f3;
    Expression* exp = malloc(sizeof(Expression));
    isMemoryAllocated(exp);
    exp->num_instructions = count_instructionsf3();
    exp->registers = malloc(sizeof(int) * NUM_REG);
    isMemoryAllocated(exp->registers);
    populate_instruc_arr(exp, ptr_f3);
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


Expression* generate_f4(){
    printf("\nInside generate_f4\n");
    const char** ptr_f4 = f4;
    Expression* exp = malloc(sizeof(Expression));
    isMemoryAllocated(exp);
    exp->num_instructions = count_instructionsf4();
    exp->registers = malloc(sizeof(int) * NUM_REG);
    isMemoryAllocated(exp->registers);
    populate_instruc_arr(exp, ptr_f4);
    
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

Expression* generate_f5(){
    printf("\nInside generate_f5\n");
    const char** ptr_f5 = f5;
    Expression* exp = malloc(sizeof(Expression));
    isMemoryAllocated(exp);
    exp->num_instructions = count_instructionsf5();
    exp->registers = malloc(sizeof(int) * NUM_REG);
    isMemoryAllocated(exp->registers);
    populate_instruc_arr(exp, ptr_f5);
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

int check_best_chrom(Population* p){
    int num_instructions = p->e->num_instructions;
    char* chrom_benchmark = malloc(sizeof(char) * (num_instructions * NUM_BITS+1));
    int index_chrom = 0;
    for(int i = 0; i < num_instructions; i++){
        for(int j = 0; j < NUM_BITS; j++){
            chrom_benchmark[index_chrom] = p->e->Instruc_arr[i].code[j];
            index_chrom++;
        }
    }
    chrom_benchmark[index_chrom] = '\0';
    printf("%s\n", chrom_benchmark);
    for(int i = 0; i < num_instructions * NUM_BITS; ){
        if(chrom_benchmark[i] == p->best_chromosome.bin_arr[i] + '0'){
            i++;
        }else{
            printf("not equal!\n");
            return FALSE;
        }
    }
    return TRUE;
}
void helper_fill_exp_str_with_vals(char* aux_exp_str, int reg, int* ptr_j){
    //printf("inside helper_fill_exp_str_with_vals\n");
    char str[10];
    sprintf(str, "%d", reg);
    //printf("str: %s\n", str);
    int i = 0;
    //printf("before while -> i: %d j: %d\n", i, *ptr_j);
    while(str[i] != '\0'){
        aux_exp_str[*ptr_j] = str[i];
        i++;
        (*ptr_j)++; 
        //printf("i: %d j: %d\n", i, *ptr_j);
    }
    aux_exp_str[*ptr_j] = '\0';
    //printf("aux_exp_str: %s\n", aux_exp_str);
}
char* fill_exp_str_with_vals(char* exp_string, int regA, int regB, int regC, int regD){
    //printf("inside fill function\n");
    int i = 0, size = 0, j = 0;
    int* ptr_j = &j;
    while(exp_string[i] != '\0'){ size++; i++; }
    char* aux_exp_str = malloc(sizeof(char) * (size * 20));
    i = 0; 
    while(exp_string[i] != '\0'){
        if(exp_string[i] != 'A' && exp_string[i] != 'B' &&  exp_string[i] != 'C'  && exp_string[i] != 'D'){
            aux_exp_str[j] = exp_string[i];
            i++; 
            j++;
            continue;
        }
        if(exp_string[i] == 'A') helper_fill_exp_str_with_vals(aux_exp_str, regA, &j);
        if(exp_string[i] == 'B') helper_fill_exp_str_with_vals(aux_exp_str, regB, &j); 
        if(exp_string[i] == 'C') helper_fill_exp_str_with_vals(aux_exp_str, regC, &j);
        if(exp_string[i] == 'D') helper_fill_exp_str_with_vals(aux_exp_str, regD, &j); 
        i++;
    }
    aux_exp_str[j] = '\0';
    //printf("%s\n", aux_exp_str);
    return aux_exp_str;
}
void test_benchmark_with_values(Population* pop, int correct_answer, int regA, int regB, int regC, char* exp_string){
    Expression* exp = pop->e;
    int num_instructions = pop->e->num_instructions;
    int* input1;
    int* input2;
    char *is_correct = NULL;
    char* exp_string_with_values = NULL;
    for(int i = 0; i < num_instructions; i++){
        input1 = exp->Instruc_arr[i].input_regs[0];
        //printf("&input1: %p *input1: %d\n", exp->Instruc_arr[i].input_regs[0], *exp->Instruc_arr[i].input_regs[0]);
        input2 = exp->Instruc_arr[i].input_regs[1];
        //printf("&input2: %p *input2: %d\n", exp->Instruc_arr[i].input_regs[1], *exp->Instruc_arr[i].input_regs[1]);
        *(exp->Instruc_arr[i].output_reg) = exp->Instruc_arr[i].ptr_to_func(*input1, *input2);
        //printf("output[%d]: %p *output[%d]: %d\n", i, exp->Instruc_arr[i].output_reg, i, *(exp->Instruc_arr[i].output_reg));
    }
    //is_correct = (*exp->Instruc_arr[i].output_reg == correct_answer)? "correct": "incorrect";
    if(exp->registers[3] == correct_answer) is_correct = "correct";
    else "incorrect";
    exp_string_with_values = fill_exp_str_with_vals(exp_string, regA, regB, regC, correct_answer);
    printf("      %s               |         %d         |       %s    \n", exp_string_with_values, exp->registers[3], is_correct);
}

int main(){
    setlocale(LC_ALL, "");
    srand((unsigned)time(NULL));
    Population pop; //Initial population
    pop.size = 150; 
    pop.generation = 1;
    int chromosome_size;
    pop.chromosomes = malloc(sizeof(Chromosome) * pop.size);
    isMemoryAllocated(pop.chromosomes);
    printf("\n====================================================================================\n");
    printf("                            CHOOSE AN OPTION OF BENCHMARK\n");
    printf("======================================================================================\n");
    int answer = 5;
    int num_instructions = 0;
    int correct_answer = 0;
    int isBestChrom = 0;
    int values_to_regA[] = {10, 3, 10, 9, 100, 32, 40, 54, 23, 62};
    int values_to_regB[] = {15, 36, 2, 9, 12, 24, 54, 23, 11, 7};
    int values_to_regC[] = {5, 13, 24, 39, 52, 62, 55, 33, 21, 50};
    int regA = 0, regB = 0, regC = 0;
    char* exp_string  = NULL; 
    switch(answer){
        case 1:
            exp_string = "D = A + B"; //expression
            chromosome_size = 16;
            initialize_population(&pop, chromosome_size);
            print_population(&pop);
            pop.e = generate_f1(); //sum, mov
            num_instructions = pop.e->num_instructions;
            genetic_alg(&pop);
            isBestChrom = check_best_chrom(&pop);
            if(isBestChrom){
                printf("%s(correct answer)      |       GA ANSWER       |       CORRECTNESS   \n", exp_string);
                for(int i = 0; i < sizeof(values_to_regA)/sizeof(values_to_regA[0]); i++){
                    populate_registers(pop.e->registers, values_to_regA[i], values_to_regB[i], 0, 0); //A, B, C, D
                    correct_answer = values_to_regA[i] + values_to_regB[i];
                    regA = values_to_regA[i];
                    regB = values_to_regB[i];
                    test_benchmark_with_values(&pop, correct_answer, regA, regB, 0, exp_string);
                }
            }else{
                printf("Not equal! Not the best chrom!\n");
            }
            break;
        case 2:
            exp_string = "D = A % B"; //expression
            chromosome_size = 16;
            initialize_population(&pop, chromosome_size);
            print_population(&pop);
            pop.e = generate_f2(); //mod, mov
            num_instructions = pop.e->num_instructions;
            genetic_alg(&pop);
            isBestChrom = check_best_chrom(&pop);
            if(isBestChrom){
                printf("%s(correct answer)      |       GA ANSWER       |       CORRECTNESS   \n", exp_string);
                for(int i = 0; i < sizeof(values_to_regA)/sizeof(values_to_regA[0]); i++){
                    populate_registers(pop.e->registers, values_to_regA[i], values_to_regB[i], 4, 0); //A, B, C, D
                    correct_answer = values_to_regA[i] % values_to_regB[i];
                    regA = values_to_regA[i];
                    regB = values_to_regB[i];
                    test_benchmark_with_values(&pop, correct_answer, regA, regB, 0, exp_string);
                }
            }else{
                printf("Not equal! Not the best chrom!\n");
            }
            break;
        case 3:
            exp_string = "D = (A + B) - (B + C)"; //expression
            chromosome_size = 16;
            initialize_population(&pop, chromosome_size);
            print_population(&pop);
            pop.e = generate_f3(); //
            num_instructions = pop.e->num_instructions;
            genetic_alg(&pop);
            isBestChrom = check_best_chrom(&pop);
            if(isBestChrom){
                printf("%s(correct answer)      |       GA ANSWER       |       CORRECTNESS   \n", exp_string);
                for(int i = 0; i < sizeof(values_to_regA)/sizeof(values_to_regA[0]); i++){
                    populate_registers(pop.e->registers, values_to_regA[i], values_to_regB[i], values_to_regC[i], 0); //A, B, C, D
                    correct_answer = (values_to_regA[i] + values_to_regB[i]) - (values_to_regB[i] + values_to_regC[i]);
                    regA = values_to_regA[i];
                    regB = values_to_regB[i];
                    regC = values_to_regC[i];
                    test_benchmark_with_values(&pop, correct_answer, regA, regB, regC, exp_string);
                }
            }else{
                printf("Not equal! Not the best chrom!\n");
            }
            break;
        case 4:
            exp_string = "D = IF(A + B > C) THEN 1 ELSE 0"; //expression
            chromosome_size = 16;
            initialize_population(&pop, chromosome_size);
            print_population(&pop);
            pop.e = generate_f4(); //"add", "greater_than", "if_function", "mov"
            num_instructions = pop.e->num_instructions;
            genetic_alg(&pop);
            isBestChrom = check_best_chrom(&pop);
            if(isBestChrom){
                printf("%s(correct answer)      |       GA ANSWER       |       CORRECTNESS   \n", exp_string);
                for(int i = 0; i < sizeof(values_to_regA)/sizeof(values_to_regA[0]); i++){
                    populate_registers(pop.e->registers, values_to_regA[i], values_to_regB[i], values_to_regC[i], 0); //A, B, C, D
                    correct_answer = ((values_to_regA[i] + values_to_regB[i]) > values_to_regC[i])? 1: 0;
                    regA = values_to_regA[i];
                    regB = values_to_regB[i];
                    regC = values_to_regC[i];
                    test_benchmark_with_values(&pop, correct_answer, regA, regB, regC, exp_string);
                }
            }else{
                printf("Not equal! Not the best chrom!\n");
            }
            break;
        case 5:
            exp_string = "D = IF(A == B+1 && B == C+1) THEN 1 ELSE 0"; //expression
            chromosome_size = 28;
            initialize_population(&pop, chromosome_size);
            print_population(&pop);
            pop.e = generate_f5(); //increment, is_equal, increment, is_equal, and_function, if_function, mov
            num_instructions = pop.e->num_instructions;
            genetic_alg(&pop);
            isBestChrom = check_best_chrom(&pop);
            if(isBestChrom){
                printf("%s(correct answer)      |       GA ANSWER       |       CORRECTNESS   \n", exp_string);
                for(int i = 0; i < sizeof(values_to_regA)/sizeof(values_to_regA[0]); i++){
                    populate_registers(pop.e->registers, values_to_regA[i], values_to_regB[i], values_to_regC[i], 0); //A, B, C, D
                    int a = values_to_regA[i], b = values_to_regB[i], c = values_to_regC[i];
                    b++;
                    c++;
                    correct_answer = (a == b && b == c)? 1: 0; 
                    regA = values_to_regA[i];
                    regB = values_to_regB[i];
                    regC = values_to_regC[i];
                    test_benchmark_with_values(&pop, correct_answer, regA, regB, regC, exp_string);
                }
            }else{
                printf("Not equal! Not the best chrom!\n");
            }
            break;
    }
    return 0;
}


