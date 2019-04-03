#include<iostream>
#include<fstream>
using namespace std;
int n,a[401],type1,type2,priceP[400][400],priceV[400][400];
int Ans[2][400],br = 0;
void Vuvejdane(){
    ifstream Fin;
    Fin.open("sorting.in",ios::in);
    Fin>>n;
    for(int i = 1; i <= n; i++)
        Fin>>a[i];
    Fin>>type1;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            Fin>>priceP[i][j];
    Fin>>type2;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            Fin>>priceV[i][j];
    Fin.close();
}

void Izvejdane(){
    ofstream Fout;
    Fout.open("sorting.out",ios::out);
    Fout<<br<<endl;
    for(int i = 0; i < br; i++)
        Fout<<Ans[0][i]<<" "<<Ans[1][i]<<endl;

    Fout.close();
}

int main(){
    Vuvejdane();
    if((type1 == 4 && type2 == 0) || (type1 == 4 && type2 == 4)){
            for(int i = n; i >= 1; i--){
            if(i == a[i])continue;
            for(int j = 1; j <= n; j++){
                if(a[j] == i){
                    Ans[0][br] = i;
                    Ans[1][br] = j;
                    br++;
                    swap(a[i],a[j]);
                    break;
                }
            }
        }
    }
    else {

        for(int i = 1; i <= n; i++){
            while(i != a[i]){
                Ans[0][br] = i;
                Ans[1][br] = a[i];
                br++;
                int c = a[i];
                swap(a[i],a[c]);
            }
        }
    }


    Izvejdane();
    return 0;
}
