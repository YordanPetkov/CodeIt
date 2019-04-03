#include<iostream>
#include<fstream>
#include<utility>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>

#define MAXN 512
#define MAX_VALUE 8192
#define NO_PARENT (unsigned) (-1)
using namespace std;

 int N,PricePositions[MAXN][MAXN],PriceValue[MAXN][MAXN],AllPrice = 0;
 int FullPrice[MAXN][MAXN],Perm[MAXN],BestPrice[MAXN][MAXN],BestWayPred[MAXN][MAXN];
 short TypePricePos,TypePriceVal;
int MinPrice = MAX_VALUE,MinIndex=0;


pair < int ,  int> MyPath[MAXN];
 int CountPathSize = 0;

vector<pair < int ,  int> > FullPath;
 int FullCountPathSize = 0;

char T[MAXN];
unsigned d[MAXN];
 int pred[MAXN];

 class AllPaths {
    public:
    vector <pair < int ,  int> > MyPath;
    int CountPathSize;
    int price;
 }Path[MAXN];

class Queues {
    public :
    int Perm[MAXN];
    int Price;
};

vector <Queues> MyLoops;

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

void dijkstra(unsigned s)
{
    unsigned i;
    for(i = 1; i <= N; i++){
        if(FullPrice[s][i] == 0){
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
            if(T[i]==1 && d[i] < di){
                di = d[i];
                j = i;
            }



        if(NO_PARENT == j)break;
        T[j] = 0;



        for(i = 1; i <= N; i++)
            if(T[i]==1 && FullPrice[j][i] != 0)
                if(d[i] > d[j] + FullPrice[j][i]){
                    d[i] = d[j] + FullPrice[j][i];
                    pred[i] = j;
                }
        //if(j == Perm[s])return;
    }
}

void MakePath_X_0(int First, int Last){
    if(pred[Last] != First)MakePath_X_0(First,pred[Last]);
    Path[First].MyPath.push_back(make_pair(pred[Last], Last));
    Path[First].price += FullPrice[pred[Last]][Last];
}

void SortingType_X_0(){
    MakeMatrix();
    for(int i = 1; i <= N; i++){
        dijkstra(i);
        Path[i].price = 0;
        if(i != Perm[i]){MakePath_X_0(i,Perm[i]);Path[i].CountPathSize = Path[i].MyPath.size();}
        else Path[i].CountPathSize = 0;
    }
    Start:
    int MinSize = MAX_VALUE,MinSizeIndex = 1,MinSizePrice = MAX_VALUE;
    for(int i = 1; i <= N; i++){
        if(Path[i].CountPathSize <= MinSize && Path[i].CountPathSize != 0 && i != Perm[i])
        {
            if(Path[i].CountPathSize < MinSize){
                MinSize = Path[i].CountPathSize;
                MinSizePrice = Path[i].price;
                MinSizeIndex = i;
            }
            if(Path[i].CountPathSize == MinSize && Path[i].price < MinSizePrice){
                MinSize = Path[i].CountPathSize;
                MinSizePrice = Path[i].price;
                MinSizeIndex = i;
            }
        }
    }

    for(int i = 0; i < Path[MinSizeIndex].CountPathSize; i++){
        swap(Perm[Path[MinSizeIndex].MyPath[i].first],Perm[Path[MinSizeIndex].MyPath[i].second]);
        FullPath.push_back(Path[MinSizeIndex].MyPath[i]);

    }
    FullCountPathSize += Path[MinSizeIndex].CountPathSize;
    Path[MinSizeIndex].CountPathSize = 0;

    if(CheckPerm() == false)goto Start;
}

void MakePath(unsigned First, unsigned Last)//N^2
{
    if(pred[Last] != First)MakePath(First,pred[Last]);
    CountPathSize++;
    FullPath.push_back(make_pair(First,Last));

    swap(Perm[First],Perm[Last]);

}

void SortingAll(){
    for(int i = 1; i <= N; i++){
        if(i == Perm[i])continue;
        dijkstra(i);
        int Pos,j;
        for(j = 1; j <= N; j++)
            if(Perm[j] == i){Pos = j;break;}
        MakePath(i,j);
        FullCountPathSize += CountPathSize;
        AllPrice += d[j];
        CountPathSize = 0;
    }
}

void SortingType_2$3_2$3(){
    pair<int,int> Dist[MAXN];
    for(int i = 1; i <= N; i++)
        Dist[Perm[i]] = make_pair(FullPrice[i][Perm[i]],i);
    sort(Dist+1,Dist+N+1);
    for(int i = 1; i <= N; i++){
        int ii = Dist[i].second;
            if(Perm[ii] != ii){
                for(int j = 1; j <= N; j++){
                    if(j == Perm[ii]){

                        FullPath.push_back(make_pair(ii,j));
                        AllPrice += FullPrice[ii][j];
                        swap(Perm[ii],Perm[j]);
                        return;
                    }
                }
            }
        }
}


void Sorting(){
    if(TypePriceVal == 0){
        SortingType_X_0();
        return;
    }




    /// sortingMyBest.cpp code
    MakeMatrix();
    if((TypePriceVal == 2 || TypePriceVal == 3) && (TypePricePos == 2 || TypePricePos == 3)){
        while(CheckPerm() == false){
            SortingAll();
        }

        return;
    }
    while(CheckPerm() == false){

        SortingType_2$3_2$3();
    }

    return;

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
    //cout<<AllPrice<<endl;
    return 0;
}



