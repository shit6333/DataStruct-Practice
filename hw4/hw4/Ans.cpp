#include"Ans.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


// 加入資料
void AnsList::Add_FailList( int oid, int cid, int delay, int abort ){

    FailType temp;
    temp.oid = oid;
    temp.cid = cid;
    temp.delay = delay;
    temp.abort = abort;

    failList.push_back(temp);
}
void AnsList::Add_TimeOutList( int oid, int cid, int delay, int departure ){

    TimeOutType temp;
    temp.oid = oid;
    temp.cid = cid;
    temp.delay = delay;
    temp.departure = departure;

    timeoutList.push_back(temp);

}

// 印出 List 資訊
void AnsList::Show_FailList(){
    cout << "\tOID\tCID\tDelay\tAbort\n";
    for(int i=0; i<failList.size(); i++){
        cout << "[" << i+1 << "] \t";
        cout << failList[i].oid << "\t" << failList[i].cid << "\t" << failList[i].delay << "\t" << failList[i].abort << endl;
    }
}
void AnsList::Show_TimeOutList(){
    cout << "\t[Timeout List]\n";
    cout << "\tOID\tCID\tDelay\tDeparture\n";
    for(int i=0; i<timeoutList.size(); i++){
        cout << "[" << i+1 << "]\t";
        cout << timeoutList[i].oid << "\t" << timeoutList[i].cid << "\t" << timeoutList[i].delay << "\t" << timeoutList[i].departure << endl;
    }
}

// Clear
void AnsList::Clear(){
    failList.clear();
    timeoutList.clear();
}

// 是否為空
bool AnsList::FailListIsEmpty(){
    return failList.empty();
}
bool AnsList::TimeOutListIsEmpty(){
    return timeoutList.empty();
}


// 計算統計值
int AnsList::GetSize(){
    return failList.size() + timeoutList.size();
}

int AnsList::GetTotalDelay(){
    int sum = 0;
    for(int i=0; i<failList.size(); i++){
        sum += failList[i].delay;
    }
        for(int i=0; i<timeoutList.size(); i++){
        sum += timeoutList[i].delay;
    }
    return sum;
}


