#include "final_proj.h"
#include <mpi.h>

void print_population(Population* population){
    for(int i = 0; i < population->size; i++){
        printf("%d chrom: ", i + 1);
        for(int j = 0; j < population->chromosomes->size; j++){
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
    population.size = 10;
    int chromosome_size = 16;
    //int is_memory_allocated;
    population.chromosomes = malloc(sizeof(Chromosome) * population.size);
    isMemoryAllocated(population.chromosomes);
    initialize_population(&population, chromosome_size);
    print_population(&population);
    validation_chrom = generate_validation(chromosome_size);
    print_chromosome(validation_chrom);
    //genetic_alg(&population);
    return 0;
}
