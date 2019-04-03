#include<iostream>
#include<fstream>
#include<utility>
#include<vector>
#include<cmath>
#include<algorithm>

#define MAXN 512
#define MAX_VALUE 8192
#define NO_PARENT (unsigned) (-1)
using namespace std;

 int N,PricePositions[MAXN][MAXN],PriceValue[MAXN][MAXN],AllPrice = 0;
 int FullPrice[MAXN][MAXN],Perm[MAXN],Perm2[MAXN],Perm3[MAXN],Perm4[MAXN],Perm5[MAXN],Perm6[MAXN],Perm7[MAXN],Perm8[MAXN],Perm9[MAXN],Perm10[MAXN],BestPrice[MAXN][MAXN],BestWayPred[MAXN][MAXN];
 short TypePricePos,TypePriceVal;

int PRICE1 = 0, PRICE2 = 0,PRICE3 = 0,PRICE4 = 0,PRICE5 = 0,PRICE6 = 0,PRICE7 = 0, PRICE8 = 0, PRICE9 = 0,PRICE10 = 0;

pair < int ,  int> MyPath[MAXN];
 int CountPathSize = 0;

vector<pair < int ,  int> > FullPath,FullPath2,FullPath3,FullPath4,FullPath5,FullPath6,FullPath7,FullPath8,FullPath9,FullPath10;
 int FullCountPathSize = 0,FullCountPathSize2 = 0,FullCountPathSize3 = 0;
 int FullCountPathSize4 = 0,FullCountPathSize5 = 0,FullCountPathSize6 = 0;
 int FullCountPathSize7 = 0,FullCountPathSize8 = 0,FullCountPathSize9 = 0, FullCountPathSize10 = 0;


char T[MAXN];
unsigned d[MAXN];
 int pred[MAXN];

void Input(){//N^2
    ifstream InputFile;
    InputFile.open("sorting.in",ios::in);
    InputFile>>N;
    for(int i = 1 ; i <= N; i++){
        InputFile>>Perm[i];
        Perm2[i] = Perm[i];
        Perm3[i] = Perm[i];
        Perm4[i] = Perm[i];
        Perm5[i] = Perm[i];
        Perm6[i] = Perm[i];
        Perm7[i] = Perm[i];
        Perm8[i] = Perm[i];
        Perm9[i] = Perm[i];
        Perm10[i] = Perm[i];
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

void Output2(){//N^2
    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize2 = FullPath2.size();
    OutputFile<<FullCountPathSize2<<endl;
    for(int i = 0; i < FullCountPathSize2; i++)
        OutputFile<<FullPath2[i].first<<" "<<FullPath2[i].second<<endl;

    OutputFile.close();
}
void Output3(){//N^2

    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize3 = FullPath3.size();
    OutputFile<<FullCountPathSize3<<endl;
    for(int i = 0; i < FullCountPathSize3; i++)
        OutputFile<<FullPath3[i].first<<" "<<FullPath3[i].second<<endl;

    OutputFile.close();
}
void Output4(){//N^2
    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize4 = FullPath4.size();
    OutputFile<<FullCountPathSize4<<endl;
    for(int i = 0; i < FullCountPathSize4; i++)
        OutputFile<<FullPath4[i].first<<" "<<FullPath4[i].second<<endl;

    OutputFile.close();
}
void Output5(){//N^2
    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize5 = FullPath5.size();
    OutputFile<<FullCountPathSize5<<endl;
    for(int i = 0; i < FullCountPathSize5; i++)
        OutputFile<<FullPath5[i].first<<" "<<FullPath5[i].second<<endl;

    OutputFile.close();
}
void Output6(){//N^2
    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize6 = FullPath6.size();
    OutputFile<<FullCountPathSize6<<endl;
    for(int i = 0; i < FullCountPathSize6; i++)
        OutputFile<<FullPath6[i].first<<" "<<FullPath6[i].second<<endl;

    OutputFile.close();
}
void Output7(){//N^2
    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize7 = FullPath7.size();
    OutputFile<<FullCountPathSize7<<endl;
    for(int i = 0; i < FullCountPathSize7; i++)
        OutputFile<<FullPath7[i].first<<" "<<FullPath7[i].second<<endl;

    OutputFile.close();
}
void Output8(){//N^2
    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize8 = FullPath8.size();
    OutputFile<<FullCountPathSize8<<endl;
    for(int i = 0; i < FullCountPathSize8; i++)
        OutputFile<<FullPath8[i].first<<" "<<FullPath8[i].second<<endl;

    OutputFile.close();
}
void Output9(){//N^2
    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize9 = FullPath9.size();
    OutputFile<<FullCountPathSize9<<endl;
    for(int i = 0; i < FullCountPathSize9; i++)
        OutputFile<<FullPath9[i].first<<" "<<FullPath9[i].second<<endl;

    OutputFile.close();
}
void Output10(){//N^2
    ofstream OutputFile;
    OutputFile.open("sorting.out",ios::out);
    FullCountPathSize10 = FullPath10.size();
    OutputFile<<FullCountPathSize10<<endl;
    for(int i = 0; i < FullCountPathSize10; i++)
        OutputFile<<FullPath10[i].first<<" "<<FullPath10[i].second<<endl;

    OutputFile.close();
}
bool CheckPerm(){
    for(int i = 1; i <= N; i++){
        if(Perm[i] != i)return false;
    }
    return true;
}
bool CheckPerm2(){
    for(int i = 1; i <= N; i++){
        if(Perm2[i] != i)return false;
    }
    return true;
}
bool CheckPerm3(){
    for(int i = 1; i <= N; i++){
        if(Perm3[i] != i)return false;
    }
    return true;
}
bool CheckPerm4(){
    for(int i = 1; i <= N; i++){
        if(Perm4[i] != i)return false;
    }
    return true;
}
bool CheckPerm5(){
    for(int i = 1; i <= N; i++){
        if(Perm5[i] != i)return false;
    }
    return true;
}
bool CheckPerm6(){
    for(int i = 1; i <= N; i++){
        if(Perm6[i] != i)return false;
    }
    return true;
}
bool CheckPerm7(){
    for(int i = 1; i <= N; i++){
        if(Perm7[i] != i)return false;
    }
    return true;
}
bool CheckPerm8(){
    for(int i = 1; i <= N; i++){
        if(Perm8[i] != i)return false;
    }
    return true;
}
bool CheckPerm9(){
    for(int i = 1; i <= N; i++){
        if(Perm9[i] != i)return false;
    }
    return true;
}
bool CheckPerm10(){
    for(int i = 1; i <= N; i++){
        if(Perm10[i] != i)return false;
    }
    return true;
}
void MakeMatrix(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            FullPrice[i][j] = PricePositions[i][j] + PriceValue[Perm4[i]][Perm4[j]];
        }
    }
}

void SortingType_2$3_0(){
    pair<int,int> Dist[MAXN];
    for(int i = 1; i <= N; i++)
        Dist[Perm[i]] = make_pair(abs(Perm[i] - i),i);
    sort(Dist+1,Dist+N+1);

    for(int i = 1; i <= N; i++){
        int ii = Dist[i].second;
            if(Perm[ii] != ii){
                for(int j = 1; j <= N; j++){
                    if(j == Perm[ii]){

                        FullPath.push_back(make_pair(ii,j));
                        PRICE1 += PricePositions[ii][j] + PriceValue[Perm[ii]][Perm[j]];
                        swap(Perm[ii],Perm[j]);

                        return;
                    }
                }
            }
        }
}

void SortingType_2$3_2$3(){
    pair<int,int> Dist[MAXN];
    for(int i = 1; i <= N; i++)
        Dist[Perm3[i]] = make_pair(FullPrice[i][Perm3[i]],i);
    sort(Dist+1,Dist+N+1);
    for(int i = 1; i <= N; i++){
        int ii = Dist[i].second;
            if(Perm3[ii] != ii){
                for(int j = 1; j <= N; j++){
                    if(j == Perm3[ii]){

                        FullPath3.push_back(make_pair(ii,j));
                        AllPrice += FullPrice[ii][j];
                        PRICE3 += PricePositions[ii][j] + PriceValue[Perm3[ii]][Perm3[j]];
                        swap(Perm3[ii],Perm3[j]);

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
        if(FullPrice[s][i] == 0 || Perm4[i] == i){
            d[i] = MAX_VALUE;
            pred[i] = NO_PARENT;
        }

            else {
                d[i] = FullPrice[s][i];
                pred[i] = s;
            }
    }



    for(i = 1; i <= N; i++)if(i != Perm4[i])T[i] = 1;
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
    FullPath4.push_back(make_pair(First,Last));
    PRICE4 += PricePositions[First][Last] + PriceValue[Perm4[First]][Perm4[Last]];
    swap(Perm4[First],Perm4[Last]);


}

void SortingAll(){
    for(int i = 1; i <= N; i++){
        if(i == Perm4[i])continue;
        dijkstra(i);
        int Pos,j;
        for(j = 1; j <= N; j++)
            if(Perm4[j] == i){Pos = j;break;}
        MakePath(i,j);
        FullCountPathSize4 += CountPathSize;
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
        PRICE6 += PricePositions[First][Second] + PriceValue[Perm6[First]][Perm6[Second]];
        swap(Perm6[First],Perm6[Second]);
        FullCountPathSize6++;
        FullPath6.push_back(make_pair(First,Second));
        CurIndex = Next;
        if(CurIndex == LoopSize - 1){Next = 0;}
        else {Next = CurIndex + 1;}
    }while(Next != StartIndex);
}

void SortingWithLoops(){
    for(int i = 1; i <= N; i++){
        if(i == Perm6[i])Used[i] = true;
        vector <int> CurLoop;
        int CurIndex = i;
        if(Used[i] == false){
            do{
                Used[CurIndex] = true;
                CurLoop.push_back(CurIndex);
                CurIndex = Perm6[CurIndex];
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
    if(CheckPerm6() == false)SortingWithLoops();
}

void Sorting(){
MakeMatrix();
        while(CheckPerm() == false){
            SortingType_2$3_0();
        }


    while(CheckPerm3() == false){

        SortingType_2$3_2$3();
    }

    while(CheckPerm4() == false){
            SortingAll();
        }
    while(CheckPerm6() == false){
        SortingWithLoops();
    }
        start:

    if(CheckPerm5() == true)goto end;
        for(int i = 1; i <= N; i++){
            if(Perm5[i] != i){
                for(int j = 1; j <= N; j++){
                    if(j == Perm5[i]){

                        FullPath5.push_back(make_pair(i,j));
                        swap(Perm5[i],Perm5[j]);
                        PRICE5 += PricePositions[i][j] + PriceValue[Perm5[i]][Perm5[j]];
                        goto start;

                    }
                }
            }
        }
    end:

    if(CheckPerm() == false || CheckPerm3 == false || CheckPerm4 == false || CheckPerm5 == false || CheckPerm6 == false)
        Sorting();
}

void SortingDump(){
    int MinDumpPrice = MAX_VALUE,MinDumpIndex;
    for(int i = 1; i <= N; i++){
        if(i == Perm2[i])continue;
        int price = PricePositions[i][Perm2[i]] + PriceValue[Perm2[i]][Perm2[Perm2[i]]];
        if(price < MinDumpPrice){MinDumpPrice = price;MinDumpIndex = i;}
    }

    if(MinDumpPrice < MAX_VALUE){
        FullCountPathSize2++;
        FullPath2.push_back(make_pair(MinDumpIndex,Perm2[MinDumpIndex]));
        PRICE2 += PricePositions[MinDumpIndex][Perm2[MinDumpIndex]] + PriceValue[Perm2[MinDumpIndex]][Perm2[Perm2[MinDumpIndex]]];
        swap(Perm2[MinDumpIndex],Perm2[Perm2[MinDumpIndex]]);
        //PRICE2 += PricePositions[MinDumpIndex][Perm2[MinDumpIndex]] + PriceValue[Perm2[MinDumpIndex]][Perm2[Perm2[MinDumpIndex]]];
        //cout<<MinDumpIndex<<endl;
        //cout<<Perm2[MinDumpIndex]<<" "<<Perm2[Perm2[MinDumpIndex]]<<" "<<PricePositions[MinDumpIndex][Perm2[MinDumpIndex]] + PriceValue[Perm2[MinDumpIndex]][Perm2[Perm2[MinDumpIndex]]]<<endl;
        //cout<<Perm[MinDumpPrice]<<" "<<Perm[Perm[MinDumpPrice]]<<endl;
    }
}

void Sorting2(){
    if(true){
        while(CheckPerm2() == false){
            SortingDump();
        }
        return;
    }
}

/// TYPE(4-0) pos=4/0 val=0/4 (n*n)
void SortByType4_0(){

    for(int i = N; i >= 1; i--){
        if(i == Perm7[i])continue;
        for(int j = 1; j <= N; j++){
            if(Perm7[j] == i){
                if(i == Perm7[i])break;
                PRICE7 += PricePositions[i][j] + PriceValue[Perm7[i]][Perm7[j]];
                FullPath7.push_back(make_pair(j,i));
                AllPrice +=PricePositions[i][j] + PriceValue[Perm7[i]][Perm7[j]];
                swap(Perm7[j],Perm7[i]);
                break;
            }
        }
    }
}
/// END TYPE(4-0) pos=4/0 val=0/4

/// TYPE(23-0) pos=2/3 val=0 (n*n)
void SortByType23_0(){

    int Min = MAX_VALUE,MinIndex = 1;
    for(int i = 1; i <= N; i++){
        if(i == Perm8[i])continue;
        int ValA,PosA,ValB,PosB,ValC,PosC;
        PosA = i;
        ValA = Perm8[PosA];
        PosB = ValA;
        ValB = Perm8[PosB];
        PosC = ValB;
        ValC = Perm8[PosC];
        //cout<<ValA<<" "<<ValB<<" "<<ValC<<endl;

        int MidPriceA,MidPriceB,CurMidPriceB,FullMidPrice;
        MidPriceA = abs(PosA - PosB);
        MidPriceB = abs(PosB - PosC);
        CurMidPriceB = abs(PosA - PosC);
        FullMidPrice = MidPriceA + (CurMidPriceB - MidPriceB);

        if(FullMidPrice < Min){Min = FullMidPrice; MinIndex = PosA;}
    }

    if(Min != MAX_VALUE){
        FullPath8.push_back(make_pair(MinIndex,Perm8[MinIndex]));
        AllPrice += PricePositions[MinIndex][Perm8[MinIndex]] + PriceValue[Perm8[MinIndex]][Perm8[Perm8[MinIndex]]];
        //cout<<MinIndex<<" "<<Perm[MinIndex]<<endl;
        PRICE8 += PricePositions[MinIndex][Perm8[MinIndex]] + PriceValue[Perm8[MinIndex]][Perm8[Perm8[MinIndex]]];
        swap(Perm8[MinIndex],Perm8[Perm8[MinIndex]]);


    }


}
/// END TYPE(23-0) pos=2/3 val=0

/// TYPE(0-2) pos=0 val=2/3 (n*n)
void SortByType0_23(){
    int Min = MAX_VALUE,MinIndex = 1;
    for(int i = 1; i <= N; i++){
        if(i == Perm9[i])continue;
        int ValA,PosA,ValB,PosB,ValC,PosC;
        PosA = i;
        ValA = Perm9[PosA];
        PosB = ValA;
        ValB = Perm9[PosB];
        PosC = ValB;
        ValC = Perm9[PosC];
        //cout<<ValA<<" "<<ValB<<" "<<ValC<<endl;

        int MidPriceA,MidPriceB,CurMidPriceB,FullMidPrice;
        MidPriceA = abs(ValA - ValB);
        MidPriceB = abs(ValB - ValC);
        CurMidPriceB = abs(ValA - ValC);
        FullMidPrice = MidPriceA + (CurMidPriceB - MidPriceB);

        if(FullMidPrice < Min){Min = FullMidPrice; MinIndex = PosA;}
    }

    if(Min != MAX_VALUE){
        FullPath9.push_back(make_pair(MinIndex,Perm9[MinIndex]));
        AllPrice += PricePositions[MinIndex][Perm9[MinIndex]] + PriceValue[Perm9[MinIndex]][Perm9[Perm9[MinIndex]]];
        //cout<<MinIndex<<" "<<Perm[MinIndex]<<endl;
        PRICE9 += PricePositions[MinIndex][Perm9[MinIndex]] + PriceValue[Perm9[MinIndex]][Perm9[Perm9[MinIndex]]];
        swap(Perm9[MinIndex],Perm9[Perm9[MinIndex]]);


    }
}
/// END TYPE(0-2) pos=0 val=2/3

/// TYPE(23-23) pos=2/3 val=2/3 (n*n)
void SortByType23_23(){
    int Min = MAX_VALUE,MinIndex = 1;
    for(int i = 1; i <= N; i++){
        if(i == Perm10[i])continue;
        int ValA,PosA,ValB,PosB,ValC,PosC;
        PosA = i;
        ValA = Perm10[PosA];
        PosB = ValA;
        ValB = Perm10[PosB];
        PosC = ValB;
        ValC = Perm10[PosC];
        //cout<<ValA<<" "<<ValB<<" "<<ValC<<endl;

        int MidPriceA,MidPriceB,CurMidPriceB,FullMidPrice;
        MidPriceA = abs(PosA - PosB) + abs(ValA - ValB);
        MidPriceB = abs(PosB - PosC) + abs(ValB - ValC);
        CurMidPriceB = abs(PosA - PosC) + abs(ValA - ValC);
        FullMidPrice = MidPriceA + (CurMidPriceB - MidPriceB);

        if(FullMidPrice < Min){Min = FullMidPrice; MinIndex = PosA;}
    }

    if(Min != MAX_VALUE){
        FullPath10.push_back(make_pair(MinIndex,Perm10[MinIndex]));
        AllPrice += PricePositions[MinIndex][Perm10[MinIndex]] + PriceValue[Perm10[MinIndex]][Perm10[Perm10[MinIndex]]];
        //cout<<MinIndex<<" "<<Perm[MinIndex]<<endl;
        PRICE10 += PricePositions[MinIndex][Perm10[MinIndex]] + PriceValue[Perm10[MinIndex]][Perm10[Perm10[MinIndex]]];
        swap(Perm10[MinIndex],Perm10[Perm10[MinIndex]]);


    }
}
/// END TYPE(23-23) pos=2/3 val=2/3



void Sorting3(){
    while(CheckPerm7() == false){
            SortByType4_0();
        }
    while(CheckPerm8() == false){
            SortByType23_0();
        }
    while(CheckPerm9() == false){
            SortByType0_23();
        }
    while(CheckPerm10() == false){
            SortByType23_23();
        }
}
int main() {
    Input();
    Sorting();
    Sorting2();
    Sorting3();
    if(PRICE1 == 0)PRICE1 = MAX_VALUE;
    if(PRICE2 == 0)PRICE2 = MAX_VALUE;
    if(PRICE3 == 0)PRICE3 = MAX_VALUE;
    if(PRICE4 == 0)PRICE4 = MAX_VALUE;
    if(PRICE5 == 0)PRICE5 = MAX_VALUE;
    if(PRICE6 == 0)PRICE6 = MAX_VALUE;
    if(PRICE7 == 0)PRICE7 = MAX_VALUE;
    if(PRICE8 == 0)PRICE8 = MAX_VALUE;
    if(PRICE9 == 0)PRICE9 = MAX_VALUE;
    if(PRICE10 == 0)PRICE10 = MAX_VALUE;

    cout<<PRICE1<<" "<<PRICE2<<" "<<PRICE3<<" "<<PRICE4<<" "<<PRICE5<<" "<<PRICE6<<" "<<PRICE7<<" "<<PRICE8<<" "<<PRICE9<<" "<<PRICE10<<endl;
    int MIN = min(PRICE1,PRICE2),MIN2 = min(PRICE3,PRICE4);
    MIN = min(MIN,MIN2);
    MIN = min(MIN,PRICE5);
    MIN = min(MIN,PRICE6);
    MIN = min(MIN,PRICE7);
    MIN = min(MIN,PRICE8);
    MIN = min(MIN,PRICE9);
    MIN = min(MIN,PRICE10);
    //cout<<MIN<<endl;

    if(MIN == PRICE6){Output6();return 0;}
    if(MIN == PRICE2){Output2();return 0;}


    if((TypePriceVal == 0 && TypePricePos == 2) ||(TypePriceVal == 0 && TypePricePos == 3)){
        if(MIN == PRICE8){Output8();return 0;}
        if(MIN == PRICE1){Output();return 0;}
    }



    if((TypePriceVal == 2 || TypePriceVal == 3) && (TypePricePos == 2 || TypePricePos == 3)){
        if(MIN == PRICE10){Output10();return 0;}
        if(MIN == PRICE4){Output4();return 0;}
    }

    if(TypePricePos == 4 && TypePriceVal == 0){
        if(MIN == PRICE7){Output7();return 0;}
    }

    if((TypePriceVal == 2 || TypePriceVal == 3) && (TypePricePos == 0)){
        if(MIN == PRICE9){Output9();return 0;}
    }

    if(MIN == PRICE3)Output3();
    else if(MIN == PRICE7)Output7();
    else if(MIN == PRICE8)Output8();
    else if(MIN == PRICE9)Output9();
    else if(MIN == PRICE10)Output10();
    else if(MIN == PRICE1)Output();
    else if(MIN == PRICE4)Output4();
    else if(MIN == PRICE5)Output5();

    //cout<<AllPrice<<endl;
    return 0;
}



