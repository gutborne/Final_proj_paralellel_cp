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

int main(){
    Chromosome* validation_chrom = NULL;//will be used to measure the fitness
    Population population;
    population.best_chromosome.double_arr = NULL;
    population.best_chromosome.bin_arr = NULL;
    population.size = 100;
    int chromosome_size = 19;
    //int is_memory_allocated;
    population.chromosomes = malloc(sizeof(Chromosome) * population.size);
    isMemoryAllocated(population.chromosomes);
    initialize_population(&population, chromosome_size);
    print_population(&population);
    validation_chrom = generate_validation(chromosome_size);
    print_chromosome(validation_chrom);

    int benchmark = 1;
    printf("Selecione o benchmark de treino:\n");
    printf("1 - F1: A+B-C-D = 0\n");
    printf("2 - F2: (A+B)>0 && C==D\n");
    printf("3 - F3: A %% B == 0\n");
    printf("4 - F4: A=B+1 && B=C+1 && C=D+1\n");
    printf("5 - F5: CH(A) + CH(B) + CH(C) + CH(D) + CH(A) == \"OTIMO\"\n");
    printf("Opção: ");
    scanf("%d", &benchmark);

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
    for(int i = 0; i < population.size; i++){
        free(population.chromosomes[i].double_arr);
        free(population.chromosomes[i].bin_arr);
    }
    free(population.chromosomes);

    free(validation_chrom->double_arr);
    free(validation_chrom->bin_arr);
    free(validation_chrom);
    printf("\nBest fitness: %lf", population.best_fitness);
    printf("\n");
    printf("\nBest chromosome: ");
    for(int i = 0; i < population.best_chromosome.size; i++){
        printf("%6.2lf ", population.best_chromosome.double_arr[i]);
    }
    printf("\n");
    printf("\nBest chromosome bin: ");
    for(int i = 0; i < population.best_chromosome.size; i++){
        printf("%d ", population.best_chromosome.bin_arr[i]);
    }
    printf("\n");
    return 0;
}
