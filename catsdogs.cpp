#include<iostream>
#include<fstream>

#define MAX_NODES 128
#define MAX_VALUE 2000000000

using namespace std;
class AllWays
{
    public:
    string Moves;
    int x,y;
    int Front;
};
int F,K,N,M,B;
char T[102][102];
AllWays w[101];

void Input();
void Output();
int main()
{
    Input();
    Output();
    return 0;
}
int brDogs=0,brCats=0;
int maxCat=0;
void Input()
{

    ifstream inCat;
    inCat.open("catsdogs.in");
    inCat>>F>>K;
    ///1 Problem

    //cout<<F<<" "<<K<<endl;
    for(int k=1;k<=F;k++)
    {
        inCat>>N>>M>>B;

        //cout<<N<<" "<<M<<" "<<B<<endl;
        int brCat=0;
        for(int i=1;i<=N;i++)
        {

            for(int j=1;j<=M;j++)
            {
                inCat>>T[i][j];
                if(T[i][j]>='1' && T[i][j]<='9' )
                {
                    w[brDogs].x=i;
                    w[brDogs].y=j;
                    w[brDogs].Front=k;
                    brDogs++;
                    
                    brCats++;
                }


               // cout<<T[i][j]<<" ";
            }
           // cout<<endl;
        }
        
    }
    inCat.close();
    return;
}

void Output()
{
    ofstream outCat;
    outCat.open("catsdogs.out");
    int brOutDogs=0;
    int l=min(K,brDogs);
    for(int i=0;i<l;i++)
    {
        
        if(w[i].Front<1 || w[i].Front>F)break;
        outCat<<w[i].Front<<endl;
        outCat<<w[i].x<<" "<<w[i].y<<endl;
        outCat<<"STAY"<<endl;
        brOutDogs++;

    }
    if(brOutDogs<K)
    {
        for(int i=1;i<=N,brOutDogs<K;i++)
        for(int j=1;j<=M,brOutDogs<K;j++){
        if(T[i][j]!='#')
        outCat<<F<<endl;
        outCat<<i<<" "<<j<<endl;
        outCat<<"STAY"<<endl;
        brOutDogs++;
        }
    }
    outCat.close();
    return;
}
