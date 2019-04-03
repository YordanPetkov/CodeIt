#include<iostream>
#include<fstream>
#include<utility>
#include<vector>
#include<cmath>
#include<algorithm>

#define MAXN 512
#define MAX_VALUE 8192
using namespace std;
 int N,PricePositions[MAXN][MAXN],PriceValue[MAXN][MAXN],AllPrice = 0;
 int FullPrice[MAXN][MAXN],Perm[MAXN];
 //BestPrice[MAXN][MAXN],BestWayPred[MAXN][MAXN];
 short TypePricePos,TypePriceVal;



vector<pair < int ,  int> > FullPath;
 int FullCountPathSize = 0;



/// Basic Functions {(N*N) + FullPathSize(1 000 000) + N}
void Input();
void Output();
bool CheckPerm();
/// End Basic Functions

/// TYPE(4-0) pos=4 val=0 (n*n)
void SortByType4_0();
/// END TYPE(4-0) pos=4 val=0

int main(){
    Input();
    if(TypePricePos == 4 && TypePriceVal == 0){
        SortByType4_0();
    }
    Output();
    return 0;
}

/// Basic Functions
void Input(){
    ifstream InputFile;
    InputFile.open("sorting.in",ios::in);
    InputFile>>N;
    for(int i = 1 ; i <= N; i++){
        InputFile>>Perm[i];
    }
    InputFile>>TypePricePos;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            InputFile>>PricePositions[i][j];
            FullPrice[i][j] += PricePositions[i][j];
        }
    }
    InputFile>>TypePriceVal;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            InputFile>>PriceValue[i][j];
            FullPrice[i][j] += PriceValue[Perm[i]][Perm[j]];
        }
    }
    InputFile.close();
}

void Output(){
    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize = FullPath.size();
    OutputFile<<FullCountPathSize<<endl;
    for(int i = 0; i < FullCountPathSize; i++)
        OutputFile<<FullPath[i].first<<" "<<FullPath[i].second<<endl;

    OutputFile.close();
}

bool CheckPerm(){
    for(int i = 1; i <= N; i++){
        if(Perm[i] != i)return false;
    }
    return true;
}
/// End Basic Functions

/// TYPE(4-0) pos=4 val=0
void SortByType4_0(){
    for(int i = N; i >= 1; i--){
        if(i == Perm[i])continue;
        for(int j = 1; j <= N; j++){
            if(Perm[j] == i){
                swap(Perm[j],Perm[i]);
                FullPath.push_back(make_pair(j,i));
            }
        }
    }
}
/// END TYPE(4-0) pos=4 val=0
