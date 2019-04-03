#include<iostream>
#include<fstream>

#define MAX_NODES 128
#define MAX_VALUE 2000000000

using namespace std;
int F,K,N,M,B;
char T[102][102];
string Way[101];
bool Problem[7];
int V, E, a[MAX_NODES][MAX_NODES], parent[MAX_NODES], dist[MAX_NODES], from, to, x, y, z,CurNode;
bool visited[MAX_NODES];

void Input();
void Dijkstra(int node);
void printWay(int node);
void Promlem_1();
void Promlem_2();
void Promlem_3();
void Promlem_4();
void Promlem_5();
void Promlem_6();
int main()
{
    Input();
    return 0;
}
void Input()
{
    for(int i=0;i<=6;i++)Problem[i]=true;
    for(int i=0;i<101;i++)visited[i]=false;
    ifstream inCat;
    inCat.open("catsdogs.in");
    inCat>>F>>K;
    ///1 Problem
    if(F!=1)Problem[1]=false;
    if(F>50){Problem[2]=false;Problem[5];}
    if(K!=1)Problem[3]=false;
    //cout<<F<<" "<<K<<endl;
    for(int k=1;k<=F;k++)
    {
        inCat>>N>>M>>B;
        if(N>50 || M>50)Problem[5]=false;
        //cout<<N<<" "<<M<<" "<<B<<endl;
        int brCat=0;
        for(int i=1;i<=N;i++)
        {
            
            for(int j=1;j<=M;j++)
            {
                inCat>>T[i][j];
                if(T[i][j]>='1' && T[i][j]<='9')
                {
                    brCat++;
                    if(T[i][j]!='1')Problem[4]=false;
                }
                
            
               // cout<<T[i][j]<<" ";
            }
           // cout<<endl;
        }
        if(brCat>9)Problem[2]=false;
        // make the graph
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(T[i][j]=='.')
                {
                    if(T[i][j-1]=='.' || (T[i][j-1]>='1' && T[i][j-1]<='9'))
                    {
                        int x1=i,y1=j-1,x2=i,y2=j;
                        a[(x1-1)*M+y1][(x2-1)*M+y2]=1;
                        }
                    if(T[i][j+1]=='.' || (T[i][j+1]>='1' && T[i][j+1]<='9'))
                    {
                        int x1=i,y1=j+1,x2=i,y2=j;
                       a[(x1-1)*M+y1][(x2-1)*M+y2]=1;
                        }
                    if(T[i-1][j]=='.' || (T[i-1][j]>='1' && T[i-1][j]<='9'))
                    {int x1=i-1,y1=j,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=1;}
                    if(T[i+1][j]=='.' || (T[i+1][j]>='1' && T[i+1][j]<='9'))
                    {int x1=i+1,y1=j,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=1;}
                }
                else if(T[i][j]>='1' && T[i][j]<='9')
                {
                    int o=T[i][j]-'0';
                    
                    if(T[i][j-1]=='.' || (T[i][j-1]>='1' && T[i][j-1]<='9'))
                    {int x1=i,y1=j-1,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=o+1;}
                    if(T[i][j+1]=='.' || (T[i][j+1]>='1' && T[i][j+1]<='9'))
                    {int x1=i,y1=j+1,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=o+1;}
                    if(T[i-1][j]=='.' || (T[i-1][j]>='1' && T[i-1][j]<='9'))
                    {int x1=i-1,y1=j,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=o+1;}
                    if(T[i+1][j]=='.' || (T[i+1][j]>='1' && T[i+1][j]<='9'))
                    {int x1=i+1,y1=j,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=o+1;}                    
                }
        }
    }
        for(int i=1;i<=N*M;i++){
        for(int j=1;j<=N*M;j++)
        cout<<a[i][j]<<" ";
        cout<<endl;}
        for(int j=1;j<=6;j++)
        cout<<Problem[j]<<" ";
        cout<<endl;
        
        if(Problem[3])Promlem_3();
        
    }
    
}

void Promlem_3(int k=1)
{
    for(int i=1;i<=M;i++)
    {
        
    }
}