#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>


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


int main(){
	// main file
	std::ifstream file_in("CAR.bmp",std::ios::binary);

	file_header header_of_file;
	v3_header header_v3_of_file;
	file_in.read(reinterpret_cast<char*>(&header_of_file),sizeof(file_header));
	file_in.read(reinterpret_cast<char*>(&header_v3_of_file),sizeof(v3_header));

	int bytes_row=std::floor((header_v3_of_file.bit_per_pixel*header_v3_of_file.width+31)/32)*4, read_count=0;

	file_in.seekg(header_of_file.bm_offset,std::ios::beg);
	std::vector<std::vector<unsigned char>> old_rows;
	std::vector<unsigned char> buffer(bytes_row);
	while(1){
		file_in.read(reinterpret_cast<char*>(buffer.data()),bytes_row);
		read_count=file_in.gcount();
		if(read_count>0) old_rows.push_back(buffer);
		else break;
	}

	file_in.close();


	// logo file
	std::ifstream file_logo("LOGO.BMP",std::ios::binary);

	file_header logo_header;
	v3_header header_v3_logo;
	file_logo.read(reinterpret_cast<char*>(&logo_header),sizeof(file_header));
	file_logo.read(reinterpret_cast<char*>(&header_v3_logo),sizeof(v3_header));

	bytes_row=std::floor((header_v3_logo.bit_per_pixel*header_v3_logo.width+31)/32)*4;
	color_info color_table[256];
	file_logo.read(reinterpret_cast<char*>(color_table),256*sizeof(color_info));

	file_logo.seekg(logo_header.bm_offset,std::ios::beg);
	std::vector<std::vector<color_info>> logo_src;
	buffer.clear();
	buffer.resize(bytes_row);
	while(1){
		file_logo.read(reinterpret_cast<char*>(buffer.data()),bytes_row);
		read_count=file_logo.gcount();
		if(read_count<=0) break;
		logo_src.push_back(std::vector<color_info>());
		for(int i=0;i<read_count;++i){
			logo_src.back().push_back(color_table[buffer[i]]);
		}
	}
	buffer.clear();
	file_logo.close();

	// output file
	std::ofstream file_out("new_CAR.bmp",std::ios::binary);
	if(!file_out){
		std::cout<<" out file not open\n";
		file_in.close();
		return 4;
	}

	file_out.write(reinterpret_cast<char*>(&header_of_file),sizeof(file_header));
	file_out.write(reinterpret_cast<char*>(&header_v3_of_file),sizeof(v3_header));

	int logo_x=logo_src[0].size(), logo_y=logo_src.size();
	int img_x=old_rows[0].size(), img_y=old_rows.size();
	double k=0.5;

	for(int i=0;i<img_y;++i){
		int cur_x=0;
		for(int j=0;j<img_x;j+=3, ++cur_x){
			if(i>=logo_y || cur_x>=logo_x){
				file_out.put(old_rows[i][j]);
				file_out.put(old_rows[i][j+1]);
				file_out.put(old_rows[i][j+2]);
				continue;
			}
			file_out.put(old_rows[i][j]*k+logo_src[i][cur_x].blue*(1-k));
			file_out.put(old_rows[i][j+1]*k+logo_src[i][cur_x].green*(1-k));
			file_out.put(old_rows[i][j+2]*k+logo_src[i][cur_x].red*(1-k));
		}
	}

	file_out.close();
	std::cout<<"Work complete\n";
	return 0;
}