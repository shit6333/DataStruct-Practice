#include<iostream>
#include<fstream>   // Ū���ɮ�
#include<sstream>   // ���Φr��
#include<vector>    // Vector

using namespace std;

// ��ƳB�z���O
class DataProcess{
    public:
        void ReadData( ifstream & file, vector<vector<string>> & data_vec );                // �s�����
        void ReadLine( string line_str, vector<string> & line_vec );                         // �s���� line ���
        void PrintData( vector<vector<string>> & data_vec );                                 // �L�X���
        void DeleteLine( vector<vector<string>> & data_vec, int start_idx, int end_idx=-1 );// �R���Y Line (�i�[�Wend_idx �ӧR���h line ���)
        void OuputData( vector<vector<string>> & data_vec, string file_name );              // ��X�ɮ�
        void CleanData( vector<vector<string>> & data_vec );                                 // �M���Ҧ����

        string SetName( string origin_name, string new_head );                                // ��X�s�ɮצW�� (��l�ɮצW, �s�ɮ׶}�Y)

};

// �������O
class FileTask{
    public:
        string name;                            // �ɮצW��
        vector<vector<string>> data_vec;      // ��� vector
        DataProcess dp;                         // ��ƳB�z���O
        // --------------------------------
        void Copy();
        bool ReadFile( string filename );     // Ū�����
};



int main(){

    FileTask ft;
    ft.ReadFile("input201.txt");
    ft.Copy();

}



// =================================  FileTask ���O��� ========================================================

// �ƻs�ɮ�
void FileTask::Copy(){
    dp.DeleteLine( data_vec, 0, 2);
    dp.PrintData(data_vec);

    // ��X
    string output_name = dp.SetName( name, "copy" );
    ofstream  outfile( output_name );
    dp.OuputData( data_vec, output_name );
}


// Ū���ɮ�
bool FileTask::ReadFile( string filename ){
    // Ū���ɮ�
    ifstream infile( filename );

    // �T�{���LŪ���ɮ�
    if( infile.fail() ){
        cout << "Fail to read File" << endl;
        infile.close();                     // �����ɮ�
        return false;
    }

    else{
        cout << "Read File Success" << endl;
        name = filename;
        dp.ReadData( infile, data_vec );  // �s���ɮ�
        infile.close();                   // �����ɮ�
        return true;
    }
}


// =================================  DataProcess ���O��� ========================================================


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

// �x�s Data ���s�ɮ� (�νƼg�ɮ�)
void DataProcess::OuputData( vector<vector<string>> & data_vec, string file_name ){

    ofstream outfile(file_name);

    for ( int i=0 ; i < data_vec.size() ; i++ ){

        // �L�X1 line
        for ( int j=0 ; j < 11 ; j++ ){
            outfile << data_vec[i][j] << "\t";
        }
        outfile << endl;
    }
}


// �L�X Data
void DataProcess::PrintData( vector<vector<string>> & data_vec ){
    // �L�X Data
    for ( int i=0 ; i < data_vec.size() ; i++ ){
        cout << "[" << i+1 << "]\t";

        // �L�X1 line
        for ( int j=0 ; j < 11 ; j++ ){
            cout << data_vec[i][j] << "\t";
        }
        cout << endl;
    }
}


// �R�� Line
void DataProcess::DeleteLine( vector<vector<string>> & data_vec, int start_idx, int end_idx ){

    vector<vector<string>>::iterator it;   // ��m���Э��N��

    // �R��1 line
    if( end_idx == -1){
        it = data_vec.begin() + start_idx;        // ���o�n�R������m���N
        data_vec.erase(it);                       // �R����line
    }
    // �R���h�� line
    else{
        vector<vector<string>>::iterator it2;
        it = data_vec.begin() + start_idx;
        it2 = data_vec.begin() + end_idx;
        data_vec.erase(it, it2+1);
    }
}


// Ū�� Data
void DataProcess::ReadData( ifstream & file, vector<vector<string>> & data_vec){

    string line_str;    // line �r��

    while( getline( file, line_str, '\n' ) ){
        vector<string> line_vec;            // �s�W line_vec
        ReadLine(line_str, line_vec);        // �s�� line ���
        data_vec.push_back( line_vec );     // �N line_vec �[�J data_vec
    }
}

// Ū�� Line Data
void DataProcess::ReadLine( string line_str, vector<string> & line_vec ){

    stringstream ss(line_str);              // Ū�� line_str
    string str;

    // �s����� ( 11: �C line ��Ƽ� )
    for( int i = 0 ; i<11 ; i++ ){
        getline(ss, str, '\t');              // \t ���θ��
        line_vec.push_back( str );          // �s���Ӹ��
    }
}
