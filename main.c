#include <pthread.h>
#include <stdio.h>

void *increment(void *arg) {
  	pthread_mutex_lock(&mutex);
  	count += 1;
  	printf("Counter = %d\n", count);
  	pthread_mutex_unlock(&mutex);
  	return arg;
}

struct matriz {
	matriz[ordem][ordem]
};


int main(void) {

	int ordem;

    printf("Insira a ordem da Matriz: ");
    scanf("%d", &ordem);
    int matriz[ordem][ordem];

    for (int linha = 0; linha < ordem; linha++) {
        for (int coluna = 0; coluna < ordem; coluna++) {
            scanf("%d", &matriz[linha][coluna]);
        }
    }

	int threads_qtd = ordem;
	pthread_t threads[threads_qtd];


  	for (int index = 0; index < threads_qtd; index++) {
    	if (pthread_create(&(threads[index]), NULL, increment, NULL)) {
      		printf("Thread %d not created", index);
      		return 1;
    	}
  	}

	for (int linha = 0; linha < threads_qtd; linha++) {
		if (pthread_create(&(threads[linha]), NULL, increment, NULL)) {
			for(int coluna = 0; coluna < ordem; coluna++) {
        		threads[linha] = matriz[linha][coluna];
    		}
      	return 1;
    	}
	}


	return 0;}