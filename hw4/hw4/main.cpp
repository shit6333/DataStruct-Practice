#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include"Job_Class.h"
#include"Ans.h"
#include"Job_Queue.h"
#include"Simulation_Class.h"

using namespace std;


int main(){

    // 讀取 Job List
    Jobs jj("sort401.txt");
    jj.ShowJobs();

    cout << endl;

    // 創建 Ans List(fail,TimeOut)
    // AnsList ansList;
    // ansList.Add_FailList(101,2,3,4);
    // ansList.Show_FailList();
    // ansList.Add_TimeOutList(102,2,5,6);
    // ansList.Show_TimeOutList();

    cout << endl;

    // 使用工作 Queue
    /*JobType jt1 = jj.GetNextJob();

    JobQueue q;
    q.EnQueue( jt1 );
    q.ShowQueue();*/

    // q.GetFront(jt1);
    // q.ShowQueue();

    Simulation sim("sort401.txt");
    sim.Simulate();
    sim.ShowList();
}

