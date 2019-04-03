#include<iostream>
using namespace std;
int main()
{
    int N,M,a[100][100];
    char T[50][50];
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    for(int j=1;j<=M;j++)
    {
        cin>>T[i][j];
        if(T[i][j]=='.')
                {
                    if(T[i][j-1]=='.' || (T[i][j-1]>='1' && T[i][j-1]<='9'))
                    {
                        int x1=i,y1=j-1,x2=i,y2=j;
                        a[(x1-1)*M+y1][(x2-1)*M+y2]=1;
                        cout<<"1";
                        cout<<"\n"<<(x1-1)*M+y1<<" : "<< (x2-1)*M+y2<<endl;
                        }
                    if(T[i][j+1]=='.' || (T[i][j+1]>='1' && T[i][j+1]<='9'))
                    {
                        int x1=i,y1=j+1,x2=i,y2=j;
                       a[(x1-1)*M+y1][(x2-1)*M+y2]=1;
                       cout<<"2";
                        cout<<"\n"<<(x1-1)*M+y1<<" : "<< (x2-1)*M+y2<<endl;
                        }
                    if(T[i-1][j]=='.' || (T[i-1][j]>='1' && T[i-1][j]<='9'))
                    {
                        int x1=i-1,y1=j,x2=i,y2=j;
                        a[(x1-1)*M+y1][(x2-1)*M+y2]=1;
                       cout<<"3";
                        cout<<"\n"<<(x1-1)*M+y1<<" : "<< (x2-1)*M+y2<<endl;                        
                        }
                    if(T[i+1][j]=='.' || (T[i+1][j]>='1' && T[i+1][j]<='9'))
                    {int x1=i+1,y1=j,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=1;
                                           cout<<"4";
                        cout<<"\n"<<(x1-1)*M+y1<<" : "<< (x2-1)*M+y2<<endl;}
                }
                else if(T[i][j]>='1' && T[i][j]<='9')
                {
                    int o=T[i][j]-'0';
                    
                    if(T[i][j-1]=='.' || (T[i][j-1]>='1' && T[i][j-1]<='9'))
                    {int x1=i,y1=j-1,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=o+1;
                                           cout<<"5";
                        cout<<"\n"<<(x1-1)*M+y1<<" : "<< (x2-1)*M+y2<<endl;}
                    if(T[i][j+1]=='.' || (T[i][j+1]>='1' && T[i][j+1]<='9'))
                    {int x1=i,y1=j+1,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=o+1;
                                           cout<<"6";
                        cout<<"\n"<<(x1-1)*M+y1<<" : "<< (x2-1)*M+y2<<endl;}
                    if(T[i-1][j]=='.' || (T[i-1][j]>='1' && T[i-1][j]<='9'))
                    {int x1=i-1,y1=j,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=o+1;
                                           cout<<"7";
                        cout<<"\n"<<(x1-1)*M+y1<<" : "<< (x2-1)*M+y2<<endl;}
                    if(T[i+1][j]=='.' || (T[i+1][j]>='1' && T[i+1][j]<='9'))
                    {int x1=i+1,y1=j,x2=i,y2=j;a[(x1-1)*M+y1][(x2-1)*M+y2]=o+1;
                                           cout<<"8";
                        cout<<"\n"<<(x1-1)*M+y1<<" : "<< (x2-1)*M+y2<<endl;}                    
                }
    }
    for(int i=1;i<=N*M;i++)
    {
        for(int j=1;j<=M*N;j++)
        cout<<a[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}