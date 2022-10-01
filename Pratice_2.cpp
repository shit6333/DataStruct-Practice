#include<iostream>
#include<fstream>   // 讀取檔案
#include<sstream>   // 切割字串
#include<vector>    // Vector

using namespace std;

void ReadData( ifstream & file, vector<vector<string>> & data_vec);
void ReadLine( string line_str, vector<string> & line_vec );
void PrintData( vector<vector<string>> & data_vec );
void DeleteLine( vector<vector<string>> & data_vec, int start_idx, int end_idx=-1 );
void OuputData( vector<vector<string>> & data_vec, string file_name );



int main(){

    // 讀取檔案
    ifstream infile("input201.txt");

    // 確認有無讀取檔案
    if( infile.fail() )
        cout << "Fail to read File" << endl;
    else
        cout << "Read File Success" << endl;


    vector<vector<string>> data_vec;

    ReadData( infile, data_vec );
    DeleteLine( data_vec, 0, 2);
    PrintData(data_vec);

    ofstream  outfile("test_copy.txt");
    OuputData( data_vec, "test_copy.txt");


    infile.close();
}

// 儲存 Data 為新檔案 (或複寫檔案)
void OuputData( vector<vector<string>> & data_vec, string file_name ){

    ofstream outfile(file_name);

    for ( int i=0 ; i < data_vec.size() ; i++ ){

        // 印出1 line
        for ( int j=0 ; j < 11 ; j++ ){
            outfile << data_vec[i][j] << "\t";
        }
        outfile << endl;
    }
}


// 印出 Data
void PrintData( vector<vector<string>> & data_vec ){
    // 印出 Data
    for ( int i=0 ; i < data_vec.size() ; i++ ){
        cout << "[" << i+1 << "]\t";

        // 印出1 line
        for ( int j=0 ; j < 11 ; j++ ){
            cout << data_vec[i][j] << "\t";
        }
        cout << endl;
    }
}


// 刪除 Line
void DeleteLine( vector<vector<string>> & data_vec, int start_idx, int end_idx ){

    vector<vector<string>>::iterator it;   // 位置指標迭代器

    // 刪除1 line
    if( end_idx == -1){
        it = data_vec.begin() + start_idx;        // 取得要刪除的位置迭代
        data_vec.erase(it);                       // 刪除該line
    }
    // 刪除多個 line
    else{
        vector<vector<string>>::iterator it2;
        it = data_vec.begin() + start_idx;
        it2 = data_vec.begin() + end_idx;
        data_vec.erase(it, it2+1);
    }
}


// 讀取 Data
void ReadData( ifstream & file, vector<vector<string>> & data_vec){

    string line_str;    // line 字串

    while( getline( file, line_str, '\n' ) ){
        vector<string> line_vec;            // 新增 line_vec
        ReadLine(line_str, line_vec);        // 存取 line 資料
        data_vec.push_back( line_vec );     // 將 line_vec 加入 data_vec
    }
}

// 讀取 Line Data
void ReadLine( string line_str, vector<string> & line_vec ){

    stringstream ss(line_str);              // 讀取 line_str
    string str;

    // 存取資料 ( 11: 每 line 資料數 )
    for( int i = 0 ; i<11 ; i++ ){
        getline(ss, str, '\t');              // \t 切割資料
        line_vec.push_back( str );          // 存取該資料
    }
}
