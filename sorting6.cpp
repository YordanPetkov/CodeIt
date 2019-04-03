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


void MakePath(unsigned First, unsigned Last)//N^2
{
    if(pred[Last] != First)MakePath(First,pred[Last]);
    CountPathSize++;
    FullPath.push_back(make_pair(First,Last));

    swap(Perm[First],Perm[Last]);

}

vector < vector <int> > Loops;
bool Used[MAXN];

void SortingLoop(int LoopIndex, int StartIndex){
    int LoopSize = Loops[LoopIndex].size();
    int CurIndex = StartIndex,Next;
    if(CurIndex == LoopSize - 1)Next = 0;
        else Next = CurIndex + 1;

    do {

        int First = Loops[LoopIndex][StartIndex];
        int Second = Loops[LoopIndex][Next];
        swap(Perm[First],Perm[Second]);
        FullCountPathSize++;
        FullPath.push_back(make_pair(First,Second));
        CurIndex = Next;
        if(CurIndex == LoopSize - 1){Next = 0;}
        else {Next = CurIndex + 1;}
    }while(Next != StartIndex);
}

void SortingWithLoops(){
    for(int i = 1; i <= N; i++){
        if(i == Perm[i])Used[i] = true;
        vector <int> CurLoop;
        int CurIndex = i;
        if(Used[i] == false){
            do{
                Used[CurIndex] = true;
                CurLoop.push_back(CurIndex);
                CurIndex = Perm[CurIndex];
            }while(CurIndex != i);
            Loops.push_back(CurLoop);
        }
    }
    int CountLoops = Loops.size();
    int MinPriceLoops = MAX_VALUE,MinStartIndex = 1;
    for(int i = 0; i < CountLoops; i++){
        int CountNumInLoop = Loops[i].size();
        for(int j = 0; j < CountNumInLoop; j++){
            int CountLoopPrice = 0,Next;
            for(int k = 0; k < CountNumInLoop; k++){
                if(k == CountNumInLoop - 1)Next = 0;
                else Next = k + 1;
                if(k == j)continue;
                int First = Loops[i][j];
                int Second = Loops[i][k];
                CountLoopPrice += PricePositions[First][Second];
                First = Loops[i][k];
                Second = Loops[i][Next];
                CountLoopPrice += PriceValue[First][Second];
            }
            if(CountLoopPrice < MinPriceLoops){
                MinPriceLoops = CountLoopPrice;
                MinStartIndex = j;
            }
        }
        SortingLoop(i, MinStartIndex);
    }
    if(CheckPerm() == false)SortingWithLoops();
}

void SortingDump(){
    int MinDumpPrice = MAX_VALUE,MinDumpIndex;
    for(int i = 1; i <= N; i++){
        if(i == Perm[i])continue;
        int price = PricePositions[i][Perm[i]] + PriceValue[Perm[i]][Perm[Perm[i]]];
        if(price < MinDumpPrice){MinDumpPrice = price;MinDumpIndex = i;}
    }

    if(MinDumpPrice < MAX_VALUE){
        FullCountPathSize++;
        FullPath.push_back(make_pair(MinDumpIndex,Perm[MinDumpIndex]));
        swap(Perm[MinDumpIndex],Perm[Perm[MinDumpIndex]]);
        //cout<<Perm[MinDumpPrice]<<" "<<Perm[Perm[MinDumpPrice]]<<endl;
    }
}

void Sorting(){
    if(true){
        while(CheckPerm() == false){
            SortingDump();
        }
        return;
    }

    if(true){
        while(CheckPerm() == false){
            SortingWithLoops();
        }
    }
}

int main() {
    Input();
    Sorting();
    Output();
    //cout<<AllPrice<<endl;
    return 0;
}




