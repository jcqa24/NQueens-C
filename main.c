#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct gen{
	double fitness;
	int * config; 
};typedef struct gen Gen;


int * InitConf(int N){
	int * conf = calloc(sizeof(int), N);
	int pos;
	int i;
	

	for(i = 0; i<N ; i++){
		conf[i] = -1;
	}
	i=0;
	while(i<N){
		pos = rand() % (N); // pos en el arreglo
		if((conf[pos] == -1) && (conf[pos] != i)){
			conf[pos] = i;
			i++;
		}
	}


	return conf;
}


void printConf(int * conf, int N){
	for(int i =0; i<N;i++){
		for(int j = 0; j<N;j++){
			if(conf[i] == j){
				printf("%c",'X');
			}else{
				printf("%c",'-');
			}
		}
		printf("\n");
	}

}

int  calFit(int * conf, int N){
	
	
	return 0;
}


int main(){
	srand(time(NULL)); 
	int N;
	int p; // size of population

	printf("Agoritmo genetico para N reinias \n");

	// reinas
	N = 8;
	
	p = 100;
	
	printf("Numero de Reinas -> %d\n",N);
	printf("Poblacion inicial -> %d\n",p);
	

	Gen * population = calloc(sizeof(Gen),p);

	for (int i = 0; i < p; i++){
		population[i].fitness = 0;
		population[i].config = InitConf(N);
	}
	

	printConf(population[0].config,N);
	return 0;
}
