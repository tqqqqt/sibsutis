#include<iostream>
#include<vector>
using namespace std;
int main() {
	int n=10;
	int *mas=new int[n];
	bool powerOf2 = n && !(n&(n-1));
	for(int i=0; i<n; i++) {
		mas[i]=rand()%200;
		cout<<mas[i]<<" ";
	}
	cout<<endl;
	int stepR=0, h=2, stepL=0;
	vector<int> temp;
	while(h<=n) {
		stepR=h;
		int l=0, r=h/2;
		stepL=r;
		while(stepR<=n) {
			while(l<stepL && r<stepR && l<r) {
				if(mas[l]<mas[r]) {
					temp.push_back(mas[l]);
					l++;
				} else {
					temp.push_back(mas[r]);
					r++;
				}
			}
			while(l<stepL) {
				temp.push_back(mas[l]);
				l++;
			}
			while(r<stepR) {
				temp.push_back(mas[r]);
				r++;
			}
			stepR+=h;
			r+=h/2;
			l+=h/2;
			stepL=r;
		}
		for(int i=0; i<n; i++) mas[i]=temp[i];
		temp.clear();
		for(int i=0; i<n; i++) {
			cout<<mas[i]<<" ";
			if((i+1)%h==0) cout<<"| ";
		}
		cout<<endl;
		h*=2;
	}
	
	//--------
	if(powerOf2==false){
		int ttemp=1;
		while(ttemp<n) {
			ttemp*=2;
		}
		ttemp/=2;
		int r=ttemp, l=0;
		stepL=r;
		stepR=n;
		while(l<stepL && r<stepR && l<r) {
			if(mas[l]<mas[r]) {
				temp.push_back(mas[l]);
				l++;
			} else {
				temp.push_back(mas[r]);
				r++;
			}
		}
		while(l<stepL) {
			temp.push_back(mas[l]);
			l++;
		}
		while(r<stepR) {
			temp.push_back(mas[r]);
			r++;
		}
		for(int i=0; i<n; i++) mas[i]=temp[i];
	}
	for(int i=0;i<n;i++) cout<<mas[i]<<" ";
}
