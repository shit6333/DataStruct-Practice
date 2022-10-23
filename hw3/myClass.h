#ifndef MYCLASS
#define MYCLASS
#include<string>

using namespace std;

class Node{
public:
    bool isNumber;
    string symbol;
    Node * next;

    Node( bool isNum, string sym );
};

// =========================================================================

class Stack{

private:
    Node * head;
    int len;

    void ReversePrint( Node * node );

public:
    Stack();

    void Push( bool isNum, string sym );          // �W�[���
    void Pop();                                  // �R�����(�̫�@��)
    void Retrive( bool & isNum, string & sym );   // ���X�̫�@�Ӹ��
    void ShowAll();                              // �L�X���
    void ShowReverse();
    void PopAll();

    // Node * GetNode( int index );                 // ���X���� index Node
    string GetTop();
    bool isEmpty();
    int GetLength();

};

// =========================================================================

class Manipulate_Stack{
private:
    string function_str;
    Stack symbol_st;    // �B�⦡ stack
    Stack postfix_st;   // ��Ǧ� stack
    Stack infix_st;     // ���Ǧ� stack
    Stack str_st;       // �r�� stack

    bool IsNum( char ch );  // �O�_���Ʀr
    bool IsBiggerSymbol( string new_sym, string old_sym );  // ����B��l�춥
    void Backward( bool back_to_end );                       // ���e���X symbol stack
    void In2Postfix();                                        // �e�������
    void Str2Stack( string str );                            // str �s�J stack
    Stack Reverse_Stack( Stack & old_st );                    // ���� stack (from str_st=>infix_str)

    int String2Int( string str );                           // string �� int
    int Calculate( int front_num, int back_number, string cal_operator );   // �|�h�B��

public:
    Manipulate_Stack();


    void String2Postfix( string str );  // string ���Ǧ� stack
    void PrintPostFix();                 // �L�X��Ǧ�
    int CalculatePostfix();              // �p���Ǧ� (�|�M�ū�Ǧ�)

};



#endif // MYCLASS

