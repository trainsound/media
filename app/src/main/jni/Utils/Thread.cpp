//
// Created by lena on 2018. 4. 24..
//

#include "Thread.h"

//private:
//pthread_t thread;
//bool runFlag;
//public :
//Thread(void *arg);
//~Thread();
//virtual void run();
//
//bool getRunnableFlag();
//int threadStop();
//int threadPause();
//int threadResume();
void* pthreadCreate(void* arg){
    Thread *thread = (Thread*)arg;
    thread->run();

    return NULL;
}

Thread::Thread(void* arg){
    this->runFlag = true;
    if(!pthread_create(&(this->thread), NULL, pthreadCreate, arg)){
        //exit
        this->runFlag = false;
    }
}

Thread::~Thread(){
    
}

bool Thread::getRunnableFlag(){
    return runFlag;
}

int Thread::threadStop(){
    this->runFlag = false;

    return 0;
}