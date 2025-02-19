#include <iostream>
#include <fstream>
#include <string>


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
};
#pragma pach(pop)


void changeColor(struct color_info *table, const int& table_size){
	unsigned char new_value;
	for(int i=0;i<table_size;++i){
		new_value=(unsigned char)(0.29*table[i].red+0.59*table[i].green+0.11*table[i].blue);
		
		table[i].red=new_value;
		table[i].green=new_value;
		table[i].blue=new_value;
	}
}


int main(){
	std::ifstream file_in("CAT256.BMP",std::ios::binary);
	if(!file_in){
		std::cout<<" file not open\n";
		return 4;
	}

	file_header header_of_file;
	v3_header header_v3_of_file;
	file_in.read(reinterpret_cast<char*>(&header_of_file),sizeof(file_header));
	file_in.read(reinterpret_cast<char*>(&header_v3_of_file),sizeof(v3_header));

	std::cout<<" File header info:\n";
	std::cout<<"id="<<header_of_file.id<<", f_size="<<header_of_file.f_size;
	std::cout<<", r1="<<header_of_file.rez_1<<", r2="<<header_of_file.rez_2<<", ofset="<<header_of_file.bm_offset<<"\n \n";

	std::cout<<" v3 header info:\n";
	std::cout<<"size="<<header_v3_of_file.h_size<<", width="<<header_v3_of_file.width<<", height="<<header_v3_of_file.height<<'\n';
	std::cout<<"planes="<<header_v3_of_file.planes<<", bit_per_pix="<<header_v3_of_file.bit_per_pixel<<", compression="<<header_v3_of_file.compression<<'\n';
	std::cout<<"size_image="<<header_v3_of_file.size_image<<", h_res="<<header_v3_of_file.h_res<<", v_res="<<header_v3_of_file.v_res<<'\n';
	std::cout<<"clr_used="<<header_v3_of_file.clr_used<<", clr_imp="<<header_v3_of_file.clr_imp<<"\n \n";

	color_info color_table[256];

	file_in.read(reinterpret_cast<char*>(color_table),256*sizeof(color_info));

	changeColor(color_table,256);

	std::ofstream file_out("new_cat256.BMP",std::ios::binary);
	if(!file_out){
		std::cout<<" error open out file\n";
		file_in.close();
		return 4;
	}

	file_out.write(reinterpret_cast<char*>(&header_of_file),sizeof(file_header));
	file_out.write(reinterpret_cast<char*>(&header_v3_of_file),sizeof(v3_header));
	file_out.write(reinterpret_cast<char*>(color_table),256*sizeof(color_info));
	file_in.seekg(header_of_file.bm_offset,std::ios::beg);

	int bytes_per_row=1024, read_size=0;
	unsigned char temp_row[bytes_per_row];
	
	do{
		file_in.read(reinterpret_cast<char*>(temp_row),bytes_per_row);
		read_size=file_in.gcount();
		file_out.write(reinterpret_cast<char*>(temp_row),read_size);
	} while(read_size>0);


	file_in.close();
	file_out.close();
	return 0;
}