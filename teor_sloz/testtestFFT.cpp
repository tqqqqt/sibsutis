#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define N pow(2,21)
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

void DirectFastFurie(furie *mas, int *shet, int n) {
    if (n <= 1) return;
    furie *even=(furie*)malloc(sizeof(struct furie)*(n/2)), *odd=(furie*)malloc(sizeof(struct furie)*(n/2));
    for(int i=0;i<n/2;i++) even[i]=mas[i*2];
	for(int i=0;i<n/2;i++) odd[i]=mas[i*2+1];
    DirectFastFurie(even,shet,n/2);
    DirectFastFurie(odd,shet,n/2);
    for (int i = 0; i < n / 2; i++) {
        furie temp = furie(cos(-2 * pi * i / n),sin(-2 * pi * i / n));
        //temp=MulFurie(temp,odd[i]);
        temp.des=temp.des*mas[i].des-temp.mnim*mas[i].mnim;
        temp.mnim=temp.des*mas[i].mnim+temp.mnim*mas[i].des;
        *shet+=1;
        mas[i].des=even[i].des+temp.des;
        mas[i].mnim=even[i].mnim+temp.mnim;
        mas[i+n/2].des=even[i].des-temp.des;
        mas[i+n/2].mnim=even[i].mnim-temp.mnim;
    }
    free(even);
    free(odd);
}

void PrintFurie(furie *mas, int n) {
    cout<<" Direct : \n";
    for (int i = 0; i < n; i++) printf(" %f + %f * i \n",mas[i].des,mas[i].mnim);
    cout<<"----------------\n";
}

void BackFastFurie(furie *mas, int *shet, int n) {
    for (int i = 0; i < n; i++) mas[i].mnim=mas[i].mnim*-1;
    DirectFastFurie(mas,shet,n);
    for (int i = 0; i < n; i++) mas[i].mnim=mas[i].mnim*-1;
    for (int i = 0; i < n; i++) {
        mas[i].des=mas[i].des/n;
        mas[i].mnim=mas[i].mnim/n;
    }
}

void PrintBack(furie *mas, int n) {
    cout<<"\n Back : \n";
    for (int i = 0; i < n; i++) printf(" %f + %f * i \n",mas[i].des,mas[i].mnim);
}

int main()
{
    furie *mas=(furie*)malloc(sizeof(struct furie)*N);
    for(int i=0;i<N;i++){
    	mas[i].des=i;
    	mas[i].mnim=0;
	}
    /*double** mas = new double* [N];
    for(int i=0;i<N;i++) mas[i]=new double[2];
    for (int i = 0; i < N; i++) {
        mas[i][0]= i;
        mas[i][1]=0;
    }*/
    //cout<<" Mas: \n ";
    //for(int i=0;i<N;i++) cout<<mas[i].des<<" ";
    //cout<<"\n \n";
    //while (mas.size() && !(mas.size() & (mas.size() - 1)) == false) mas.push_back(furie(0, 0));
    int shet=0;

    DirectFastFurie(mas,&shet,N);
    //DirectFastFurie2(mas,&shet,N);
    //PrintFurie(mas,N);
    cout << "\n \n Shet = " << shet << "\n";
    //BackFastFurie(mas,&shet,N);
    //PrintBack(mas,N);

    //cout<<"\n \n Shet = "<<shet<<"\n";
    free(mas);
    return 0;
}
