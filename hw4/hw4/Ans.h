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
    // �[�J���
    void Add_FailList( int oid, int cid, int delay, int abort );
    void Add_TimeOutList( int oid, int cid, int delay, int departure );

    // �L�X���
    void Show_FailList();
    void Show_TimeOutList();

    // �M�� List
    void Clear();

    // ��X�έp��
    int GetSize();      // ���o������ƶq(����)
    int GetTotalDelay();// ���o Delay �`�M

    // ���O�_����
    bool FailListIsEmpty();
    bool TimeOutListIsEmpty();

};

#endif // ANS

