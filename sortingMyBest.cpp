#include<iostream>
#include<fstream>
#include<utility>
#include<vector>
#include<cmath>
#include<algorithm>
#include<ctime>

#define TimeLimit 1.7
#define MAXN 512
#define MyAlgo 23
#define MAX_VALUE 81928292
#define NO_PARENT (unsigned) (-1)
using namespace std;

 clock_t StartTime,CurTime;
 double  Duration;
 bool HaveTime = true;
 int N,PricePositions[MAXN][MAXN],PriceValue[MAXN][MAXN],AllPrice = 0;
 int FullPrice[MAXN][MAXN],Perm[MyAlgo][MAXN],BestPrice[MAXN][MAXN],BestWayPred[MAXN][MAXN];
 short TypePricePos,TypePriceVal;


int PRICE[MyAlgo],MinPrice = MAX_VALUE;

pair < int ,  int> MyPath[MAXN];
 int CountPathSize = 0;

vector<pair < int ,  int> > FullPath[MyAlgo];
 int FullCountPathSize[MyAlgo];


char T[MAXN];
unsigned d[MAXN];
 int pred[MAXN];

void Input(){//N^2
    ifstream InputFile;
    InputFile.open("sorting.in",ios::in);
    InputFile>>N;
    for(int i = 1 ; i <= N; i++){
        int MyPermI;
        InputFile>>MyPermI;
        for(int j = 1; j < MyAlgo;j++)
            Perm[j][i] = MyPermI;
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
            FullPrice[i][j] += PriceValue[Perm[1][i]][Perm[1][j]];
        }
    }
    InputFile.close();
}

void Output(int IndexAlgo){//N^2
    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize[IndexAlgo] = FullPath[IndexAlgo].size();
    OutputFile<<FullCountPathSize[IndexAlgo]<<endl;
    for(int i = 0; i < FullCountPathSize[IndexAlgo]; i++)
        OutputFile<<FullPath[IndexAlgo][i].first<<" "<<FullPath[IndexAlgo][i].second<<endl;

    OutputFile.close();
}
double MyTime(){
    CurTime = clock();
    return (CurTime - StartTime)/(double)CLOCKS_PER_SEC;
}

bool CheckPerm(int IndexAlgo){
    for(int i = 1; i <= N; i++){
        if(Perm[IndexAlgo][i] != i)return false;
    }
    return true;
}

void MakeMatrix(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            FullPrice[i][j] = PricePositions[i][j] + PriceValue[Perm[4][i]][Perm[4][j]];
        }
    }
}

void SortingType_1(){
    pair<int,int> Dist[MAXN];
    for(int i = 1; i <= N; i++)
        Dist[Perm[1][i]] = make_pair(abs(Perm[1][i] - i),i);
    sort(Dist+1,Dist+N+1);

    for(int i = 1; i <= N; i++){
        int ii = Dist[i].second;
            if(Perm[1][ii] != ii){
                for(int j = 1; j <= N; j++){
                    if(j == Perm[1][ii]){

                        FullPath[1].push_back(make_pair(ii,j));
                        PRICE[1] += PricePositions[ii][j] + PriceValue[Perm[1][ii]][Perm[1][j]];
                        swap(Perm[1][ii],Perm[1][j]);

                        return;
                    }
                }
            }
        }
}

void SortingType_3(){
    pair<int,int> Dist[MAXN];
    for(int i = 1; i <= N; i++)
        Dist[Perm[3][i]] = make_pair(FullPrice[i][Perm[3][i]],i);
    sort(Dist+1,Dist+N+1);
    for(int i = 1; i <= N; i++){
        int ii = Dist[i].second;
            if(Perm[3][ii] != ii){
                for(int j = 1; j <= N; j++){
                    if(j == Perm[3][ii]){

                        FullPath[3].push_back(make_pair(ii,j));
                        AllPrice += FullPrice[ii][j];
                        PRICE[3] += PricePositions[ii][j] + PriceValue[Perm[3][ii]][Perm[3][j]];
                        swap(Perm[3][ii],Perm[3][j]);

                        return;
                    }
                }
            }
        }
}

void dijkstra(unsigned s)
{
    unsigned i;
    for(i = 1; i <= N; i++){
        if(FullPrice[s][i] == 0 || Perm[4][i] == i){
            d[i] = MAX_VALUE;
            pred[i] = NO_PARENT;
        }

            else {
                d[i] = FullPrice[s][i];
                pred[i] = s;
            }
    }



    for(i = 1; i <= N; i++)if(i != Perm[4][i])T[i] = 1;
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
            if(T[i] && FullPrice[j][i] != 0)
                if(d[i] > d[j] + FullPrice[j][i]){
                    d[i] = d[j] + FullPrice[j][i];
                    pred[i] = j;
                }
    }
}

void MakePath(unsigned First, unsigned Last)//N^2
{
    if(pred[Last] != First)MakePath(First,pred[Last]);
    CountPathSize++;
    FullPath[4].push_back(make_pair(First,Last));
    PRICE[4] += PricePositions[First][Last] + PriceValue[Perm[4][First]][Perm[4][Last]];
    swap(Perm[4][First],Perm[4][Last]);


}

void SortingType_4(){
    for(int i = 1; i <= N; i++){
        if(i == Perm[4][i])continue;
        dijkstra(i);
        int Pos,j;
        for(j = 1; j <= N; j++)
            if(Perm[4][j] == i){Pos = j;break;}
        MakePath(i,j);
        FullCountPathSize[4] += CountPathSize;
        AllPrice += d[j];
        CountPathSize = 0;
    }
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
        PRICE[6] += PricePositions[First][Second] + PriceValue[Perm[6][First]][Perm[6][Second]];
        swap(Perm[6][First],Perm[6][Second]);
        FullCountPathSize[6]++;
        FullPath[6].push_back(make_pair(First,Second));
        CurIndex = Next;
        if(CurIndex == LoopSize - 1){Next = 0;}
        else {Next = CurIndex + 1;}
    }while(Next != StartIndex);
}

void SortingType_6(){
    for(int i = 1; i <= N; i++){
        if(i == Perm[6][i])Used[i] = true;
        vector <int> CurLoop;
        int CurIndex = i;
        if(Used[i] == false){
            do{
                Used[CurIndex] = true;
                CurLoop.push_back(CurIndex);
                CurIndex = Perm[6][CurIndex];
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
    if(CheckPerm(6) == false)SortingType_6();
}



void SortingType_2(){
    int MinDumpPrice = MAX_VALUE,MinDumpIndex;
    for(int i = 1; i <= N; i++){
        if(i == Perm[2][i])continue;
        int price = PricePositions[i][Perm[2][i]] + PriceValue[Perm[2][i]][Perm[2][Perm[2][i]]];
        if(price < MinDumpPrice){MinDumpPrice = price;MinDumpIndex = i;}
    }

    if(MinDumpPrice < MAX_VALUE){
        FullCountPathSize[2]++;
        FullPath[2].push_back(make_pair(MinDumpIndex,Perm[2][MinDumpIndex]));
        PRICE[2] += PricePositions[MinDumpIndex][Perm[2][MinDumpIndex]] + PriceValue[Perm[2][MinDumpIndex]][Perm[2][Perm[2][MinDumpIndex]]];
        swap(Perm[2][MinDumpIndex],Perm[2][Perm[2][MinDumpIndex]]);
        //PRICE2 += PricePositions[MinDumpIndex][Perm2[MinDumpIndex]] + PriceValue[Perm2[MinDumpIndex]][Perm2[Perm2[MinDumpIndex]]];
        //cout<<MinDumpIndex<<endl;
        //cout<<Perm2[MinDumpIndex]<<" "<<Perm2[Perm2[MinDumpIndex]]<<" "<<PricePositions[MinDumpIndex][Perm2[MinDumpIndex]] + PriceValue[Perm2[MinDumpIndex]][Perm2[Perm2[MinDumpIndex]]]<<endl;
        //cout<<Perm[MinDumpPrice]<<" "<<Perm[Perm[MinDumpPrice]]<<endl;
    }
}


/// TYPE(4-0) pos=4/0 val=0/4 (n*n)
void SortingType_7(){

    for(int i = N; i >= 1; i--){
        if(i == Perm[7][i])continue;
        for(int j = 1; j <= N; j++){
            if(Perm[7][j] == i){
                if(i == Perm[7][i])break;
                PRICE[7] += PricePositions[i][j] + PriceValue[Perm[7][i]][Perm[7][j]];
                FullPath[7].push_back(make_pair(j,i));
                AllPrice +=PricePositions[i][j] + PriceValue[Perm[7][i]][Perm[7][j]];
                swap(Perm[7][j],Perm[7][i]);
                break;
            }
        }
    }
}
/// END TYPE(4-0) pos=4/0 val=0/4

/// TYPE(23-0) pos=2/3 val=0 (n*n)
void SortingType_8(){

    int Min = MAX_VALUE,MinIndex = 1;
    for(int i = 1; i <= N; i++){
        if(i == Perm[8][i])continue;
        int ValA,PosA,ValB,PosB,ValC,PosC;
        PosA = i;
        ValA = Perm[8][PosA];
        PosB = ValA;
        ValB = Perm[8][PosB];
        PosC = ValB;
        ValC = Perm[8][PosC];
        //cout<<ValA<<" "<<ValB<<" "<<ValC<<endl;

        int MidPriceA,MidPriceB,CurMidPriceB,FullMidPrice;
        MidPriceA = abs(PosA - PosB);
        MidPriceB = abs(PosB - PosC);
        CurMidPriceB = abs(PosA - PosC);
        FullMidPrice = MidPriceA + (CurMidPriceB - MidPriceB);

        if(FullMidPrice < Min){Min = FullMidPrice; MinIndex = PosA;}
    }

    if(Min != MAX_VALUE){
        FullPath[8].push_back(make_pair(MinIndex,Perm[8][MinIndex]));
        AllPrice += PricePositions[MinIndex][Perm[8][MinIndex]] + PriceValue[Perm[8][MinIndex]][Perm[8][Perm[8][MinIndex]]];
        //cout<<MinIndex<<" "<<Perm[MinIndex]<<endl;
        PRICE[8] += PricePositions[MinIndex][Perm[8][MinIndex]] + PriceValue[Perm[8][MinIndex]][Perm[8][Perm[8][MinIndex]]];
        swap(Perm[8][MinIndex],Perm[8][Perm[8][MinIndex]]);


    }


}
/// END TYPE(23-0) pos=2/3 val=0

/// TYPE(0-2) pos=0 val=2/3 (n*n)
void SortingType_9(){
    int Min = MAX_VALUE,MinIndex = 1;
    for(int i = 1; i <= N; i++){
        if(i == Perm[9][i])continue;
        int ValA,PosA,ValB,PosB,ValC,PosC;
        PosA = i;
        ValA = Perm[9][PosA];
        PosB = ValA;
        ValB = Perm[9][PosB];
        PosC = ValB;
        ValC = Perm[9][PosC];
        //cout<<ValA<<" "<<ValB<<" "<<ValC<<endl;

        int MidPriceA,MidPriceB,CurMidPriceB,FullMidPrice;
        MidPriceA = abs(ValA - ValB);
        MidPriceB = abs(ValB - ValC);
        CurMidPriceB = abs(ValA - ValC);
        FullMidPrice = MidPriceA + (CurMidPriceB - MidPriceB);

        if(FullMidPrice < Min){Min = FullMidPrice; MinIndex = PosA;}
    }

    if(Min != MAX_VALUE){
        FullPath[9].push_back(make_pair(MinIndex,Perm[9][MinIndex]));
        AllPrice += PricePositions[MinIndex][Perm[9][MinIndex]] + PriceValue[Perm[9][MinIndex]][Perm[9][Perm[9][MinIndex]]];
        //cout<<MinIndex<<" "<<Perm[MinIndex]<<endl;
        PRICE[9] += PricePositions[MinIndex][Perm[9][MinIndex]] + PriceValue[Perm[9][MinIndex]][Perm[9][Perm[9][MinIndex]]];
        swap(Perm[9][MinIndex],Perm[9][Perm[9][MinIndex]]);


    }
}
/// END TYPE(0-2) pos=0 val=2/3

/// TYPE(23-23) pos=2/3 val=2/3 (n*n)
void SortingType_10(){
    int Min = MAX_VALUE,MinIndex = 1;
    for(int i = 1; i <= N; i++){
        if(i == Perm[10][i])continue;
        int ValA,PosA,ValB,PosB,ValC,PosC;
        PosA = i;
        ValA = Perm[10][PosA];
        PosB = ValA;
        ValB = Perm[10][PosB];
        PosC = ValB;
        ValC = Perm[10][PosC];
        //cout<<ValA<<" "<<ValB<<" "<<ValC<<endl;

        int MidPriceA,MidPriceB,CurMidPriceB,FullMidPrice;
        MidPriceA = abs(PosA - PosB) + abs(ValA - ValB);
        MidPriceB = abs(PosB - PosC) + abs(ValB - ValC);
        CurMidPriceB = abs(PosA - PosC) + abs(ValA - ValC);
        FullMidPrice = MidPriceA + (CurMidPriceB - MidPriceB);

        if(FullMidPrice < Min){Min = FullMidPrice; MinIndex = PosA;}
    }

    if(Min != MAX_VALUE){
        FullPath[10].push_back(make_pair(MinIndex,Perm[10][MinIndex]));
        AllPrice += PricePositions[MinIndex][Perm[10][MinIndex]] + PriceValue[Perm[10][MinIndex]][Perm[10][Perm[10][MinIndex]]];
        //cout<<MinIndex<<" "<<Perm[MinIndex]<<endl;
        PRICE[10] += PricePositions[MinIndex][Perm[10][MinIndex]] + PriceValue[Perm[10][MinIndex]][Perm[10][Perm[10][MinIndex]]];
        swap(Perm[10][MinIndex],Perm[10][Perm[10][MinIndex]]);


    }
}
/// END TYPE(23-23) pos=2/3 val=2/3

/// TYPE(2-0)
void SortingType_11(){
    int MaxNum = 0,MaxNumPos = 0,MinNum = MAX_VALUE,MinNumPos = 0;
    for(int i = 1; i <= N; i++){
        if(i != Perm[11][i] && Perm[11][i] > MaxNum){MaxNum = Perm[11][i];MaxNumPos = i;}
    }


    if(MaxNumPos < MaxNum){/// числото k се намира на на позиция k-n
        for(int i=MaxNumPos+1; i <= MaxNum; i++){
            int CurNumPos,CurNumVal,CurDist,NewDist;
            CurNumPos = i;
            CurNumVal = Perm[11][i];
            CurDist = abs(CurNumPos - CurNumVal);
            NewDist = abs(MaxNumPos - CurNumVal);
            //cout<<CurDist<<" "<<NewDist<<" "<<MaxNum<<" "<<CurNumVal<<endl;
            if(CurDist > NewDist){
                PRICE[11] += PricePositions[MaxNumPos][CurNumPos] + PriceValue[MaxNum][CurNumVal];
                FullPath[11].push_back(make_pair(MaxNumPos,CurNumPos));

                swap(Perm[11][MaxNumPos],Perm[11][CurNumPos]);
                MaxNumPos = CurNumPos;
            }
        }
    }
    if(MaxNumPos > MaxNum){/// числото k се намира на на позиция k-n
        for(int i=MaxNumPos-1; i >= 1; i--){
            int CurNumPos,CurNumVal,CurDist,NewDist;
            CurNumPos = i;
            CurNumVal = Perm[11][i];
            CurDist = abs(CurNumPos - CurNumVal);
            NewDist = abs(MaxNumPos - CurNumVal);
            //cout<<CurDist<<" "<<NewDist<<" "<<MaxNum<<" "<<CurNumVal<<endl;
            if(CurDist > NewDist){
                PRICE[11] += PricePositions[MaxNumPos][CurNumPos] + PriceValue[MaxNum][CurNumVal];
                FullPath[11].push_back(make_pair(MaxNumPos,CurNumPos));

                swap(Perm[11][MaxNumPos],Perm[11][CurNumPos]);
                MaxNumPos = CurNumPos;
            }
        }
    }
    if(CheckPerm(11) == true)return;

    for(int i = 1; i <= N; i++){
        if(i != Perm[11][i] && Perm[11][i] < MinNum){MinNum = Perm[11][i];MinNumPos = i;}
    }
    if(MinNumPos < MinNum){/// числото k се намира на на позиция k-n
        for(int i=MinNumPos+1; i <= MinNum; i++){
            int CurNumPos,CurNumVal,CurDist,NewDist;
            CurNumPos = i;
            CurNumVal = Perm[11][i];
            CurDist = abs(CurNumPos - CurNumVal);
            NewDist = abs(MinNumPos - CurNumVal);
            //cout<<CurDist<<" "<<NewDist<<" "<<MinNum<<" "<<CurNumVal<<endl;
            if(CurDist > NewDist){
                PRICE[11] += PricePositions[MinNumPos][CurNumPos] + PriceValue[MinNum][CurNumVal];
                FullPath[11].push_back(make_pair(MinNumPos,CurNumPos));

                swap(Perm[11][MinNumPos],Perm[11][CurNumPos]);
                MinNumPos = CurNumPos;
            }
        }
    }
    if(MinNumPos > MinNum){/// числото k се намира на на позиция k-n
        for(int i=MinNumPos-1; i >= 1; i--){
            int CurNumPos,CurNumVal,CurDist,NewDist;
            CurNumPos = i;
            CurNumVal = Perm[11][i];
            CurDist = abs(CurNumPos - CurNumVal);
            NewDist = abs(MinNumPos - CurNumVal);
            //cout<<CurDist<<" "<<NewDist<<" "<<MinNum<<" "<<CurNumVal<<endl;
            if(CurDist > NewDist){
                PRICE[11] += PricePositions[MinNumPos][CurNumPos] + PriceValue[MinNum][CurNumVal];
                FullPath[11].push_back(make_pair(MinNumPos,CurNumPos));

                swap(Perm[11][MinNumPos],Perm[11][CurNumPos]);
                MinNumPos = CurNumPos;
            }
        }
    }

    if(MaxNum != Perm[11][MaxNumPos] && MinNum != Perm[11][MinNumPos]){
        //cout<<MaxNum<<" "<<Perm[11][MaxNumPos]<<endl;
        int CurMinDist,NewMinDist,CurMaxDist,NewMaxDist,MinV,MaxV;
            CurMinDist = abs(MinNum - Perm[11][MinNum]);
            NewMinDist = abs(MinNumPos - Perm[11][MinNum]);
            MinV = NewMinDist - CurMinDist;

            CurMaxDist = abs(MaxNum - Perm[11][MaxNum]);
            NewMaxDist = abs(MaxNumPos - Perm[11][MaxNum]);
            MaxV = NewMaxDist - CurMaxDist;
            //cout<<CurDist<<" "<<NewDist<<" "<<MinNum<<" "<<CurNumVal<<endl;
            if(MaxV > MinV){
                int CurNumPos = MinNum,CurNumVal = Perm[11][CurNumPos];
                PRICE[11] += PricePositions[MinNumPos][CurNumPos] + PriceValue[MinNum][CurNumVal];
                FullPath[11].push_back(make_pair(MinNumPos,CurNumPos));
                MinNumPos = CurNumPos;
                swap(Perm[11][MinNumPos],Perm[11][CurNumPos]);
            }
            else{
                int CurNumPos = MaxNum,CurNumVal = Perm[11][CurNumPos];
                PRICE[11] += PricePositions[MaxNumPos][CurNumPos] + PriceValue[MaxNum][CurNumVal];
                FullPath[11].push_back(make_pair(MaxNumPos,CurNumPos));
                MaxNumPos = CurNumPos;
                swap(Perm[11][MaxNumPos],Perm[11][CurNumPos]);
            }
    }
    /*cout<<MinNum<<" "<<MaxNum<<endl;
    for(int i = 1;i <= N; i++)
    {
        cout<<Perm[11][i]<<" ";
    }
    cout<<endl;*/
}
/// END TYPE(2-0)

/// TYPE(2-2)
void SortingType_12(){
    Duration = MyTime();
    if(Duration >= TimeLimit){HaveTime = false;return;}

    pair<int,int> MinSwap[MAXN];
    int MinPrice = MAX_VALUE,MinPriceIndex[2];
    for(int i = 1; i <= N; i++){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
        if(i == Perm[12][i]){
            MinSwap[i].first = MAX_VALUE;
            MinSwap[i].second = i;

        }
        if(i > Perm[12][i]){
            int MinCurPrice = MAX_VALUE,MinCurPriceIndex = 0;
            int LastIndex = (i - 2*Perm[12][i]);
            if(LastIndex <= 0)LastIndex = 1;
            for(int j = i-1; j >= LastIndex; j--){
                Duration = MyTime();
                if(Duration >= TimeLimit){HaveTime = false;return;}

                int CurPrice = 0;
                if(abs(j-Perm[12][j]) < abs(i - Perm[12][j]))CurPrice += abs(i-j)*6+abs(Perm[12][i]-Perm[12][j])*6;
                else {
                    CurPrice += CurPrice += abs(i-j)+abs(Perm[12][i]-Perm[12][j]);
                }
                if(CurPrice < MinCurPrice){
                    MinCurPrice = CurPrice;
                    MinCurPriceIndex = j;
                }
            }
            MinSwap[i].first = MinCurPrice;
            MinSwap[i].second = MinCurPriceIndex;
        }

        if(i < Perm[12][i]){
            int MinCurPrice = MAX_VALUE,MinCurPriceIndex = 0;
            int LastIndex = (i + 2*Perm[12][i]);
            if(LastIndex > N)LastIndex = N;
            for(int j = i+1; j <= LastIndex; j++){

                Duration = MyTime();
                if(Duration >= TimeLimit){HaveTime = false;return;}

                int CurPrice = 0;
                if(abs(j-Perm[12][j]) < abs(i - Perm[12][j]))CurPrice += abs(i-j)*6+abs(Perm[12][i]-Perm[12][j])*6;
                else {
                    CurPrice += CurPrice += abs(i-j)+abs(Perm[12][i]-Perm[12][j]);
                }
                if(CurPrice < MinCurPrice){
                    MinCurPrice = CurPrice;
                    MinCurPriceIndex = j;
                }
            }
            MinSwap[i].first = MinCurPrice;
            MinSwap[i].second = MinCurPriceIndex;
        }

        if(MinPrice > MinSwap[i].first){
            MinPrice = MinSwap[i].first;
            MinPriceIndex[0] = i;

            MinPriceIndex[1] = MinSwap[i].second;
        }
    }
    PRICE[12] += PricePositions[MinPriceIndex[0]][MinPriceIndex[1]]
                + PriceValue[Perm[12][MinPriceIndex[0]]][Perm[12][MinPriceIndex[1]]];
    FullPath[12].push_back(make_pair(MinPriceIndex[0],MinPriceIndex[1]));
    //cout<<Perm[12][MinPriceIndex[0]]<<" "<<Perm[12][MinPriceIndex[1]]<<endl;
    swap(Perm[12][MinPriceIndex[0]],Perm[12][MinPriceIndex[1]]);

}
/// END TYPE(2-2)

void SortingType_13(){
    for(int i = N; i >= 1; i--){
        if(i != Perm[13][i]){
            //cout<<i<<" "<<Perm[13][i]<<endl;
            PRICE[13] += PricePositions[i][Perm[13][i]] + PriceValue[Perm[13][i]][Perm[13][Perm[13][i]]];
            FullPath[13].push_back(make_pair(i,Perm[13][i]));
            swap(Perm[13][i],Perm[13][Perm[13][i]]);
            break;
        }
    }
    //for(int i = 1; i <= N; i++)cout<<Perm[13][i]<<" ";cout<<endl;
    for(int i = 1; i <= N; i++){
        if(i != Perm[13][i]){
            //cout<<i<<" "<<Perm[13][i]<<endl;
            PRICE[13] += PricePositions[i][Perm[13][i]] + PriceValue[Perm[13][i]][Perm[13][Perm[13][i]]];
            FullPath[13].push_back(make_pair(i,Perm[13][i]));
            swap(Perm[13][i],Perm[13][Perm[13][i]]);
            break;
        }
    }
    //for(int i = 1; i <= N; i++)cout<<Perm[13][i]<<" ";cout<<endl;
}

void SortingType_14(){
    for(int i = 1; i < N; i++){
        if(i == Perm[14][i])continue;
        for(int j = i+1 ; j <= N; j++){
            if(j == Perm[14][j])continue;
            if(Perm[14][i] > Perm[14][j]){
                PRICE[14] += PricePositions[i][j] + PriceValue[Perm[14][i]][Perm[14][j]];
                FullPath[14].push_back(make_pair(i,j));
                swap(Perm[14][i],Perm[14][j]);
            }
        }
    }
}

void SortingType_15(){
    for(int i = 1; i <= N; i++){
        while(i != Perm[15][i]){
            int pos1=i,val1=Perm[15][i],pos2=Perm[15][i],val2=Perm[15][Perm[15][i]];
            PRICE[15] += PricePositions[pos1][pos2] + PriceValue[val1][val2];
            FullPath[15].push_back(make_pair(pos1,pos2));
            swap(Perm[15][pos1],Perm[15][pos2]);
        }
    }
}

void SortingType_16(){
    int MinDumpPrice = MAX_VALUE,MinDumpIndex;
    for(int i = 1; i <= N; i++){
        int Index;
        for(int j = 1; j <= N; j++)if(Perm[16][j] == i){Index = j;break;}
        if(i == Index)continue;
        int price = PricePositions[Index][Perm[16][Index]] + PriceValue[Perm[16][Index]][Perm[16][Perm[16][Index]]];
        if(price < MinDumpPrice){MinDumpPrice = price;MinDumpIndex = Index;}
    }

    if(MinDumpPrice < MAX_VALUE){
        FullCountPathSize[16]++;
        FullPath[16].push_back(make_pair(MinDumpIndex,Perm[16][MinDumpIndex]));
        PRICE[16] += MinDumpPrice;
        swap(Perm[16][MinDumpIndex],Perm[16][Perm[16][MinDumpIndex]]);
        //PRICE2 += PricePositions[MinDumpIndex][Perm2[MinDumpIndex]] + PriceValue[Perm2[MinDumpIndex]][Perm2[Perm2[MinDumpIndex]]];
        //cout<<MinDumpIndex<<endl;
        //cout<<Perm2[MinDumpIndex]<<" "<<Perm2[Perm2[MinDumpIndex]]<<" "<<PricePositions[MinDumpIndex][Perm2[MinDumpIndex]] + PriceValue[Perm2[MinDumpIndex]][Perm2[Perm2[MinDumpIndex]]]<<endl;
        //cout<<Perm[MinDumpPrice]<<" "<<Perm[Perm[MinDumpPrice]]<<endl;
    }
}

void SortingType_17(){
    for(int i = 1; i < N; i++){
        if(i == Perm[17][i])continue;
        for(int j = i+1; j <= N; j++){
            if(j > Perm[17][j]){
                PRICE[17] += PricePositions[i][j] + PriceValue[Perm[17][i]][Perm[17][j]];
                FullPath[17].push_back(make_pair(i,j));
                swap(Perm[17][i],Perm[17][j]);
                break;
            }
        }
    }
}

void SortingType_18(){
    int IndexI;
    for(int i = N; i >= 1; i--){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}

        for(int j = 1; j <= N; j++)
            if(Perm[18][j] == i){IndexI = j;break;}
        if(i == IndexI)continue;
        int F,L;
        if(i > IndexI)
        {
            F = IndexI+1;
            L = i;
            for(int j = F; j <= L; j++){
                Duration = MyTime();
                if(Duration >= TimeLimit){HaveTime = false;return;}

                int PriceNow = FullPrice[Perm[18][j]][j],PriceAfterSwap = FullPrice[Perm[18][j]][IndexI];
                if(PriceAfterSwap <= PriceNow){
                    PRICE[18] += PricePositions[IndexI][j] + PriceValue[i][Perm[18][j]];
                    FullPath[18].push_back(make_pair(IndexI,j));
                    swap(Perm[18][IndexI],Perm[18][j]);
                    continue;
                }
            }
        }
        else
        {
            F = IndexI - 1;
            L = i;
            for(int j = F; j >= L; j--){
                Duration = MyTime();
                if(Duration >= TimeLimit){HaveTime = false;return;}
                int PriceNow = FullPrice[Perm[18][j]][j],PriceAfterSwap = FullPrice[Perm[18][j]][IndexI];
                    if(PriceAfterSwap <= PriceNow){
                        PRICE[18] += PricePositions[IndexI][j] + PriceValue[i][Perm[18][j]];
                        FullPath[18].push_back(make_pair(IndexI,j));
                        swap(Perm[18][IndexI],Perm[18][j]);
                        continue;
                    }
            }
        }

    }
}

void SortingType_19(){
    for(int i = 1;i < N; i++){
        if(i == Perm[19][i])continue;
        for(int j = i+1; j <= Perm[19][i]; j++){
            if(Perm[19][j] <= i){
                PRICE[19] += PricePositions[i][j] + PriceValue[Perm[19][i]][Perm[19][j]];
                FullPath[19].push_back(make_pair(i,j));
                swap(Perm[19][i],Perm[19][j]);
            }
        }
        //for(int j = 1;j <= N; j++)cout<<Perm[19][j]<<" ";cout<<endl;
    }

}
/*int MCurPrice=FullPrice[i][j],MNextPrice=FullPrice[j][Perm[19][i]],MFullPrice=FullPrice[i][Perm[19][i]];
cout<<i<<" "<<j<<endl;
            cout<<MCurPrice<<" "<<MNextPrice<<" "<<MFullPrice<<endl;
            cout<<MCurPrice+MNextPrice<<endl;
                        if(MFullPrice < MCurPrice+MNextPrice){cout<<"CONTINUE: "<<MCurPrice<<" "<<MNextPrice<<" "<<MFullPrice<<endl;continue;}

*/

void SortingType_20(){
    int MaxNum = 0,MaxNumPos = 0,MinNum = MAX_VALUE,MinNumPos = 0;
    for(int i = 1; i <= N; i++){
        if(i != Perm[20][i] && Perm[20][i] > MaxNum){MaxNum = Perm[20][i];MaxNumPos = i;}
    }
    if(MaxNumPos < MaxNum){/// числото k се намира на на позиция k-n
            for(int i=MaxNumPos+1; i <= MaxNum; i++){
                int CurNumPos,CurNumVal,CurDist,NewDist;
                int MCurPrice=FullPrice[MaxNumPos][i],MNextPrice=FullPrice[i][MaxNum],MFullPrice=FullPrice[MaxNumPos][MaxNum];
                CurNumPos = i;
                CurNumVal = Perm[20][i];
                CurDist = abs(CurNumPos - CurNumVal);
                NewDist = abs(MaxNumPos - CurNumVal);
                //cout<<CurDist<<" "<<NewDist<<" "<<MaxNum<<" "<<CurNumVal<<endl;
                //cout<<MCurPrice<<" "<<MNextPrice<<" "<<MFullPrice<<endl;
                if(CurDist > NewDist && (MFullPrice >= MCurPrice+MNextPrice)){
                    PRICE[20] += PricePositions[MaxNumPos][CurNumPos] + PriceValue[MaxNum][CurNumVal];
                    FullPath[20].push_back(make_pair(MaxNumPos,CurNumPos));
                    //cout<<MaxNumPos<<" "<<CurNumPos<<endl;
                    swap(Perm[20][MaxNumPos],Perm[20][CurNumPos]);
                    MaxNumPos = CurNumPos;
                }
                /*else if(i == MaxNum){
                    PRICE[20] += PricePositions[MaxNumPos][CurNumPos] + PriceValue[MaxNum][CurNumVal];
                    FullPath[20].push_back(make_pair(MaxNumPos,CurNumPos));
                    //cout<<MaxNumPos<<" "<<CurNumPos<<endl;
                    swap(Perm[20][MaxNumPos],Perm[20][CurNumPos]);
                    MaxNumPos = CurNumPos;
                }*/
            }
        }
    if(MaxNumPos > MaxNum){/// числото k се намира на на позиция k-n
        for(int i=MaxNumPos-1; i >= 1; i--){
            int CurNumPos,CurNumVal,CurDist,NewDist;
            int MCurPrice=FullPrice[MaxNumPos][i],MNextPrice=FullPrice[i][MaxNum],MFullPrice=FullPrice[MaxNumPos][MaxNum];

            CurNumPos = i;
            CurNumVal = Perm[20][i];
            CurDist = abs(CurNumPos - CurNumVal);
            NewDist = abs(MaxNumPos - CurNumVal);
            //cout<<CurDist<<" "<<NewDist<<" "<<MaxNum<<" "<<CurNumVal<<endl;
            if(CurDist > NewDist && (MFullPrice >= MCurPrice+MNextPrice)){
                PRICE[20] += PricePositions[MaxNumPos][CurNumPos] + PriceValue[MaxNum][CurNumVal];
                FullPath[20].push_back(make_pair(MaxNumPos,CurNumPos));

                swap(Perm[20][MaxNumPos],Perm[20][CurNumPos]);
                MaxNumPos = CurNumPos;
            }
        }
    }
    if(CheckPerm(20) == true)return;

    for(int i = 1; i <= N; i++){
        if(i != Perm[20][i] && Perm[20][i] < MinNum){MinNum = Perm[20][i];MinNumPos = i;}
    }
    if(MinNumPos < MinNum){/// числото k се намира на на позиция k-n
        for(int i=MinNumPos+1; i <= MinNum; i++){
            int CurNumPos,CurNumVal,CurDist,NewDist;
            int MCurPrice=FullPrice[MinNumPos][i],MNextPrice=FullPrice[i][MinNum],MFullPrice=FullPrice[MaxNumPos][MinNum];
            CurNumPos = i;
            CurNumVal = Perm[20][i];
            CurDist = abs(CurNumPos - CurNumVal);
            NewDist = abs(MinNumPos - CurNumVal);
            //cout<<CurDist<<" "<<NewDist<<" "<<MinNum<<" "<<CurNumVal<<endl;
            if(CurDist > NewDist && (MFullPrice >= MCurPrice+MNextPrice)){
                PRICE[20] += PricePositions[MinNumPos][CurNumPos] + PriceValue[MinNum][CurNumVal];
                FullPath[20].push_back(make_pair(MinNumPos,CurNumPos));

                swap(Perm[20][MinNumPos],Perm[20][CurNumPos]);
                MinNumPos = CurNumPos;
            }
        }
    }
    if(MinNumPos > MinNum){/// числото k се намира на на позиция k-n
        for(int i=MinNumPos-1; i >= 1; i--){
            int CurNumPos,CurNumVal,CurDist,NewDist;
            int MCurPrice=FullPrice[MinNumPos][i],MNextPrice=FullPrice[i][MinNum],MFullPrice=FullPrice[MaxNumPos][MinNum];
            CurNumPos = i;
            CurNumVal = Perm[20][i];
            CurDist = abs(CurNumPos - CurNumVal);
            NewDist = abs(MinNumPos - CurNumVal);
            //cout<<CurDist<<" "<<NewDist<<" "<<MinNum<<" "<<CurNumVal<<endl;
            if(CurDist > NewDist && (MFullPrice >= MCurPrice+MNextPrice)){
                PRICE[20] += PricePositions[MinNumPos][CurNumPos] + PriceValue[MinNum][CurNumVal];
                FullPath[20].push_back(make_pair(MinNumPos,CurNumPos));

                swap(Perm[20][MinNumPos],Perm[20][CurNumPos]);
                MinNumPos = CurNumPos;
            }
        }
    }

    if(MaxNum != Perm[20][MaxNumPos] && MinNum != Perm[20][MinNumPos]){
        //cout<<MaxNum<<" "<<Perm[20][MaxNumPos]<<endl;
        int CurMinDist,NewMinDist,CurMaxDist,NewMaxDist,MinV,MaxV;
            CurMinDist = abs(MinNum - Perm[20][MinNum]);
            NewMinDist = abs(MinNumPos - Perm[20][MinNum]);
            MinV = NewMinDist - CurMinDist;

            CurMaxDist = abs(MaxNum - Perm[20][MaxNum]);
            NewMaxDist = abs(MaxNumPos - Perm[20][MaxNum]);
            MaxV = NewMaxDist - CurMaxDist;
            //cout<<CurDist<<" "<<NewDist<<" "<<MinNum<<" "<<CurNumVal<<endl;
            if(MaxV > MinV){
                int CurNumPos = MinNum,CurNumVal = Perm[20][CurNumPos];
                PRICE[20] += PricePositions[MinNumPos][CurNumPos] + PriceValue[MinNum][CurNumVal];
                FullPath[20].push_back(make_pair(MinNumPos,CurNumPos));
                MinNumPos = CurNumPos;
                swap(Perm[20][MinNumPos],Perm[20][CurNumPos]);
            }
            else{
                int CurNumPos = MaxNum,CurNumVal = Perm[20][CurNumPos];
                PRICE[20] += PricePositions[MaxNumPos][CurNumPos] + PriceValue[MaxNum][CurNumVal];
                FullPath[20].push_back(make_pair(MaxNumPos,CurNumPos));
                MaxNumPos = CurNumPos;
                swap(Perm[20][MaxNumPos],Perm[20][CurNumPos]);
            }
    }

    if(MaxNum != Perm[20][MaxNum]){
        PRICE[20] += PricePositions[MaxNum][MaxNumPos] + PriceValue[MaxNum][Perm[20][MaxNum]];
        FullPath[20].push_back(make_pair(MaxNum,MaxNumPos));
        swap(Perm[20][MaxNum],Perm[20][MaxNumPos]);
    }

}

void SortingType_21(){
    int MINPRICE = MAX_VALUE,MININDEX = 1;
    for(int i = 1; i <= N; i++){
        Duration = MyTime();
            if(Duration >= TimeLimit){HaveTime = false;return;}
        if(i == Perm[21][i])continue;
        if(MINPRICE < FullPrice[i][Perm[21][i]]){MINPRICE = FullPrice[i][Perm[21][i]];MININDEX = i;}
    }
    int VALUE = Perm[21][MININDEX];
    PRICE[21] += PricePositions[MININDEX][Perm[21][MININDEX]] + PriceValue[VALUE][Perm[21][VALUE]];
        FullPath[21].push_back(make_pair(MININDEX,VALUE));
        swap(Perm[21][MININDEX],Perm[21][VALUE]);
}

void SortingType_22(){
    int MinDist = MAX_VALUE, MinDistIndex = 1, MinDistPlus = 1;
    for(int i = 1; i < N; i++){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
        for(int j = 1; j <= N-i; j++){
            Duration = MyTime();
            if(Duration >= TimeLimit){HaveTime = false;return;}

            if(j == Perm[22][j] || j+i == Perm[22][j+i])continue;
            if(Perm[22][j] > Perm[22][j+i] && j >= Perm[22][j+i]){
                if(MinDist > Perm[22][j] - Perm[22][j+i]){
                    MinDist = Perm[22][j] - Perm[22][j+i];
                    MinDistIndex = j;
                    MinDistPlus = i;
                }
            }
        }

    }
    if(MinDist != MAX_VALUE){
            PRICE[22] += PricePositions[MinDistIndex][MinDistIndex+MinDistPlus] + PriceValue[Perm[22][MinDistIndex]][Perm[22][MinDistIndex+MinDistPlus]];
            FullPath[22].push_back(make_pair(MinDistIndex,MinDistIndex+MinDistPlus));
            swap(Perm[22][MinDistIndex],Perm[22][MinDistIndex+MinDistPlus]);
        }
}

void SortingType_216(){
    for(int i = 1; i <= N; i++){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
        if(i == Perm[21][i])Used[i] = true;
        vector <int> CurLoop;
        int CurIndex = i;
        if(Used[i] == false){
            do{
                Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
                Used[CurIndex] = true;
                CurLoop.push_back(CurIndex);
                CurIndex = Perm[21][CurIndex];
            }while(CurIndex != i);
            Loops.push_back(CurLoop);
        }
    }
    int CountLoops = Loops.size();
    int MinPriceLoops = MAX_VALUE,MinStartIndex = 1;
    for(int i = 0; i < CountLoops; i++){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
        int CountNumInLoop = Loops[i].size();
        for(int j = 0; j < CountNumInLoop; j++){
            int CountLoopPrice = 0,Next;
            for(int k = 0; k < CountNumInLoop; k++){
                Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
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
    if(CheckPerm(21) == false)SortingType_216();
}
void SortingType_226(){
    for(int i = 1; i <= N; i++){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
        if(i == Perm[22][i])Used[i] = true;
        vector <int> CurLoop;
        int CurIndex = i;
        if(Used[i] == false){
            do{
                Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
                Used[CurIndex] = true;
                CurLoop.push_back(CurIndex);
                CurIndex = Perm[22][CurIndex];
            }while(CurIndex != i);
            Loops.push_back(CurLoop);
        }
    }
    int CountLoops = Loops.size();
    int MinPriceLoops = MAX_VALUE,MinStartIndex = 1;
    for(int i = 0; i < CountLoops; i++){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
        int CountNumInLoop = Loops[i].size();
        for(int j = 0; j < CountNumInLoop; j++){
            int CountLoopPrice = 0,Next;
            for(int k = 0; k < CountNumInLoop; k++){
                Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
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
    if(CheckPerm(22) == false)SortingType_226();
}
void SortingType_126(){
    for(int i = 1; i <= N; i++){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
        if(i == Perm[12][i])Used[i] = true;
        vector <int> CurLoop;
        int CurIndex = i;
        if(Used[i] == false){
            do{
                Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
                Used[CurIndex] = true;
                CurLoop.push_back(CurIndex);
                CurIndex = Perm[12][CurIndex];
            }while(CurIndex != i);
            Loops.push_back(CurLoop);
        }
    }
    int CountLoops = Loops.size();
    int MinPriceLoops = MAX_VALUE,MinStartIndex = 1;
    for(int i = 0; i < CountLoops; i++){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
        int CountNumInLoop = Loops[i].size();
        for(int j = 0; j < CountNumInLoop; j++){
            int CountLoopPrice = 0,Next;
            for(int k = 0; k < CountNumInLoop; k++){
                Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
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
    if(CheckPerm(12) == false)SortingType_126();
}
void SortingType_186(){
    for(int i = 1; i <= N; i++){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
        if(i == Perm[18][i])Used[i] = true;
        vector <int> CurLoop;
        int CurIndex = i;
        if(Used[i] == false){
            do{
                Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
                Used[CurIndex] = true;
                CurLoop.push_back(CurIndex);
                CurIndex = Perm[18][CurIndex];
            }while(CurIndex != i);
            Loops.push_back(CurLoop);
        }
    }
    int CountLoops = Loops.size();
    int MinPriceLoops = MAX_VALUE,MinStartIndex = 1;
    for(int i = 0; i < CountLoops; i++){
        Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
        int CountNumInLoop = Loops[i].size();
        for(int j = 0; j < CountNumInLoop; j++){
            int CountLoopPrice = 0,Next;
            for(int k = 0; k < CountNumInLoop; k++){
                Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;return;}
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
    if(CheckPerm(18) == false)SortingType_186();
}

void Sorting(){
    if(HaveTime == false)return;
MakeMatrix();
        while(CheckPerm(1) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
            if(HaveTime == false){PRICE[1] = MAX_VALUE;break;}
            SortingType_1();
            if(PRICE[1] >= MinPrice){PRICE[1] = MAX_VALUE;break;}
        }
        if(MinPrice < PRICE[1])MinPrice = PRICE[1];


    while(CheckPerm(3) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[3] = MAX_VALUE;break;}
        SortingType_3();
        if(PRICE[3] >= MinPrice){PRICE[3] = MAX_VALUE;break;}
    }
    if(MinPrice < PRICE[3])MinPrice = PRICE[3];

    while(CheckPerm(4) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[4] = MAX_VALUE;break;}
            SortingType_4();
            if(PRICE[4] >= MinPrice){PRICE[4] = MAX_VALUE;break;}
        }
        if(MinPrice < PRICE[4])MinPrice = PRICE[4];
    while(CheckPerm(6) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[6] = MAX_VALUE;break;}
        SortingType_6();
        if(PRICE[6] >= MinPrice){PRICE[6] = MAX_VALUE;break;}
    }
    if(MinPrice < PRICE[6])MinPrice = PRICE[6];

    while(CheckPerm(2) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[2] = MAX_VALUE;break;}
            SortingType_2();
            if(PRICE[2] >= MinPrice){PRICE[2] = MAX_VALUE;break;}
        }
        if(MinPrice < PRICE[2])MinPrice = PRICE[2];
    while(CheckPerm(7) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[7] = MAX_VALUE;break;}
            SortingType_7();
            if(PRICE[7] >= MinPrice){PRICE[7] = MAX_VALUE;break;}
        }
        if(MinPrice < PRICE[7])MinPrice = PRICE[7];
    while(CheckPerm(8) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[8] = MAX_VALUE;break;}
            SortingType_8();
            if(PRICE[8] >= MinPrice){PRICE[8] = MAX_VALUE;break;}
        }
        if(MinPrice < PRICE[8])MinPrice = PRICE[8];
    while(CheckPerm(9) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[9] = MAX_VALUE;break;}
            SortingType_9();
            if(PRICE[9] >= MinPrice){PRICE[9] = MAX_VALUE;break;}
        }
        if(MinPrice < PRICE[9])MinPrice = PRICE[9];
    while(CheckPerm(10) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[10] = MAX_VALUE;break;}
            SortingType_10();
            if(PRICE[10] >= MinPrice){PRICE[10] = MAX_VALUE;break;}
        }
        if(MinPrice < PRICE[10])MinPrice = PRICE[10];
    while(CheckPerm(11) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[11] = MAX_VALUE;break;}
            SortingType_11();
            if(PRICE[11] >= MinPrice){PRICE[11] = MAX_VALUE;break;}

        }
        if(MinPrice < PRICE[11])MinPrice = PRICE[11];


    while(CheckPerm(13) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[13] = MAX_VALUE;break;}
            SortingType_13();
            if(PRICE[13] >= MinPrice){PRICE[13] = MAX_VALUE;break;}

    }
    if(MinPrice < PRICE[13])MinPrice = PRICE[13];

    while(CheckPerm(14) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[14] = MAX_VALUE;break;}
            SortingType_14();
            if(PRICE[14] >= MinPrice){PRICE[14] = MAX_VALUE;break;}

    }
    if(MinPrice < PRICE[14])MinPrice = PRICE[14];

    while(CheckPerm(15) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[15] = MAX_VALUE;break;}
            SortingType_15();
            if(PRICE[15] >= MinPrice){PRICE[15] = MAX_VALUE;break;}

    }
    if(MinPrice < PRICE[15])MinPrice = PRICE[15];
    while(CheckPerm(16) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[16] = MAX_VALUE;break;}
            SortingType_16();
            if(PRICE[16] >= MinPrice){PRICE[16] = MAX_VALUE;break;}

    }
    if(MinPrice < PRICE[16])MinPrice = PRICE[16];
    while(CheckPerm(17) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[17] = MAX_VALUE;break;}
            SortingType_17();
            if(PRICE[17] >= MinPrice){PRICE[17] = MAX_VALUE;break;}

    }
    if(MinPrice < PRICE[17])MinPrice = PRICE[17];


    while(CheckPerm(19) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[19] = MAX_VALUE;break;}
            SortingType_19();
            if(PRICE[19] >= MinPrice){PRICE[19] = MAX_VALUE;break;}
    }
    if(MinPrice < PRICE[19])MinPrice = PRICE[19];
    while(CheckPerm(20) == false){
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}
        if(HaveTime == false){PRICE[20] = MAX_VALUE;break;}
            SortingType_20();
            if(PRICE[20] >= MinPrice){PRICE[20] = MAX_VALUE;break;}

    }
    if(MinPrice < PRICE[20])MinPrice = PRICE[20];





            start:
            Duration = MyTime();
        if(Duration >= TimeLimit){HaveTime = false;}

    if(HaveTime == false){PRICE[5] = MAX_VALUE;goto end;}
    if(CheckPerm(5) == true)goto end;
        for(int i = 1; i <= N; i++){
            if(Perm[5][i] != i){
                for(int j = 1; j <= N; j++){
                    if(j == Perm[5][i]){

                        FullPath[5].push_back(make_pair(i,j));
                        swap(Perm[5][i],Perm[5][j]);
                        PRICE[5] += PricePositions[i][j] + PriceValue[Perm[5][i]][Perm[5][j]];
                        goto start;

                    }
                }
            }
        }

    end:;


    if(MinPrice < PRICE[5])MinPrice = PRICE[5];

    while(CheckPerm(21) == false){

            if(CheckPerm(21) == false && HaveTime == false)
            {

                //PRICE[21] = 0;
                while(CheckPerm(21) == false){
                    if(CheckPerm(21) == false && HaveTime == false){PRICE[21] = MAX_VALUE;break;}
                    SortingType_216();
                    if(PRICE[21] >= MinPrice){PRICE[21] = MAX_VALUE;break;}
                    }
                    break;
            }
            SortingType_21();
            if(PRICE[21] >= MinPrice){PRICE[21] = MAX_VALUE;break;}

    }
    if(MinPrice < PRICE[21])MinPrice = PRICE[21];

    while(CheckPerm(22) == false){
        if(CheckPerm(22) == false && HaveTime == false)
            {
                //PRICE[22] = 0;
                while(CheckPerm(22) == false){
                    if(CheckPerm(22) == false && HaveTime == false){PRICE[22] = MAX_VALUE;break;}
                SortingType_226();
                if(PRICE[22] >= MinPrice){PRICE[22] = MAX_VALUE;break;}
                }
                break;
            }
            SortingType_22();
            if(PRICE[22] >= MinPrice){PRICE[22] = MAX_VALUE;break;}

    }
    if(MinPrice < PRICE[22])MinPrice = PRICE[22];

    while(CheckPerm(12) == false){

            if(CheckPerm(12) == false && HaveTime == false)
            {
                //PRICE[12] = 0;
                while(CheckPerm(12) == false){
                    if(CheckPerm(12) == false && HaveTime == false){PRICE[12] = MAX_VALUE;break;}
                SortingType_126();
                if(PRICE[12] >= MinPrice){PRICE[12] = MAX_VALUE;break;}
                }
                break;
            }
            SortingType_12();
            if(PRICE[12] >= MinPrice){PRICE[12] = MAX_VALUE;break;}

        }
    if(MinPrice < PRICE[12])MinPrice = PRICE[12];
    while(CheckPerm(18) == false){

            if(CheckPerm(18) == false && HaveTime == false)
            {
                //PRICE[18] = 0;
                while(CheckPerm(18) == false){
                    if(CheckPerm(18) == false && HaveTime == false){PRICE[18] = MAX_VALUE;break;}
                SortingType_186();
                if(PRICE[18] >= MinPrice){PRICE[18] = MAX_VALUE;break;}
                }
                break;
            }
            SortingType_18();
            if(PRICE[18] >= MinPrice){PRICE[18] = MAX_VALUE;break;}

    }
    if(MinPrice < PRICE[18])MinPrice = PRICE[18];


    //for(int i = 1; i < MyAlgo; i++)if(CheckPerm(i) == false && i != 12 && i != 18){Sorting();return;}
}



void SortingByType(){
    if(TypePricePos == 4 && (TypePriceVal == 0 || TypePriceVal == 4)){
        while(CheckPerm(7) == false){
            SortingType_7();
            if(PRICE[7] >= MinPrice){PRICE[7] = MAX_VALUE;break;}
        }
        if(MinPrice < PRICE[7])MinPrice = PRICE[7];
        return;
    }
    if(TypePricePos == 2 && TypePriceVal == 0){
        while(CheckPerm(19) == false){
            SortingType_19();
            if(PRICE[19] >= MinPrice){PRICE[19] = MAX_VALUE;break;}
        }
        if(MinPrice < PRICE[19])MinPrice = PRICE[19];
        return;
    }


    Sorting();
}
int main() {

    StartTime = clock();
    Input();
    SortingByType();
    for(int i = 1; i < MyAlgo; i++)if(PRICE[i] == 0)PRICE[i] = MAX_VALUE;
    int MIN = PRICE[6],MINIndex=6;
    for(int i = 1; i < MyAlgo; i++){
        if(MIN > PRICE[i]){MIN = PRICE[i];MINIndex = i;}
    }


   /*
     for(int i = 1; i < MyAlgo; i++)
        cout<<PRICE[i]<<" ";
        cout<<endl;
        //*/
    //cout<<PRICE1<<" "<<PRICE2<<" "<<PRICE3<<" "<<PRICE4<<" "<<PRICE5<<" "<<PRICE6<<" "<<PRICE7<<" "<<PRICE8<<" "<<PRICE9<<" "<<PRICE10<<endl;


    Output(MINIndex);

    //cout<<AllPrice<<endl;
    return 0;
}



