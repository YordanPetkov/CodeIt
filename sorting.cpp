#include<iostream>
#include<fstream>
#include<utility>
#include<vector>

#define MAXN 512
#define MAX_VALUE 8192
#define NO_PARENT (unsigned) (-1)
using namespace std;

unsigned int N,PricePositions[MAXN][MAXN],PriceValue[MAXN][MAXN];
unsigned int FullPrice[MAXN][MAXN],Perm[MAXN],BestPrice[MAXN][MAXN],BestWayPred[MAXN][MAXN];
unsigned short TypePricePos,TypePriceVal;

pair <unsigned int , unsigned int> MyPath[MAXN];
unsigned int CountPathSize = 1;

vector<pair <unsigned int , unsigned int> > FullPath;
unsigned int FullCountPathSize = 0;

char T[MAXN];
unsigned d[MAXN];
unsigned int pred[MAXN];



void dijkstra(unsigned s)
{
    unsigned i;
    for(i = 1; i <= N; i++){
        if(FullPrice[s][i] == 0 || Perm[i] == i || Perm[s] == s){
            d[i] = MAX_VALUE;
            pred[i] = NO_PARENT;
        }

            else {
                d[i] = FullPrice[s][i];
                pred[i] = s;
            }
    }



    for(i = 1; i <= N; i++)T[i] = 1;
    T[s] = 0;
    pred[s] = NO_PARENT;

    while(true){
        unsigned j = NO_PARENT;
        unsigned di = MAX_VALUE;
        for(i = 1; i <= N; i++)
            if(T[i] && d[i] < di){
                di = d[i];
                j = i;
            }



        if(NO_PARENT == j)break;
        T[j] = 0;



        for(i = 1; i <= N; i++)
            if(T[i] && FullPrice[j][i] != 0 && Perm[i] != i && Perm[s] != s)
                if(d[i] > d[j] + FullPrice[j][i]){
                    d[i] = d[j] + FullPrice[j][i];
                    pred[i] = j;
                }
    }
}



void MakePath(unsigned First, unsigned Last)//N^2
{
    if(BestWayPred[First][Last] != First)MakePath(First, BestWayPred[First][Last]);
    MyPath[CountPathSize] = make_pair(First,Last);
    CountPathSize++;
    swap(Perm[First],Perm[Last]);
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            FullPrice[i][j] = PricePositions[i][j] + PriceValue[Perm[i]][Perm[j]];

}

void MakeTree(){//n^3
    for(unsigned int i = 1; i <= N; i++){
        dijkstra(i);
        for(unsigned int j = 1; j <= N; j++){
            BestPrice[i][j] = d[j];
            BestWayPred[i][j] = pred[j];
        }
    }
}

void printPath(unsigned s, unsigned j)
{
    if(BestWayPred[s][j] == 0)return;
    if(BestWayPred[s][j] != s)printPath(s, BestWayPred[s][j]);
    cout<<j<<" ";
    cout<<endl;
}

void Sorting(){//2 * n^3
    //MakeClass();
    MakeTree();
    for(unsigned int i = 1; i <= N; i++){
        for(unsigned int j = 1; j <= N; j++){
            cout<<i<<" "<<j<<" "<<BestPrice[i][j]<<endl;
            if(i!= j)cout<<i<<" ";
            if(i!= j)printPath(i,j);
        }
    }
    for(unsigned int i = 1; i <= N; i++){//n^3
        if(Perm[i] != i){
            if(BestPrice[i][Perm[i]] != MAX_VALUE){
                MakePath(i,Perm[i]);
                FullCountPathSize += CountPathSize - 1;
                for(unsigned k = 1; k < CountPathSize; k++){
                    FullPath.push_back(MyPath[k]);
                }
                CountPathSize = 1;
            }
            return;
        }
    }
}

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
}

bool CheckPerm(){
    for(int i = 1; i <= N; i++){
        if(Perm[i] != i)return false;
    }
    return true;
}

int main(){
    Input();
    while(CheckPerm() == false){
        Sorting();
        cout<<FullCountPathSize<<endl;
        for(int i = 1; i <= N; i++)
            cout<<Perm[i]<<" ";
        cout<<endl;
    }

    cout<<FullCountPathSize<<endl;
    for(int i = 1; i <= FullCountPathSize; i++){
        cout<<FullPath[i].first<<" "<<FullPath[i].second<<endl;
    }

    return 0;
}
