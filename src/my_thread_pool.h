#ifndef MY_THREAD_POOL_H
#define MY_THREAD_POOL_H

#include <iostream>
#include <list>
using namespace std;

typedef enum tag_pool_status
{
	pool_init = 0,
	pool_running = 1,
	pool_finished = 2,
	pool_waitting_destroy = 3,
	pool_destroyed = 4,

	pool_status_butt
}pool_status;

//线程task
class thread_task
{
    public:
        thread_task(void* (*func)(void* arg), void*arg);
        ~thread_task();
        void* (*func)(void* arg);
        void* arg;
};

//spin 计数类
class spin_count
{
    private:
        pthread_spinlock_t lock;
        int32_t count;
    public:
        spin_count();
        ~spin_count();
        int32_t spin_get_count();
        void spin_add(int32_t inc_num);
        void spin_dec(int32_t dec_num);
};

//spin list模板类
template<typename T>
class spin_list
{
    private:
        pthread_spinlock_t lock;
        std::list<T> *list;
    public:
        spin_list();
        ~spin_list();
        T spin_list_front();
        void spin_list_push_back(T node);
        void spin_list_pop_front();
        int32_t spin_list_size();
};


//线程池
class thread_pool
{
    public:
        thread_pool(uint32_t max_num);
        ~thread_pool();
        int32_t add_task(void* (*func)(void* arg), void* arg);
    private:
    	//thread pool属性
        const uint32_t thread_num;
        pool_status status;
        spin_count task_num;
        spin_list<thread_task*> wait_list;
        pthread_t deamon;
        pthread_t *pthreads;

		//thread pool调度和同步
        pthread_mutex_t mutex_task_comming;
        pthread_cond_t task_comming;

        pthread_mutex_t mutex_all_finished;
        pthread_cond_t all_finished;


        pthread_mutex_t mutex_wake_deamon;
        pthread_cond_t wake_deamon;
	
        //thread_pool的执行线程，守护线程，添加任务的函数
        static void* deamon_func(void* arg);
        static void* thread_func(void* arg);
};


#endif

