#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N (int)(pow(2,24))

struct Signal {
	double Real;
	double Image;
};

const double PI=3.14159265;
int shet=0;
double* Input;
struct Signal* Sig;

void BitReverse()
{
    for (int i = 0; i < N / 2; i++) {
        Sig[i].Real = Input[i * 2];
        Sig[i].Image=0;
    }
    for (int i = 0; i < N / 2; i++) {
        Sig[(N / 2) + i].Real = Input[i * 2 + 1];
        Sig[(N/2)+i].Image = 0;
    }
}

void Butterfly_Opreation(int Pre, int Next, double theta)
{

    double Sin_Omega = -sin(theta); //sin_omega is nagetive
    double Cos_Omega = cos(theta);
    struct Signal temp[2];


    temp[0].Real = Sig[Pre].Real + Cos_Omega * Sig[Next].Real - Sin_Omega * Sig[Next].Image;
    temp[0].Image = Sig[Pre].Image + Cos_Omega * Sig[Next].Image + Sin_Omega * Sig[Next].Real;


    temp[1].Real = Sig[Pre].Real - Cos_Omega * Sig[Next].Real + Sin_Omega * Sig[Next].Image;
    temp[1].Image = Sig[Pre].Image - Cos_Omega * Sig[Next].Image - Sin_Omega * Sig[Next].Real;


    Sig[Pre].Real = temp[0].Real;
    Sig[Pre].Image = temp[0].Image;
    Sig[Next].Real = temp[1].Real;
    Sig[Next].Image = temp[1].Image;
}

void FFT2()
{
    int i, j, k, LogN=log2(N);
    double  theta;

    for (i = 0; i < LogN; i++)
    {
        for (j = 0; j < (N >> (i + 1)); j++)
        {
            for (k = 0; k < (1 << i); k++)
            {
                theta = 2 * PI / (1 << (i + 1)) * k;
                Butterfly_Opreation(k + j * (1 << (i + 1)), k + j * (1 << (i + 1)) + (1 << i), theta);
                shet+=1;
            }
        }
    }
}

void BackFastFurie() {
    int i;
    for (i = 0; i < N; i++) Sig[i].Image = Sig[i].Image * -1;
    FFT2();
    for (i = 0; i < N; i++) Sig[i].Image = Sig[i].Image * -1;
    for (i = 0; i < N; i++) {
        Sig[i].Real = Sig[i].Real / N;
        Sig[i].Image = Sig[i].Image / N;
    }
}

int main()
{
    int i;
    Sig = (Signal*)malloc(sizeof(struct Signal) * N);
    Input = (double*)malloc(sizeof(double) * N);
    //BSig = malloc(sizeof(struct Signal)*N);
    for (i = 0; i < N; i++) Input[i] = i;
    //for(i=0;i<N;i++) printf("%f \n",Input[i]);
    BitReverse();
    //for (i = 0; i < N; i++) printf(" %f + %f * i \n", Sig[i].Real, Sig[i].Image);
    //printf("\n \n");
    FFT2();
    printf("Shet = %d\n",shet);
    return 0;
}

