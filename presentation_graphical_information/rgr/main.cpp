#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>


#define COLOR_DIF 100


#pragma pack(push,1)
struct file_header{
	unsigned short id;
	unsigned int f_size;
	unsigned short rez_1, rez_2;
	unsigned int bm_offset;
};

struct v3_header{
	unsigned int h_size;
	unsigned int width;
	unsigned int height;
	unsigned short planes, bit_per_pixel;
	unsigned int compression;
	unsigned int size_image;
	unsigned int h_res;
	unsigned int v_res;
	unsigned int clr_used;
	unsigned int clr_imp;
};

struct color_info{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char temp;

	color_info(){ }
	color_info(int b, int g, int r): blue(b), green(g), red(r), temp(0){ }
};
#pragma pack(pop)


int findNead(int b, int g, int r, const std::vector<color_info>& arr){
	int result=0, min_val=INT_MAX, siz=arr.size(), temp=0;
	for(int i=0;i<siz;++i){
		temp=std::pow(b-arr[i].blue,2)+std::pow(g-arr[i].green,2)+std::pow(r-arr[i].red,2);
		if(temp<min_val){
			result=i;
			min_val=temp;
		}
	}
	return result;
}


int main(){
	std::ifstream file_in("CAR.bmp",std::ios::binary);

	file_header header;
	v3_header header_v3;

	// read headers
	file_in.read(reinterpret_cast<char*>(&header),sizeof(file_header));
	file_in.read(reinterpret_cast<char*>(&header_v3),sizeof(v3_header));

	// show info
	std::cout<<" File header info:\n";
	std::cout<<"id="<<header.id<<", f_size="<<header.f_size;
	std::cout<<", r1="<<header.rez_1<<", r2="<<header.rez_2<<", ofset="<<header.bm_offset<<"\n \n";

	std::cout<<" v3 header info:\n";
	std::cout<<"size="<<header_v3.h_size<<", width="<<header_v3.width<<", height="<<header_v3.height<<'\n';
	std::cout<<"planes="<<header_v3.planes<<", bit_per_pix="<<header_v3.bit_per_pixel<<", compression="<<header_v3.compression<<'\n';
	std::cout<<"size_image="<<header_v3.size_image<<", h_res="<<header_v3.h_res<<", v_res="<<header_v3.v_res<<'\n';
	std::cout<<"clr_used="<<header_v3.clr_used<<", clr_imp="<<header_v3.clr_imp<<"\n \n";

	// read pixel information
	file_in.seekg(header.bm_offset,std::ios::beg);
	int byter_row=std::floor((header_v3.bit_per_pixel*header_v3.width+31)/32)*4, read_count=0;
	std::vector<std::vector<unsigned char>> rows;
	while(1){
		rows.push_back(std::vector<unsigned char>(byter_row));
		file_in.read(reinterpret_cast<char*>(rows.back().data()),byter_row);
		read_count=file_in.gcount();
		if(read_count>0) continue;
		rows.pop_back();
		break;
	}
	file_in.close();


	// collect colors
	std::cout<<" * Start color selection\n";
	std::vector<color_info> colors;
	int x=rows[0].size(), y=rows.size(), color_size=0;
	bool find_el=false;
	for(int i=0;i<y;++i){
		for(int j=0;j<x;j+=3){
			find_el=false;

			for(int ii=0;ii<color_size;++ii){
				if((std::pow(rows[i][j]-colors[ii].blue,2)+std::pow(rows[i][j+1]-colors[ii].green,2)+std::pow(rows[i][j+2]-colors[ii].red,2))<=COLOR_DIF){
					find_el=true;
					colors[ii].temp+=1;
					break;
				}
			}

			if(find_el==false){
				colors.push_back(color_info(rows[i][j],rows[i][j+1],rows[i][j+2]));
				colors.back().temp=1;
				++color_size;
			}
		}
	}
	std::sort(colors.begin(),colors.end(),[](const color_info& x, const color_info& y){
		return x.temp>y.temp;
	});
	colors.resize(256);
	std::cout<<" * End color selection\n";


	// output file
	std::ofstream file_out("CAR256.bmp",std::ios::binary);

	// change options
	header_v3.bit_per_pixel=8;
	header_v3.clr_imp=256;
	header_v3.clr_used=256;
	header.bm_offset=sizeof(file_header)+sizeof(v3_header)+256*sizeof(color_info);

	// write headers and color table
	file_out.write(reinterpret_cast<char*>(&header),sizeof(file_header));
	file_out.write(reinterpret_cast<char*>(&header_v3),sizeof(v3_header));
	file_out.write(reinterpret_cast<char*>(colors.data()),256*sizeof(color_info));

	// write byte array
	std::cout<<" * Start write in file\n";
	byter_row=std::floor((header_v3.bit_per_pixel*header_v3.width+31)/32)*4;
	for(int i=0;i<y;++i){
		int cur_byte=0, val=0;
		for(int j=0;j<x;j+=3){
			val=findNead(rows[i][j],rows[i][j+1],rows[i][j+2],colors);
			file_out.put(val);
			++cur_byte;
		}
		for(int j=cur_byte;j<byter_row;++j) file_out.put(0);
	}
	std::cout<<" * End write in file\n";

	file_out.close();
	return 0;
}