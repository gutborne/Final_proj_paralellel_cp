#ifndef FINAL_PROJ_H
#define FINAL_PROJ_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 0

typedef struct CHROMOSOME Chromosome;
typedef struct POPULATION Population;

typedef struct CHROMOSOME{
    double* double_arr; 
    int* bin_arr;
    int regA, regB, regC, regD;
    double fitness;
    int size; // Number of elements in the chromosome
}Chromosome;

typedef struct POPULATION{
    Chromosome* chromosomes; // Pointer to an array of chromosomes
    int size; // Number of chromosomes in the population
    int generation; // Current generation number
    double best_fitness; // Best fitness value in the population
    Chromosome best_chromosome; // Best chromosome in the population
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
 * @param reg 
 * @param value 
 */
void mov(int* reg, int value);

/**
 * @brief this function mutates a chromosome.
 * @param chromosome_n 
 */
void mutation(Chromosome* chromosome_n);

/**
 * @brief this function increments a register by 1.
 * @param reg 
 */
void increment(int* reg);

/**
 * @brief this function decrements a register by 1.
 * @param reg 
 */
void decrement(int* reg);


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
