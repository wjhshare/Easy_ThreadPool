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
    struct TaskNode{
        void* (*function)(void*);   //函数指针作为回调函数
        void* arg;                  //回调函数参数
    };

    struct ThreadNode{
/*        enum State{
            RUN = 0,
            WAITTING = 1,
        };*/
        pthread_t tid = 0;
//        State state;
    };

public:
    pthread_mutex_t lock;   /*互斥锁*/
    pthread_cond_t task_queue_full;
    pthread_cond_t task_queue_not_full;
    pthread_cond_t task_queue_not_empty;

    queue<TaskNode*> task_queue;
    ThreadNode* thread_list;

public:
    int task_queue_max_size;
    int thread_queue_size;
    bool shut_down;
    bool clear_down;

public:
    void add_task(void* (*function)(void*), void* Arg){
        TaskNode* task = new TaskNode();
        task->function = function;
        task->arg = Arg;

        pthread_mutex_lock(&(lock));
        while(task_queue.size() >= task_queue_max_size && (!shut_down) && (!clear_down)){
            pthread_cond_wait(&task_queue_not_full, &lock);
        }

        if(shut_down || clear_down){
            pthread_cond_broadcast(&task_queue_not_empty);
            pthread_mutex_unlock(&lock);
            return;
        }

        task_queue.push(task);
        pthread_cond_broadcast(&task_queue_not_empty);
        pthread_mutex_unlock(&lock);
    }
    static void* Run(void* _pool){
        ThreadPool* pool = (ThreadPool*)_pool;
        while(true){
            pthread_mutex_lock(&(pool->lock));

            while(pool->task_queue.empty() && (!pool->shut_down) && (!pool->clear_down)){
                pthread_cond_wait(&(pool->task_queue_not_empty), &(pool->lock));
            }

            if(pool->clear_down || (pool->shut_down && pool->task_queue.empty())){
                pthread_cond_broadcast(&(pool->task_queue_not_empty));
                pthread_cond_broadcast(&(pool->task_queue_not_full));
                pthread_mutex_unlock(&(pool->lock));
                break;
            }

            TaskNode* task = pool->task_queue.front();
            pool->task_queue.pop();

            if(pool->task_queue.empty()){
                pthread_cond_broadcast(&(pool->task_queue_not_full));
            }
            else{
                pthread_cond_broadcast(&(pool->task_queue_not_empty));
            }

            pthread_mutex_unlock(&(pool->lock));

            task->function(task->arg);
        }
    }

    ThreadPool(int _task_queue_max_size, int _thread_queue_size)
            :task_queue_max_size(_task_queue_max_size), thread_queue_size(_thread_queue_size),
             shut_down(false), clear_down(false){
        thread_list = (ThreadNode*)malloc(sizeof(ThreadNode)*thread_queue_size);

        if(pthread_mutex_init(&lock, NULL) != 0 ||
           pthread_cond_init(&task_queue_full, NULL) != 0 ||
           pthread_cond_init(&task_queue_not_full, NULL) != 0 ||
           pthread_cond_init(&task_queue_not_empty, NULL) != 0){
            perror("init lock or cont error\n");
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < thread_queue_size; ++i){
            ThreadNode* new_thread = new ThreadNode();
            pthread_create(&new_thread->tid, NULL, Run, (void*)this);
        }
    }

public:
    //紧急关闭（没执行的任务不执行了）
    void ThreadPool_clear_down(){
        clear_down = true;
        for(int i = 0; i < thread_queue_size; ++i){
            pthread_cond_broadcast(&task_queue_not_empty);
        }
        for(int i = 0; i < thread_queue_size; ++i){
            pthread_join(thread_list[i].tid, NULL);
        }
        free(thread_list);
        thread_list = nullptr;

        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&task_queue_full);
        pthread_cond_destroy(&task_queue_not_full);
        pthread_cond_destroy(&task_queue_not_empty);
    }

    //正常关闭，任务队列所有任务执行完再关闭
    void ThreadPool_shut_down(){
        shut_down = true;
        while(!task_queue.empty()){
            pthread_cond_broadcast(&task_queue_not_empty);
        }

        for(int i = 0; i < thread_queue_size; ++i){
            pthread_cond_broadcast(&task_queue_not_empty);
        }
        for(int i = 0; i < thread_queue_size; ++i){
            pthread_join(thread_list[i].tid, NULL);
        }
        free(thread_list);
        thread_list = nullptr;

        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&task_queue_full);
        pthread_cond_destroy(&task_queue_not_full);
        pthread_cond_destroy(&task_queue_not_empty);
    }
};


#endif //EASY_THREADPOOL_THREADPOOL_H
