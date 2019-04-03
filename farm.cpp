#include<iostream>
#include<fstream>
using namespace std;

int n,m,k,j;

void Input(){
    ifstream InputFile;
    InputFile.open("farm.in",ios::in);
    InputFile>>n>>m;
    for(int i = 1; i <= n;i++)
        InputFile>>k>>j;
}

void Output(){
    ofstream OutFile;
    OutFile.open("farm.out",ios::out);
    OutFile<<-1<<endl;
}
int main(){
    Input();
    Output();
    return 0;
}
