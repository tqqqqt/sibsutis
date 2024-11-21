#include <iostream>
#include <vector>
#include <cmath>

void findMinElement(std::vector<int> arr, int* value, int* index){
	if(arr.size()==0) return;
	*value=arr[0];
	*index=0;
	for(int i=1;i<arr.size();i++){
		if(arr[i]>=(*value)) continue;
		*value=arr[i];
		*index=i;
	}
}

void bubleSort(std::vector<int>& arr){
	for(int i=0;i<arr.size();i++){
		for(int j=arr.size()-1;j>i;j--){
			if(arr[j]<arr[j-1]) std::swap(arr[j],arr[j-1]);
		}
	}
}

int findElement(std::vector<int> arr, int value){
	int l=0, r=arr.size()-1;
	while(l<r){
		int mid=std::floor((l+r)/2);
		if(arr[mid]==value) return mid;
		else if(arr[mid]<value) l=mid+1;
		else r=mid-1;
	}
	return -1;
}

void findMinInToSize(std::vector<std::vector<int>> arr, int* value, int* row, int* cols){
	if(arr.size()==0) return;
	for(int i=0;i<arr.size();i++){
		for(int j=0;j<arr[i].size();j++){
			if(*value<=arr[i][j]) continue;
			*value=arr[i][j];
			*row=i;
			*cols=j;
		}
	}
}

void reverseMas(std::vector<int>& arr){
	int l=0, r=arr.size()-1;
	while(l<r){
		std::swap(arr[l],arr[r]);
		l++;
		r--;
	}
}

void moveMas(std::vector<int>& arr, int value){
	std::vector<int> temp=arr;
	for(int i=0;i<temp.size();i++){
		temp[i]=arr[(i+value)%arr.size()];
	}
	arr=temp;
}

void findAndChangeValue(std::vector<int>& arr, int key, int value){
	for(int i=0;i<arr.size();i++){
		if(arr[i]==key) arr[i]=value;
	}
}

int main(){
	std::vector<int> temp{2,2,6,6,8,8,9,9,4,4,5,5,0,1,7};
	int value=0, index=0;
	
	findMinElement(temp,&value,&index);
	std::cout<<value<<" "<<index<<'\n';

	bubleSort(temp);
	for(auto x:temp) std::cout<<x<<" ";
	std::cout<<'\n';

	int res=findElement(temp,4);
	if(res==-1) std::cout<<"No find\n";
	else std::cout<<"Find in "<<res<<"\n";

	std::vector<std::vector<int>> ttemp{{9,8,7},{6,5,4},{3,2,1}};
	int second_index=0;
	value=99;

	findMinInToSize(ttemp,&value,&index,&second_index);
	std::cout<<value<<" "<<index<<" "<<second_index<<'\n';

	reverseMas(temp);
	for(auto x:temp) std::cout<<x<<" ";
	std::cout<<'\n';

	moveMas(temp,5);
	for(auto x:temp) std::cout<<x<<" ";
	std::cout<<'\n';

	findAndChangeValue(temp,4,3);
	for(auto x:temp) std::cout<<x<<" ";
	std::cout<<'\n';

	return 0;
}