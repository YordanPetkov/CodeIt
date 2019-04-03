#include<iostream>
#include<fstream>
using namespace std;

int n,m,k,j;

void Input(){
    ifstream InputFile;
    InputFile.open("graph.in",ios::in);
    InputFile>>n>>m;
    for(int i = 1; i <= m;i++)
        InputFile>>k>>j;
}

void Output(){
    ofstream OutFile;
    OutFile.open("graph.out",ios::out);
    OutFile<<"No"<<endl;
}

int main(){
    Input();
    Output();
    return 0;
    //int Board[n+2][n+2];


}

