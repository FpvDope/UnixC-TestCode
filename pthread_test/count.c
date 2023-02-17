#include <stdio.h>
#include <pthread.h>

int val = 0;	//全局变量属于当前进程中的临界资源;

/*
 *	可重入函数：函数中不涉及临界资源，只是用自己的栈帧;
 *	不可重入函数：函数中会涉及临界资源：当前进程的代码段、
 * 	数据段、堆，属于当前进程中多个线程的公共资源;
 */
void *fun(void * arg){
	int i, j;

	for(i=0; i<5000; i++){
		j = val;
		j++;
		printf("%d\n", j);
		val = j;
	}
	
	return NULL;
}

/*
 *	用来模拟：如果没有线程同步，多个线程访问临界资源时会发生什么?
 */
int main(void){
	pthread_t tid, pid;

	pthread_create(&tid, NULL, fun, NULL);	
	pthread_create(&pid, NULL, fun, NULL);	

	pthread_join(tid, NULL);
	pthread_join(pid, NULL);

	return 0;
}

