#ifndef FINAL_PROJ_H
#define FINAL_PROJ_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//================================Genetic Algorithm Functions====================================

/**
 * @brief Converts the double array of the chromosome to a binary representation.
 * @param chromosome Pointer to the chromosome to be converted.
 */
void double_to_bin(Chromosome* chromosome);

/**
 * @brief Mutates a chromosome by applying random changes to its genes.
 * @param chromosome Pointer to the chromosome to be mutated.
 */
void mutation(Chromosome* chromosome);

/**
 * @brief Performs crossover between two parent chromosomes to create two child chromosomes.
 * @param parent1 Pointer to the first parent chromosome.
 * @param parent2 Pointer to the second parent chromosome.
 */
void crossover(Chromosome* parent1, Chromosome* parent2);

/**
 * @brief Performs tournament selection to create a new population of chromosomes.
 * @param population Pointer to the population structure.
 */
void selection(Population* population);

/**
 * @brief Initializes the population with random chromosomes.
 * @param population Pointer to the population structure.
 * @param chrom_size The number of genes in each chromosome.
 */
void initialize_population(Population* population, int chrom_size);

/**
 * @brief Converts a slice of the binary array to an integer.
 * @param bin_arr Pointer to the binary array.
 * @param start Start index.
 * @param n Number of bits.
 * @return Integer value represented by the selected bits.
 */
int bits_to_int(int* bin_arr, int start, int n);

/**
 * @brief Fitness function pointer type. Takes a pointer to a population.
 */
typedef void (*FitnessFunc)(Population*);

/**
 * @brief Fitness function: maximize chromosomes where A + B - C - D = 0.
 */
void fitness_F1(Population* population);

/**
 * @brief Fitness function: maximize chromosomes where (A + B) > 0 and C == D.
 */
void fitness_F2(Population* population);

/**
 * @brief Fitness function: maximize chromosomes where A % B == 0.
 */
void fitness_F3(Population* population);

/**
 * @brief Fitness function: maximize chromosomes where A = B+1, B = C+1, and C = D+1.
 */
void fitness_F4(Population* population);

/**
 * @brief Fitness function: maximize chromosomes where CH(A) + CH(B) + CH(C) + CH(D) + CH(A) == "OTIMO".
 *        Each CH(X) maps register value 0-25 to 'A'-'Z'. Fitness is 1.0 if the string matches "OTIMO", else 0.1.
 */
void fitness_F5(Population* population);

/**
 * @brief Main genetic algorithm loop.
 * @param population Pointer to the population structure.
 * @param fitness_func Pointer to the chosen fitness function.
 */
void genetic_alg(Population* population, FitnessFunc fitness_func);

//================================End of Genetic Algorithm Functions============================
#endif
