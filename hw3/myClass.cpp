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

// �W�[�`�I
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


// �R���`�I
void Stack::Pop(){
    if( isEmpty() ) return;
    if( len == 1 ){ // �u�Ѥ@�� Node
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

// �R�������`�I
void Stack::PopAll(){
    while( len > 0 ){
        Pop();
    }
}

// ���o�̫�@�� Node ���
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

// �L�X�Ҧ� Node ��T
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

// �O�_����
bool Stack::isEmpty(){
    if( len == 0 ) return true;
    else return false;
}

// ���o����
int Stack::GetLength(){
   return len;
}

//============================================================

// ��l���
Manipulate_Stack::Manipulate_Stack(){
    function_str = "0";
    function_Is_valid = true;
}

bool Manipulate_Stack::FunctionIsValid(){
    return function_Is_valid;
}

// �p���Ǧ� (�p�⧹��Ǧ��|����)
int Manipulate_Stack::CalculatePostfix(){
        Stack temp_st;
        int len = postfix_st.GetLength();

        for( int i=0 ; i < len ; i++ ){
            string temp_str;
            bool temp_isNum;

            postfix_st.Retrive( temp_isNum, temp_str );

            // Ū����Ʀr
            if( temp_isNum ){
                temp_st.Push( temp_isNum, temp_str );
                postfix_st.Pop();
            }
            // Ū����B�⤸
            else{
                int back_number = String2Int( temp_st.GetTop() );
                temp_st.Pop();
                int front_number = String2Int( temp_st.GetTop() );
                temp_st.Pop();

                // "x / 0" ���p
                if( temp_str == "/" && back_number==0 ){
                    function_Is_valid = false;
                    return -999;
                }

                int cal = Calculate( front_number, back_number, temp_str );
                temp_st.Push( true, to_string(cal) );

                postfix_st.Pop();
            }

        }

        // �^�ǭp�⵲�G
        int ans = String2Int( temp_st.GetTop() );
        temp_st.PopAll();
        return ans;
}

// �|�h�B��
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


// �L�X��Ǧ�
void Manipulate_Stack::PrintPostFix(){
    if( postfix_st.isEmpty() )
        String2Postfix( function_str );

    postfix_st.ShowAll();
}

// �N string �ର postfix
void Manipulate_Stack::String2Postfix( string str ){
    function_str = str;
    postfix_st.PopAll();                           // �T�O��Ǧ� stack ����

    Str2Stack( function_str );                     // string �s�J stack
    infix_st = Reverse_Stack( str_st );            // ���� string stack
    In2Postfix();                                  // �N���Ǧ��ର��Ǧ�
    postfix_st = Reverse_Stack( postfix_st );      // �����Ǧ� stack ( ��K�B�� )
}

//----------------------------------------------------


// �N�����ର���
void Manipulate_Stack::In2Postfix(){
    int len = infix_st.GetLength();

    for( int i=0 ; i < len ; i++ ){
        string str;
        bool isNumber;
        infix_st.Retrive( isNumber, str );

        // �r�ꬰ�Ʀr
        if( isNumber )
            postfix_st.Push( true, str );
        // �r�ꬰ�B�⤸
        else{

            // sym stack �S���B�⤸ ------------------------------------//
            if( symbol_st.isEmpty() ){
                symbol_st.Push( false, str );
            }
            // �B��쬰 "(" �� symbol stack �̤W�h�� "(" ----------------//
            else if( ( str == "(" || symbol_st.GetTop()=="(" ) && str !=")" )
                symbol_st.Push( false, str );
            // �s�B�⤸�춥����e�@�B�⤸ ------------------------------------//
            else if( IsBiggerSymbol( str, symbol_st.GetTop() ) )  {
                symbol_st.Push( false, str );
            }
            // �s�B�⤸�춥�C��e�@�B�⤸ --------------------------------------//
            else{
                // Ū�� ")"
                if( str == ")" ){
                    Backward( false );
                }
                // ���X�¹B�⤸�A����s�B�⤸�춥�����ª�
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

    // ���X�Ѿl�B�⤸
    Backward( true );
}


// �O�_���Ʀr
bool Manipulate_Stack::IsNum( char ch ){
    if( ch >= '0' && ch<= '9' ) return true;
    return false;
}


// �s�� Symbol �O�_����j
bool Manipulate_Stack::IsBiggerSymbol( string new_sym, string old_sym ){
    if( (old_sym == "+" || old_sym == "-" ) && (new_sym=="*" || new_sym=="/") )
        return true;
    return false;
}


// ���e���X symbol stack
void Manipulate_Stack::Backward( bool back_to_end ){
    if( symbol_st.isEmpty() ) return;
    while( !symbol_st.isEmpty() ){
        // ���X symbol
        string sym = symbol_st.GetTop();
        symbol_st.Pop();
        // �J�� "(" ������X
        if( sym == "(" && !back_to_end) return;
        // ��J��Ǧ�
        else postfix_st.Push( false, sym );
    }
}


// String ��Ʀr
int Manipulate_Stack::String2Int( string str ){
    return stoi(str);
}


// �N���Ǧ��r���ର stack
void Manipulate_Stack::Str2Stack( string str ){

    int j=-1;
    for( int i=0 ;i < str.length() ; i++ ){

        // �r���O�Ʀr�A�B��B�⦡����
        if( IsNum(str[i]) && i==str.length()-1 ){
            if( j==-1 ) j=i;
            string number_str = str.substr( j, i-j+1 ); // �[�J�Ʀr�r��
            str_st.Push( true, number_str );
        }
        // �r���O�Ʀr�A�B�e�@�Ӥ��O�Ʀr
        else if( IsNum(str[i]) && j == -1 ){
            j=i;
        }
        // �r�����O�Ʀr�A�e�̦r���O�Ʀr
        else if( !IsNum(str[i]) && j != -1 ){
            string number_str = str.substr( j, i-j ); // �[�J�Ʀr�r��
            str_st.Push( true, number_str );
            string sym_str = str.substr( i, 1 );    // �[�J�B��l
            str_st.Push( false, sym_str);
            j=-1;
        }
        // �r�����O�Ʀr (�e�@�Ӥ]���O�Ʀr)
        else if( !IsNum(str[i]) && j == -1 ){
            string sym_str = str.substr( i, 1 );
            str_st.Push( false, sym_str);
        }
    }
}


// ���� Stack
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
