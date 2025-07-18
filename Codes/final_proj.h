#ifndef FINAL_PROJ_H
#define FINAL_PROJ_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define NUM_REG 4
#define NUM_INPUTS 2
#define NUM_BITS 4

typedef struct INSTRUCTION Instruction;
typedef struct EXPRESSION Expression;
typedef struct CHROMOSOME Chromosome;
typedef struct POPULATION Population;
typedef struct INSTRUCTION{
    char* name;
    int(*ptr_to_func)(int, int);
    char* code;
    int** input_regs;
    int* output_reg;
}Instruction;

typedef struct EXPRESSION{
    int* registers;
    Instruction* Instruc_arr;
    //Instruction* Instruc_output;
    int num_instructions; //how many instructions the expression has
    int result;
}Expression;

typedef struct CHROMOSOME{
    double* double_arr; 
    int* bin_arr;
    int fitness;
    int size; // Number of elements in the chromosome
}Chromosome;

typedef struct POPULATION{
    Chromosome* chromosomes; // Pointer to an array of chromosomes
    int size; // Number of chromosomes in the population
    int generation; // Current generation number
    int best_fitness; // Best fitness value in the population
    Chromosome best_chromosome; // Best chromosome in the population
    Expression* e; //Expression
}Population;

//================================Chromosome Instructions========================================
/**
 * @brief this function adds two registers and returns the result.
 * @param regA 
 * @param regB 
 * @return int 
 */
int add(int regA, int regB);

/**
 * @brief this function subtracts regB from regA and returns the result.
 * @param regA 
 * @param regB 
 * @return int 
 */
int sub(int regA, int regB);

/**
 * @brief this function multiplies two registers and returns the result.
 * @param regA 
 * @param regB 
 * @return int 
 */
int mult(int regA, int regB);

/**
 * @brief this function moves a value into a register.
 * @param value value tha belongs to some register
 * @param x is just a value to standardize the fuctions signatures
 * @return int 
 */
int mov(int value, int x);



/**
 * @brief this function increments an int value from the register by 1.
 * @param reg hold the value that belongs to the register
 * @param x is just a value to standardize the fuctions signatures
 * return int 
 */
int increment(int reg, int x);


/**
 * @brief this function decrements an int value from the register by 1.
 * @param reg hold the value that belongs to the register
 * @param x is just a value to standardize the fuctions signatures
 * return int 
 */
int decrement(int reg, int x);


/**
 * @brief this function checks if regA is greater than regB.
 * @param regA 
 * @param regB 
 * @return int 
 */
int greater_than(int regA, int regB);

/**
 * @brief this function checks if regA is less than regB.
 * @param regA 
 * @param regB 
 * @return int 
 */
int less_than(int regA, int regB);

/**
 * @brief this function calculates the modulus of regA by regB.
 * @param regA 
 * @param regB 
 * @return int 
 */
int module(int regA, int regB);


/**
 * @brief this function performs a logical AND operation on two registers.
 * @param regA 
 * @param regB 
 * @return int 
 */
int and_function(int regA, int regB);


/**
 * @brief this function checks if regA is equal to 1 or 0
 * @param regA int value
 * @param regB int value just for maintenance of the signature
 * @return int 
 */
int if_function(int regA, int regB);


/**
 * @brief this function checks if regA is equal to RegB.
 * @param regA int value
 * @param regB int value
 * @return int 
 */
int is_equal(int regA, int regB);
//================================Chromosome Instructions========================================

//================================GA Functions================================================

/**
 * @brief Converts the double array of the chromosome to a binary representation. 
 * @param chromosome 
*/
void double_to_bin(Chromosome* chromosome);

/**
 * @brief Mutates a chromosome by applying random changes to its genes.
 * @param chromosome_n Pointer to the chromosome to be mutated.
 */
void mutation(Chromosome* chromosome_n, int num_instructions);

/**
 * @brief Performs crossover between two parent chromosomes to create two child chromosomes.
 * @param parent1 Pointer to the first parent chromosome.
 * @param parent2 Pointer to the second parent chromosome.
 * @param n_instructions number of instructions
 * @param curr_index_chrom index of the current chromosome
 * @return a chromosome
 */
Chromosome crossover(Chromosome* parent1, Chromosome* parent2, int n_instructions, int curr_index_chrom);

/**
 * @brief Prints the population of chromosomes.
 * @param population Pointer to the population structure.
 * return a chromosome
 */
Chromosome selection(Population* population);

/**
 * @brief Runs the genetic algorithm for a specified number of generations.
 * @param population Pointer to the population structure.
 */
void genetic_alg(Population* population);


/**
 * @brief Prints the population of chromosomes.
 * @param population Pointer to the population structure.
 * @param chromosome_size how many elements each chromosome will have.
 */
void initialize_population(Population* population, int chrom_size);


/**
 * @brief Evaluates the fitness of each chromosome in the population.
 * @param population Pointer to the population structure.
 * @param index_curr_chrom index to the current chromosome
 */
void fitness_func(Population* population, int index_curr_chrom); 
//================================GA Functions================================================

//================================Expression Functions========================================
/**
 * @brief generates the expression that will calculate the first bench f1: D = A + B
 * @return an Expression address 
 */
Expression* generate_f1();

/**
 * @brief generates the expression that will calculate the second bench f2: D = A % B
 * @return an Expression address 
 */
Expression* generate_f2();

/**
 * @brief generates the expression that will calculate the third bench f3: D = (A + B) - (B + C)
 * @return an Expression address 
 */
Expression* generate_f3();

/**
 * @brief generates the expression that will calculate the fourth bench f4: D = IF(A + B > C) THEN 1 ELSE 0
 * @return an Expression address 
 */
Expression* generate_f4();

/**
 * @brief generates the expression that will calculate the fifth bench f5: D = IF (A == B+1 && B == C+1) THEN 1 ELSE 0
 * @return an Expression address 
 */
Expression* generate_f5();

//================================Expression Functions========================================

//================================Utility Functions========================================
/**
 * @brief receives an address of any type and checks if the memory was allocated successfully.
 * @param pointer pointer to check if it the address it points to is allocated
 */
void isMemoryAllocated(void* pointer);

/**
 * @brief prints the detailed informations about each element in the instruc_arr.
 * @param Instruc_arr pointer to the instruction array.
 * @param num_instructions how many instructions.
 */
void print_registers_address(Instruction* Instruc_arr, int num_instructions);

/**
 * @brief prints the instruction array with some informations.
 * @param i pointer to the instruction array.
 * @param limit how many instructions to print.
 */
void print_instruc_arr(Instruction* i, int limit);

/**
 * @brief Populates the instruction array with the given instructions.
 * @param exp Pointer to the Expression structure.
 * @param instruc_input Array of strings containing instruction names.
 */
void populate_instruc_arr(Expression* exp, const char* instruc_input[]);
//================================Utility Functions========================================


#endif
