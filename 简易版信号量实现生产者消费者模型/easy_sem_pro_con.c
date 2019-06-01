/*==================
 *  zhangxu
 *  利用信号量实现简易版的
 *  生产者与消费者模型
 *  sem
 *=================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#define NUM 5

int queue[NUM];  //模拟环形队列
sem_t sem_data;  //数据资源计数信号量
sem_t sem_freespace; //空闲资源计数


//生产者线程入口函数
void* productor(void* arg){
	int i = 0 ;
	while(1){
		sem_wait(&sem_freespace);//消耗空间，空闲空间计数信号量-1
		queue[i] = rand()%1000 + 1;
		printf("~~~produce a data:%d\n",queue[i]);
		sem_post(&sem_data); //生产数据，数据资源计数信号量+1

		i = (i + 1) % NUM ;
		sleep(rand()%3);
	}
	return NULL;
}
//消费者线程入口函数
void* consumer(void* arg){
	int i = 0;
	while(1){
		sem_wait(&sem_data); //消耗资源，数据资源计数信号量-1
		printf("~~~consume a data:%d\n",queue[i]); 
		queue[i] = 0;
		sem_post(&sem_freespace);//消耗数据，空闲空间计数信号量+1

		i = (i + 1) % NUM;
		sleep(rand()%3);
	}
	return NULL;
}



int main(void){

	//定义生产者消费者线程
	pthread_t ptid,ctid;
	int ret;
	ret = sem_init(&sem_data,0,0);
	if(ret == -1){
		printf("sem_data init error!\n");
		return -1;
	}
	ret = sem_init(&sem_freespace,0,NUM);
	if(ret == -1){
		printf("sem_freespace init error!\n");
		return -1;
	}

	//创建线程
	ret = pthread_create(&ptid,NULL,productor,NULL);
	if(ret != 0){
		printf("porductor create error!\n");
		return -1;
	}
	
	ret = pthread_create(&ctid,NULL,consumer,NULL);
	if(ret != 0){
		printf("consumer create error!\n");
		return -1;
	}

	//回收线程
	ret = pthread_join(ptid,NULL);
	if(ret != 0){
		printf("porductor join error!\n");
		return -1;
	}
	ret = pthread_join(ctid,NULL);
	if(ret != 0){
		printf("consumer join error!\n");
		return -1;
	}

	//销毁信号量
	ret = sem_destroy(&sem_data);
	if(ret == -1){
		printf("sem_data destroy error!\n");
		return -1;
	}
	ret = sem_destroy(&sem_freespace);
	if(ret == -1){
		printf("sem_freespace destroy error!\n");
		return -1;
	}

	return 0;
}
