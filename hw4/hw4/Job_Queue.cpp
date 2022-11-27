#include"Job_Queue.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Constructor
JobQueue::JobQueue( int maxlen ){
    q_front = NULL;
    q_back = NULL;
    len = 0;
    max_len = maxlen;
}
JobQueue::JobQueue(){
    q_front = NULL;
    q_back = NULL;
    len = 0;
    max_len = 3;
}

// 是否為空/滿
bool JobQueue::IsEmpty(){
    if(len<=0) return true;
    return false;
}
bool JobQueue::IsFull(){
    if(len>=max_len) return true;
    return false;
}

// 取得長度
int JobQueue::GetLength(){
    return len;
}

// EnQueue
void JobQueue::EnQueue( JobType job ){
    if(len==0){
        q_front = new JobNode;
        q_front->job = job;
        q_front->next = NULL;
        q_back = q_front;

    }
    else{
        q_back->next = new JobNode;
        q_back = q_back->next;
        q_back->job = job;
        q_back->next = NULL;
    }

    len += 1;
}

// Dequeue
void JobQueue::DeQueue(){
    if( IsEmpty() ) return;

    // 刪除 Node
    JobNode * temp = q_front;
    q_front = q_front->next;
    delete temp;

    len-=1;
    if(len==0){
        q_front = NULL;
        q_back = NULL;
    }
}
void JobQueue::DeQueue( JobType & job ){
    if( IsEmpty() ) return;

    job = q_front->job; // 取出 Job

    // 刪除 Node
    JobNode * temp = q_front;
    q_front = q_front->next;
    delete temp;

    len-=1;
    if(len==0){
        q_front = NULL;
        q_back = NULL;
    }
}

// GetFront
void JobQueue::GetFront(JobType & job ){
    job = q_front->job;
}

// ClearQ
void JobQueue::ClearQ(){
    while( !IsEmpty()){
        DeQueue();
    }
}

// ShowQueue
void JobQueue::ShowQueue(){
    JobNode * temp = q_front;
    int i = 0;

    cout << "     OID\tArrival\tDuration\tTimeOut\n";

    while( temp != NULL ){
        JobType jt_temp = temp->job;
        i += 1;

        cout << "(" << i << ")  ";
        cout << jt_temp.oid << "\t" << jt_temp.arrival << "\t" << jt_temp.duration << "\t" << jt_temp.timeout << endl;

        temp = temp->next;

    }
}






