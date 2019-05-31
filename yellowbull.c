#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

//互斥锁简单应用
//黄牛抢票程序


//定义票的数量
int ticket = 100;

//定义互斥锁变量
pthread_mutex_t mutex;

//线程入口函数
void* thr_start(void* args){
	while(1){
		//加锁要在临界资源访问之前
		pthread_mutex_lock(&mutex);
		if(ticket > 0){
			//sleep(1);
			printf("我是黄牛%d,我正在抢票%d~~\n",*(int*)args,ticket);
			ticket--;
		}
		else{
			//在线程任意有可能退出的地方解锁
			pthread_mutex_unlock(&mutex);
			pthread_exit(NULL);
		}
	
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}


int main(){

	//定义黄牛个数
	pthread_t tid[4];
	int i , ret;	
	//初始化互斥锁变量
	pthread_mutex_init(&mutex,NULL);

	//创建线程，让黄牛抢票
	for(i = 0; i < 4; i++){
		ret = pthread_create(&tid[i],NULL,thr_start,(void*)&i);
		if(ret != 0){
			printf("yellowbull is not exist!\n");
			return -1;
		}
	}

	//线程等待，回收资源
	for(i = 0 ; i < 4; i++){
		pthread_join(tid[i],NULL);
	}
	//销毁互斥锁变量
	
	pthread_mutex_destroy(&mutex);

	return 0;
}

