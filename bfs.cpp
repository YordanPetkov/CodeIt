#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
int n,v,used[101];
queue<int>q;
vector<int>a[101];

void bfs()
{
  q.push(v);
  used[v]=1;
  while(!q.empty()) // докато опашката не е празна
  {
    int t=q.front();
    q.pop();
    printf("%d ",t);
    for(int i=0; i<a[t].size(); i++)
    {
       if(used[a[t][i]]==0) /* ако не е обходен */
       {
          q.push(a[t][i]);
          used[a[t][i]]=1;
       }
    }
  }
}

int main()
{
  scanf("%d %d",&n,&v); /* дължина на графа и връх,   от който да обхождаме*/
  int b,c;
  while(b!=0 || c!=0)
  {
    scanf("%d %d",&b,&c);
    a[b].push_back(c);
    a[c].push_back(b);
  }
  bfs();
  printf("\n");
  return 0;
}
