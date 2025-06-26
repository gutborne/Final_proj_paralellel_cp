#include "final_proj.h"
// #include <mpi.h>

void print_population(Population* population){
    for(int i = 0; i < population->size; i++){
        printf("%d chrom: ", i + 1);
        for(int j = 0; j < population->chromosomes[i].size; j++) {
            printf("%.3lf ", population->chromosomes[i].double_arr[j]);
        }
        printf("\n");
    }
}
void print_chromosome(Chromosome* chrom){
    printf("===============================================================Validation Chromosome===========================\n");
    printf("Double_arr: ");
    for(int i = 0; i < chrom->size; i++)
        printf("%6.2lf", chrom->double_arr[i]);
    printf("\n");
    printf("Bin_arr: ");
    for(int i = 0; i < chrom->size; i++)
        printf("%6d", chrom->bin_arr[i]);
    printf("\n===============================================================Validation Chromosome===========================\n");
}

void isMemoryAllocated(void* pointer){
    if(pointer != NULL){
        printf("memory alocated!\n");
    }else{
        printf("error in allocate memory!\n");
    }
}
Chromosome* generate_validation(int chromosome_size){
    srand((unsigned) time(NULL));
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

#define MIN_POP_SIZE 10
#define MAX_POP_SIZE 10000
#define MIN_CHROM_SIZE 8
#define MAX_CHROM_SIZE 1024

// Sugestão de tamanho ideal para cada benchmark
int suggest_chromosome_size(int benchmark) {
    switch(benchmark) {
        case 5: return 20; // 4 registradores x 5 bits (para F5)
        case 1: case 2: case 3: case 4: default: return 16; // 4 regs x 4 bits
    }
}

int input_int(const char* msg, int min, int max) {
    int val, valid = 0;
    do {
        printf("%s", msg);
        int res = scanf("%d", &val);
        while(getchar() != '\n'); // Limpa buffer
        if(res != 1 || val < min || val > max) {
            printf("Valor inválido. Digite um número entre %d e %d.\n", min, max);
        } else {
            valid = 1;
        }
    } while(!valid);
    return val;
}

int main() {
    int sair = 0;
    while (!sair) {
        printf("\n\n==================================================\n");
        printf("== Algoritmo Genético para Programação Genética Linear ==\n");

        // Benchmark selection FIRST to sugerir cromossomo ideal
        printf("\nSelecione o benchmark de treino:\n");
        printf("0 - Sair\n");
        printf("1 - F1: A+B-C-D = 0\n");
        printf("2 - F2: (A+B)>0 && C==D\n");
        printf("3 - F3: A %% B == 0\n");
        printf("4 - F4: A=B+1 && B=C+1 && C=D+1\n");
        printf("5 - F5: CH(A) + CH(B) + CH(C) + CH(D) + CH(A) == \"OTIMO\"\n");
        int benchmark = input_int("Opção: ", 0, 5);

        if (benchmark == 0) {
            sair = 1;
            break;
        }

        int suggested_size = suggest_chromosome_size(benchmark);

        int pop_size = input_int("Digite o tamanho da população: ", MIN_POP_SIZE, MAX_POP_SIZE);

        printf("Digite o tamanho do cromossomo (sugestão para esse benchmark: %d): ", suggested_size);
        int chromosome_size = input_int("", MIN_CHROM_SIZE, MAX_CHROM_SIZE);

        // Inicializa structs principais
        Chromosome* validation_chrom = NULL;
        Population population = {0};
        population.best_chromosome.double_arr = NULL;
        population.best_chromosome.bin_arr = NULL;
        population.size = pop_size;
        population.chromosomes = malloc(sizeof(Chromosome) * population.size);

        if (!population.chromosomes) {
            printf("Erro: Falha ao alocar memória para população.\n");
            exit(1);
        }

        initialize_population(&population, chromosome_size);
        print_population(&population);

        validation_chrom = generate_validation(chromosome_size);
        if (validation_chrom) {
            print_chromosome(validation_chrom);
        } else {
            printf("Erro: Falha ao gerar cromossomo de validação.\n");
        }

        FitnessFunc fitness_func;
        switch(benchmark) {
            case 2: fitness_func = fitness_F2; break;
            case 3: fitness_func = fitness_F3; break;
            case 4: fitness_func = fitness_F4; break;
            case 5: fitness_func = fitness_F5; break;
            case 1:
            default: fitness_func = fitness_F1; break;
        }

        genetic_alg(&population, fitness_func);

        printf("\nMelhor fitness: %lf\n", population.best_fitness);
        printf("Melhor cromossomo: ");
        for(int i = 0; i < population.best_chromosome.size; i++){
            printf("%6.2lf ", population.best_chromosome.double_arr[i]);
        }
        printf("\nBinário do melhor cromossomo: ");
        for(int i = 0; i < population.best_chromosome.size; i++){
            printf("%d ", population.best_chromosome.bin_arr[i]);
        }
        printf("\n");

        // Liberação de memória com checagem
        for(int i = 0; i < population.size; i++){
            free(population.chromosomes[i].double_arr);
            free(population.chromosomes[i].bin_arr);
        }
        free(population.chromosomes);

        if (validation_chrom) {
            free(validation_chrom->double_arr);
            free(validation_chrom->bin_arr);
            free(validation_chrom);
        }
    }
    printf("Programa finalizado.\n");
    return 0;
}
