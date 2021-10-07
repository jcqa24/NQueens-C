#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Chromosome
{
	int fitness;
	int *config;
};
typedef struct Chromosome Chromo;

void ip(Chromo *population, int p, int N)
{
	for (int j = 0; j < p; j++)
	{
		printf("Gen: %d [ ", j);
		for (int i = 0; i < N; i++)
		{
			printf(" %d ", population[j].config[i] + 1);
		}
		printf("] fitnes ==> %d \n", population[j].fitness);
	}
}

void Insertion_sort(Chromo *population, int p)
{

	int i, j;
	Chromo temp;

	for (i = 1; i < p; i++)
	{
		temp = population[i];
		for (j = i; j > 0 && population[j - 1].fitness > temp.fitness; j--)
		{
			population[j] = population[j - 1];
		}
		population[j] = temp;
	}
}

void InitConf(Chromo *population, int N, int p)
{

	int pos;
	int i, j, k;

	for (k = 0; k < p; k++)
	{
		population[k].config = (int *)malloc(sizeof(int) * N);
		for (j = 0; j < N; j++)
		{
			population[k].config[j] = -1;
		}
		i = 0;
		while (i < N)
		{
			pos = rand() % (N); // pos en el arreglo
			if ((population[k].config[pos] == -1) && (population[k].config[pos] != i))
			{
				population[k].config[pos] = i;
				i++;
			}
		}
	}
}

void shuffle(Chromo *population, int p, int N)
{
	int i, j;
	Chromo temp;
	temp.config = (int *)malloc(sizeof(int) * N);
	int c = 0;					   //contador de cambios;
	int nc = rand() % (p - 2) + 2; //numero de cambios
	while (c <= nc)
	{

		i = rand() % (p);
		j = rand() % (p);
		if (j != i)
		{
			temp = population[i];
			population[i] = population[j];
			population[j] = temp;
			c++;
		}
	}
}

//Partially Mapped Crossover
void Crossover(Chromo *parents, Chromo *population, int N, int np)
{
	//hijos
	int *c1 = (int *)malloc(sizeof(int) * N);
	int *c2 = (int *)malloc(sizeof(int) * N);
	//padres
	int *p1, *p2;
	int flag1;
	int flag2;
	int pos1, pos2;
	int k = N / 3;
	int posnp = np;

	for (int n = 0; (n + 1) < np; n = n + 2)
	{

		//inicializo los hijos
		for (int m = 0; m < N; m++)
		{
			c1[m] = -1;
			c2[m] = -1;
		}
		flag1 = 0;
		flag2 = 0;

		//inicializo los padres

		p1 = parents[n].config;
		p2 = parents[n + 1].config;

		for (int a = k; a < (N - k); a++)
		{
			c1[a] = p2[a];
			c2[a] = p1[a];
		}

		for (int a = 0; a < k; a++)
		{
			flag1 = 0;
			flag2 = 0;
			pos1 = p1[a];
			pos2 = p2[a];
			for (int b = k; b < (N - k); b++)
			{
				if (pos1 == c1[b])
				{
					flag1 = 1;
				}
				if (pos2 == c2[b])
				{
					flag2 = 1;
				}
			}
			if (!flag1)
			{
				c1[a] = pos1;
			}
			if (!flag2)
			{
				c2[a] = pos2;
			}
		}

		for (int a = (N - k); a < N; a++)
		{
			pos1 = p1[a];
			pos2 = p2[a];
			flag1 = 0;
			flag2 = 0;
			for (int b = k; b < (N - k); b++)
			{
				if (pos1 == c1[b])
				{
					flag1 = 1;
				}
				if (pos2 == c2[b])
				{
					flag2 = 1;
				}
			}
			if (!flag1)
			{
				c1[a] = pos1;
			}
			if (!flag2)
			{
				c2[a] = pos2;
			}
		}

		int count, co;
		for (int a = 0; a < N; a++)
		{
			flag1 = 0;
			count = 0;
			co = 0;
			while ((!flag1) && count < N)
			{
				if (a == c1[count])
				{
					flag1 = 1;
				}
				count++;
			}

			if (!flag1)
			{
				while ((c1[co] != -1) && (co < N))
				{
					co = rand() % N;
				}
				c1[co] = a;
			}
			flag1 = 0;
			count = 0;
			co = 0;
			while ((!flag1) && count < N)
			{
				if (a == c2[count])
				{
					flag1 = 1;
				}
				count++;
			}

			if (!flag1)
			{
				while ((c2[co] != -1) && (co < N))
				{
					co = rand() % N;
				}
				c2[co] = a;
			}
		}

		for (int i = 0; i < N; i++)
		{
			population[posnp].config[i] = c1[i];
			population[posnp + 1].config[i] = c2[i];
		}

		posnp = posnp + 2;
	}
}

void selectChampionship(Chromo *parents, Chromo *population, int N, int p)
{

	int j, i, c = 0;

	shuffle(population, p, N); // check

	for (i = 0; i < p; i = i + 2)
	{
		if (population[i].fitness <= population[i + 1].fitness)
		{
			//parents[c] = population[i];
			for (j = 0; j < N; j++)
			{
				parents[c].config[j] = population[i].config[j];
			}
		}
		else
		{
			//parents[c] = population[i + 1];
			for (j = 0; j < N; j++)
			{
				parents[c].config[j] = population[i + 1].config[j];
			}
		}
		c++;
	}
}

void printConf(int *conf, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (conf[i] == j)
			{
				printf(" %c ", 'X');
			}
			else
			{
				printf(" %c ", '-');
			}
		}
		printf("\n");
	}
}

void calFit(Chromo *population, int N, int p)
{
	int errores;
	int k, i, j;
	for (k = 0; k < p; k++)
	{
		errores = 0;
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (i != j)
				{
					if ((population[k].config[i] - i) == (population[k].config[j] - j))
					{
						errores++;
					}
					if ((population[k].config[i] + i) == (population[k].config[j] + j))
					{
						errores++;
					}
				}
			}
		}

		population[k].fitness = errores;
	}
}

void mutation(Chromo *population, int prob, int N, int p)
{
	int aux, i, p1 = 0, p2 = 0;
	for (i = 0; i < p; i++)
	{
		srand(time(NULL));
		if (rand() % (101) <= prob)
		{
			do
			{
				p1 = rand() % (N + 1);
				p2 = rand() % (N + 1);
			} while (p1 == p2);
			aux = population[i].config[p1];
			population[i].config[p1] = population[i].config[p2];
			population[i].config[p2] = aux;
		}
	}
}

int main()
{
	srand(time(NULL));
	int i;
	int N;
	int p, np, prob; // size of population and size of parents

	N = 8;			   // reinas
	p = 50;			   //poplacion incial
	np = p / 2;		   // numero de padres
	prob = 30;		   //probabilidad de mutacion
	int numMaxGen = 250; // Numero Maximo de Generaciones
	int countGen = 0;  //Contador de Generaciones

	Chromo Best;
	Best.config = (int *)malloc(sizeof(int) * N);
	Chromo *population = (Chromo *)malloc(sizeof(Chromo) * p);
	Chromo *parents = (Chromo *)malloc(sizeof(Chromo) * np);

	for (i = 0; i < p; i++)
	{
		population[i].config = (int *)malloc(sizeof(int) * N);
	}

	for (i = 0; i < np; i++)
	{
		parents[i].config = (int *)malloc(sizeof(int) * N);
	}

	printf("Agoritmo genetico para N reinias \n");
	printf("Numero de Reinas -> %d\n", N);
	printf("Poblacion inicial -> %d\n", p);

	//Generamos la poblacion incial
	InitConf(population, N, p); //check

	//Calculamos el fit de la poblacion inicial
	calFit(population, N, p); //check

	//ordenamos por mejor fit
	Insertion_sort(population, p); //check

	//Caso donde se encuentra un optimo en la primer generacion
	if (population[0].fitness == 0)
	{
		printf("\n\n=============================================\n");
		printf("La mejor solucion tiene un fit de %d \n", population[0].fitness);
		printf("La mejor solucion es: [ ");
		for (int i = 0; i < N; i++)
		{
			printf(" %d ", population[0].config[i] + 1);
		}
		printf("]\n");
		printConf(population[0].config, N);
		printf("\n===============================================\n");
		return 0;
	}

	// En caso contrario se guarda el candidato mas optimo
	for (i = 0; i < N; i++)
	{
		Best.config[i] = population[0].config[i];
	}
	Best.fitness = population[0].fitness;

	do
	{

		//Seleccion de padres
		selectChampionship(parents, population, N, p); //check

		//Cruza
		Crossover(parents, population, N, np); //check

		//Mutacion
		mutation(population, prob, N, np);

		//Calculo del Fit
		calFit(population, N, p);

		//Ordenamos
		Insertion_sort(population, p);

		//Comprobamos si hay un mejor candidato

		if (population[0].fitness <= Best.fitness)
		{
			for (i = 0; i < N; i++)
			{
				Best.config[i] = population[0].config[i];
			}
			Best.fitness = population[0].fitness;
		}

		countGen++;
		

	} while ((Best.fitness != 0) && (countGen < numMaxGen));

	printf("\n\n=============================================\n");
	printf("La mejor solucion tiene un fit de %d \n", Best.fitness);
	printf("La mejor solucion es: [ ");
	for (int i = 0; i < N; i++)
	{
		printf(" %d ", Best.config[i] + 1);
	}
	printf("]\n");
	printConf(Best.config, N);
	printf("\n===============================================\n");

	return 0;
}
