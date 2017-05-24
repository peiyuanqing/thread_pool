#define THREAD_POOL_CPP
#ifdef THREAD_POOL_CPP
//C++线程池，暂时不支持异步task
//todo:实现cpu分核，支持异步task，实现优先级调度
#include <iostream>
#include <assert.h>
#include <windows.h>
#include "my_thread_pool.h"
using namespace std;
#define UNREFERENCE_PARAM(x)

//thread_task类的实现
thread_task::thread_task(void* (*func)(void* arg), void*arg)
{
    this->func = func;
    this->arg = arg;
}

thread_task::~thread_task()
{
    this->func = NULL;
    this->arg = NULL;
}

//spin_count类的实现
spin_count::spin_count()
{
    pthread_spin_init(&this->lock, 0);
    this->count = 0;
}
spin_count::~spin_count()
{
    pthread_spin_destroy(&this->lock);
}

void spin_count::spin_add(int32_t inc_num)
{
    pthread_spin_lock(&this->lock);
    this->count += inc_num;
    pthread_spin_unlock(&this->lock);
    return;
}

void spin_count::spin_dec(int32_t dec_num)
{
    pthread_spin_lock(&this->lock);
    this->count -= dec_num;
    pthread_spin_unlock(&this->lock);
    return;
}

int32_t spin_count::spin_get_count()
{
    int32_t get_count = 0;
    pthread_spin_lock(&this->lock);
    get_count = this->count;
    pthread_spin_unlock(&this->lock);
    return get_count;
}

//模板类spin_list的实现
template<typename T>
spin_list<T>::spin_list()
{
    pthread_spin_init(&this->lock, 0);
    this->list = new std::list<T>();
}

template<typename T>
spin_list<T>::~spin_list()
{
    T node;
    pthread_spin_lock(&this->lock);
    while(this->list->size() != 0)
    {
        node = this->list->front();
        delete node;
        this->list->pop_front();
    }
    pthread_spin_unlock(&this->lock);

    pthread_spin_destroy(&this->lock);
    delete this->list;
}

template<typename T>
void spin_list<T>::spin_list_push_back(T node)
{
    pthread_spin_lock(&this->lock);
    this->list->push_back(node);
    pthread_spin_unlock(&this->lock);
    return;
}

template<typename T>
void spin_list<T>::spin_list_pop_front()
{
    pthread_spin_lock(&this->lock);
    this->list->pop_front();
    pthread_spin_unlock(&this->lock);
    return;
}

template<typename T>
T spin_list<T>::spin_list_front()
{
    T node;
    pthread_spin_lock(&this->lock);
    if(this->list->size()!=0)
    {
        node = this->list->front();
    }
    else
    {
        node = NULL;
    }
    pthread_spin_unlock(&this->lock);

    return node;
}

template<typename T>
int32_t spin_list<T>::spin_list_size()
{
    int32_t list_size = 0;
    pthread_spin_lock(&this->lock);
    list_size = this->list->size();
    pthread_spin_unlock(&this->lock);

    return list_size;
}

thread_pool::thread_pool(uint32_t max_num):thread_num(max_num),status(pool_init),task_num(),wait_list()//初始化列表
{
    assert(this->thread_num > 0);

    pthread_mutex_init(&this->mutex_task_comming, NULL);
    pthread_cond_init(&this->task_comming, NULL);

    pthread_mutex_init(&this->mutex_wake_deamon, NULL);
    pthread_cond_init(&this->wake_deamon, NULL);

    pthread_mutex_init(&this->mutex_all_finished, NULL);
    pthread_cond_init(&this->all_finished, NULL);

    pthread_create(&this->deamon,NULL, deamon_func, (void*)this);

    try
    {
        this->pthreads = new pthread_t[this->thread_num];
        //assert(this->pthreads != NULL);//new并不会返回一个空指针给你
    }
    catch(bad_alloc)
    {
        cout<<"alloc pthread_t array failed.";
        //TO DO:销毁锁和条件变量
    }
    for(uint32_t i=0; i<this->thread_num; i++)
    {
        pthread_create(&this->pthreads[i], NULL, thread_func, (void*)this);
    }

    this->status = pool_running;
    cout<<"Pool init success"<<endl;
}

int32_t g_flag = 0;
thread_pool::~thread_pool()
{
    this->status = pool_waitting_destroy;
    pthread_cond_signal(&this->wake_deamon);
    pthread_join(this->deamon, NULL);

    thread_task *task = NULL;
    if(this->task_num.spin_get_count() != 0 || this->wait_list.spin_list_size() != 0)
    {
        cout<<"some logic error accured."<<endl;
        g_flag = 1;
    }

    while(this->wait_list.spin_list_size())
    {
        task = this->wait_list.spin_list_front();
        this->wait_list.spin_list_pop_front();
        if(task != NULL) delete task;
    }

    for(uint32_t i = 0; i<this->thread_num; i++)
    {
        pthread_kill(this->pthreads[i] ,0);
    }

    pthread_mutex_destroy(&this->mutex_task_comming);
    pthread_mutex_destroy(&this->mutex_wake_deamon);
    pthread_mutex_destroy(&this->mutex_all_finished);

    pthread_cond_destroy(&this->task_comming);
    pthread_cond_destroy(&this->wake_deamon);
    pthread_cond_destroy(&this->all_finished);

    this->status = pool_destroyed;

    cout<<"Pool destroy success."<<endl;
    return;
}




void* thread_pool::deamon_func(void* arg)
{
    thread_pool *pool = (thread_pool*)arg;
    assert(pool != NULL);
    for(;;)
    {
        pthread_mutex_lock(&pool->mutex_wake_deamon);
        while(pool->status == pool_init || pool->status == pool_running)
        {
            pthread_cond_wait(&pool->wake_deamon, &pool->mutex_wake_deamon);
        }
        pthread_mutex_unlock(&pool->mutex_wake_deamon);

        pthread_mutex_lock(&pool->mutex_wake_deamon);
        while(pool->task_num.spin_get_count() != 0 )
        {
            pthread_cond_wait(&pool->wake_deamon, &pool->mutex_wake_deamon);
            cout<<"task num is "<<pool->task_num.spin_get_count()<<endl;
        }

        break;
        pthread_mutex_unlock(&pool->mutex_wake_deamon);

    }
    pool->status = pool_finished;
    pthread_mutex_unlock(&pool->mutex_wake_deamon);
    return NULL;
}

void* thread_pool::thread_func(void* arg)
{
    thread_pool *pool = (thread_pool*)arg;
    thread_task *task = NULL;
    assert(pool != NULL);
    for(;;)
    {
        pthread_mutex_lock(&pool->mutex_task_comming);
        while(pool->wait_list.spin_list_size() == 0)
        {
            pthread_cond_wait(&pool->task_comming, &pool->mutex_task_comming);
        }
        pthread_mutex_unlock(&pool->mutex_task_comming);
        task = pool->wait_list.spin_list_front();
        pool->wait_list.spin_list_pop_front();
        pool->task_num.spin_dec(1);
        if(task != NULL)
        {
            task->func(task->arg);
        }
        pthread_cond_signal(&pool->wake_deamon);//唤醒deamon
    }

    return NULL;
}


int32_t thread_pool::add_task(void* (*func)(void* arg), void* arg)
{
    thread_task *task = NULL;
    task = new thread_task(func, arg);
    if(task == NULL)
    {
        return -1;
    }

    this->wait_list.spin_list_push_back(task);
    this->task_num.spin_add(1);
    pthread_cond_signal(&this->task_comming);
    return 0;
}

pthread_spinlock_t print_lock = PTHREAD_SPINLOCK_INITIALIZER;

pthread_t g_tid_array[1000000];

uint32_t index = 0;

void* task_func(void* arg)
{
    pthread_t tid = pthread_self();
    pthread_spin_lock(&print_lock);
    g_tid_array[index] = tid;
    index++;
    pthread_spin_unlock(&print_lock);
    return NULL;
}

int32_t main(int32_t argc, char**argv)
{
    thread_pool *pool = new thread_pool(10);
    //delete pool;
    for(uint32_t i = 0; i<500000; i++)
    {
        pool->add_task(task_func, NULL);
    }


    delete pool;

    for(uint32_t i=0; i<50; i++)
    {
        cout<<"my tid is"<<g_tid_array[i]<<endl;
    }

    cout<<g_flag<<endl;
    return 0;
}
#endif


