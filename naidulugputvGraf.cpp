#include<iostream>
#include<stack>
#include<vector>
using namespace std;
int G[100][100],maxway=0,brway=0;
int n,m;
stack <int> way,curway;
vector <int> s[100];
bool notvisited[100];
void longWay(int from,int to)
{
    notvisited[from]=1;
    for(int i=0;i<s[from].size();i++)
    {
        if(s[from][i]==to)
        {
            brway+=G[from][to];
            curway.push(to);
            if(maxway<brway)
            {   
                way=curway;
                maxway=brway;
            }
        }
        else if(notvisited[s[from][i]])
        {
            brway+=G[from][s[from][i]];
            curway.push(s[from][i]);
            longWay(s[from][i],to);
            notvisited[s[from][i]]=0;
            brway-=G[from][s[from][i]];
            curway.pop();
        }
    }
    return;
}
int main()
{
    
    cin>>n>>m;
    int aa,bb;
    cin>>aa>>bb;
    
    for(int i=1;i<=m;i++)
    {
        int a,b,x;
        cin>>a>>b>>x;
        G[a][b]=x;
        s[a].push_back(b);
        s[b].push_back(a);
    }
    longWay(aa,bb);
    cout<<maxway<<endl;
    while(!way.empty())
    {
        cout<<way.top()<<" ";
        way.pop();
    }
    return 0;
    
}