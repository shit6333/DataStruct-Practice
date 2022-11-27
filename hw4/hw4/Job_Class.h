#ifndef JOBCLASS
#define JOBCLASS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct JobType{
    int oid;
    int arrival;
    int duration;
    int timeout;
};

// ========================================================

class Jobs{
    vector<JobType> jobList;
    // string fileID;

public:
    Jobs( string filename);
    Jobs();
    void ShowJobs();
    void LoadJobList( string filename );
    void Clear();

    int GetSize();

    bool IsEmpty();
    JobType GetNextJob();

};



#endif // JOBCLASS
