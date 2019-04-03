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
 int FullPrice[MAXN][MAXN],Perm[MAXN];
 //BestPrice[MAXN][MAXN],BestWayPred[MAXN][MAXN];
 short TypePricePos,TypePriceVal;

pair < int ,  int> MyPath[MAXN];
int CountPathSize = 0;

int AllPrice1[MAXN];
vector<pair < int ,  int> > FullPath1[MAXN];
vector<pair < int ,  int> > FullPath;
 int FullCountPathSize = 0;

class Solution {
    public :
    vector<pair < int ,  int> > FullPath;
    int price;
    int Perm[MAXN];
}CurSol,MinSol;

/// Basic Functions {(N*N) + FullPathSize(1 000 000) + N}
void Input();
void Output();
void PrintPrice();
bool CheckPerm(Solution MySol);
bool CheckPerm2();
void CombineFunctions();
/// End Basic Functions

/// TYPE(4-0) pos=4/0 val=0/4 (n*n)
Solution SortByType4_0();
/// END TYPE(4-0) pos=4/0 val=0/4

/// TYPE(23-0) pos=2/3 val=0 (n*n)
Solution SortByType23_0();
/// END TYPE(23-0) pos=2/3 val=0

/// TYPE(0-23) pos=0 val=2/3 (n*n)
Solution SortByType0_23();
/// END TYPE(0-2/3) pos=0 val=2/3

/// TYPE(23-23) pos=2/3 val=2/3 (n*n)
Solution SortByType23_23();
/// END TYPE(23-23) pos=2/3 val=2/3

/// FUNCTIONS FROM SORTINGCOMBINE3AND6
Solution SortingType_2$3_0();
Solution SortingType_2$3_2$3();
void SortingLoop(int LoopIndex, int StartIndex);
Solution SortingWithLoops();
void dijkstra(unsigned s);
void MakePath(unsigned First, unsigned Last);
Solution SortingAll();
Solution SortingDump();
void SortingBasic();
/// END OF FUNCTIONS OF SORTINGCOMBINE3AND6

int main(){
    Input();
    /*if((TypePricePos == 4 && TypePriceVal == 0) || (TypePricePos == 0 && TypePriceVal == 4)){
        SortByType4_0();
    }

    else if(TypePricePos == 2 && TypePriceVal == 0){
        SortByType23_0();
    }

    else if(TypePricePos == 3 && TypePriceVal == 0){
        SortByType23_0();
    }

    else if(TypePricePos == 0 && TypePriceVal == 2){
        SortByType0_23();
    }

    else if(TypePricePos == 0 && TypePriceVal == 3){
        SortByType0_23();
    }

    else if((TypePricePos == 2 || TypePricePos == 3) && (TypePriceVal == 2 || TypePriceVal == 3)){
        SortByType23_23();
    }*/

    StartMain:
    CombineFunctions();
    FullCountPathSize = FullPath.size();
    for(int i = 0; i < FullCountPathSize; i++){
        swap(Perm[FullPath[i].first],Perm[FullPath[i].second]);
    }

    Output();

    //PrintPrice();
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

void PrintPrice(){
    ofstream OutputFile;
    OutputFile.open("AllPrice/sorting.out",ios::out);
    OutputFile<<AllPrice<<endl;

    OutputFile.close();
}

bool CheckPerm(Solution MySol){
    for(int i = 1; i <= N; i++){
        if(MySol.Perm[i] != i)return false;
    }
    return true;
}

bool CheckPerm2(){
    for(int i = 1; i <= N; i++){
        if(Perm[i] != i)return false;
    }
    return true;
}

void CombineFunctions(){
    int MinPrice = MAX_VALUE,MinI;
    CurSol = SortByType4_0();
    if(AllPrice1[0] < MinPrice){MinPrice = AllPrice1[0];MinSol = CurSol;MinI = 0;}//cout<<40<<endl;}

    CurSol = SortByType23_0();
    if(AllPrice1[1] < MinPrice){MinPrice = AllPrice1[1];MinSol = CurSol;MinI = 1;}//cout<<23<<endl;}

    CurSol = SortByType0_23();
    if(AllPrice1[2] < MinPrice){MinPrice = AllPrice1[2];MinSol = CurSol;MinI = 2;}//cout<<023<<endl;}

    CurSol = SortByType23_23();
    if(AllPrice1[3] < MinPrice){MinPrice = AllPrice1[3];MinSol = CurSol;MinI = 3;}//cout<<2323<<endl;}

    CurSol = SortingType_2$3_0();
    if(AllPrice1[4] < MinPrice){MinPrice = AllPrice1[4];MinSol = CurSol;MinI = 4;}//cout<<"2$3-0"<<endl;}

    CurSol = SortingType_2$3_2$3();
    if(AllPrice1[5] < MinPrice){MinPrice = AllPrice1[5];MinSol = CurSol;MinI = 5;}//cout<<"2$3-2$3"<<endl;}

    CurSol = SortingWithLoops();
    if(AllPrice1[6] < MinPrice){MinPrice = AllPrice1[6];MinSol = CurSol;MinI = 6;}//cout<<"Loops"<<endl;}

    CurSol = SortingAll();
    if(AllPrice1[7] < MinPrice){MinPrice = AllPrice1[7];MinSol = CurSol;MinI = 7;}//cout<<"All"<<endl;}

    CurSol = SortingDump();
    if(AllPrice1[8] < MinPrice){MinPrice = AllPrice1[8];MinSol = CurSol;MinI = 8;}

    SortingBasic();
    if(AllPrice1[9] < MinPrice){MinPrice = AllPrice1[9];MinSol = CurSol;MinI = 9;}

    AllPrice = MinSol.price;
    for(int i=0;i<FullPath1[MinI].size();i++)
        FullPath.push_back(FullPath1[MinI][i]);
}
/// End Basic Functions

/// TYPE(4-0) pos=4/0 val=0/4 (n*n)
Solution SortByType4_0(){
    Solution MySol;
    MySol.price = 0;
    for(int i = 1; i <= N; i++)MySol.Perm[i] = Perm[i];

    Start:
    for(int i = N; i >= 1; i--){
        if(i == MySol.Perm[i])continue;
        for(int j = 1; j <= N; j++){
            if(MySol.Perm[j] == i){
                if(i == MySol.Perm[i])break;
                MySol.price += PricePositions[i][j] + PriceValue[MySol.Perm[i]][MySol.Perm[j]];
                MySol.FullPath.push_back(make_pair(j,i));
                FullPath1[0].push_back(make_pair(j,i));
                AllPrice1[0] +=PricePositions[i][j] + PriceValue[MySol.Perm[i]][MySol.Perm[j]];
                swap(MySol.Perm[j],MySol.Perm[i]);
                break;
            }
        }
    }
    if(CheckPerm(MySol) == false)goto Start;
    return MySol;
}
/// END TYPE(4-0) pos=4/0 val=0/4

/// TYPE(23-0) pos=2/3 val=0 (n*n)
Solution SortByType23_0(){
    Solution MySol;
    MySol.price = 0;
    for(int i = 1; i <= N; i++)MySol.Perm[i] = Perm[i];

    Start:
    int Min = MAX_VALUE,MinIndex = 1;
    for(int i = 1; i <= N; i++){
        if(i == MySol.Perm[i])continue;
        int ValA,PosA,ValB,PosB,ValC,PosC;
        PosA = i;
        ValA = MySol.Perm[PosA];
        PosB = ValA;
        ValB = MySol.Perm[PosB];
        PosC = ValB;
        ValC = MySol.Perm[PosC];
        //cout<<ValA<<" "<<ValB<<" "<<ValC<<endl;

        int MidPriceA,MidPriceB,CurMidPriceB,FullMidPrice;
        MidPriceA = abs(PosA - PosB);
        MidPriceB = abs(PosB - PosC);
        CurMidPriceB = abs(PosA - PosC);
        FullMidPrice = MidPriceA + (CurMidPriceB - MidPriceB);

        if(FullMidPrice < Min){Min = FullMidPrice; MinIndex = PosA;}
    }

    if(Min != MAX_VALUE){
        MySol.FullPath.push_back(make_pair(MinIndex,MySol.Perm[MinIndex]));
        FullPath1[1].push_back(make_pair(MinIndex,MySol.Perm[MinIndex]));
        AllPrice1[1] += PricePositions[MinIndex][MySol.Perm[MinIndex]] + PriceValue[MySol.Perm[MinIndex]][MySol.Perm[MySol.Perm[MinIndex]]];
        //cout<<MinIndex<<" "<<Perm[MinIndex]<<endl;
        MySol.price += PricePositions[MinIndex][MySol.Perm[MinIndex]] + PriceValue[MySol.Perm[MinIndex]][MySol.Perm[MySol.Perm[MinIndex]]];
        swap(MySol.Perm[MinIndex],MySol.Perm[MySol.Perm[MinIndex]]);


    }

    if(CheckPerm(MySol) == false)goto Start;
    return MySol;
}
/// END TYPE(23-0) pos=2/3 val=0

/// TYPE(0-2) pos=0 val=2/3 (n*n)
Solution SortByType0_23(){
    Solution MySol;
    MySol.price = 0;
    for(int i = 1; i <= N; i++)MySol.Perm[i] = Perm[i];

    Start:
    int Min = MAX_VALUE,MinIndex = 1;
    for(int i = 1; i <= N; i++){
        if(i == MySol.Perm[i])continue;
        int ValA,PosA,ValB,PosB,ValC,PosC;
        PosA = i;
        ValA = MySol.Perm[PosA];
        PosB = ValA;
        ValB = MySol.Perm[PosB];
        PosC = ValB;
        ValC = MySol.Perm[PosC];
        //cout<<ValA<<" "<<ValB<<" "<<ValC<<endl;

        int MidPriceA,MidPriceB,CurMidPriceB,FullMidPrice;
        MidPriceA = abs(ValA - ValB);
        MidPriceB = abs(ValB - ValC);
        CurMidPriceB = abs(ValA - ValC);
        FullMidPrice = MidPriceA + (CurMidPriceB - MidPriceB);

        if(FullMidPrice < Min){Min = FullMidPrice; MinIndex = PosA;}
    }

    if(Min != MAX_VALUE){
        MySol.FullPath.push_back(make_pair(MinIndex,MySol.Perm[MinIndex]));
        FullPath1[2].push_back(make_pair(MinIndex,MySol.Perm[MinIndex]));
        AllPrice1[2] += PricePositions[MinIndex][MySol.Perm[MinIndex]] + PriceValue[MySol.Perm[MinIndex]][MySol.Perm[MySol.Perm[MinIndex]]];
        //cout<<MinIndex<<" "<<Perm[MinIndex]<<endl;
        MySol.price += PricePositions[MinIndex][MySol.Perm[MinIndex]] + PriceValue[MySol.Perm[MinIndex]][MySol.Perm[MySol.Perm[MinIndex]]];
        swap(MySol.Perm[MinIndex],MySol.Perm[MySol.Perm[MinIndex]]);


    }

    if(CheckPerm(MySol) == false)goto Start;
    return MySol;
}
/// END TYPE(0-2) pos=0 val=2/3

/// TYPE(23-23) pos=2/3 val=2/3 (n*n)
Solution SortByType23_23(){
    Solution MySol;
    MySol.price = 0;
    for(int i = 1; i <= N; i++)MySol.Perm[i] = Perm[i];

    Start:
    int Min = MAX_VALUE,MinIndex = 1;
    for(int i = 1; i <= N; i++){
        if(i == MySol.Perm[i])continue;
        int ValA,PosA,ValB,PosB,ValC,PosC;
        PosA = i;
        ValA = MySol.Perm[PosA];
        PosB = ValA;
        ValB = MySol.Perm[PosB];
        PosC = ValB;
        ValC = MySol.Perm[PosC];
        //cout<<ValA<<" "<<ValB<<" "<<ValC<<endl;

        int MidPriceA,MidPriceB,CurMidPriceB,FullMidPrice;
        MidPriceA = abs(PosA - PosB) + abs(ValA - ValB);
        MidPriceB = abs(PosB - PosC) + abs(ValB - ValC);
        CurMidPriceB = abs(PosA - PosC) + abs(ValA - ValC);
        FullMidPrice = MidPriceA + (CurMidPriceB - MidPriceB);

        if(FullMidPrice < Min){Min = FullMidPrice; MinIndex = PosA;}
    }

    if(Min != MAX_VALUE){
        MySol.FullPath.push_back(make_pair(MinIndex,MySol.Perm[MinIndex]));
        FullPath1[3].push_back(make_pair(MinIndex,MySol.Perm[MinIndex]));
        AllPrice1[3] += PricePositions[MinIndex][MySol.Perm[MinIndex]] + PriceValue[MySol.Perm[MinIndex]][MySol.Perm[MySol.Perm[MinIndex]]];
        //cout<<MinIndex<<" "<<Perm[MinIndex]<<endl;
        MySol.price += PricePositions[MinIndex][MySol.Perm[MinIndex]] + PriceValue[MySol.Perm[MinIndex]][MySol.Perm[MySol.Perm[MinIndex]]];
        swap(MySol.Perm[MinIndex],MySol.Perm[MySol.Perm[MinIndex]]);


    }

    if(CheckPerm(MySol) == false)goto Start;
    return MySol;
}
/// END TYPE(23-23) pos=2/3 val=2/3

/// FUNCTIONS FROM SORTINGCOMBINE3AND6
Solution SortingType_2$3_0(){
    Solution MySol;
    MySol.price = 0;
    for(int i = 1; i <= N; i++)MySol.Perm[i] = Perm[i];

    Start:
    pair<int,int> Dist[MAXN];
    for(int i = 1; i <= N; i++)
        Dist[MySol.Perm[i]] = make_pair(abs(MySol.Perm[i] - i),i);
    sort(Dist+1,Dist+N+1);

    for(int i = 1; i <= N; i++){
        int ii = Dist[i].second;
            if(MySol.Perm[ii] != ii){
                for(int j = 1; j <= N; j++){
                    if(j == MySol.Perm[ii]){

                        MySol.FullPath.push_back(make_pair(ii,j));
                        FullPath1[4].push_back(make_pair(ii,j));
                        AllPrice1[4] += PricePositions[ii][j] + PriceValue[MySol.Perm[ii]][MySol.Perm[j]];
                        MySol.price += PricePositions[ii][j] + PriceValue[MySol.Perm[ii]][MySol.Perm[j]];
                        swap(MySol.Perm[ii],MySol.Perm[j]);

                        if(CheckPerm(MySol) == false)goto Start;
                    }
                }
            }
        }

    if(CheckPerm(MySol) == false)goto Start;
    return MySol;
}

Solution SortingType_2$3_2$3(){
    Solution MySol;
    MySol.price = 0;
    for(int i = 1; i <= N; i++)MySol.Perm[i] = Perm[i];

    Start:
    pair<int,int> Dist[MAXN];
    for(int i = 1; i <= N; i++)
        Dist[MySol.Perm[i]] = make_pair(FullPrice[i][MySol.Perm[i]],i);
    sort(Dist+1,Dist+N+1);
    for(int i = 1; i <= N; i++){
        int ii = Dist[i].second;
            if(MySol.Perm[ii] != ii){
                for(int j = 1; j <= N; j++){
                    if(j == MySol.Perm[ii]){

                        MySol.FullPath.push_back(make_pair(ii,j));
                        FullPath1[5].push_back(make_pair(ii,j));
                        AllPrice1[5] += PricePositions[ii][j] + PriceValue[MySol.Perm[ii]][MySol.Perm[j]];
                        MySol.price += PricePositions[ii][j] + PriceValue[MySol.Perm[ii]][MySol.Perm[j]];
                        swap(MySol.Perm[ii],MySol.Perm[j]);

                        if(CheckPerm(MySol) == false)goto Start;
                    }
                }
            }
        }
        if(CheckPerm(MySol) == false)goto Start;
    return MySol;
}

vector < vector <int> > Loops;
bool Used[MAXN];
Solution MySol;

void SortingLoop(int LoopIndex, int StartIndex){
    int LoopSize = Loops[LoopIndex].size();
    int CurIndex = StartIndex,Next;
    if(CurIndex == LoopSize - 1)Next = 0;
        else Next = CurIndex + 1;

    do {

        int First = Loops[LoopIndex][StartIndex];
        int Second = Loops[LoopIndex][Next];
        MySol.price += PricePositions[First][Second] + PriceValue[MySol.Perm[First]][MySol.Perm[Second]];

        MySol.FullPath.push_back(make_pair(First,Second));
        FullPath1[6].push_back(make_pair(First,Second));
        AllPrice1[6] += PricePositions[First][Second] + PriceValue[MySol.Perm[First]][MySol.Perm[Second]];
        swap(MySol.Perm[First],MySol.Perm[Second]);
        CurIndex = Next;
        if(CurIndex == LoopSize - 1){Next = 0;}
        else {Next = CurIndex + 1;}
    }while(Next != StartIndex);
}

Solution SortingWithLoops(){
    MySol.price = 0;
    for(int i = 1; i <= N; i++)MySol.Perm[i] = Perm[i];

    Start:
    for(int i = 1; i <= N; i++){
        if(i == MySol.Perm[i])Used[i] = true;
        vector <int> CurLoop;
        int CurIndex = i;
        if(Used[i] == false){
            do{
                Used[CurIndex] = true;
                CurLoop.push_back(CurIndex);
                CurIndex = MySol.Perm[CurIndex];
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
    if(CheckPerm(MySol) == false)goto Start;
    return MySol;
}


char T[MAXN];
unsigned d[MAXN];
int pred[MAXN];
Solution MySol2;
void dijkstra(unsigned s)
{
    unsigned i;
    for(i = 1; i <= N; i++){
        if(FullPrice[s][i] == 0 || MySol2.Perm[i] == i){
            d[i] = MAX_VALUE;
            pred[i] = NO_PARENT;
        }

            else {
                d[i] = FullPrice[s][i];
                pred[i] = s;
            }
    }



    for(i = 1; i <= N; i++)if(i != MySol2.Perm[i])T[i] = 1;
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
    MySol2.FullPath.push_back(make_pair(First,Last));
    FullPath1[7].push_back(make_pair(First,Last));
    AllPrice1[7] +=PricePositions[First][Last] + PriceValue[MySol2.Perm[First]][MySol2.Perm[Last]];
    MySol2.price += PricePositions[First][Last] + PriceValue[MySol2.Perm[First]][MySol2.Perm[Last]];
    swap(MySol2.Perm[First],MySol2.Perm[Last]);


}

Solution SortingAll(){
    MySol2.price = 0;
    for(int i = 1; i <= N; i++)MySol2.Perm[i] = Perm[i];

    Start:
    for(int i = 1; i <= N; i++){
        if(i == MySol2.Perm[i])continue;
        dijkstra(i);
        int Pos,j;
        for(j = 1; j <= N; j++)
            if(MySol2.Perm[j] == i){Pos = j;break;}
        MakePath(i,j);
    }
    if(CheckPerm(MySol2) == false)goto Start;
    return MySol2;


}

Solution SortingDump(){
    Solution MySol3;
    MySol3.price = 0;
    for(int i = 1; i <= N; i++)MySol3.Perm[i] = Perm[i];

    Start:
    int MinDumpPrice = MAX_VALUE,MinDumpIndex;
    for(int i = 1; i <= N; i++){
        if(i == MySol3.Perm[i])continue;
        int price = PricePositions[i][MySol3.Perm[i]] + PriceValue[MySol3.Perm[i]][MySol3.Perm[MySol3.Perm[i]]];
        if(price < MinDumpPrice){MinDumpPrice = price;MinDumpIndex = i;}
    }

    if(MinDumpPrice < MAX_VALUE){
        MySol3.FullPath.push_back(make_pair(MinDumpIndex,MySol3.Perm[MinDumpIndex]));
        FullPath1[8].push_back(make_pair(MinDumpIndex,MySol3.Perm[MinDumpIndex]));
        AllPrice1[8] +=PricePositions[MinDumpIndex][MySol3.Perm[MinDumpIndex]] + PriceValue[MySol3.Perm[MinDumpIndex]][MySol3.Perm[MySol3.Perm[MinDumpIndex]]];
        MySol3.price+= PricePositions[MinDumpIndex][MySol3.Perm[MinDumpIndex]] + PriceValue[MySol3.Perm[MinDumpIndex]][MySol3.Perm[MySol3.Perm[MinDumpIndex]]];
        swap(MySol3.Perm[MinDumpIndex],MySol3.Perm[MySol3.Perm[MinDumpIndex]]);
        //PRICE2 += PricePositions[MinDumpIndex][Perm2[MinDumpIndex]] + PriceValue[Perm2[MinDumpIndex]][Perm2[Perm2[MinDumpIndex]]];
        //cout<<MinDumpIndex<<endl;
        //cout<<Perm2[MinDumpIndex]<<" "<<Perm2[Perm2[MinDumpIndex]]<<" "<<PricePositions[MinDumpIndex][Perm2[MinDumpIndex]] + PriceValue[Perm2[MinDumpIndex]][Perm2[Perm2[MinDumpIndex]]]<<endl;
        //cout<<Perm[MinDumpPrice]<<" "<<Perm[Perm[MinDumpPrice]]<<endl;
    }
    if(CheckPerm(MySol3) == false)goto Start;
    return MySol3;
}

void SortingBasic(){
    start:
    if(CheckPerm2())return;
    for(int i = 1; i <= N; i++){
            if(Perm[i] != i){
                for(int j = 1; j <= N; j++){
                    if(j == Perm[i]){

                        FullPath1[9].push_back(make_pair(i,j));
                        AllPrice1[9] += PricePositions[i][j] + PriceValue[Perm[i]][Perm[j]];
                        swap(Perm[i],Perm[j]);

                        goto start;

                    }
                }
            }
        }
}
/// END OF FUNCTIONS OF SORTINGCOMBINE3AND6
