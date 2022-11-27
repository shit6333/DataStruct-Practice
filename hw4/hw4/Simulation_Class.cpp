#include"Simulation_Class.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Constructor
Simulation::Simulation( string jobList_name ){
    jobList.LoadJobList( jobList_name );
    count_of_data = jobList.GetSize();
}



// Simulate
void Simulation::Simulate(){

    if(jobList.IsEmpty()) return;   // �� job list

    int curr_time = 0;
    int start_work_time = 0;

    JobQueue job_Queue;
    JobType watting_job = jobList.GetNextJob();
    JobType working_job;
    working_job.oid = 0;


    // Time Line

    for( curr_time=0 ; !jobList.IsEmpty() || !job_Queue.IsEmpty() ; curr_time++ ){

        // �ˬd�����u�@  ----------------------------------------------------------------------------------------
        Check_Work_Done( 1, working_job, curr_time, start_work_time);

        // �]�w�u�@  ----------------------------------------------------------------------------------------
        if( working_job.oid == 0 && !job_Queue.IsEmpty() ){
            job_Queue.DeQueue( working_job );
            // �o�{ Timeout
            while( (curr_time >= working_job.timeout )){
                ansList.Add_FailList( working_job.oid, 1, curr_time-working_job.arrival, curr_time);    // �ߧY����

                if(!job_Queue.IsEmpty()) job_Queue.DeQueue( working_job );
                else{
                    working_job.oid = 0;
                    break;
                }
            }
            if( working_job.oid != 0 ) start_work_time = curr_time;   // �]�w�s�� job �}�l�ɶ�
        }

        // Watting Job Arrival ----------------------------------------------------------------------------------------

        while( watting_job.arrival <= curr_time && watting_job.oid != 0 ){  // watting_job.oid == 0 �N�� watting �M��
            // Queue ����
            if( !job_Queue.IsFull() ){
                job_Queue.EnQueue( watting_job );    // �[�J�s�u�@
            }
            // Queue �w��
            else{
                ansList.Add_FailList( watting_job.oid, 1, 0, curr_time);    // �ߧY����
            }
            // Ū���s�� watting job
            if(jobList.IsEmpty())
                watting_job.oid = 0;
            else
                watting_job = jobList.GetNextJob();
        }

        // �ˬd�����u�@  ----------------------------------------------------------------------------------------
        Check_Work_Done( 1, working_job, curr_time, start_work_time);

        // �]�w�u�@  ----------------------------------------------------------------------------------------
        if( working_job.oid == 0 && !job_Queue.IsEmpty() ){
            job_Queue.DeQueue( working_job );
            // �o�{ Timeout
            while( (curr_time >= working_job.timeout )){
                ansList.Add_FailList( working_job.oid, 1, curr_time-working_job.arrival, curr_time);    // �ߧY����

                if(!job_Queue.IsEmpty()) job_Queue.DeQueue( working_job );
                else{
                    working_job.oid = 0;
                    break;
                }
            }
            if( working_job.oid != 0 ) start_work_time = curr_time;   // �]�w�s�� job �}�l�ɶ�
        }
    }
}


// Simulate2
void Simulation::Simulate2(){

    if(jobList.IsEmpty()) return;   // �� job list

    int curr_time = 0;
    int start_work_time1 = 0;
    int start_work_time2 = 0;

    JobQueue job_Queue1;
    JobQueue job_Queue2;

    JobType watting_job = jobList.GetNextJob();

    JobType working_job1;
    JobType working_job2;
    working_job1.oid = 0;
    working_job2.oid = 0;

    // Time Line
    for( curr_time=0 ; !jobList.IsEmpty() || !job_Queue1.IsEmpty() || !job_Queue2.IsEmpty() || working_job1.oid!=0 || working_job2.oid!=0 ; curr_time++ ){

        // �ˬd�����u�@  ----------------------------------------------------------------------------------------
        Check_Work_Done( 1, working_job1, curr_time, start_work_time1); // �ˬd�u�@�� 1
        Check_Work_Done( 2, working_job2, curr_time, start_work_time2); // �ˬd�u�@�� 2
        // �]�w�u�@  ----------------------------------------------------------------------------------------
        // �]�w�u�@�� 1
        if( working_job1.oid == 0 && !job_Queue1.IsEmpty() ){
            job_Queue1.DeQueue( working_job1 );

            // �o�{ Timeout
            while( (curr_time >= working_job1.timeout )){
                ansList.Add_FailList( working_job1.oid, 1, curr_time-working_job1.arrival, curr_time);    // �ߧY����
                if(!job_Queue1.IsEmpty()) job_Queue1.DeQueue( working_job1 );
                else{
                    working_job1.oid = 0;
                    break;
                }
            }
            if( working_job1.oid != 0 ) start_work_time1 = curr_time;   // �]�w�s�� job �}�l�ɶ�
        }
        // �]�w�u�@�� 2
        if( working_job2.oid == 0 && !job_Queue2.IsEmpty() ){
            job_Queue2.DeQueue( working_job2 );

            // �o�{ Timeout
            while( (curr_time >= working_job2.timeout )){
                ansList.Add_FailList( working_job2.oid, 2, curr_time-working_job2.arrival, curr_time);    // �ߧY����
                if(!job_Queue2.IsEmpty()) job_Queue2.DeQueue( working_job2 );
                else{
                    working_job2.oid = 0;
                    break;
                }
            }
            if( working_job2.oid != 0 ) start_work_time2 = curr_time;   // �]�w�s�� job �}�l�ɶ�
        }


        // Watting Job Arrival ----------------------------------------------------------------------------------------

        while( watting_job.arrival <= curr_time && watting_job.oid != 0  ){  // watting_job.oid == 0 �N�� watting �M��

            // cout << "===================\n";
            // cout << "t = " << curr_time << endl;
            // cout << "work 1:" << working_job1.oid << " , Len : " << job_Queue1.GetLength() << endl;
            // cout << "work 2:" << working_job2.oid << " , Len : " << job_Queue2.GetLength() << endl;
            // cout << "Watting Job: " << watting_job.oid << endl;

            // �u���@�춢�m
            if( (working_job1.oid==0 && working_job2.oid!=0) || (working_job2.oid==0 && working_job1.oid!=0) ){
                if(working_job1.oid==0) job_Queue1.EnQueue( watting_job );
                else job_Queue2.EnQueue(watting_job);
            }
            // ���Ҷ��m
            else if( working_job1.oid==0 && working_job2.oid==0){
                job_Queue1.EnQueue(watting_job);
            }
            // �Ҥ����m�A���ܤ� 1 Queue �i�ƶ�
            else if( !job_Queue1.IsFull() || !job_Queue2.IsFull() ){
                if( job_Queue1.GetLength() > job_Queue2.GetLength() )       job_Queue2.EnQueue(watting_job);
                else if( job_Queue1.GetLength() < job_Queue2.GetLength() )  job_Queue1.EnQueue(watting_job);
                else job_Queue1.EnQueue(watting_job);
            }
            // Queue ����
            else{
                ansList.Add_FailList( watting_job.oid, 0, 0, curr_time);
            }


            // Ū���s�� watting job
            if(jobList.IsEmpty())
                watting_job.oid = 0;
            else
                watting_job = jobList.GetNextJob();
        }

        // �ˬd�����u�@  ----------------------------------------------------------------------------------------
        Check_Work_Done( 1, working_job1, curr_time, start_work_time1); // �ˬd�u�@�� 1
        Check_Work_Done( 2, working_job2, curr_time, start_work_time2); // �ˬd�u�@�� 2

        // �]�w�u�@  ----------------------------------------------------------------------------------------

        // �]�w�u�@�� 1
        if( working_job1.oid == 0 && !job_Queue1.IsEmpty() ){
            job_Queue1.DeQueue( working_job1 );

            // �o�{ Timeout
            while( (curr_time >= working_job1.timeout )){
                ansList.Add_FailList( working_job1.oid, 1, curr_time-working_job1.arrival, curr_time);    // �ߧY����
                if(!job_Queue1.IsEmpty()) job_Queue1.DeQueue( working_job1 );
                else{
                    working_job1.oid = 0;
                    break;
                }
            }
            if( working_job1.oid != 0 ) start_work_time1 = curr_time;   // �]�w�s�� job �}�l�ɶ�
        }

        // �]�w�u�@�� 2
        if( working_job2.oid == 0 && !job_Queue2.IsEmpty() ){
            job_Queue2.DeQueue( working_job2 );

            // �o�{ Timeout
            while( (curr_time >= working_job2.timeout )){
                ansList.Add_FailList( working_job2.oid, 2, curr_time-working_job2.arrival, curr_time);    // �ߧY����
                if(!job_Queue2.IsEmpty()) job_Queue2.DeQueue( working_job2 );
                else{
                    working_job2.oid = 0;
                    break;
                }
            }
            if( working_job2.oid != 0 ) start_work_time2 = curr_time;   // �]�w�s�� job �}�l�ɶ�
        }
    }
}


void Simulation::Check_Work_Done( int cid, JobType & working_job, int curr_time, int start_work_time ){
    // �ˬd�u�@��
    if( working_job.oid != 0 ){
        int end_job_time = start_work_time + working_job.duration;  // �u�@�����ɶ�

        // �����u�@
        if( end_job_time == curr_time ){
            // Timeout
            if( end_job_time > working_job.timeout ){
                ansList.Add_TimeOutList( working_job.oid, cid, start_work_time-working_job.arrival, end_job_time );   // �[�J timeout list
            }
            working_job.oid = 0;
        }
    }
}



// Calculate Ans
void Simulation::Calculate_Ans(){
    total_delay = ansList.GetTotalDelay();                                         // �p�� Total Delay
    fail_Percentage = 100*((float)ansList.GetSize() / (float)count_of_data);     // �p�� fail_percentage
}

// showList
void Simulation::ShowList(){
    ansList.Show_FailList();
    ansList.Show_TimeOutList();

    Calculate_Ans();

    cout << "[Total Delay]\n";
    cout << total_delay << " min.\n";
    cout << "[Failure Percentage]\n";
    cout << round(fail_Percentage*100)/100 << " %\n";
}
