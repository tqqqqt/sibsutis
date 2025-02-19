#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>


#define CODE_LEN 4
#define CODE_NUM ((1<<CODE_LEN)-1)
#define CODE_CNT (std::ceil(8/(double)CODE_LEN))


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


	// text file
	std::ifstream text_file("text.txt",std::ios::binary);

	std::vector<unsigned char> text_rows;
	buffer.resize(1024);
	while(1){
		text_file.read(reinterpret_cast<char*>(buffer.data()),1024);
		read_count=text_file.gcount();
		if(read_count>0) text_rows.insert(text_rows.end(),buffer.begin(),buffer.begin()+read_count);
		else break;
	}
	text_file.close();


	// output file
	std::ofstream file_out("new_CAR.bmp",std::ios::binary);
	if(!file_out){
		std::cout<<" out file not open\n";
		file_in.close();
		return 4;
	}

	file_out.write(reinterpret_cast<char*>(&header_of_file),sizeof(file_header));
	file_out.write(reinterpret_cast<char*>(&header_v3_of_file),sizeof(v3_header));


	int img_x=old_rows[0].size(), img_y=old_rows.size();
	int point=0, count_code=0, cur_code=0;

	for(int i=0;i<img_y;++i){
		for(int j=0;j<img_x;j+=3){
			file_out.put(old_rows[i][j]);
			file_out.put(old_rows[i][j+1]);
			if(point<text_rows.size()){
				old_rows[i][j+2]=((old_rows[i][j+2]>>CODE_LEN)<<CODE_LEN) | (text_rows[point]&CODE_NUM);
				text_rows[point]=text_rows[point]>>CODE_LEN;
				++cur_code;
				if(cur_code==CODE_CNT){
					cur_code=0;
					++point;
				}
				++count_code;
			}
			file_out.put(old_rows[i][j+2]);
		}
	}
	file_out.close();


	// decode
	text_rows.clear();
	int cur_mask=0, temp=0, count_decode=0, temp_val=0;
	cur_code=0;
	for(int i=0;i<img_y;++i){
		for(int j=0;j<img_x;j+=3){
			if(count_decode==count_code) break;
			temp=((old_rows[i][j+2] & CODE_NUM)<<cur_mask);
			temp_val=temp_val | temp;
			++cur_code;
			cur_mask+=CODE_LEN;
			if(cur_code==CODE_CNT){
				text_rows.push_back(temp_val);
				temp_val=0;
				cur_code=0;
				cur_mask=0;
			}
			++count_decode;
		}
		if(count_decode==count_code) break;
	}

	std::ofstream file_text_out("dec_text.txt",std::ios::binary);
	file_text_out.write(reinterpret_cast<char*>(text_rows.data()),text_rows.size());
	file_text_out.close();

	std::cout<<"Work complete\n";
	return 0;
}