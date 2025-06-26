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

void mov(int* reg, int value){
    *reg = value;
}

void increment(int* reg){
    *reg += 1;
}

void decrement(int* reg){
    *reg -= 1;
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
//================================Chromosome Instructions========================================

//================================Genetic Algorithm Functions====================================

typedef void (*FitnessFunc)(Population*);

// Converts the double array of a chromosome to its binary representation.
void double_to_bin(Chromosome* chromosome) {
    for (int i = 0; i < chromosome->size; i++) {
        chromosome->bin_arr[i] = (chromosome->double_arr[i] > 0.5) ? 1 : 0;
    }
}

// Converts a set of bits in the binary array to an integer value.
int bits_to_int(int* bin_arr, int start, int n) {
    int value = 0;
    for (int i = 0; i < n; i++) {
        value = (value << 1) | bin_arr[start + i];
    }
    return value;
}

// Applies mutation by flipping a random bit in the chromosome.
void mutation(Chromosome* chromosome) {
    int idx = rand() % chromosome->size;
    chromosome->bin_arr[idx] ^= 1;
    chromosome->double_arr[idx] = chromosome->bin_arr[idx] ? 1.0 : 0.0;
}

// Performs one-point crossover between two parent chromosomes.
void crossover(Chromosome* parent1, Chromosome* parent2) {
    int point = rand() % parent1->size;
    for (int i = point; i < parent1->size; i++) {
        // Swap binary representation
        int tmp_bin = parent1->bin_arr[i];
        parent1->bin_arr[i] = parent2->bin_arr[i];
        parent2->bin_arr[i] = tmp_bin;
        // Swap double representation
        double tmp_double = parent1->double_arr[i];
        parent1->double_arr[i] = parent2->double_arr[i];
        parent2->double_arr[i] = tmp_double;
    }
}

// Tournament selection: creates a new population by selecting the best of two random chromosomes.
void selection(Population* population) {
    Population new_pop;
    new_pop.size = population->size;
    new_pop.generation = population->generation + 1;
    new_pop.chromosomes = malloc(sizeof(Chromosome) * new_pop.size);

    for (int i = 0; i < new_pop.size; i++) {
        int i1 = rand() % population->size;
        int i2 = rand() % population->size;
        Chromosome* best = (population->chromosomes[i1].fitness > population->chromosomes[i2].fitness)
            ? &population->chromosomes[i1] : &population->chromosomes[i2];

        // Deep copy of chromosome
        new_pop.chromosomes[i].size = best->size;
        new_pop.chromosomes[i].double_arr = malloc(sizeof(double) * best->size);
        new_pop.chromosomes[i].bin_arr = malloc(sizeof(int) * best->size);
        for (int j = 0; j < best->size; j++) {
            new_pop.chromosomes[i].double_arr[j] = best->double_arr[j];
            new_pop.chromosomes[i].bin_arr[j] = best->bin_arr[j];
        }
        new_pop.chromosomes[i].fitness = best->fitness;
        new_pop.chromosomes[i].regA = best->regA;
        new_pop.chromosomes[i].regB = best->regB;
        new_pop.chromosomes[i].regC = best->regC;
        new_pop.chromosomes[i].regD = best->regD;
    }

    // Free old population
    for (int i = 0; i < population->size; i++) {
        free(population->chromosomes[i].double_arr);
        free(population->chromosomes[i].bin_arr);
    }
    free(population->chromosomes);

    population->chromosomes = new_pop.chromosomes;
    population->generation = new_pop.generation;
}

// Fitness 1: Maximize chromosomes where A + B - C - D = 0
void fitness_F1(Population* population) {
    for (int i = 0; i < population->size; i++) {
        Chromosome* chrom = &population->chromosomes[i];
        chrom->regA = bits_to_int(chrom->bin_arr, 0, 4);
        chrom->regB = bits_to_int(chrom->bin_arr, 4, 4);
        chrom->regC = bits_to_int(chrom->bin_arr, 8, 4);
        chrom->regD = bits_to_int(chrom->bin_arr, 12, 4);

        int result = chrom->regA + chrom->regB - chrom->regC - chrom->regD;
        chrom->fitness = 1.0 / (1.0 + abs(result));
    }
}

// Fitness 2: Maximize chromosomes where (A + B) > 0 and C == D
void fitness_F2(Population* population) {
    for (int i = 0; i < population->size; i++) {
        Chromosome* chrom = &population->chromosomes[i];
        chrom->regA = bits_to_int(chrom->bin_arr, 0, 4);
        chrom->regB = bits_to_int(chrom->bin_arr, 4, 4);
        chrom->regC = bits_to_int(chrom->bin_arr, 8, 4);
        chrom->regD = bits_to_int(chrom->bin_arr, 12, 4);

        int cond1 = (chrom->regA + chrom->regB) > 0;
        int cond2 = (chrom->regC == chrom->regD);
        chrom->fitness = (cond1 && cond2) ? 1.0 : 0.1;
    }
}

// Fitness 3: Maximize chromosomes where A % B == 0
void fitness_F3(Population* population) {
    for (int i = 0; i < population->size; i++) {
        Chromosome* chrom = &population->chromosomes[i];
        chrom->regA = bits_to_int(chrom->bin_arr, 0, 4);
        chrom->regB = bits_to_int(chrom->bin_arr, 4, 4);

        chrom->fitness = (chrom->regB != 0 && chrom->regA % chrom->regB == 0) ? 1.0 : 0.1;
    }
}

// Fitness 4: Maximize chromosomes where A = B+1, B = C+1, and C = D+1
void fitness_F4(Population* population) {
    for (int i = 0; i < population->size; i++) {
        Chromosome* chrom = &population->chromosomes[i];
        chrom->regA = bits_to_int(chrom->bin_arr, 0, 4);
        chrom->regB = bits_to_int(chrom->bin_arr, 4, 4);
        chrom->regC = bits_to_int(chrom->bin_arr, 8, 4);
        chrom->regD = bits_to_int(chrom->bin_arr, 12, 4);

        int cond = (chrom->regA == chrom->regB + 1) &&
                   (chrom->regB == chrom->regC + 1) &&
                   (chrom->regC == chrom->regD + 1);
        chrom->fitness = cond ? 1.0 : 0.1;
    }
}

// Fitness 5: Maximize chromosomes where CH(A) + CH(B) + CH(C) + CH(D) + CH(A) == "OTIMO"
void fitness_F5(Population* population) {
    const char* TARGET = "OTIMO";
    for (int i = 0; i < population->size; i++) {
        Chromosome* chrom = &population->chromosomes[i];
        // Extrai valores dos registradores (assumindo 4 bits cada)
        chrom->regA = bits_to_int(chrom->bin_arr, 0, 5);
        chrom->regB = bits_to_int(chrom->bin_arr, 5, 5);
        chrom->regC = bits_to_int(chrom->bin_arr, 10, 5);
        chrom->regD = bits_to_int(chrom->bin_arr, 15, 5);

        char str[6] = {0};
        // Mapeia valores 0-25 para 'A'-'Z', senão usa '?'
        str[0] = (chrom->regA >= 0 && chrom->regA < 26) ? ('A' + chrom->regA) : '?';
        str[1] = (chrom->regB >= 0 && chrom->regB < 26) ? ('A' + chrom->regB) : '?';
        str[2] = (chrom->regC >= 0 && chrom->regC < 26) ? ('A' + chrom->regC) : '?';
        str[3] = (chrom->regD >= 0 && chrom->regD < 26) ? ('A' + chrom->regD) : '?';
        str[4] = (chrom->regA >= 0 && chrom->regA < 26) ? ('A' + chrom->regA) : '?';
        str[5] = '\0';

        // Fitness escalonado: +0.18 para cada letra certa (0.1 mínimo, 1.0 máximo)
        int score = 0;
        for (int k = 0; k < 5; k++) {
            if (str[k] == TARGET[k]) score++;
        }
        chrom->fitness = 0.1 + 0.18 * score; // 5 acertos: 1.0, 0 acertos: 0.1

        printf("Chromosome %d: %s, Fitness: %.2f\n", i, str, chrom->fitness);
    }
}

#define NUM_GENERATIONS 100
#define CROSSOVER_RATE 0.8
#define MUTATION_RATE 0.05

// Main loop of the genetic algorithm.
void genetic_alg(Population* population, FitnessFunc fitness_func) {
    for (int gen = 0; gen < NUM_GENERATIONS; gen++) {
        fitness_func(population);
        selection(population);

        // Crossover
        for (int i = 0; i < population->size; i += 2) {
            if (((double)rand() / RAND_MAX) < CROSSOVER_RATE && (i + 1 < population->size)) {
                crossover(&population->chromosomes[i], &population->chromosomes[i + 1]);
            }
        }
        // Mutation
        for (int i = 0; i < population->size; i++) {
            if (((double)rand() / RAND_MAX) < MUTATION_RATE) {
                mutation(&population->chromosomes[i]);
            }
        }

        // Find and save the best chromosome (deep copy)
        double best = 0.0;
        int best_idx = 0;
        for (int i = 0; i < population->size; i++) {
            if (population->chromosomes[i].fitness > best) {
                best = population->chromosomes[i].fitness;
                best_idx = i;
            }
        }
        population->best_fitness = best;
        if (population->best_chromosome.double_arr != NULL) free(population->best_chromosome.double_arr);
        if (population->best_chromosome.bin_arr != NULL) free(population->best_chromosome.bin_arr);

        population->best_chromosome.size = population->chromosomes[best_idx].size;
        population->best_chromosome.fitness = population->chromosomes[best_idx].fitness;
        population->best_chromosome.regA = population->chromosomes[best_idx].regA;
        population->best_chromosome.regB = population->chromosomes[best_idx].regB;
        population->best_chromosome.regC = population->chromosomes[best_idx].regC;
        population->best_chromosome.regD = population->chromosomes[best_idx].regD;

        population->best_chromosome.double_arr = malloc(sizeof(double) * population->chromosomes[best_idx].size);
        population->best_chromosome.bin_arr = malloc(sizeof(int) * population->chromosomes[best_idx].size);
        for (int i = 0; i < population->chromosomes[best_idx].size; i++) {
            population->best_chromosome.double_arr[i] = population->chromosomes[best_idx].double_arr[i];
            population->best_chromosome.bin_arr[i] = population->chromosomes[best_idx].bin_arr[i];
        }
        printf("Generation %d: Best fitness: %lf\n", gen + 1, best);
    }
}

// Initializes the population with random chromosomes.
void initialize_population(Population* population, int chrom_size) {
    srand((unsigned) time(NULL));
    for (int i = 0; i < population->size; i++) {
        population->chromosomes[i].size = chrom_size;
        population->chromosomes[i].double_arr = malloc(sizeof(double) * chrom_size);
        population->chromosomes[i].bin_arr = malloc(sizeof(int) * chrom_size);
        for (int j = 0; j < chrom_size; j++) {
            double rand_val = (double)rand() / RAND_MAX;
            population->chromosomes[i].double_arr[j] = rand_val;
        }
        double_to_bin(&population->chromosomes[i]);
    }
}

//================================ End of Genetic Algorithm Functions ===========================
