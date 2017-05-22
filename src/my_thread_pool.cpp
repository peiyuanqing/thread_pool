/*
#ifdef ___thread_pool_with_c
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <list>
#include <assert.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
using namespace std;

typedef struct tag_thread_task
{
    void* (*routin)(void* arg);
    void *arg;
} thread_task;


typedef struct tag_my_thread_pool
{
    int max_num;
    bool switch_status;
    //bool all_finished;
    int task_num;
    std::list<thread_task*> *wait_list;//pool调度队列，task来的时候先将task放入队列，然后up一次信号量


    pthread_spinlock_t pool_spin_lock;//操作pool的spin lock
    pthread_cond_t task_come;//通知执行线程从wait list取下task执行
    pthread_cond_t wake_deamon;//通知deamon线程检查任务是否已经完成
    pthread_mutex_t pool_mutex;

    pthread_t *pool_entity;//程序执行线程实体
    pthread_t daemon_thread;//守护线程，负责通知pool创建者任务完成
} my_pool;



bool spin_get_pool_switch(my_pool *pool)
{
    bool ret = false;
    pthread_spin_lock(&(pool->pool_spin_lock));
    ret = pool->switch_status;
    pthread_spin_unlock(&(pool->pool_spin_lock));
    return ret;
}

int32_t set_pool_switch(my_pool *pool, bool pool_switch)
{
    assert(pool != NULL);
    pthread_spin_lock(&(pool->pool_spin_lock));
    pool == FALSE? pool->switch_status = 0 : pool->switch_status = 1;
    pthread_spin_unlock(&(pool->pool_spin_lock));
    return 0;
}


int32_t add_task(my_pool *thread_pool, void* (*task_func)(void *arg), void *arg)
{
    assert(thread_pool != NULL);
    assert(task_func != NULL);

    thread_task *task = NULL;
    if(0 == spin_get_pool_switch(thread_pool))
    {
        printf("thread pool has been closed.\n");
        return -1;
    }


    task = (thread_task*)malloc(sizeof(thread_task));
    assert(task != NULL);
    task->arg = arg;
    task->routin = task_func;

    pthread_mutex_lock(&(thread_pool->pool_mutex));
    pthread_spin_lock(&(thread_pool->pool_spin_lock));
    //printf("size : %d\n", thread_pool->wait_list->size());
    thread_pool->wait_list->push_back(task);
    thread_pool->task_num++;
    pthread_spin_unlock(&(thread_pool->pool_spin_lock));

    pthread_cond_broadcast(&thread_pool->task_come);
    pthread_mutex_unlock(&(thread_pool->pool_mutex));
    return 0;

}


void* deamon_func(void *arg)
{
    my_pool *pool = (my_pool*)arg;

    while(1)
    {

        pthread_mutex_lock(&(pool->pool_mutex));
        pthread_cond_wait(&(pool->wake_deamon), &(pool->pool_mutex));
        pthread_spin_lock(&(pool->pool_spin_lock));
        if(pool->task_num == 0 && pool->wait_list->size() == 0)
        {
            //pool->all_finished = true;//若所有task全部执行完毕，break，结束线程
            pthread_spin_unlock(&(pool->pool_spin_lock));
            pthread_mutex_unlock(&(pool->pool_mutex));
            break;
        }
        pthread_spin_unlock(&(pool->pool_spin_lock));
        pthread_mutex_unlock(&(pool->pool_mutex));

    }

    return NULL;

}

pthread_t a[500000];
int32_t index = 0;
pthread_spinlock_t print_lock;

void* task_func(void* arg)
{
    pthread_t tid = 0;
    tid = pthread_self();
    pthread_spin_lock(&print_lock);
    a[index] = tid;
    index++;
    pthread_spin_unlock(&print_lock);
    //Sleep(10);
    return NULL;
}


void* thread_func(void* arg)
{
    my_pool *pool = (my_pool*)arg;
    thread_task *task = NULL;
    //void* ret = NULL;
    while(1)
    {

        pthread_mutex_lock(&(pool->pool_mutex));

        pthread_cond_wait(&(pool->task_come), &(pool->pool_mutex));//尝试down一次信号量
        pthread_spin_lock(&(pool->pool_spin_lock));
        if(pool->wait_list->size() != 0)
        {
            task = pool->wait_list->front();
            pool->wait_list->pop_front();
            pool->task_num--;
        }

        pthread_spin_unlock(&(pool->pool_spin_lock));

        if(task != NULL)
        {
            task->routin(task->arg);
            free(task);
            task = NULL;
            pthread_cond_signal(&(pool->wake_deamon));//唤醒deamon检查task是否都已完成
        }
        pthread_mutex_unlock(&(pool->pool_mutex));
    }

}

my_pool* init_my_thread_pool(int max_num)
{
    my_pool *pool = NULL;
    int i = 0;
    if(max_num <=0)
    {
        printf("input max thread num invalid.\n");
    }
    pool = (my_pool*)malloc(sizeof(my_pool));

    assert(pool != NULL);

    pool->pool_entity = (pthread_t*)malloc(max_num * sizeof(pthread_t));
    if(pool->pool_entity == NULL)
    {
        free(pool);
        pool = NULL;
        printf("Alloc pthread entity failed.\n");
        return NULL;
    }

    pool->max_num = max_num;
    pool->switch_status = true;//初始化时打开pool开关
    //pool->all_finished = false;
    pool->task_num = 0;
    pool->wait_list = new list<thread_task*>;
    pthread_spin_init(&(pool->pool_spin_lock), 0);
    pthread_mutex_init(&(pool->pool_mutex), NULL);
    pthread_cond_init(&(pool->task_come), NULL);
    pthread_cond_init(&(pool->wake_deamon), NULL);


    for(i = 0; i<pool->max_num; i++)
    {
        pthread_create(&pool->pool_entity[i], NULL, thread_func, (void*)pool);
    }
    //创建守护线程，当所有任务完成后，通知thread pool创建者
    pthread_create(&(pool->daemon_thread), NULL, deamon_func, (void*)pool);


    return pool;
}



int32_t destroy_pool(my_pool *thread_pool)
{
    int32_t i = 0;
    int32_t ret = 0;
    thread_task *task = NULL;
    pthread_join(thread_pool->daemon_thread, NULL);
    pthread_spin_lock(&(thread_pool->pool_spin_lock));

    if(thread_pool->task_num !=0 ||
        thread_pool->wait_list->size() != 0)
    {
        ret = -1;
        while(thread_pool->wait_list->size() != 0)
        {
            task = thread_pool->wait_list->front();
            thread_pool->wait_list->pop_front();
            if(task != NULL)
            {
                free(task);
                task = NULL;
            }
        }

    }
    thread_pool->

    pthread_spin_unlock(&(thread_pool->pool_spin_lock));

    pthread_spin_lock(&(thread_pool->pool_spin_lock));

    for(; i<thread_pool->max_num; i++)
    {
        (void)pthread_kill(thread_pool->pool_entity[i], 0);
    }

    pthread_spin_destroy(&(thread_pool->pool_spin_lock));
    pthread_cond_destroy(&(thread_pool->task_come));
    pthread_cond_destroy(&(thread_pool->wake_deamon));


    free(thread_pool->pool_entity);

    return 0;


}

int32_t main(int argc, char** argv)
{
    my_pool *pool = NULL;
    pool = init_my_thread_pool(50);
    assert(pool != NULL);
    pthread_spin_init(&print_lock, 0);
    printf("creat thread pool success.\n");
    int32_t i = 0;
    for(i = 0; i<500000; i++)
    {
        add_task(pool,task_func, NULL);
    }

    for(i=0; i<500000; i++)
    {
        printf("task run on thread:%d\n", a[i]);
    }

    return 0;

}


#endif

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

    this->pthreads = new pthread_t[this->thread_num];
    assert(this->pthreads != NULL);

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
    for(uint32_t i = 0; i<50; i++)
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

//thread work in pipe mode
/*
 * pipe.c
 *
 * Simple demonstration of a pipeline. main() is a loop that
 * feeds the pipeline with integer values. Each stage of the
 * pipeline increases the integer by one before passing it along
 * to the next. Entering the command "=" reads the pipeline
 * result. (Notice that too many '=' commands will hang.)
 */
/*
#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;

std::list<int> g_hashArray[100];

int main(int argc, char**argv)
{
    unsigned i = 0;
    unsigned randVal = 0;
    std::list<int> *bucket = NULL;
    std::list<int> :: iterator iter;
    for(; i<1000; i++)
    {
        srand(i);
        randVal = rand();
        bucket = &g_hashArray[randVal%100];
        bucket->push_back(randVal);
    }
    for(i = 0; i<100; i++)
    {
        bucket = &g_hashArray[i];
        while(bucket->size()!=0)
        {
            randVal = bucket->front();
            cout<<randVal<<endl;
            bucket->pop_front();
        }
    }

    for(i = 0; i<100; i++)
    {
        bucket = &g_hashArray[i];
        cout<<bucket->size()<<endl;
    }
    return 0;
}
*/

// map::insert
/*
#include <iostream>
#include <map>
using namespace std;

int main ()
{
  map<char,int> mymap;
  map<char,int>::iterator it;
  pair<map<char,int>::iterator,bool> ret;

  // first insert function version (single parameter):
  mymap.insert ( pair<char,int>('a',100) );
  mymap.insert ( pair<char,int>('z',200) );
  ret=mymap.insert (pair<char,int>('z',500) );
  if (ret.second==false)
  {
    cout << "element 'z' already existed";
    cout << " with a value of " << ret.first->second << endl;
  }

  // second insert function version (with hint position):
  it=mymap.begin();
  mymap.insert (it, pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert (it, pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  map<char,int> anothermap;
  anothermap.insert(mymap.begin(),mymap.find('c'));

  // showing contents:
  cout << "mymap contains:\n";
  for ( it=mymap.begin() ; it != mymap.end(); it++ )
    cout << (*it).first << " => " << (*it).second << endl;

  cout << "anothermap contains:\n";
  for ( it=anothermap.begin() ; it != anothermap.end(); it++ )
    cout << (*it).first << " => " << (*it).second << endl;

  return 0;
}
*/

/*
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

typedef struct tagAXIS
{
    int x;
    int y;
}AXIS;

AXIS getAxis(int vertexNo)
{
    AXIS asix = {0};
    asix.x = vertexNo%4;
    asix.y = vertexNo/4;
    return asix;
}

int g_matrix[16][16];


void makeMatrix()
{
    AXIS axisX;
    AXIS axisY;

    for(int i=0; i<16; i++)
    {

        axisX = getAxis(i);
        for(int j=0; j<16; j++)
        {
            axisY = getAxis(j);
            if(i == j)
            {
                g_matrix[i][j]=0;
                continue;
            }
            if(abs(axisX.x-axisY.x)>1 || abs(axisX.y-axisX.y)>1)
            {
                g_matrix[i][j] = g_matrix[j][i] = 9;
            }
            else
            {
                g_matrix[i][j] = g_matrix[j][i] = 1;
            }
        }
    }

}


void printMatrix()
{
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            cout<<g_matrix[i][j]<<"     ";
        }
        cout<<endl;
        cout<<endl;
    }
}

int getVertixNO(AXIS axis)
{
    return axis.y * 4 + axis.x;
}

void setVertexInfo(int vertexNo, int type)
{
    AXIS axis = getAxis(vertexNo);
    AXIS up = {axis.x, axis.y+1};
    AXIS down = {axis.x, axis.y-1};
    AXIS left = {axis.x-1, axis.y};
    AXIS right = {axis.x+1, axis.y};

}

int main()
{
    makeMatrix();
    printMatrix();
    cout<<getVertixNO({0,0})<<endl;
    cout<<getVertixNO({3,3})<<endl;
    cout<<getVertixNO({0,1})<<endl;
    cout<<g_matrix[0][4]<<endl;

    return 0;
}
*/


#include <iostream>

namespace MY_NAME_SPACE
{

    int func(std::string);
    double guc(int);
}

namespace MSP = MY_NAME_SPACE;

int MSP::func(std::string name)
{
    std::cout<<name<<std::endl;
    return 0;
}

double MSP::guc(int param)
{
    return (double)param*param;
}


namespace A
{
    class TEST
    {
        int i;
    };
    int func(int);
    int guc(int);
}
namespace B
{
    using namespace A;
    int huc(int);
}

namespace C
{
    using namespace B;
    int iuc();
}

//
/*
int C::func(int i)
{
    return i;
}
*/
namespace D
{
    int func(int i);
}

namespace D
{
    int gunc(int i);
}
using namespace std;
int main(int argc, char **argv)
{
    MSP::func("hello world");
    double res = MSP::guc(2);
    std::cout<<res<<std::endl;

    C::TEST test;

    int i(0);
    cout<<i<<endl;
    return 0;
}




