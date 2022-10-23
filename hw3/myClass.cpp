#include "myClass.h"
#include<iostream>
#include<string>

using namespace std;

//===================  Node ============================================================

Node::Node( bool isNum, string sym ){

    isNumber = isNum;
    symbol = sym;
    next = NULL;
}

//===================  Stack ============================================================

Stack::Stack(){
    head = NULL;
    len = 0;
}

// 增加節點
void Stack::Push( bool isNum, string sym ){

    if( isEmpty() ){
        len++;

        head = new Node( isNum, sym );
    }
    else{
        len++;
        Node * temp = head;
        head = new Node( isNum, sym );
        head->next = temp;
    }

}


// 刪除節點
void Stack::Pop(){
    if( isEmpty() ) return;
    if( len == 1 ){ // 只剩一個 Node
        delete head;
        head=NULL;
        len--;
    }
    else{
        Node * temp = head->next;
        delete head;
        head = temp;
        len--;
    }
}

// 刪除全部節點
void Stack::PopAll(){
    while( len > 0 ){
        Pop();
    }
}

// 取得最後一個 Node 資料
void Stack::Retrive( bool & isNum, string & sym ){
    isNum = head->isNumber;
    sym = head->symbol;
}

void Stack::ShowReverse(){
    ReversePrint( head );
}
void Stack::ReversePrint( Node * node ){
    if( node==NULL ) return;

    ReversePrint( node->next );
    cout << node->symbol << ",";
}

// 印出所有 Node 資訊
void Stack::ShowAll(){
    if(len==0) return;

    Node * temp = head;
    for( int i=0 ; i<len ; i++ ){
        cout << temp->symbol << ",";
        temp = temp->next;
    }
    cout << endl;
}

string Stack::GetTop(){
    return head->symbol;
}

// 是否為空
bool Stack::isEmpty(){
    if( len == 0 ) return true;
    else return false;
}

// 取得長度
int Stack::GetLength(){
   return len;
}

//============================================================

// 初始函數
Manipulate_Stack::Manipulate_Stack(){
    function_str = "0";
    function_Is_valid = true;
}

bool Manipulate_Stack::FunctionIsValid(){
    return function_Is_valid;
}

// 計算後序式 (計算完後序式會為空)
int Manipulate_Stack::CalculatePostfix(){
        Stack temp_st;
        int len = postfix_st.GetLength();

        for( int i=0 ; i < len ; i++ ){
            string temp_str;
            bool temp_isNum;

            postfix_st.Retrive( temp_isNum, temp_str );

            // 讀取到數字
            if( temp_isNum ){
                temp_st.Push( temp_isNum, temp_str );
                postfix_st.Pop();
            }
            // 讀取到運算元
            else{
                int back_number = String2Int( temp_st.GetTop() );
                temp_st.Pop();
                int front_number = String2Int( temp_st.GetTop() );
                temp_st.Pop();

                // "x / 0" 情況
                if( temp_str == "/" && back_number==0 ){
                    function_Is_valid = false;
                    return -999;
                }

                int cal = Calculate( front_number, back_number, temp_str );
                temp_st.Push( true, to_string(cal) );

                postfix_st.Pop();
            }

        }

        // 回傳計算結果
        int ans = String2Int( temp_st.GetTop() );
        temp_st.PopAll();
        return ans;
}

// 四則運算
int Manipulate_Stack::Calculate( int front_num, int back_number, string cal_operator ){
    if( cal_operator == "+" )
        return front_num + back_number;
    if( cal_operator == "-" )
        return front_num - back_number;
    if( cal_operator == "*" )
        return front_num * back_number;
    if( cal_operator == "/" )
        return front_num / back_number;

    return 0;
}


// 印出後序式
void Manipulate_Stack::PrintPostFix(){
    if( postfix_st.isEmpty() )
        String2Postfix( function_str );

    postfix_st.ShowAll();
}

// 將 string 轉為 postfix
void Manipulate_Stack::String2Postfix( string str ){
    function_str = str;
    postfix_st.PopAll();                           // 確保後序式 stack 為空

    Str2Stack( function_str );                     // string 存入 stack
    infix_st = Reverse_Stack( str_st );            // 反轉 string stack
    In2Postfix();                                  // 將中序式轉為後序式
    postfix_st = Reverse_Stack( postfix_st );      // 反轉後序式 stack ( 方便運算 )
}

//----------------------------------------------------


// 將中序轉為後序
void Manipulate_Stack::In2Postfix(){
    int len = infix_st.GetLength();

    for( int i=0 ; i < len ; i++ ){
        string str;
        bool isNumber;
        infix_st.Retrive( isNumber, str );

        // 字串為數字
        if( isNumber )
            postfix_st.Push( true, str );
        // 字串為運算元
        else{

            // sym stack 沒有運算元 ------------------------------------//
            if( symbol_st.isEmpty() ){
                symbol_st.Push( false, str );
            }
            // 運算原為 "(" 或 symbol stack 最上層為 "(" ----------------//
            else if( ( str == "(" || symbol_st.GetTop()=="(" ) && str !=")" )
                symbol_st.Push( false, str );
            // 新運算元位階高於前一運算元 ------------------------------------//
            else if( IsBiggerSymbol( str, symbol_st.GetTop() ) )  {
                symbol_st.Push( false, str );
            }
            // 新運算元位階低於前一運算元 --------------------------------------//
            else{
                // 讀到 ")"
                if( str == ")" ){
                    Backward( false );
                }
                // 取出舊運算元，直到新運算元位階高於舊的
                else{
                    string sym = symbol_st.GetTop();
                    while( !symbol_st.isEmpty() && sym != "(" && !IsBiggerSymbol( str, sym ) ){
                        postfix_st.Push( false, sym );
                        symbol_st.Pop();
                        if( !symbol_st.isEmpty() )  sym = symbol_st.GetTop();
                    }
                    symbol_st.Push( false, str);
                }
            }
        }

        infix_st.Pop();
    }

    // 取出剩餘運算元
    Backward( true );
}


// 是否為數字
bool Manipulate_Stack::IsNum( char ch ){
    if( ch >= '0' && ch<= '9' ) return true;
    return false;
}


// 新的 Symbol 是否比較大
bool Manipulate_Stack::IsBiggerSymbol( string new_sym, string old_sym ){
    if( (old_sym == "+" || old_sym == "-" ) && (new_sym=="*" || new_sym=="/") )
        return true;
    return false;
}


// 往前取出 symbol stack
void Manipulate_Stack::Backward( bool back_to_end ){
    if( symbol_st.isEmpty() ) return;
    while( !symbol_st.isEmpty() ){
        // 取出 symbol
        string sym = symbol_st.GetTop();
        symbol_st.Pop();
        // 遇到 "(" 停止取出
        if( sym == "(" && !back_to_end) return;
        // 放入後序式
        else postfix_st.Push( false, sym );
    }
}


// String 轉數字
int Manipulate_Stack::String2Int( string str ){
    return stoi(str);
}


// 將中序式字串轉為 stack
void Manipulate_Stack::Str2Stack( string str ){

    int j=-1;
    for( int i=0 ;i < str.length() ; i++ ){

        // 字元是數字，且到運算式尾端
        if( IsNum(str[i]) && i==str.length()-1 ){
            if( j==-1 ) j=i;
            string number_str = str.substr( j, i-j+1 ); // 加入數字字串
            str_st.Push( true, number_str );
        }
        // 字元是數字，且前一個不是數字
        else if( IsNum(str[i]) && j == -1 ){
            j=i;
        }
        // 字元不是數字，前依字元是數字
        else if( !IsNum(str[i]) && j != -1 ){
            string number_str = str.substr( j, i-j ); // 加入數字字串
            str_st.Push( true, number_str );
            string sym_str = str.substr( i, 1 );    // 加入運算子
            str_st.Push( false, sym_str);
            j=-1;
        }
        // 字元不是數字 (前一個也不是數字)
        else if( !IsNum(str[i]) && j == -1 ){
            string sym_str = str.substr( i, 1 );
            str_st.Push( false, sym_str);
        }
    }
}


// 反轉 Stack
Stack Manipulate_Stack::Reverse_Stack( Stack & old_st ){
    Stack new_st;
    int len = old_st.GetLength();

    for( int i=0 ; i<len ; i++ ){
        string temp_sym;
        bool temp_isNum;
        old_st.Retrive( temp_isNum, temp_sym);

        new_st.Push( temp_isNum, temp_sym );
        old_st.Pop();
    }

    return new_st;
}
