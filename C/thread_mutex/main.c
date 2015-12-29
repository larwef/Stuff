#include <pthread.h>
#include <stdio.h>

int i = 0;
pthread_mutex_t mtx;

void* add(){
	for(int x = 0; x < 1000001; x++){
        pthread_mutex_lock(&mtx);
        i++;
		pthread_mutex_unlock(&mtx);
		printf("1");
    }
    return NULL;
}

void* sub(){
	for(int x = 0; x < 1000000; x++){
		pthread_mutex_lock(&mtx);
        i--;
		pthread_mutex_unlock(&mtx);
		printf("2");
    }
    return NULL;
}

int main(){
	
	pthread_mutex_init(&mtx, NULL);	

	pthread_t add_thr;
	pthread_t sub_thr;
	
	pthread_create(&sub_thr, NULL, sub, NULL);
	pthread_create(&add_thr, NULL, add, NULL);

	pthread_join(add_thr, NULL);
	pthread_join(sub_thr, NULL);
	printf("Done: %i\n", i);

	pthread_mutex_destroy(&mtx);
	return 0;
}
