#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void FindName(FILE *file, Elf64_Ehdr header, Elf64_Shdr *symtab, Elf64_Shdr *strtab){
	uint ii;
	Elf64_Shdr sheader;
	fseek(file,header.e_shoff+header.e_shstrndx*sizeof(sheader),SEEK_SET);
	fread(&sheader,1,sizeof(sheader),file);
	char *sNames=malloc(sheader.sh_size);
	fseek(file,sheader.sh_offset,SEEK_SET);
	fread(sNames,1,sheader.sh_size,file);
	for(ii=0;ii<header.e_shnum;ii++){
			const char* name="";
			fseek(file,header.e_shoff+ii*sizeof(sheader),SEEK_SET);
			fread(&sheader,1,sizeof(sheader),file);
			if(sheader.sh_name);
			name=sNames+sheader.sh_name;
			//fprintf(stdout,"%2u - %s\n",ii,name);
			if(name[1]=='s' && name[2]=='y' && name[3]=='m' && name[4]=='t' && name[5]=='a' && name[6]=='b') *symtab=(Elf64_Shdr)sheader;
			if(name[1]=='s' && name[2]=='t' && name[3]=='r' && name[4]=='t' && name[5]=='a' && name[6]=='b') *strtab=(Elf64_Shdr)sheader;
	}
}

int main(int argc, char** argv){
	const char* elfFile="liblab5.so";
	//const char* elfFile=argv[1];
	Elf64_Ehdr header;
	Elf64_Shdr sheader;
	Elf64_Shdr symtab;
	Elf64_Shdr strtab;
	Elf64_Sym sym;
	char sname[32];
	int i;
	FILE* file=fopen(elfFile,"rb");
	fread(&header,sizeof(header),1,file);
	//FindName(file,header,&symtab,&strtab);
	//fprintf(stdout,"\n \n \n");
	
	fseek(file,header.e_shoff,SEEK_SET);
	fread(&sheader,sizeof(sheader),1,file);
	//symtab=FindName(file,header);
	for(i=0;i<header.e_shnum;i++){
		fseek(file,header.e_shoff+header.e_shentsize*i,SEEK_SET);
		fread(&sheader,sizeof(sheader),1,file);
		FindName(file,header,&symtab,&strtab);
		//if(FindName(file,header)) 
		//	symtab=(Elf64_Shdr)sheader;
		//if(i==5) 
		//	strtab=(Elf64_Shdr)sheader;
		//fprintf(stdout,"%d - %ld - %ld\n",i,symtab.sh_size,symtab.sh_entsize);
	}

	for(i=0;i<symtab.sh_size/symtab.sh_entsize;i++){
		fseek(file,symtab.sh_offset+symtab.sh_entsize*i,SEEK_SET);
		fread(&sym,sizeof(Elf64_Sym),1,file);
		fseek(file,strtab.sh_offset+sym.st_name,SEEK_SET);
		fread(sname,1,32,file);
		fprintf(stdout,"%d\t%ld\t%u\t%u\t%hd\t%s\n",i,sym.st_size,ELF64_ST_TYPE(sym.st_info),ELF64_ST_BIND(sym.st_info),sym.st_shndx,sname);
	}
	return 0;
}
