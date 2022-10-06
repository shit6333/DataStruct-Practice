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


        string SetName( int title_length , string origin_name, string new_head );            // ��X�s�ɮצW�� ( ���ɶ}�Y�r����, ��l�ɮצW, �s�ɮ׶}�Y )
        string SetOuputTitle( string name1 );                                                 // �]�w case3 �� output �ɮ� title

        vector<string> GetUniqueData( vector<vector<string>> data_vec, int data_colunm );   // ���o unique data
        vector<vector<string>> UniqueSort( vector<vector<string>> data_vec, int data_column, vector<string> unique_data );  // �̷� unique_data �Ƨ� data
};

// �������O
class FileTask{
    public:
        string name1;                              // �ɮצW��
        string name2;                              // �X���ɮצW��
        DataProcess dp;                            // ��ƳB�z���O
        vector<vector<string>> data_vec_1;      // ��� vector
        vector<vector<string>> data_vec_2;      // �ΥH�x�s�n�X�֪� data

        // --------------------------------

        void Copy( vector<vector<string>> & data_vec );
        void Combine( vector<vector<string>> & data_vec1, vector<vector<string>> & data_vec2 );
        bool ReadFile( string filename, vector<vector<string>> & data_vec, string & name );     // Ū�����
};



int main(){

    FileTask ft;
    // ft.ReadFile("input202.txt", ft.data_vec_1 );
    // ft.Copy( ft.data_vec_1 );

    ft.ReadFile("copy204.txt", ft.data_vec_1, ft.name1 );
    ft.ReadFile("copy205.txt", ft.data_vec_2, ft.name2 );

    ft.Combine( ft.data_vec_1, ft.data_vec_2 );

}



// =================================  FileTask ���O��� ========================================================

// �X���ɮ�
void FileTask::Combine( vector<vector<string>> & data_vec1, vector<vector<string>> & data_vec2 ){
    // �X���ɮ�
    data_vec1.insert( data_vec1.end(), data_vec2.begin(), data_vec2.end() );

    // �ά�t�W�Ƨ�
    vector<string> unique_data = dp.GetUniqueData( data_vec1, 3);
    vector<vector<string>> sort_data_vec = dp.UniqueSort( data_vec1, 3, unique_data );
    // �ξǮզW�Ƨ�
    unique_data = dp.GetUniqueData( data_vec1, 1);
    sort_data_vec = dp.UniqueSort( sort_data_vec, 1, unique_data );

    // �]�w��X�ɮצW
    string title = dp.SetOuputTitle( name1 );
    string output_name = dp.SetName( 4, name2, title);

    // ��X�ɮ�
    ofstream  outfile( output_name );
    dp.OuputData( sort_data_vec, output_name );

    // �L�X���
    dp.PrintData(sort_data_vec);
}


// �ƻs�ɮ�
void FileTask::Copy( vector<vector<string>> & data_vec ){

    // �R���e�T��æL�X Data
    dp.DeleteLine( data_vec, 0, 2);
    dp.PrintData(data_vec);

    // ��X
    string output_name = dp.SetName( 5, name1, "copy" );
    ofstream  outfile( output_name );
    dp.OuputData( data_vec, output_name );
}


// Ū���ɮ�
bool FileTask::ReadFile( string filename, vector<vector<string>> & data_vec, string & name ){
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

vector<vector<string>> DataProcess::UniqueSort( vector<vector<string>> data_vec, int data_column, vector<string> unique_data ){

    vector<vector<string>> sort_data_vec;

    // �M�� unique data
    for( int i=0; i<unique_data.size(); i++ ){
        // �M���Ҧ� data
        for(int j=0; j<data_vec.size(); j++ ){
            if( unique_data[i] == data_vec[j][data_column] ){
                sort_data_vec.push_back( data_vec[j] );
            }
        }
    }


    return sort_data_vec;
}


// ��o�Y column �D���Ƹ��
vector<string> DataProcess::GetUniqueData( vector<vector<string>> data_vec, int data_colunm ){
    vector<string> unique_data;

    // �M���Ҧ� data
    for( int i=0; i< data_vec.size(); i++ ){
        if( unique_data.empty() ){
            unique_data.push_back( data_vec[i][data_colunm] );
        }
        else{
            // �M���w�� unique data
            for( int j=0; j < unique_data.size(); j++ ){
                // �p�G�w���ۦP data ���X
                if( data_vec[i][data_colunm] == unique_data[j] )    break;
                // �p�G�����S���ۦP data�A�s�� data
                if( j == unique_data.size() - 1 )   unique_data.push_back( data_vec[i][data_colunm] );
            }
        }
    }
    return unique_data;
}

// �]�w Task3 �ɮ׶}�Y
string DataProcess::SetOuputTitle( string name1 ){
    string title = "";

    for (int i=4 ; name1[i] != '.' ; i++ ){
        title += name1[i];
    }

    return "output" + title + "_";
}

// �]�w��X�ɮצW
string DataProcess::SetName( int title_length , string origin_name, string new_head ){

    string new_name = "";

    // ���L�}�Y (input:5, copy:4, ...)
    for (int i=title_length ; origin_name[i] != '.' ; i++ ){
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
