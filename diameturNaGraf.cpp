#include<iostream>
#include<vector>
#include<string>
using namespace std;

class PointGraph
{
    public :
    int T[100];
    vector<int> neighs;
    
    
    int brN;
    
    void MakeNull()
    {
        brN=0;
        for(int i=0;i<100;i++)
        {
            T[100]=0;
        }
    }
};
PointGraph G[100];
bool visited[100];
string way="",maxway;
int waysize=0,maxsize=0;
int An;
void Diam(int k)
{
   int Ann;
    visited[k]=true;
    cout<<"k / "<<k<<endl;
    char help=k+48;
    way+=help;
    waysize+=G[An].T[k];
    for(int i=0;i<G[k].brN;i++)
    {
        if(!visited[G[k].neighs[i]]){cout<<G[k].neighs[i]<<endl;An=G[k].neighs[i];goto rek;}
    }
    ///
    if(waysize>maxsize)
    {
        maxway=way;
        maxsize=waysize;
    }
    way.erase(way.size()-2,1);
    waysize-=G[An].T[k];
    visited[k]=false;
    cout<<way<<endl;
    return;
    
    
    rek :
    An=k;
    Diam(An);
    return;
    
}
int main()
{
    for(int i=0;i<100;i++)
    G[i].MakeNull();
    
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int a,b,x;
        cin>>a>>b>>x;
        
        if(G[a].T[b]==0){G[a].neighs.push_back(b);G[a].brN++;}
        G[a].T[b]=x;
        G[b].T[a]=x;
    }
     for(int i=1;i<=n;i++)
     Diam(i);
    for(int i=1;i<=m;i++)
    {
        cout<<i<<endl;
        for(int j=0;j<G[i].brN;i++)
        {
            cout<<i<<":"<<G[i].neighs[j]<<" "<<G[i].T[G[i].neighs[j]]<<endl;
        }
    }
    cout<<maxsize<<endl;
    cout<<maxway<<endl;
}