#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *fun1(void *arg){
	printf("%s\tpid:%d\ttid:%lu\n", (char *)arg, getpid(), pthread_self());
	return (void *)1;
}

void *fun2(void *arg){
	printf("fun2 is running...\n");
	sleep(1);
	pthread_exit((void *)2);
}

void *fun3(void *arg){
	while(1){
		printf("fun3 is running...\n");			
		sleep(1);
	}
}

int main(void){
	pthread_t thread_id;
	void * retval;
	
	//use return to return
	pthread_create(&thread_id, NULL, fun1, "hello");
	sleep(1);
	pthread_join(thread_id, &retval);
	printf("fun1 retval is %d\n", (int)retval);

	//use pthread_exit to return
	pthread_create(&thread_id, NULL, fun2, NULL);
	pthread_join(thread_id, &retval);
	printf("fun2 retval is %d\n", (int)retval);

	//use pthread_cancel to stop a thread
	pthread_create(&thread_id, NULL, fun3, NULL);
	sleep(3);
	pthread_cancel(thread_id);
	pthread_join(thread_id, &retval);
	printf("fun3 retval is %d\n", (int)retval);
	if(retval == PTHREAD_CANCELED)	printf("hahahahhaha\n");
		
	return 0;
}

