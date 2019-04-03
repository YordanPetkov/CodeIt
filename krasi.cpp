#include<iostream>
#include<fstream>

using namespace std;

int n,k,j,a[100000],s=0,br0=0,sF0,ans;
//vector <int> v;
void Input(){
    ifstream InputFile;
    InputFile.open("krasi.in",ios::in);
    InputFile>>n>>k;
    for(int i = 1; i <= n;i++)
        {
            InputFile>>a[i];
            if(a[i] == 0)br0++;
            if(br0 == 1)sF0 = s;
            if(br0 <= k)s+=a[i];
            if(br0 > k){
                br0--;
                ans = s;
                s -= sF0;
            }
        }
}

void Output(){
    ofstream OutFile;
    OutFile.open("krasi.out",ios::out);
    if(s>ans)ans = s;
    OutFile<<ans<<endl;
}
int main(){
    Input();
    Output();
    return 0;
}
