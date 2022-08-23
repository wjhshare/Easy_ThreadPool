#include <iostream>
#include "include/ThreadPool.h"

using namespace std;
struct Arg1{
    int a;
    int b;
    int idx;
    Arg1(int _a, int _b, int _idx):a(_a),b(_b),idx(_idx){}
};

struct Arg2{
    float a;
    float b;
    int idx;
};

void* task_fun1(void* _arg){
    Arg1* arg = static_cast<Arg1*>(_arg);
    cout << "fun1 idx: " << arg->idx
         << ", a + b = " << arg->a + arg->b << endl;

    return &arg->idx;
}

void* task_fun2(void* _arg){
    Arg2* arg = static_cast<Arg2*>(_arg);
    cout << "fun2 idx: " << arg->idx
         << ", a * b = " << arg->a * arg->b << endl;

    return &arg->idx;
}

int main() {
    ThreadPool* pool = new ThreadPool(500,4);

    for(int i = 0; i < 1000; ++i){
        if(i % 2 == 0){
            Arg1* arg1 = new Arg1(1,2,i);
            pool->add_task(&task_fun1, arg1);
        }
        else{
            Arg2* arg2 = new Arg2();
            arg2->a = 1.0;
            arg2->b = 2.0;
            arg2->idx = i;

            pool->add_task(&task_fun2, arg2);
        }
    }
    pool->ThreadPool_shut_down();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
