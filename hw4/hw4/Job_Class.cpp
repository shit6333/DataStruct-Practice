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
    // �M���¸��
    Clear();

    // Ū���ɮ�
    ifstream infile;
    infile.open(filename);

    // Ū������
    if(infile.fail()){
        cout << "Fail to Read File" << endl;
    }
    else{
        // Ū�����\
        //string uid,arr,dur,timeout;
        string uid,arr,dur,timeout; // ?? Bug ?????????????????????????????????
        infile >> uid >> arr >> dur >> timeout; // ���L���Y��T

        int temp;
        while(!infile.eof()){
                infile >> uid >> arr >> dur >> timeout; // Ū���ɮ�

                int a,b,c,d;
                JobType data_line;

                // string �� int
                a = stoi(uid);
                b = stoi(arr);
                c = stoi(dur);
                d = stoi(timeout);

                // ����hŪ�̫�@��
                if(a == temp) break;
                temp = a;

                // �s�J list
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

