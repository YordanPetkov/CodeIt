#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
int n,m,a,b;
bool Graph[1001][1001],used[1001];
vector<int> Ans;
void Input(){
    ifstream InputFile;
    InputFile.open("maxpath.in",ios::in);
    InputFile>>n>>m;

    int x,y;
    for(int i = 1; i <= m;i++)
        {
            InputFile>>x>>y;
            if(x<1001 && y<1001)Graph[x][y] = true;
            if(x<1001 && y<1001)Graph[y][x] = true;
        }
}

void Output(){
    ofstream OutFile;
    OutFile.open("maxpath.out",ios::out);
    OutFile<<Ans.size()<<endl;
    for(int i = 0; i < Ans.size(); i++){
        OutFile<<Ans[i]<<endl;
    }
}
int main(){
    Input();
    int i = 1;
    used[i] = true;
    Ans.push_back(i);
    if(n> 1000)n = 1000;
    while(true){
        bool change = false;
        for(int j = 1; j <= n; j++)
        {
            if(i == j)continue;
            if(Graph[i][j] == true && used[j] == false){
                used[j] = true;
                Ans.push_back(j);
                i = j;
                change = true;
            }
        }
        if(change == false)break;
    }
    Output();
    return 0;
}
