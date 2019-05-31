/*====================
 *  zhangxu
 *  生产者消费者模型
 *  链表存储
 *===================*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//定义链表存储数据

struct mp{
	int data;
	struct mp* next;
};

struct mp* head = NULL;
struct mp* cur = NULL;


pthread_mutex_t mutex;
pthread_cond_t noodle;



//生产者线程入口函数
void* productor(void* arg){
	while(1){
		//生产者创建数据节点
		cur = malloc(sizeof(struct mp));
		cur->data = rand()%1000+1;
		printf("~~~~produce push a data:%d~~~~\n",cur->data);
		//放入链表中，加锁
		pthread_mutex_lock(&mutex);
		cur->next = head;
		head = cur;
		pthread_mutex_unlock(&mutex);
		//唤醒消费者
		pthread_cond_signal(&noodle);
		sleep(rand()%3);
	}
	return NULL;
}

//消费者线程入口函数
void* consumer(void* arg){
	while(1){
		pthread_mutex_lock(&mutex);
		while(head == NULL){
		//	阻塞等待数据
			pthread_cond_wait(&noodle,&mutex);
		}
		//获取数据 （删除节点）
		cur = head;
		head = cur->next;
		pthread_mutex_unlock(&mutex);
		printf("~~~~~~consume a data:%d~~~~\n",cur->data);
		free(cur);
		cur = NULL;
		sleep(rand()%3);
	}
	return NULL;
}


int main(void){

	pthread_t ptid;  //生产者线程ID
	pthread_t ctid[4];  //消费者线程ID
	int ret,i;	
	//创建生产者与消费者线程
	srand(time(NULL));
	ret = pthread_mutex_init(&mutex,NULL);
	if(ret != 0){
		printf("mutex init error!\n");
		return -1;
	}
	pthread_cond_init(&noodle,NULL);
		if(ret != 0){
			printf("cond init error!\n");
			return -1;
		}


	ret = pthread_create(&ptid,NULL,productor,NULL);
	if(ret != 0){
		printf("productor create error!\n");
		return -1;
	}
	for(i = 0 ; i < 4; i++){
		ret = pthread_create(&ctid[i],NULL,consumer,NULL);
		if(ret != 0){
			printf("productor create error!\n");
			return -1;
		}

	}
	//回收生产者线程
	ret = pthread_join(ptid,NULL);
	if(ret != 0){
		printf("productor join error!\n");
		return -1;
	}
	//回收消费者线程
	for(i = 0 ; i < 4; i++){
		ret = pthread_join(ctid[i],NULL);
		if(ret != 0){
			printf("productor join error!\n");
			return -1;
		}
	}

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&noodle);
	return 0;
}

