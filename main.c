#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct gen{
	int fitness;
	int * config; 
};typedef struct gen Gen;


int size;

//merge_sort
void intercambia(int ini, int mid, int fin,Gen *Aaux){
        int i, j, k;
	Gen *temp = (Gen *) malloc(sizeof(Gen)*size);

        i = ini;
        k = ini;
        j = mid + 1;
        while ((i <= mid) && (j <= fin))
        {
                if (Aaux[i].fitness <= Aaux[j].fitness)
                {
                        temp[k].fitness = Aaux[i].fitness;
                        temp[k].config = Aaux[i].config;
                        i++;
                }
                else
                {
                        temp[k].fitness = Aaux[i].fitness;
                        
                        temp[k].config = Aaux[i].config;
                        j++;
                }
                k++;
        }
        if (i > mid)
        {
                for (int h = j; h <= fin; h++)
                {
                       
                        temp[k].fitness = Aaux[i].fitness;
                        temp[k].config = Aaux[i].config;
                        k++;
                }
        }
        else
        {
                for (int h = i; h <= mid; h++)
                {
                        temp[k].fitness = Aaux[i].fitness;
                        temp[k].config = Aaux[i].config;
                        k++;
                }
        }

        for (int h = ini; h <= fin; h++)
        {
                Aaux[h].fitness = temp[h].fitness;
                Aaux[h].config = temp[h].config;
        }
}
void mergesort(int ini, int fin,Gen *Aaux){
        int mid;

        if(ini < fin)
        {
                mid = (ini + fin) / 2;
                mergesort(ini, mid,Aaux);
                mergesort(mid + 1, fin,Aaux);
                intercambia(ini, mid, fin,Aaux);
        }
}




int * InitConf(int N){
	int * conf = (int*) malloc(sizeof(int)* N);
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
				printf(" %c ",'X');
			}else{
				printf(" %c ",'-');
			}
		}
		printf("\n");
	}

}

int  calFit(int * conf, int N){
	int errores = 0;
	int pos;
	for(int i =0;i<N;i++){
		pos = i-conf[i];
		for(int j = 0; j<N; j++){
			if((i != j) && (pos == (j-conf[j]))){
				errores++;
				break;
			}
		}
	}
	
	for(int i =N-1;i>=0;i--){
		pos = i+conf[i];
		for(int j = N-1; j>=0; j--){
			if((i != j) && (pos == (j+conf[j]))){
				errores++;	
				break;
			}
		}
	}
	
	return errores;
}


int main(){
	srand(time(NULL)); 
	int N;
	int p; // size of population

	printf("Agoritmo genetico para N reinias \n");

	// reinas
	N = 8;
	
	p = 100;
	size = p;
	printf("Numero de Reinas -> %d\n",N);
	printf("Poblacion inicial -> %d\n",p);
	

	Gen * population = (Gen *)malloc(sizeof(Gen)*p);

	for (int i = 0; i < p; i++){
		population[i].config = (int *) malloc(sizeof(int)*N);
		population[i].config = InitConf(N);
	        population[i].fitness = calFit(population[i].config,N);
	}
	
	printf("Original\n");

	printConf(population[0].config,N);
	printf("Errores ->> %d\n", population[0].fitness);
    
	mergesort(0,p,population);

	printConf(population[0].config,N);

	for (int i=0; i<p; i++){

		printf("Errores ->> %d\n", population[i].fitness);
	}
    

	return 0;
}
