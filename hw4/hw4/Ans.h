#ifndef ANS
#define ANS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct FailType{
    int oid;
    int cid;
    int delay;
    int abort;
};

struct TimeOutType{
    int oid;
    int cid;
    int delay;
    int departure;
};

// ====================================

class AnsList {

    vector<FailType> failList;
    vector<TimeOutType> timeoutList;

public:
    // 加入表單
    void Add_FailList( int oid, int cid, int delay, int abort );
    void Add_TimeOutList( int oid, int cid, int delay, int departure );

    // 印出表單
    void Show_FailList();
    void Show_TimeOutList();

    // 清空 List
    void Clear();

    // 輸出統計值
    int GetSize();      // 取得全部資料量(兩表單)
    int GetTotalDelay();// 取得 Delay 總和

    // 表單是否為空
    bool FailListIsEmpty();
    bool TimeOutListIsEmpty();

};

#endif // ANS

