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
int main(){
    Population population;
    population.size = 10;
    population.chromosomes = malloc(sizeof(Chromosome) * population.size);
    if(population.chromosomes != NULL)
        printf("memory alocated!\n");
    else
        printf("error in allocate memory!\n");
    initialize_population(&population);
    print_population(&population);
    return 0;
}
