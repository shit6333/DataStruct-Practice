#include<iostream>
#include<fstream>   // 讀取檔案
#include<sstream>   // 切割字串
#include<vector>    // Vector
#include<string.h>
#include <cstdlib>

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

        string SetName( int title_length , string origin_name, string new_head );            // 輸出新檔案名稱 ( 原檔開頭字元數, 原始檔案名, 新檔案開頭 )
        string SetOuputTitle( string name1 );                                                 // 設定 case3 的 output 檔案 title
		vector<vector<string>> Filter( vector<vector<string>> data_vec, int num_students,int num_graduates );
		
        vector<string> GetUniqueData( vector<vector<string>> data_vec, int data_colunm );   // 取得 unique data
        vector<vector<string>> UniqueSort( vector<vector<string>> data_vec, int data_column, vector<string> unique_data );  // 依照 unique_data 排序 data
};

// 任務類別
class FileTask{
    public:
        string name1;                              // 檔案名稱
        string name2;                              // 合併檔案名稱
        DataProcess dp;                            // 資料處理類別
        vector<vector<string>> data_vec_1;      // 資料 vector
        vector<vector<string>> data_vec_2;      // 用以儲存要合併的 data

        // --------------------------------

		void Select( vector<vector<string>> & data_vec,int num_students, int num_graduates );
        void Copy( vector<vector<string>> & data_vec );
        void Combine( vector<vector<string>> & data_vec1, vector<vector<string>> & data_vec2 );
        void ReadFile( string filename, vector<vector<string>> & data_vec, string & name );     // 讀取資料

};

// 防呆函數 
bool HaveFile( string name ); //檢查輸入的檔案名稱是否存在 
bool Isint(string input);
bool FileIsCorrect( string name, int mode );
string FormalName( string name, int mode ); //將輸入的檔案名稱正規化 

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
				string open_file; // 檔案名稱 
				do{
					cout << endl <<"Input 201, 202, ...[0]Quit):";
					cin >> open_file;
					// 正規化檔案名稱 
					open_file = FormalName(open_file,1);
				}while(!HaveFile(open_file) or !FileIsCorrect( open_file, 1 )); // 檔案是否存在 
				
				// 若輸入0則結束 
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
				// 輸入檔案 
				do{
					cout << endl << "Input 201, 202, ...[0]Quit):";
					cin >> open_file;
					open_file = FormalName(open_file,2);
				}while( !HaveFile(open_file) or !FileIsCorrect( open_file, 2 ) );
				
				if (open_file[0] == '0' and open_file.size() == 1)
					break;
					
				// 輸入學生數 
				do{
					cout << endl << "Input a lower bound on the number of students:";
					cin >> students;
				}while(!Isint(students));
				
				// 輸入畢業數 
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



// =================================  FileTask 類別函數 ========================================================


// 合併檔案
void FileTask::Combine( vector<vector<string>> & data_vec1, vector<vector<string>> & data_vec2 ){
    // 合併檔案
    data_vec1.insert( data_vec1.end(), data_vec2.begin(), data_vec2.end() );

    // 用科系名排序
    vector<string> unique_data = dp.GetUniqueData( data_vec1, 3);
    vector<vector<string>> sort_data_vec = dp.UniqueSort( data_vec1, 3, unique_data );
    // 用學校名排序
    unique_data = dp.GetUniqueData( data_vec1, 1);
    sort_data_vec = dp.UniqueSort( sort_data_vec, 1, unique_data );

    // 設定輸出檔案名
    string title = dp.SetOuputTitle( name1 );
    string output_name = dp.SetName( 4, name2, title);

    // 輸出檔案
    ofstream  outfile( output_name );
    dp.OuputData( sort_data_vec, output_name );

    // 印出資料
    dp.PrintData(sort_data_vec);
}


// 複製檔案
void FileTask::Copy( vector<vector<string>> & data_vec ){
    // 刪除前三行並印出 Data
    dp.DeleteLine( data_vec, 0, 2);
    dp.PrintData(data_vec);

    // 輸出
    string output_name = dp.SetName( 5, name1, "copy" );
    ofstream  outfile( output_name );
    dp.OuputData( data_vec, output_name );
}

// 篩選檔案
void FileTask::Select( vector<vector<string>> & data_vec,int num_students, int num_graduates ){
	//篩選 data_vec
	data_vec = dp.Filter( data_vec, num_students, num_graduates );
    // 印出 Data
    dp.PrintData(data_vec);

    // 輸出
    string output_name = dp.SetName( 4, name1, "copy" );
    ofstream  outfile( output_name );
    dp.OuputData( data_vec, output_name );
}



// 讀取檔案 
void FileTask::ReadFile( string filename, vector<vector<string>> & data_vec, string & name ){
    // 讀取檔案
    ifstream infile( filename );
    name = filename;
    dp.ReadData( infile, data_vec );  // 存取檔案
    infile.close();                   // 關閉檔案
}

// =================================  防呆函數 ========================================================

 
// 檢查檔案名稱是否存在
bool HaveFile( string name ) {
	ifstream infile( name );
	if (name[0] == '0' and name.size() == 1)
		return true;
    // 確認有無讀取檔案
    if( infile.fail() ){
        cout << "### "<<name<<" does not exist! ###" << endl;
        infile.close();                     // 關閉檔案
        return false;
    }
	return true;
}

// 判斷名稱是否正規
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
// 正規化檔案名稱
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


// 判斷字串是否全為正整數 
bool Isint(string input){
	for( int i = 0; i < input.size() ; i++ ) {
		if( input[i] > '9' or input[i] < '0')
			return false;
	}
	return true;
} //Isint()

// =================================  DataProcess 類別函數 ========================================================

// 篩選條件
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


// 合併檔案
vector<vector<string>> DataProcess::UniqueSort( vector<vector<string>> data_vec, int data_column, vector<string> unique_data ){

    vector<vector<string>> sort_data_vec;

    // 遍歷 unique data
    for( int i=0; i<unique_data.size(); i++ ){
        // 遍歷所有 data
        for(int j=0; j<data_vec.size(); j++ ){
            if( unique_data[i] == data_vec[j][data_column] ){
                sort_data_vec.push_back( data_vec[j] );
            }
        }
    }

vector<vector<string>> DataProcess::UniqueSort( vector<vector<string>> data_vec, int data_column, vector<string> unique_data ){

    vector<vector<string>> sort_data_vec;

    // 遍歷 unique data
    for( int i=0; i<unique_data.size(); i++ ){
        // 遍歷所有 data
        for(int j=0; j<data_vec.size(); j++ ){
            if( unique_data[i] == data_vec[j][data_column] ){
                sort_data_vec.push_back( data_vec[j] );
            }
        }
    }


    return sort_data_vec;
}


// 獲得某 column 非重複資料
vector<string> DataProcess::GetUniqueData( vector<vector<string>> data_vec, int data_colunm ){
    vector<string> unique_data;

    // 遍歷所有 data
    for( int i=0; i< data_vec.size(); i++ ){
        if( unique_data.empty() ){
            unique_data.push_back( data_vec[i][data_colunm] );
        }
        else{
            // 遍歷已有 unique data
            for( int j=0; j < unique_data.size(); j++ ){
                // 如果已有相同 data 跳出
                if( data_vec[i][data_colunm] == unique_data[j] )    break;
                // 如果完全沒有相同 data，存此 data
                if( j == unique_data.size() - 1 )   unique_data.push_back( data_vec[i][data_colunm] );
            }
        }
    }
    return unique_data;
}

// 設定 Task3 檔案開頭
string DataProcess::SetOuputTitle( string name1 ){
    string title = "";

    for (int i=4 ; name1[i] != '.' ; i++ ){
        title += name1[i];
    }

    return "output" + title + "_";
}


    return sort_data_vec;
}


// 獲得某 column 非重複資料
vector<string> DataProcess::GetUniqueData( vector<vector<string>> data_vec, int data_colunm ){
    vector<string> unique_data;

    // 遍歷所有 data
    for( int i=0; i< data_vec.size(); i++ ){
        if( unique_data.empty() ){
            unique_data.push_back( data_vec[i][data_colunm] );
        }
        else{
            // 遍歷已有 unique data
            for( int j=0; j < unique_data.size(); j++ ){
                // 如果已有相同 data 跳出
                if( data_vec[i][data_colunm] == unique_data[j] )    break;
                // 如果完全沒有相同 data，存此 data
                if( j == unique_data.size() - 1 )   unique_data.push_back( data_vec[i][data_colunm] );
            }
        }
    }
    return unique_data;
}

// 設定 Task3 檔案開頭
string DataProcess::SetOuputTitle( string name1 ){
    string title = "";

    for (int i=4 ; name1[i] != '.' ; i++ ){
        title += name1[i];
    }

    return "output" + title + "_";
}



// 設定輸出檔案名
string DataProcess::SetName( int title_length , string origin_name, string new_head ){

    string new_name = "";

    // 跳過開頭 (input:5, copy:4, ...)
    for (int i=title_length ; origin_name[i] != '.' ; i++ ){
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
    int i;
    for ( i = 0 ; i < data_vec.size() ; i++ ){
        // 印出1 line
    	cout << "[" << i+1 << "]\t";
        for ( int j=0 ; j < 11 ; j++ ){
        	cout << data_vec[i][j] << "\t";		
        }
    }
    cout << endl << "Number of records = " << i << endl;
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
