#include "myClass.h"
#include "myClass.cpp"
#include<algorithm>
#include<iostream>
#include<string>

using namespace std;


int main(){
    string str = "1+(50)";

    Manipulate_Stack ms;
    ms.String2Postfix( str );
    ms.PrintPostFix();

    int ans = ms.CalculatePostfix();
    cout << endl <<  ans << endl;


}



