#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define N pow(2,24)
#define NN pow(2,1)

struct furie {
    double des, mnim;
    furie() {
        des = 0;
        mnim = 0;
    }
    furie(double newDes, double newMnim) {
        des = newDes;
        mnim = newMnim;
    }
};

const double pi = 3.14159265;

furie MulFurie(furie x, furie y) {
    return furie((x.des * y.des - x.mnim * y.mnim), (x.des * y.mnim + x.mnim * y.des));
}

void DirectFastFurie(vector<furie>& mas, int *shet) {
    int n=mas.size();
    if (n <= 1) return;
    vector<furie> even, odd;
    for (int i = 0; i < n/2; i++) even.push_back(furie(mas[i*2].des,mas[i*2].mnim));
    for (int i = 0; i < n/2; i++) odd.push_back(furie(mas[i * 2 + 1].des,mas[i * 2 + 1].mnim));
    DirectFastFurie(even,shet);
    DirectFastFurie(odd,shet);
    for (int i = 0; i < n / 2; i++) {
        furie temp = furie(cos(-2 * pi * i / n),sin(-2 * pi * i / n));
        temp=MulFurie(temp,odd[i]);
        *shet+=1;
        mas[i].des=even[i].des+temp.des;
        mas[i].mnim=even[i].mnim+temp.mnim;
        mas[i+n/2].des=even[i].des-temp.des;
        mas[i+n/2].mnim=even[i].mnim-temp.mnim;
    }
}

void PrintFurie(vector<furie>& mas) {
    cout<<" Direct : \n";
    for (int i = 0; i < mas.size(); i++) printf(" %f + %f * i \n",mas[i].des,mas[i].mnim);
    cout<<"----------------\n";
}

void BackFastFurie(vector<furie>& mas, int *shet) {
    for (int i = 0; i < mas.size(); i++) mas[i].mnim=mas[i].mnim*-1;
    DirectFastFurie(mas,shet);
    for (int i = 0; i < mas.size(); i++) mas[i].mnim=mas[i].mnim*-1;
    for (int i = 0; i < mas.size(); i++) {
        mas[i].des=mas[i].des/mas.size();
        mas[i].mnim=mas[i].mnim/mas.size();
    }
}

void PrintBack(vector<furie>& mas) {
    cout<<"\n Back : \n";
    for (int i = 0; i < mas.size(); i++) printf(" %f + %f * i \n",mas[i].des,mas[i].mnim);
}

int main()
{
    vector<furie> mas;
    for(int i=0;i<N;i++) mas.push_back(furie(i,0));
    /*double** mas = new double* [N];
    for(int i=0;i<N;i++) mas[i]=new double[2];
    for (int i = 0; i < N; i++) {
        mas[i][0]= i;
        mas[i][1]=0;
    }
    cout<<" Mas: \n ";
    //for(int i=0;i<mas.size();i++) cout<<mas[i].des<<" ";
    cout<<"\n \n";*/
    //while (mas.size() && !(mas.size() & (mas.size() - 1)) == false) mas.push_back(furie(0, 0));
    int shet=0;

    DirectFastFurie(mas,&shet);
    //DirectFastFurie2(mas,&shet,N);
    //PrintFurie(mas);
    cout << "\n \n Shet = " << shet << "\n";
    //BackFastFurie(mas,&shet);
    //PrintBack(mas);

    //cout<<"\n \n Shet = "<<shet<<"\n";
    return 0;
}
