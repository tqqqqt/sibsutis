#include "mashine.h"

mashine::mashine(){
	curent_h=1.0;
	sort_data=false;
}

double mashine::yadro(int _h){
	if(std::abs(_h)<=1) return (1-std::abs(_h));
	return 0;
}

bool mashine::isDataSort(){
	return sort_data;
}

void mashine::setData(std::vector<file_element>& _data){
	data=std::vector(_data);
	sort_data=false;
}

void mashine::sortData(){
	std::sort(data.begin(),data.end(),[](file_element& x, file_element& y){ return x.getNullDistance()<y.getNullDistance();});
	sort_data=true;
}

void mashine::learnSort(){
	double temp_h=curent_h, k=50, best_h=temp_h, best_res=0.0;
	while(1){
		int n_true_result=0;
		for(int i=0;i<data.size();i++){
			std::vector<double> sum_weight(2,0);
			int left_point=i-1, right_point=i+1, result=-1, count_neight=temp_h+1;
			double max_h=0.0;
			while(count_neight--){
				double left_dist=INT_MAX, right_dist=INT_MAX;
				if(left_point<0 && right_point>=data.size() && count_neight){
					std::cout<<" Stop learn, h>data.size(). ";
					curent_h=best_h;
					std::cout<<" Result k="<<curent_h<<"\n \n";
					return;
				}
				if(left_point>=0) left_dist=data[i].distanceTo(data[left_point]);
				if(right_point<data.size()) right_dist=data[i].distanceTo(data[right_point]);
				if(left_dist<=right_dist){
					max_h=std::max(max_h,left_dist);
					left_point--;
				}
				else if(left_dist>right_dist){
					max_h=std::max(max_h,right_dist);
					right_point++;
				}
			}
			if(left_point<0) left_point=0;
			if(right_point>=data.size()) right_point=data.size()-1;
			for(int j=left_point;j<=right_point;j++){
				if(j==i) continue;
				sum_weight[data[j].numClass()]+=yadro(data[i].distanceTo(data[j])/max_h);
			}
			if(sum_weight[0]>sum_weight[1]) result=0;
			else if(sum_weight[0]<sum_weight[1]) result=1;
			if(data[i].checkClass(result)) n_true_result++;
		}
		std::cout<<" Curent_k = "<<temp_h<<", true_result = "<<(n_true_result/(double)data.size())*100<<"\n";
		if((n_true_result/(double)data.size())*100>best_res){
			best_res=(n_true_result/(double)data.size())*100;
			best_h=temp_h;
		}
		temp_h+=1;
		n_true_result=0;
		if(--k<=0){
			std::string input="";
			while(input!="y" && input!="n"){
				std::cout<<" Continue? y/n\n -> ";
				std::cin>>input;
			}
			if(input=="n") break;
			k=50;
		}
	}
	curent_h=best_h;
	std::cout<<" Result k="<<curent_h<<"\n \n";
}

void mashine::workSort(){
	int n_true_result=0;
	for(int i=0;i<data.size();i++){
		std::vector<std::pair<int,double>> sum_weight(2,std::make_pair(0,0));
		int left_point=i-1, right_point=i+1, result=-1, count_neight=curent_h+1;
		double max_h=0.0;
		while(count_neight--){
			double left_dist=INT_MAX, right_dist=INT_MAX;
			if(left_point>=0) left_dist=data[i].distanceTo(data[left_point]);
			if(right_point<data.size()) right_dist=data[i].distanceTo(data[right_point]);
			if(left_dist<=right_dist){
				max_h=std::max(max_h,left_dist);
				left_point--;
			}
			else if(left_dist>right_dist){
				max_h=std::max(max_h,right_dist);
				right_point++;
			}
		}
		if(left_point<0) left_point=0;
		if(right_point>=data.size()) right_point=data.size()-1;
		for(int j=left_point;j<=right_point;j++){
			if(j==i) continue;
			sum_weight[data[j].numClass()].second+=yadro(data[i].distanceTo(data[j])/max_h);
		}
		if(sum_weight[0].second>sum_weight[1].second) result=0;
		else if(sum_weight[0].second<sum_weight[1].second) result=1;
		if(data[i].checkClass(result)) n_true_result++;
	}
	std::cout<<" Curent_k = "<<curent_h<<", result_% = "<<(n_true_result/(double)data.size())*100<<", count_true = "<<n_true_result<<", data_size = "<<data.size()<<"\n";
}
