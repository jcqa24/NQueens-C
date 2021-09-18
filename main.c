#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct gen{
	int fitness;
	int * config;
};typedef struct gen Gen;


int size;


void ordena(Gen * lista,int TAM){
Gen temp;
int i,j;	
for (i=1;i<TAM;i++)
{
	for (j=0;j<TAM-1;j++)
	{
		if (lista[j].fitness > lista[j+1].fitness)	 //condicion
		{
			temp = lista[j];	 //temp guarda momentaneamente el valor de lista[j]
			lista[j]=lista[j+1];  //Asigno al la posicion lista[j], lo que hay en lista[j+1]
			lista[j+1]=temp;	//obtendra un nuevo valor por parte de temp.
		}
	}

}

}




int * InitConf(int N){
	int * conf = (int*) malloc(sizeof(int)* N);
	int pos;
	int i;
	
	srand(time(NULL)); 

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





void shuffle(Gen * population, int N){
	int i, j;
	Gen temp;
	int c = 0; //contador de cambios;
	int nc = rand() % ((N+1)/2); //numero de cambios 
	while(c <= nc){
		srand (time(NULL));
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
void Crossover(Gen * parents,Gen * population,int N,int nc){
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
		population[n].config = p1;
        population[n+1].config =p2;
	}
}


void selectChampionship(Gen * parents, Gen * population, int N,int np){
	int c = 0; // contador de cambios
	int i,j;
	while( c < np){
		srand (time(NULL));
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
	int N;
	int p,np; // size of population and size of parents
	Gen Best;
	printf("Agoritmo genetico para N reinias \n");
	int numMaxGen=100|0; // Numero Maximo de Generaciones
	int countGen = 0; //Contador de Generaciones
	
	// reinas
	N = 8;	
	p = 100;
	np = p/2;
	size = p;
	printf("Numero de Reinas -> %d\n",N);
	printf("Poblacion inicial -> %d\n",p);
	

	Gen * population = (Gen *)malloc(sizeof(Gen)*p);
	Gen * parents = (Gen *)malloc(sizeof(Gen)*np);

	for (int i = 0; i < p; i++){
		population[i].config = (int *) malloc(sizeof(int)*N);
		population[i].config = InitConf(N);
	        population[i].fitness = calFit(population[i].config,N);
	}

	Best = population[0];

	while((Best.fitness) != 0  && (countGen <= numMaxGen) ){
		
	for (int i = 0; i < p; i++){
	        population[i].fitness = calFit(population[i].config,N);
	}
		ordena(population,p);
		if (Best.fitness >= population[0].fitness){
			Best = population[0] ;
		}

		selectChampionship(parents,population,N,np);

		Crossover(parents,population,N,np);
		
		
		for(int i = np;i<p;i++){
			population[i].config = parents[i-np].config;
		}

		countGen++;
	}


	printf("\n\n=============================================\n");
	printf("La mejor solucion tiene un fit de %d \n",Best.fitness);
	printConf(Best.config,N);
	printf("\n===============================================\n");
    
	


	return 0;
}
