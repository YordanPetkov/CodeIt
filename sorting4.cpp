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


void SortingAll(){
    int MyI,MyCurI;
    int MyQueue[MAXN],CountVar = -1;
    for(int i = 1; i <= N; i++)
        if(i != Perm[i])MyI = Perm[i];
    MyCurI = MyI;
    do{
        CountVar++;
        MyQueue[CountVar] = MyCurI;
        MyCurI = Perm[MyCurI];
    }while(MyCurI != MyI);

    for(int i = 0; i < CountVar; i++) {
        Queues Temp;
        Temp.Price = 0;
        int j = i,step = 0,endI;
        if(i == 0)endI = CountVar-1;
        else endI = i-1;
        do {
            int Nextj;
            if(j == CountVar-1)Nextj = 0;
            else Nextj = j+1;
            Temp.Perm[step] = MyQueue[j];
            cout<<MyQueue[j]<<" ";
            Temp.Price += PriceValue[MyQueue[j]][MyQueue[Nextj]] + PricePositions[endI][j];
            if(j == CountVar - 1)j = 0;
            else j++;
            step++;
        }while(j != endI);
        Temp.Perm[step] = MyQueue[j];
        cout<<MyQueue[j]<<" ";
        cout<<endl;
        MyLoops.push_back(Temp);
    }
    int LMyLoops = MyLoops.size(),MyMinPriceLoops = MAX_VALUE,MyMinIndexLoops = 0;
    for(int i = 0; i < LMyLoops; i++){
        if(MyMinPriceLoops < MyLoops[i].Price){
            MyMinPriceLoops = MyLoops[i].Price;
            MyMinIndexLoops = i;
        }
        cout<<i<<" : ";
        for(int j = 0; j < CountVar ;j++)
            cout<<MyLoops[i].Perm[j]<<" ";
        cout<<endl;
    }
    FullCountPathSize += CountVar;
    for(int i = 0; i < CountVar-1; i++){
        FullPath.push_back(make_pair(MyLoops[MyMinIndexLoops].Perm[i],MyLoops[MyMinIndexLoops].Perm[i+1]));
        swap(Perm[MyLoops[MyMinIndexLoops].Perm[i]],Perm[MyLoops[MyMinIndexLoops].Perm[i+1]]);
    }
    MyLoops.erase (MyLoops.begin(),MyLoops.begin()+LMyLoops);
}

void Sorting(){
    while(CheckPerm() == false ) {
        SortingAll();
        for(int i = 1; i <= N; i++)
            cout<<Perm[i]<<" ";
            cout<<endl;
    }
}

int main() {
    Input();
    Sorting();
    Output();
    //cout<<AllPrice<<endl;
    return 0;
}


