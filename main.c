#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct Chromosome{
	int fitness;
	int * config;
};typedef struct Chromosome Chromo;


void Insertion_sort(Chromo* population, int np){

    int i, j;
    Chromo temp;

    for (i = 1; i < np; i++) {
        temp = population[i];
        for (j = i; j > 0 && population[j - 1].fitness > temp.fitness; j--) {
            population[j] = population[j - 1];
        }
        population[j] = temp;
    }


}

void InitConf(Chromo * population, int N, int p){

	int pos;
	int i,j,k;

    for (k = 0; k < p; k++){
		population[k].config = (int *) malloc(sizeof(int)*N);
		for (j=0; j<N; j++){
            population[k].config[j] = -1;
        }
        i=0;
        while(i<N){
            pos = rand() % (N); // pos en el arreglo
            if((population[k].config[pos] == -1) && (population[k].config[pos] != i)){
                population[k].config[pos] = i;
                i++;
            }
        }
    }
}





void shuffle(Chromo * population, int N){
	int i, j;
	Chromo temp;
	int c = 0; //contador de cambios;
	int nc = rand() % ((N+1)/2); //numero de cambios
	while(c <= nc){

		i = rand() % (N+1);
		j = rand() % (N+1);
		if ( j != i){
			temp = population[i];
			population[i] = population[j];
			population[j]=temp;
			c++;
		}
	}
}



//Partially Mapped Crossover
void Crossover(Chromo * parents,Chromo * population,int N,int nc){
		//hijos
		int * c1 =(int*)malloc(sizeof(int)*N);
		int * c2 =(int*)malloc(sizeof(int)*N);
		//padres
		int * p1, * p2;
		int flag1;
		int flag2;
		int pos1,pos2;
		int k = N/3;

	for(int n=0; n<(nc-1) ; n=n+2){

		for(int m = 0; m<N;m++){
			c1[m] = -1;
			c2[m] = -1;
		}
		flag1 = 0;
		flag2 = 0;

		p1 = parents[n].config;
		p2 = parents[n+1].config;




		for(int a=k; a<(N-k);a++){
			c1[a]=p2[a];
			c2[a]=p1[a];
		}


		for(int a=0;a<k;a++){
			pos1 = p1[a];
			pos2 = p2[a];
			for(int b = k; b<(N-k);b++){
				if(pos1	== c1[b]){
					flag1 = 1;
				}
				if(pos2 == c2[b]){
					flag2 = 1;
				}
			}
			if(!flag1){
				c1[a] = pos1;
			}
			if(!flag2){
				c2[a] = pos2;
			}
		}

		for(int a=(N-k);a<N;a++){
			pos1 = p1[a];
			pos2 = p2[a];
			for(int b = (N-k); b<N-k;b++){
				if(pos1	== c1[b]){
					flag1 = 1;
				}
				if(pos2 == c2[b]){
					flag2 = 1;
				}
			}
			if(!flag1){
				c1[a] = pos1;
			}
			if(!flag2){
				c2[a] = pos2;
			}
		}
		int count,co;
		for(int a = 0; a<N;a++){
			flag1 = 0;
			count = 0;
			co = 0;
			while((!flag1) && count<N){
				if(a == c1[count]){
					flag1 = 1;
				}
				count++;
			}

			if(!flag1){
				while((c1[co] != -1) && (co<N)){
					co ++;
				}
				c1[co] = a;
			}
			flag1 = 0;
			count = 0;
			co = 0;
			while((!flag1) && count<N){
				if(a == c2[count]){
					flag1 = 1;
				}
				count++;
			}

			if(!flag1){
				while((c2[co] != -1) && (co < N) ){
					co ++;
				}
				c1[co] = a;
			}
		}
		population[n].config = c1;
        population[n+1].config =c2;


	}
}


void selectChampionship(Chromo * parents, Chromo * population, int N,int np){
	int c = 0; // contador de cambios
	int i,j;
	while( c < np){

		i = rand() % (N+1);
		j = rand() % (N+1);
		if( i != j){
			shuffle(population,N);
			if(population[i].fitness <= population[j].fitness){
				parents[c] = population[i];
			}else{
				parents[c] = population[j];
			}
			c++;
		}
	}
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

void  calFit(Chromo * population, int N,int np){
	int errores;
	int pos;
    int k,i;
    for(k = 0; k< np; k++){
        errores = 0;
        for(i =0;i<N;i++){
            pos = i-population[k].config[i];
            for(int j = 0; j<N; j++){
                if((i != j) && (pos == (j-population[k].config[j]))){
                    errores++;
                    break;
                }
            }
        }

        for(i =N-1;i>=0;i--){
            pos = i+population[k].config[i];
            for(int j = N-1; j>=0; j--){
                if((i != j) && (pos == (j+population[k].config[j]))){
                    errores++;
                    break;
                }
            }
        }

        population[k].fitness = errores;

    }
}


void mutation(Chromo * population, int prob, int N, int np){
	int aux, i, p1 = 0, p2 = 0;
	for(i = 0; i<np; i++){
		srand (time(NULL));
		if(rand() % (101) <= prob){
			do{
				p1 = rand() % (N+1);
				p2 = rand() % (N+1);
			}while( p1 == p2);
			aux = population[i].config[p1];
			population[i].config[p1] = population[i].config[p2];
			population[i].config[p2] = aux;

		}
	}

}

int main(){
    srand (time(NULL));
	int N;
	int p,np,prob; // size of population and size of parents
	Chromo Best;
	printf("Agoritmo genetico para N reinias \n");
	int numMaxGen=250; // Numero Maximo de Generaciones
	int countGen = 0; //Contador de Generaciones

	// reinas
	N = 8;
	p = 50;
	np = p/2;

	printf("Numero de Reinas -> %d\n",N);
	printf("Poblacion inicial -> %d\n",p);


	prob = 10 ; //probabilidad de mutacion



	Chromo * population = (Chromo *)malloc(sizeof(Chromo)*p);
	Chromo * parents = (Chromo *)malloc(sizeof(Chromo)*np);

    InitConf(population,N,p);



	Best = population[0];
    Best.fitness = 2*N;
    do{

        calFit(population,N,np);

        printf("====== Antes de ordenar ======\n");
        for(int i = 0;i<p;i++){
			printf("****Hay %d errores\n", population[i].fitness);
		}

		Insertion_sort(population,p);

        printf("====== Despues de ordenar ======\n");
        for(int i = 0;i<p;i++){
			printf("****Hay %d errores\n", population[i].fitness);
		}


		if (population[0].fitness <= Best.fitness  ){
			Best = population[0];
		}

		selectChampionship(parents,population,N,np);

		Crossover(parents,population,N,np);


		for(int i = np;i<p;i++){
			population[i].config = parents[i-np].config;
		}

		mutation(population,prob, N, np);
		countGen++;

        printf("\n\n=============================================\n");
        printf("La mejor solucion tiene un fit de %d \n",Best.fitness);
        printf("La mejor solucion es: [ ");
        for(int i = 0; i<N;i++){
            printf(" %d ", Best.config[i]);
        }
        printf("]\n");
        printConf(Best.config,N);
        printf("\n===============================================\n");

        exit(-1);

	}while((Best.fitness) != 0  && (countGen <= numMaxGen) ) ;


	printf("\n\n=============================================\n");
	printf("La mejor solucion tiene un fit de %d \n",Best.fitness);
    printf("La mejor solucion es: [ ");
    for(int i = 0; i<N;i++){
        printf(" %d ", Best.config[i]);
    }
    printf("]\n");
	printConf(Best.config,N);
	printf("\n===============================================\n");




	return 0;
}
