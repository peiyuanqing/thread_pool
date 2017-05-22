#ifndef THREAD_POOL
#define THREAD_POOL
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <list>

struct job
{
    void* (*callback_function)(void *arg);    //�̻߳ص�����
    void *arg;                                //�ص���������
    std::list<struct job>;
};

struct threadpool
{
    int thread_num;                   //�̳߳��п����̵߳ĸ���
    int queue_max_num;                //���������job�ĸ���
    struct job *head;                 //ָ��job��ͷָ��
    struct job *tail;                 //ָ��job��βָ��
    pthread_t *pthreads;              //�̳߳��������̵߳�pthread_t
    pthread_mutex_t mutex;            //�����ź���
    pthread_cond_t queue_empty;       //����Ϊ�յ���������
    pthread_cond_t queue_not_empty;   //���в�Ϊ�յ���������
    pthread_cond_t queue_not_full;    //���в�Ϊ������������
    int job_num;                //���е�ǰ��job����
    bool queue_close;                  //�����Ƿ��Ѿ��ر�
    bool pool_close;                   //�̳߳��Ƿ��Ѿ��ر�
};

int init_my_pool(int max_thread_num, int queue_deepth)
{
	
}



//================================================================================================
//��������                   threadpool_init
//����������                 ��ʼ���̳߳�
//���룺                    [in] thread_num     �̳߳ؿ������̸߳���
//                         [in] queue_max_num  ���е����job���� 
//�����                    ��
//���أ�                    �ɹ����̳߳ص�ַ ʧ�ܣ�NULL
//================================================================================================
struct threadpool* threadpool_init(int thread_num, int queue_max_num);

//================================================================================================
//��������                    threadpool_add_job
//����������                  ���̳߳����������
//���룺                     [in] pool                  �̳߳ص�ַ
//                          [in] callback_function     �ص�����
//                          [in] arg                     �ص���������
//�����                     ��
//���أ�                     �ɹ���0 ʧ�ܣ�-1
//================================================================================================
int threadpool_add_job(struct threadpool *pool, void* (*callback_function)(void *arg), void *arg);

//================================================================================================
//��������                    threadpool_destroy
//����������                   �����̳߳�
//���룺                      [in] pool                  �̳߳ص�ַ
//�����                      ��
//���أ�                      �ɹ���0 ʧ�ܣ�-1
//================================================================================================
int threadpool_destroy(struct threadpool *pool);

//================================================================================================
//��������                    threadpool_function
//����������                  �̳߳����̺߳���
//���룺                     [in] arg                  �̳߳ص�ַ
//�����                     ��  
//���أ�                     ��
//================================================================================================
void* threadpool_function(void* arg);




using namespace std;
struct my_job
{
	void *args;
	int32_t (function)(void *args);//���ܺ�����ִ��ʵ��
	
};

struct my_job_list
{
	pthread_spinlock_t lock_in_queue;
	std::list<struct my_job> job_list;
};

struct my_thread
{
	pthread_t *pthread;
	struct my_job_list *joblist;
	
};
struct my_thread_pool
{
	int32_t max_thread_num;
	int32_t max_queue_num;
	struct my_thread *pthreads;
	pthread_cond_t 
	pthread_mutex_t pool_mutex;
	
	

};



#endif


