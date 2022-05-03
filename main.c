#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Variaveis Globais
int resultado = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Struct da Matriz
struct dados {
  	int ordem, linha_atual, *linha_matriz;
};

// Incremento das Threads
void *incremento(void *argumentos) 
{
	struct dados *dados = (struct dados *) argumentos;
	int ordem = (*dados).ordem;
	int soma = 0;

	for (int index = 0; index < ordem; index++) {
		soma += dados->linha_matriz[index];
	}
	
	pthread_mutex_lock(&mutex);
	resultado += soma;
	pthread_mutex_unlock(&mutex);
	return argumentos;
}

int main(void) {
  	
	int ordem, numero;

	printf("Insira a Ordem da Matriz: ");
	scanf("%d", &ordem);
  	int matriz[ordem][ordem];
 	pthread_t threads[ordem];

  	for (int linha = 0; linha < ordem; linha++) {
    	for (int coluna = 0; coluna < ordem; coluna++) {
			printf("Digite o %dº número da %dº linha: ", coluna, linha+1);
      		scanf("%d", &numero);
      		matriz[linha][coluna] = numero;
    	}
		printf("\n");
  	}

	for (int i = 0; i < ordem; i++) {
		struct dados *argumentos = (struct dados *)malloc(sizeof(struct dados));
		(*argumentos).ordem = ordem;
		(*argumentos).linha_matriz = (int *)malloc(ordem * sizeof(int));
		(*argumentos).linha_atual = i;

		for (int j = 0; j < ordem; j++) {
			(*argumentos).linha_matriz[j] = matriz[i][j];
		}

		pthread_create(&(threads[i]), NULL, incremento, (void *) argumentos);
	}

	for (int index = 0; index < ordem; index++) {
		pthread_join(threads[index], NULL);
	}

	printf("%d", resultado);
	return 0;
}
