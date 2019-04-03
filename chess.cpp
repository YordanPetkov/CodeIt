#include<iostream>
#include<fstream>
using namespace std;

int n,k,x1,y1,x2,y2;
bool Table[1001][1001];

void Input(){
    ifstream InputFile;
    InputFile.open("chess.in",ios::in);
    InputFile>>n>>k>>x1>>y1>>x2>>y2;
    for(int i = 1; i <= n;i++)
        for(int j = 1; j <= n; j++)
        InputFile>>Table[i][j];
}

void Output(){
    ofstream OutFile;
    OutFile.open("chess.out",ios::out);
    OutFile<<"Yes"<<endl;
}

int main(){
    Input();
    Output();
    return 0;
    //int Board[n+2][n+2];


}
