#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Variaveis Globais
int resultado = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Struct da Matriz
struct dados {
  	int ordem, *linha_matriz;
};

// Faz as somas dos Dados salvos nas Threads baseado na struct recebida e atribui o valor na variavel global do resultado
void *incremento(void *dados_matriz) 
{
	struct dados *dados = (struct dados *) dados_matriz;
	int ordem = (*dados).ordem;
	int soma = 0;

	for (int index = 0; index < ordem; index++) {
		soma += dados->linha_matriz[index];
	}
	
	pthread_mutex_lock(&mutex);
	resultado += soma;
	pthread_mutex_unlock(&mutex);
	return dados_matriz;
}

int main(void) {
  	
	int ordem, numero;

	printf("Insira a Ordem da Matriz: ");
	scanf("%d", &ordem);
  	int matriz[ordem][ordem];
 	pthread_t threads[ordem];

	// Pega os dados da matriz
  	for (int linha = 0; linha < ordem; linha++) {
    	for (int coluna = 0; coluna < ordem; coluna++) {
			printf("Digite o %dº número da %dº linha: ", coluna, linha+1);
      		scanf("%d", &numero);
      		matriz[linha][coluna] = numero;
    	}
		printf("\n");
  	}

	// Passa os dados da Matriz para uma struct e cria as threads dentro do loop, passando uma struct para cada Thread criada
	for (int linha = 0; linha < ordem; linha++) {
		struct dados *dados_matriz = (struct dados *) malloc (sizeof (struct dados));
		(*dados_matriz).ordem = ordem;
		(*dados_matriz).linha_matriz = (int *) malloc (ordem * sizeof(int));

		for (int coluna = 0; coluna < ordem; coluna++) {
			(*dados_matriz).linha_matriz[coluna] = matriz[linha][coluna];
		}

		pthread_create(&(threads[linha]), NULL, incremento, (void *) dados_matriz);
	}

	// Da Terminate nas Threads depois que elas acabarem suas funções
	for (int index = 0; index < ordem; index++) {
		pthread_join(threads[index], NULL);
	}

	printf("%d", resultado);
	return 0;
}
