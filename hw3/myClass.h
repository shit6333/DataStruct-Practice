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

    void Push( bool isNum, string sym );          // 增加資料
    void Pop();                                  // 刪除資料(最後一筆)
    void Retrive( bool & isNum, string & sym );   // 取出最後一個資料
    void ShowAll();                              // 印出資料
    void ShowReverse();
    void PopAll();

    // Node * GetNode( int index );                 // 取出對應 index Node
    string GetTop();
    bool isEmpty();
    int GetLength();

};

// =========================================================================

class Manipulate_Stack{
private:
    string function_str;
    Stack symbol_st;    // 運算式 stack
    Stack postfix_st;   // 後序式 stack
    Stack infix_st;     // 中序式 stack
    Stack str_st;       // 字串 stack

    bool IsNum( char ch );  // 是否為數字
    bool IsBiggerSymbol( string new_sym, string old_sym );  // 比較運算子位階
    void Backward( bool back_to_end );                       // 往前取出 symbol stack
    void In2Postfix();                                        // 前序轉後續
    void Str2Stack( string str );                            // str 存入 stack
    Stack Reverse_Stack( Stack & old_st );                    // 反轉 stack (from str_st=>infix_str)

    int String2Int( string str );                           // string 轉 int
    int Calculate( int front_num, int back_number, string cal_operator );   // 四則運算

public:
    Manipulate_Stack();


    void String2Postfix( string str );  // string 轉後序式 stack
    void PrintPostFix();                 // 印出後序式
    int CalculatePostfix();              // 計算後序式 (會清空後序式)

};



#endif // MYCLASS

