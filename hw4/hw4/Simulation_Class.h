#ifndef SIMULATION
#define SIMULATION

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include"Job_Class.h"
#include"Ans.h"
#include"Job_Queue.h"

class Simulation{

    AnsList ansList;
    Jobs jobList;

    JobQueue job_Queue1;
    JobQueue job_Queue2;

    // �έp��
    int count_of_data;  // data �`��
    int total_delay;
    float fail_Percentage;

    // private ��k
    void Calculate_Ans();
    void Check_Work_Done( int cid, JobType & working_job, int curr_time, int start_work_time );

public:
    Simulation( string jobList_name );
    void Simulate();
    void Simulate2();

    void ShowList();

};

#endif // SIMULATION

