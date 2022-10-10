#include<iostream>
#include<fstream>   // Ū���ɮ�
#include<sstream>   // ���Φr��
#include<vector>    // Vector
#include<string.h>
#include <cstdlib>

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
		vector<vector<string>> Filter( vector<vector<string>> data_vec, int num_students,int num_graduates );
		
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
		void Select( vector<vector<string>> & data_vec,int num_students, int num_graduates );
        void Copy( vector<vector<string>> & data_vec );
        void Combine( vector<vector<string>> & data_vec1, vector<vector<string>> & data_vec2 );
        void ReadFile( string filename, vector<vector<string>> & data_vec, string & name );     // Ū�����
};

// ���b��� 
bool HaveFile( string name ); //�ˬd��J���ɮצW�٬O�_�s�b 
bool Isint(string input);
bool FileIsCorrect( string name, int mode );
string FormalName( string name, int mode ); //�N��J���ɮצW�٥��W�� 

int main(){
	int command = 10;
	do{
		cout << endl << "*** File Object Manipulator ***";
		cout << endl << "* 0. QUIT                     *";
		cout << endl << "* 1. COPY (Read & Save a file)*";
		cout << endl << "* 2. FILTER (Reduce a file)   *";
		cout << endl << "* 3. MERGE (Join two files)   *";
		cout << endl << "*******************************";
		cout << endl << "Input a choice(0, 1, 2, 3):";
		string input;
		cin >> input;
		if (not Isint(input))
			continue;
		command = stoi(input);
		switch( command ){
			case 1:{
				string open_file; // �ɮצW�� 
				do{
					cout << endl <<"Input 201, 202, ...[0]Quit):";
					cin >> open_file;
					// ���W���ɮצW�� 
					open_file = FormalName(open_file,1);
				}while(!HaveFile(open_file) or !FileIsCorrect( open_file, 1 )); // �ɮ׬O�_�s�b 
				
				// �Y��J0�h���� 
				if (open_file[0] == '0' and open_file.size() == 1)
					break;
					
				FileTask ft;
			    ft.ReadFile(open_file, ft.data_vec_1, ft.name1 );
			    ft.Copy( ft.data_vec_1 );
			    break;
			}
			
			case 2:{
				string open_file,students,graduates;
				int num_students, num_graduates;
				// ��J�ɮ� 
				do{
					cout << endl << "Input 201, 202, ...[0]Quit):";
					cin >> open_file;
					open_file = FormalName(open_file,2);
				}while( !HaveFile(open_file) or !FileIsCorrect( open_file, 2 ) );
				
				if (open_file[0] == '0' and open_file.size() == 1)
					break;
					
				// ��J�ǥͼ� 
				do{
					cout << endl << "Input a lower bound on the number of students:";
					cin >> students;
				}while(!Isint(students));
				
				// ��J���~�� 
				do{
					cout << endl << "Input a lower bound on the number of graduates:";
					cin >> graduates;
				}while(!Isint(graduates));
				
				num_students = stoi(students);
				num_graduates = stoi(graduates);
				
				FileTask ft;
			    ft.ReadFile(open_file, ft.data_vec_1, ft.name1 );
			    ft.Select( ft.data_vec_1, num_students, num_graduates);
			    break;
			}
			
			case 3:{
				string open_file1,open_file2;
					do{
				cout << endl << "Input 201, 202, ...[0]Quit):";
					cin >> open_file1;
					open_file1 = FormalName(open_file1,3);
				}while(!HaveFile(open_file1) or !FileIsCorrect( open_file1, 3 ));
				if (open_file1[0] == '0' and open_file1.size() == 1)
					break;
					
				do{
					cout << endl << "Input 201, 202, ...[0]Quit):";
					cin >> open_file2;
					open_file2 = FormalName(open_file2,3);
				}while(!HaveFile(open_file2) or !FileIsCorrect( open_file2, 3 ));
				if (open_file2[0] == '0' and open_file2.size() == 1)
					break;
					
				FileTask ft;
			    ft.ReadFile(open_file1, ft.data_vec_1, ft.name1 );
			    ft.ReadFile(open_file2, ft.data_vec_2, ft.name2 );
			    ft.Combine( ft.data_vec_1, ft.data_vec_2 );
			    break;
			}
			
			default:{
				cout << "Command does not exist!";
			    break;
			}
		}
	}while( command != 0 );
}



// =================================  FileTask ���O��� ========================================================

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

// �z���ɮ�
void FileTask::Select( vector<vector<string>> & data_vec,int num_students, int num_graduates ){
	//�z�� data_vec
	data_vec = dp.Filter( data_vec, num_students, num_graduates );
    // �L�X Data
    dp.PrintData(data_vec);

    // ��X
    string output_name = dp.SetName( 4, name1, "copy" );
    ofstream  outfile( output_name );
    dp.OuputData( data_vec, output_name );
}


// Ū���ɮ� 
void FileTask::ReadFile( string filename, vector<vector<string>> & data_vec, string & name ){
    // Ū���ɮ�
    ifstream infile( filename );
    name = filename;
    dp.ReadData( infile, data_vec );  // �s���ɮ�
    infile.close();                   // �����ɮ�
}

// =================================  ���b��� ========================================================

 
// �ˬd�ɮצW�٬O�_�s�b
bool HaveFile( string name ) {
	ifstream infile( name );
	if (name[0] == '0' and name.size() == 1)
		return true;
    // �T�{���LŪ���ɮ�
    if( infile.fail() ){
        cout << "### "<<name<<" does not exist! ###" << endl;
        infile.close();                     // �����ɮ�
        return false;
    }
	return true;
}

// �P�_�W�٬O�_���W
bool FileIsCorrect( string name, int mode ){
	if(mode == 1){
		string test = "input";
		for( int i = 0; i < 5; i++ ){
			if( test[i]!=name[i])
				return false;
		}
	}
	else if ( mode == 2 or mode == 3) {
		string test = "copy";
		for( int i = 0; i < 4; i++ ){
			if( test[i]!=name[i])
				return false;
		}
	}
			
	return true;
}
// ���W���ɮצW��
string FormalName( string name, int mode ){
	if (name[0] == '0' and name.size() == 1)
		return name;
	if (Isint(name)){
		if(mode == 1)
			name = "input" + name + ".txt";
		else if ( mode == 2) 
			name = "copy" + name + ".txt";
		else if (mode == 3 )
			name = "copy" + name + ".txt";
	}
	return name;
} 


// �P�_�r��O�_��������� 
bool Isint(string input){
	for( int i = 0; i < input.size() ; i++ ) {
		if( input[i] > '9' or input[i] < '0')
			return false;
	}
	return true;
} //Isint()

// =================================  DataProcess ���O��� ========================================================

// �z�����
vector<vector<string>> DataProcess::Filter( vector<vector<string>> data_vec, int num_students,int num_graduates ){
	
	vector<vector<string>> result;
	
	int k = 0;
    for ( int i=0 ; i < data_vec.size() ; i++ ){
    	if ( stoi(data_vec[i][6]) > num_students and stoi(data_vec[i][8]) > num_graduates ){
			result.push_back(data_vec[i]);
			k++;
		}
    }
    return result;
}


// �X���ɮ�
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
    int i;
    for ( i = 0 ; i < data_vec.size() ; i++ ){
        // �L�X1 line
    	cout << "[" << i+1 << "]\t";
        for ( int j=0 ; j < 11 ; j++ ){
        	cout << data_vec[i][j] << "\t";		
        }
    }
    cout << endl << "Number of records = " << i << endl;
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
