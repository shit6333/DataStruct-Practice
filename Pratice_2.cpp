#include<iostream>
#include<fstream>   // 讀取檔案
#include<sstream>   // 切割字串
#include<vector>    // Vector

using namespace std;

// 資料處理類別
class DataProcess{
    public:
        void ReadData( ifstream & file, vector<vector<string>> & data_vec );                // 存取資料
        void ReadLine( string line_str, vector<string> & line_vec );                         // 存取該 line 資料
        void PrintData( vector<vector<string>> & data_vec );                                 // 印出資料
        void DeleteLine( vector<vector<string>> & data_vec, int start_idx, int end_idx=-1 );// 刪除某 Line (可加上end_idx 來刪除多 line 資料)
        void OuputData( vector<vector<string>> & data_vec, string file_name );              // 輸出檔案
        void CleanData( vector<vector<string>> & data_vec );                                 // 清除所有資料

        string SetName( string origin_name, string new_head );                                // 輸出新檔案名稱 (原始檔案名, 新檔案開頭)

};

// 任務類別
class FileTask{
    public:
        string name;                            // 檔案名稱
        vector<vector<string>> data_vec;      // 資料 vector
        DataProcess dp;                         // 資料處理類別
        // --------------------------------
        void Copy();
        bool ReadFile( string filename );     // 讀取資料
};



int main(){

    FileTask ft;
    ft.ReadFile("input201.txt");
    ft.Copy();

}



// =================================  FileTask 類別函數 ========================================================

// 複製檔案
void FileTask::Copy(){
    dp.DeleteLine( data_vec, 0, 2);
    dp.PrintData(data_vec);

    // 輸出
    string output_name = dp.SetName( name, "copy" );
    ofstream  outfile( output_name );
    dp.OuputData( data_vec, output_name );
}


// 讀取檔案
bool FileTask::ReadFile( string filename ){
    // 讀取檔案
    ifstream infile( filename );

    // 確認有無讀取檔案
    if( infile.fail() ){
        cout << "Fail to read File" << endl;
        infile.close();                     // 關閉檔案
        return false;
    }

    else{
        cout << "Read File Success" << endl;
        name = filename;
        dp.ReadData( infile, data_vec );  // 存取檔案
        infile.close();                   // 關閉檔案
        return true;
    }
}


// =================================  DataProcess 類別函數 ========================================================


string DataProcess::SetName( string origin_name, string new_head ){

    string new_name = "";

    for (int i=5 ; origin_name[i] != '.' ; i++ ){
        new_name += origin_name[i];
    }

    new_name = new_head + new_name + ".txt";
    return new_name;
}


void DataProcess::CleanData( vector<vector<string>> & data_vec ){
    data_vec.clear();
}

// 儲存 Data 為新檔案 (或複寫檔案)
void DataProcess::OuputData( vector<vector<string>> & data_vec, string file_name ){

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
void DataProcess::PrintData( vector<vector<string>> & data_vec ){
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
void DataProcess::DeleteLine( vector<vector<string>> & data_vec, int start_idx, int end_idx ){

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
void DataProcess::ReadData( ifstream & file, vector<vector<string>> & data_vec){

    string line_str;    // line 字串

    while( getline( file, line_str, '\n' ) ){
        vector<string> line_vec;            // 新增 line_vec
        ReadLine(line_str, line_vec);        // 存取 line 資料
        data_vec.push_back( line_vec );     // 將 line_vec 加入 data_vec
    }
}

// 讀取 Line Data
void DataProcess::ReadLine( string line_str, vector<string> & line_vec ){

    stringstream ss(line_str);              // 讀取 line_str
    string str;

    // 存取資料 ( 11: 每 line 資料數 )
    for( int i = 0 ; i<11 ; i++ ){
        getline(ss, str, '\t');              // \t 切割資料
        line_vec.push_back( str );          // 存取該資料
    }
}
