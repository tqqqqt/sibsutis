#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void ran(int n, int **mas) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			mas[i][j]=1+rand()%19;
			printf("%d ",mas[i][j]);
		}
		printf("\n");
	}
}

void right_di(int **mas,int *d, int n) {
	int i=0, f=n-1, h=0, p=0;
	while(true) {
		h=i;
		for(int j=f; j<n; j++) {
			d[p]=mas[h][j];
			p+=1;
			h+=1;
		}
		if(f>0) f-=1;
		if(f==0 && h==4) break;
	}
	int z=n-1;
	i+=1;
	h=i;
	while(true) {
		f=h;
		for(int j=0; j<z; j++) {
			d[p]=mas[f][j];
			p+=1;
			if(f<n) f+=1;
			else break;
		}
		h+=1;
		z-=1;
		if(h==n && f==n &&z==0) break;
	}
}

void left_di(int **mas, int *d, int n) {
	int i=0, f=0, h=0, p=0, z=0, cc=0;
	while(true) {
		p=0;
		for(int j=h; j>=0; j--) {
			d[cc]=mas[j][p];
			p+=1;
			cc+=1;
		}
		h+=1;
		if(h==n) break;
	}
	h=n-1;
	p=1;
	while(true) {
		f=p;
		for(int j=h; j>z; j--) {
			d[cc]=mas[j][f];
			f+=1;
			cc+=1;
		}
		p+=1;
		z+=1;
		if(p==n) break;
	}
}

//void spir_var(){
//	int star_x=0, star_y=0, block=n-1;
//	for(int el=0;el<n*n;el++){
//		printf("%d ",mas[j][i])
//	}
//}

void spir_ver(int **a, int *d, int n) {
	int i=0,j=0,f=0,w=n-1,l=0,cc=0;
	for (f=0; f<n*n; f+=1) { //Повторяется *кол-во элементов* раз
		d[cc]=a[i][j];
		cc+=1;
		if ((i==(l+1))&&(j==l)) {
			w-=1;    //условие перехода на внутреннюю спираль
			l+=1;
		}
		if ((j==w)&&(i<w)) {
			i+=1;    //Движение по спирали вниз
			continue;
		}
		if ((j<w)&&(i==l)) {
			j+=1;    //Вправо
			continue;
		}
		if ((i==w)&&(j>l)) {
			j-=1;    //Влевo
			continue;
		}
		if ((j==l)&&(i>l)) {
			i-=1;    //Вверх
			continue;
		}
	}
}

int main() {
	int **mas, *D;
	int n=0;
	scanf("%d",&n);
	mas=(int**)malloc(n*sizeof(int));
	for(int i=0; i<n; i++) mas[i]=(int*)malloc(n*sizeof(int));
	ran(n,mas);

	D=(int*)malloc((n*n)*sizeof(int));
	right_di(mas,D,n);
	printf("\n \nRight_diag \n");
	for(int i=0; i<n*n; i++) printf("%d ",D[i]);
	free(D);

	D=(int*)malloc((n*n)*sizeof(int));
	left_di(mas,D,n);
	printf("\n \nLeft_diag \n");
	for(int i=0; i<n*n; i++) printf("%d ",D[i]);
	free(D);

//	D=(int*)malloc((n*n)*sizeof(int));
	

	D=(int*)malloc((n*n)*sizeof(int));
	spir_ver(mas,D,n);
	printf("\n \nSpir_in \n");
	for(int i=0; i<n*n; i++) printf("%d ",D[i]);
	free(D);
	
//	for(int i=0;i<n;i++) free(mas[i]);
//	free(mas); 
//	delete[] mas;
	return 0;
}
