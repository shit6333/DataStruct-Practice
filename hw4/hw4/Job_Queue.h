#ifndef JOBQUEUE
#define JOBQUEUE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include"Job_Class.h"

using namespace std;

struct JobNode{
    JobType job;
    JobNode * next;
};

class JobQueue{
    JobNode * q_front;
    JobNode * q_back;
    int len;
    int max_len;

public:
    JobQueue( int maxlen ); // Constructor
    JobQueue(); // Constructor

    bool IsEmpty(); // 是否為空
    bool IsFull() ; // 是否為滿

    int GetLength();// 取得 Queue 長度

    void EnQueue( JobType job );    // 加入 Queue
    void DeQueue();                 // 刪除元素
    void DeQueue( JobType & job );  // 取出且刪除元素
    void GetFront(JobType & job );  // 取出元素
    void ClearQ();                  // 清空 Queue
    void ShowQueue();               // 顯示 Queue
};


#endif // JOBQUEUE

