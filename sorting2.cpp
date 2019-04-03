#include<iostream>
#include<fstream>
#include<utility>
#include<vector>

#define MAXN 512
#define MAX_VALUE 8192
#define NO_PARENT (unsigned) (-1)
using namespace std;

 int N,PricePositions[MAXN][MAXN],PriceValue[MAXN][MAXN];
 int FullPrice[MAXN][MAXN],Perm[MAXN],BestPrice[MAXN][MAXN],BestWayPred[MAXN][MAXN];
 short TypePricePos,TypePriceVal;

pair < int ,  int> MyPath[MAXN];
 int CountPathSize = 1;

vector<pair < int ,  int> > FullPath;
 int FullCountPathSize = 0;

char T[MAXN];
unsigned d[MAXN];
 int pred[MAXN];

void Input(){//N^2
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

void Output(){//N^2
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

void MakeMatrix(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            FullPrice[i][j] = PricePositions[i][j] + PriceValue[Perm[i]][Perm[j]];
        }
    }
}

void Sorting(){
    //MakeMatrix();

    if(CheckPerm())return;

    else {
        for(int i = 1; i <= N; i++){
            if(Perm[i] != i){
                for(int j = 1; j <= N; j++){
                    if(j == Perm[i]){

                        FullPath.push_back(make_pair(i,j));
                        swap(Perm[i],Perm[j]);
                        Sorting();
                        return;
                    }
                }
            }
        }
    }

    Sorting();
}

int main() {
    Input();
    Sorting();
    Output();
}
