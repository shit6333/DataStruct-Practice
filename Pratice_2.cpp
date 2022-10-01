#include<iostream>
#include<fstream>   // Ū���ɮ�
#include<sstream>   // ���Φr��
#include<vector>    // Vector

using namespace std;

void ReadData( ifstream & file, vector<vector<string>> & data_vec);
void ReadLine( string line_str, vector<string> & line_vec );
void PrintData( vector<vector<string>> & data_vec );
void DeleteLine( vector<vector<string>> & data_vec, int start_idx, int end_idx=-1 );
void OuputData( vector<vector<string>> & data_vec, string file_name );



int main(){

    // Ū���ɮ�
    ifstream infile("input201.txt");

    // �T�{���LŪ���ɮ�
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

// �x�s Data ���s�ɮ� (�νƼg�ɮ�)
void OuputData( vector<vector<string>> & data_vec, string file_name ){

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
void PrintData( vector<vector<string>> & data_vec ){
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
void DeleteLine( vector<vector<string>> & data_vec, int start_idx, int end_idx ){

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
void ReadData( ifstream & file, vector<vector<string>> & data_vec){

    string line_str;    // line �r��

    while( getline( file, line_str, '\n' ) ){
        vector<string> line_vec;            // �s�W line_vec
        ReadLine(line_str, line_vec);        // �s�� line ���
        data_vec.push_back( line_vec );     // �N line_vec �[�J data_vec
    }
}

// Ū�� Line Data
void ReadLine( string line_str, vector<string> & line_vec ){

    stringstream ss(line_str);              // Ū�� line_str
    string str;

    // �s����� ( 11: �C line ��Ƽ� )
    for( int i = 0 ; i<11 ; i++ ){
        getline(ss, str, '\t');              // \t ���θ��
        line_vec.push_back( str );          // �s���Ӹ��
    }
}
