#include <stdio.h>
#include <pthread.h>

int val = 0;
//mutex锁不能定义在线程内，要定义在临界区域
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *fun(void * arg){
	int i, j;

	for(i=0; i<5000; i++){
		//加锁
		pthread_mutex_lock(&mutex);	
		j = val;
		j++;
		printf("%d\ttid:%lu\n", j, pthread_self());
		val = j;
		//解锁
		pthread_mutex_unlock(&mutex);	
	}
	
	return NULL;
}

/*
 *	线程的同步之mutex锁的使用
 */
int main(void){
	pthread_t tid, pid;

	pthread_create(&tid, NULL, fun, NULL);	
	pthread_create(&pid, NULL, fun, NULL);	

	pthread_join(tid, NULL);
	pthread_join(pid, NULL);

	//mutex锁的销毁
	pthread_mutex_destroy(&mutex);	

	return 0;
}

