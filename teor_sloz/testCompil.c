#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
 
double PI;
typedef double complex cplx;
const int N=(int)pow(2,21);
 
void _fft(cplx buf[], cplx out[], int n, int step)
{
	if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);
 
		for (int i = 0; i < n; i += 2 * step) {
			cplx t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}
 
void fft(cplx buf[], int n)
{
	cplx out[n];
	for (int i = 0; i < n; i++) out[i] = buf[i];
 
	_fft(buf, out, n, 1);
}
 
 
void show(const char * s, cplx buf[]) {
	printf("%s", s);
	for (int i = 0; i < N; i++)
		if (!cimag(buf[i]))
			printf("%g ", creal(buf[i]));
		else
			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
}

int main()
{
	PI = atan2(1, 1) * 4;
	cplx *buf=(cplx*)malloc(sizeof(cplx)*N);
	int i;
	for(i=0;i<N;i++) buf[i]=i;
 
	//show("Data: ", buf);
	fft(buf, N);
	show("\nFFT : ", buf);
 
	return 0;
}
