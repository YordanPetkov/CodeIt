
#include<iostream>
#include<fstream>
#include<utility>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

void Output(){//N^2
    ofstream OutputFile;
    OutputFile.open("Tests/20.out",ios::out);
    for(int i = 1; i <= 400; i++)
        {
            for(int j = 1; j <= 400; j++){
                if(i == j){OutputFile<<0<<" ";continue;}
                else {
                    int k = ceil(sqrt(abs(i-j)))*75;
                    cout<<k<<" ";
                    OutputFile<<int(k)<<" ";
                }
            }
            cout<<endl;
            OutputFile<<endl;

        }

    OutputFile.close();

}

int main(){
    Output();
    return 0;
}
