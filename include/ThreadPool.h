//
// Created by 17162 on 2022/8/23.
//

#ifndef EASY_THREADPOOL_THREADPOOL_H
#define EASY_THREADPOOL_THREADPOOL_H

#include <pthread.h>
#include <iostream>
#include <mutex>
#include <queue>

using namespace std;


class ThreadPool{
public:
    //任务节点
    struct TaskNode{
        void* (*function)(void*);   //函数指针作为回调函数
        void* arg;                  //回调函数参数
    };

    //核心线程节点
    struct ThreadNode{
        pthread_t tid = 0;     //线程id
    };

public:
    pthread_mutex_t lock;   /*互斥锁，用于互斥访问任务队列等共享数据*/
    pthread_cond_t task_queue_full;     /*条件变量，用于通知add_task，任务队列已满，阻塞任务添加操作*/
    pthread_cond_t task_queue_not_full;     /*条件变量，用于通知add_task，任务队列未满，可添加任务*/
    pthread_cond_t task_queue_not_empty;    /*条件变量，用于通知线程，任务队列未空，可取任务执行*/

    queue<TaskNode*> task_queue;            /*任务队列*/
    ThreadNode* thread_list;                /*核心线程数组*/

public:
    int task_queue_max_size;            /*任务队列长度上限*/
    int thread_queue_size;              /*核心线程数*/
    bool shut_down;                     /*是否销毁线程池（正常销毁）*/
    bool clear_down;                    /*是否强制销毁线程池*/

public:
    //添加任务
    void add_task(void* (*function)(void*), void* Arg){
        TaskNode* task = new TaskNode();    /*新建任务节点*/
        task->function = function;          /*设置任务节点回调函数*/
        task->arg = Arg;                    /*设置任务节点回调函数参数*/

        //加锁将任务节点插入任务队列
        pthread_mutex_lock(&(lock));
        while(task_queue.size() >= task_queue_max_size && (!shut_down) && (!clear_down)){
            pthread_cond_wait(&task_queue_not_full, &lock);
        }

        //如果要销毁线程池，无论是哪一种销毁，都不再进行插入任务
        if(shut_down || clear_down){
            pthread_cond_broadcast(&task_queue_not_empty);  //通知所有核心线程（随后核心线程根据销毁线程池类型，自杀销毁）
            pthread_mutex_unlock(&lock);
            return;
        }

        task_queue.push(task);
        pthread_cond_broadcast(&task_queue_not_empty);  //通知所有核心线程（取任务执行）
        pthread_mutex_unlock(&lock);
    }

    //核心线程执行函数
    static void* Run(void* _pool){
        ThreadPool* pool = (ThreadPool*)_pool;
        //循环（常驻）
        while(true){
            pthread_mutex_lock(&(pool->lock));  //加锁，直到取出任务或销毁为止

            //如果任务队列为空且线程池不销毁，则阻塞等待信号
            while(pool->task_queue.empty() && (!pool->shut_down) && (!pool->clear_down)){
                pthread_cond_wait(&(pool->task_queue_not_empty), &(pool->lock));
            }

            //如果是强制销毁，则退出while(true)；如果是正常退出销毁，则依旧处理任务直到任务队列为空为止
            if(pool->clear_down || (pool->shut_down && pool->task_queue.empty())){
                pthread_cond_broadcast(&(pool->task_queue_not_empty));      //通知其它核心线程
                pthread_cond_broadcast(&(pool->task_queue_not_full));       //通知添加任务线程（主线程）
                pthread_mutex_unlock(&(pool->lock));                        //释放锁
                break;
            }

            //取出任务
            TaskNode* task = pool->task_queue.front();
            pool->task_queue.pop();

            //若取出任务后任务队列为空，通知添加任务线程（应用于之前任务队列满了阻塞添加线程）
            if(pool->task_queue.empty()){
                pthread_cond_broadcast(&(pool->task_queue_not_full));
            }
            else{   //否则，通知其它核心线程
                pthread_cond_broadcast(&(pool->task_queue_not_empty));
            }

            //取完任务后释放锁再执行任务
            pthread_mutex_unlock(&(pool->lock));

            //利用回调函数执行任务
            task->function(task->arg);
        }

        //自杀
        pthread_exit(NULL);
    }

    //线程池构造
    ThreadPool(int _task_queue_max_size, int _thread_queue_size)
            :task_queue_max_size(_task_queue_max_size), thread_queue_size(_thread_queue_size),
             shut_down(false), clear_down(false){
        //为核心线程数组分配堆空间
        thread_list = (ThreadNode*)malloc(sizeof(ThreadNode)*thread_queue_size);

        //初始化锁和信号
        if(pthread_mutex_init(&lock, NULL) != 0 ||
           pthread_cond_init(&task_queue_full, NULL) != 0 ||
           pthread_cond_init(&task_queue_not_full, NULL) != 0 ||
           pthread_cond_init(&task_queue_not_empty, NULL) != 0){
            perror("init lock or cont error\n");
            exit(EXIT_FAILURE);
        }

        //创建核心线程
        for(int i = 0; i < thread_queue_size; ++i){
            ThreadNode* new_thread = new ThreadNode();
            pthread_create(&new_thread->tid, NULL, Run, (void*)this);
        }
    }

public:
    //紧急关闭（没执行的任务不执行了）
    void ThreadPool_clear_down(){
        clear_down = true;
        //通知所有核心线程
        for(int i = 0; i < thread_queue_size; ++i){
            pthread_cond_broadcast(&task_queue_not_empty);
        }
        //等待所有核心线程结束
        for(int i = 0; i < thread_queue_size; ++i){
            pthread_join(thread_list[i].tid, NULL);
        }
        free(thread_list);  //释放核心线程数组空间
        thread_list = nullptr;      //指针置空避免野指针

        //销毁锁和信号
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&task_queue_full);
        pthread_cond_destroy(&task_queue_not_full);
        pthread_cond_destroy(&task_queue_not_empty);
    }

    //正常关闭，任务队列所有任务执行完再关闭
    void ThreadPool_shut_down(){
        shut_down = true;
        //循环通知所有核心线程，直到任务队列为空为止
        while(!task_queue.empty()){
            pthread_cond_broadcast(&task_queue_not_empty);
        }

/*        //再次通知所有核心线程
        for(int i = 0; i < thread_queue_size; ++i){
            pthread_cond_broadcast(&task_queue_not_empty);
        }
        //等待所有核心线程结束
        for(int i = 0; i < thread_queue_size; ++i){
            pthread_join(thread_list[i].tid, NULL);
        }*/
        free(thread_list);
        thread_list = nullptr;

        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&task_queue_full);
        pthread_cond_destroy(&task_queue_not_full);
        pthread_cond_destroy(&task_queue_not_empty);
    }
};


#endif //EASY_THREADPOOL_THREADPOOL_H
