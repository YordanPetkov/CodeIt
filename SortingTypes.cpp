#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
int main(){
    ofstream OutputFile;
    OutputFile.open("sortingType2.out",ios::out);
    for(int i = 1; i <= 400; i++){
        for(int j = 1; j <= 400; j++){
            int k = abs(i-j)*6;
            OutputFile<<k<<" ";
        }
        OutputFile<<endl;
    }
    OutputFile.close();
    OutputFile.open("sortingType3.out",ios::out);
    for(int i = 1; i <= 400; i++){
        for(int j = 1; j <= 400; j++){
            int k = sqrt(abs(i-j))*sqrt(400)*15/4;
            cout<<k<<endl;
            OutputFile<<k<<" ";
        }
        OutputFile<<endl;
    }
    OutputFile.close();
    OutputFile.open("sortingType4.out",ios::out);
    for(int i = 1; i <= 400; i++){
        for(int j = 1; j <= 400; j++){
            int k = max(i,j)*3;
            OutputFile<<k<<" ";
        }
        OutputFile<<endl;
    }
    OutputFile.close();
}
