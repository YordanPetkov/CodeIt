#include<iostream>
#include<cmath>
using namespace std;
int main(){
    int lK=0;
    for(int i = 1; i <= 400; i++)
    {
            int k = sqrt(i) + 0.5;
            if(k != lK){
                if(i!=1)cout<<"To : "<<i-1<<endl;
                cout<<"From : "<<i<<endl;
                cout<<k<<endl;
            }
            lK = k;
    }
    return 0;
}
