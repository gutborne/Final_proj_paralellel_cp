#ifndef FINAL_PROJ_H
#define FINAL_PROJ_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define NUM_REG 4
#define INPUTS 2
typedef struct {
    int* regA;
    char name;
}ptrRegA;
typedef struct {
    int* regB;
    char name;
}ptrRegB;
typedef struct {
    int* regC;
    char name;
}ptrRegC;
typedef struct {
    int* regD;
    char name;
}ptrRegD;


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
    Instruction* Instruc_output;
    int num_instructions; //how many instructions the expression has
    int result;
}Expression;

typedef struct CHROMOSOME{
    double* double_arr; 
    int* bin_arr;
    double fitness;
    int size; // Number of elements in the chromosome
}Chromosome;

typedef struct POPULATION{
    Chromosome* chromosomes; // Pointer to an array of chromosomes
    int size; // Number of chromosomes in the population
    int generation; // Current generation number
    double best_fitness; // Best fitness value in the population
    Chromosome best_chromosome; // Best chromosome in the population
    Expression expression;
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
void mutation(Chromosome* chromosome_n);

/**
 * @brief Performs crossover between two parent chromosomes to create two child chromosomes.
 * @param parent1 Pointer to the first parent chromosome.
 * @param parent2 Pointer to the second parent chromosome.
 */
void crossover(Chromosome* parent1, Chromosome* parent2);

/**
 * @brief Performs selection on the population to choose the best chromosomes.
 * @param population Pointer to the population structure.
 */
void selection(Population* population);

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
 * @param validation_chrom Pointer to a chromosome used for validation.
 */
void fitness_func(Population* population, Chromosome* validation_chrom); 
//================================GA Functions================================================
#endif
