#include"Job_Class.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Constructor
Jobs::Jobs( string filename){
    LoadJobList(filename);
}
Jobs::Jobs(){
    LoadJobList("sort401.txt");
}

// Load_Job_List
void Jobs::LoadJobList( string filename ){
    // 清除舊資料
    Clear();

    // 讀取檔案
    ifstream infile;
    infile.open(filename);

    // 讀取失敗
    if(infile.fail()){
        cout << "Fail to Read File" << endl;
    }
    else{
        // 讀取成功
        //string uid,arr,dur,timeout;
        string uid,arr,dur,timeout; // ?? Bug ?????????????????????????????????
        infile >> uid >> arr >> dur >> timeout; // 掠過標頭資訊

        int temp;
        while(!infile.eof()){
                infile >> uid >> arr >> dur >> timeout; // 讀取檔案

                int a,b,c,d;
                JobType data_line;

                // string 轉 int
                a = stoi(uid);
                b = stoi(arr);
                c = stoi(dur);
                d = stoi(timeout);

                // 防止多讀最後一行
                if(a == temp) break;
                temp = a;

                // 存入 list
                data_line.oid = a;
                data_line.arrival = b;
                data_line.duration = c;
                data_line.timeout = d;
                jobList.push_back(data_line);
        }
    }
}


// ShowJobs()
void Jobs::ShowJobs(){
    cout << "\tOID\tArrival\tDuration\tTimeOut\n";
    for( int i=0; i<jobList.size();i++){
        cout << "(" << i+1 << ")\t";
        cout << jobList[i].oid << "\t" << jobList[i].arrival << "\t" << jobList[i].duration << "\t" << jobList[i].timeout << endl;
    }
}

// IsEmpty()
bool Jobs::IsEmpty(){
    return jobList.empty();
}



// GetNextJob()
JobType Jobs::GetNextJob(){

    JobType temp = jobList[0];
    jobList.erase(jobList.begin());
    return temp;
}

// Clear()
void Jobs::Clear(){
    while(!IsEmpty()){
        GetNextJob();
    }
}

// GetSize()
int Jobs::GetSize(){
    return jobList.size();
}

