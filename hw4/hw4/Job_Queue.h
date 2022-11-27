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

    bool IsEmpty(); // �O�_����
    bool IsFull() ; // �O�_����

    int GetLength();// ���o Queue ����

    void EnQueue( JobType job );    // �[�J Queue
    void DeQueue();                 // �R������
    void DeQueue( JobType & job );  // ���X�B�R������
    void GetFront(JobType & job );  // ���X����
    void ClearQ();                  // �M�� Queue
    void ShowQueue();               // ��� Queue
};


#endif // JOBQUEUE

