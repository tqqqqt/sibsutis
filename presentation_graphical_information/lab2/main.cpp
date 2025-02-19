#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


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
#pragma pack(pop)


int main(int argv, char** argc){
	if(argv!=2){
		std::cout<<"Error argums. need 1.";
		return 4;
	}

	std::ifstream file_in(argc[1],std::ios::binary);
	if(!file_in){
		std::cout<<" in file not open\n";
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

	std::string new_file_name=argc[1];
	std::ofstream file_out("new_"+new_file_name,std::ios::binary);
	if(!file_out){
		std::cout<<" out file not open\n";
		file_in.close();
		return 4;
	}


	if(header_v3_of_file.bit_per_pixel==8){
		color_info color_table[256];

		file_in.read(reinterpret_cast<char*>(color_table),256*sizeof(color_info));
 		int bytes_old_row=std::floor((header_v3_of_file.bit_per_pixel*header_v3_of_file.width+31)/32)*4;

 		header_v3_of_file.height+=30;
 		header_v3_of_file.width+=30;
		file_out.write(reinterpret_cast<char*>(&header_of_file),sizeof(file_header));
		file_out.write(reinterpret_cast<char*>(&header_v3_of_file),sizeof(v3_header));
		file_out.write(reinterpret_cast<char*>(color_table),256*sizeof(color_info));
		file_in.seekg(header_of_file.bm_offset,std::ios::beg);

		int bytes_per_row=std::floor((header_v3_of_file.bit_per_pixel*header_v3_of_file.width+31)/32)*4, read_size=0;
		int bound_size=(bytes_per_row-bytes_old_row)/2;
		unsigned char bound[bytes_per_row], temp_row[bytes_old_row], left_right[bound_size];

		for(int i=0;i<bound_size;i++) left_right[i]=10;
		for(int i=0;i<bytes_per_row;i++) bound[i]=10;

		for(int i=0;i<15;i++) file_out.write(reinterpret_cast<char*>(bound),bytes_per_row);
		do{
			file_out.write(reinterpret_cast<char*>(left_right),bound_size);
			file_in.read(reinterpret_cast<char*>(temp_row),bytes_old_row);
			read_size=file_in.gcount();
			file_out.write(reinterpret_cast<char*>(temp_row),read_size);
			file_out.write(reinterpret_cast<char*>(left_right),bound_size);
		} while(read_size>0);
		for(int i=0;i<15;i++) file_out.write(reinterpret_cast<char*>(bound),bytes_per_row);
	}
	else if(header_v3_of_file.bit_per_pixel==24){
		int bytes_old_row=std::floor((header_v3_of_file.bit_per_pixel*header_v3_of_file.width+31)/32)*4;

		header_v3_of_file.height+=30;
		header_v3_of_file.width+=30;
		header_v3_of_file.size_image=header_v3_of_file.width*header_v3_of_file.height*3;
		file_out.write(reinterpret_cast<char*>(&header_of_file),sizeof(file_header));
		file_out.write(reinterpret_cast<char*>(&header_v3_of_file),sizeof(v3_header));

		file_in.seekg(header_of_file.bm_offset,std::ios::beg);

		int bytes_per_row=std::floor((header_v3_of_file.bit_per_pixel*header_v3_of_file.width+31)/32)*4;
		int bound_size=(bytes_per_row-bytes_old_row);
		int pading=bound_size-(3*std::floor(bound_size/3));
		bound_size=(bound_size-pading)/2;
		int read_size=0, size=sizeof(color_info)-sizeof(unsigned char);

		unsigned char buffer[bytes_old_row], bound[bound_size], fill_width[bytes_per_row];

		for(int i=0;i<bound_size;i+=3){
			bound[i]=10;
			bound[i+1]=200;
			bound[i+2]=10;
		}
		for(int i=0;i<bytes_per_row;i+=3){
			fill_width[i]=10;
			fill_width[i+1]=200;
			fill_width[i+2]=10;
		}

		for(int i=0;i<15;i++) file_out.write(reinterpret_cast<char*>(fill_width),bytes_per_row);
		do{
			file_out.write(reinterpret_cast<char*>(bound),bound_size);
			file_in.read(reinterpret_cast<char*>(buffer),bytes_old_row);
			read_size=file_in.gcount();
			file_out.write(reinterpret_cast<char*>(buffer),bytes_old_row);
			file_out.write(reinterpret_cast<char*>(bound),bound_size);
			for(int i=0;i<pading;++i) file_out.put(0);
		}while(read_size>0);
		for(int i=0;i<15;i++) file_out.write(reinterpret_cast<char*>(fill_width),bytes_per_row);
	}

	file_in.close();
	file_out.close();
	return 0;
}