#include <libserver/elffunction.h>

#define ENDANSWER "endAnswer444"

int flagDynTab=0, flagSymTab=0;

int CheckOption(char *buffer){
	int i=0,j=0,l=0,r=0;
	for(i;i<strlen(buffer);i++){
		if(buffer[i]==' ' || buffer[i]=='\n' || buffer[i]=='\0'){
			char temp[r];
			for(j=0;j<r;j++) temp[j]=buffer[l+j];
			if(strcmp(temp,"-d")==0) flagDynTab=1;
			if(strcmp(temp,"-s")==0) flagSymTab=1;
			l=i+1;
			r=0;
		}
		else r++;
	}
	if(flagDynTab==0 && flagSymTab==0) return 1;
	return 0;
}

const char* BuildPath(char *buffer){
	int i=0,space=0,l=-1,r=0;
	for(i;i<strlen(buffer);i++){
		if(space==1){
			if(buffer[i]==' ' || buffer[i]=='\0' || buffer[i]=='\n') break;
			if(l<0) l=i;
			else r++;
		}
		if(buffer[i]==' ') space=1;
	}
	char *tempPath=malloc(sizeof(char)*r);
	for(i=0;i<=r;i++) tempPath[i]=buffer[l+i];
	const char *filePath=tempPath;
	return filePath;
}

const char* BuildName(FILE *file, Elf64_Ehdr header, uint32_t sh_name){
	Elf64_Shdr sheader;
	fseek(file,header.e_shoff+header.e_shstrndx*sizeof(sheader),SEEK_SET);
	fread(&sheader,1,sizeof(sheader),file);
	char *sNames=malloc(sheader.sh_size);
	fseek(file,sheader.sh_offset,SEEK_SET);
	fread(sNames,1,sheader.sh_size,file);
	const char* name="";
	name=sNames+sh_name;
	return name;
}

void FindTabs(FILE *file, Elf64_Shdr *symTab, Elf64_Shdr *strTab, int flag){
	Elf64_Ehdr header;
	Elf64_Shdr sheader;
	fread(&header,sizeof(header),1,file);
	fseek(file,header.e_shoff,SEEK_SET);
	fread(&sheader,sizeof(sheader),1,file);
	int i=0;
	for(i;i<header.e_shnum;i++){
		fseek(file,header.e_shoff+header.e_shentsize*i,SEEK_SET);
		fread(&sheader,sizeof(sheader),1,file);
		if(flag==1){
			if(strcmp(BuildName(file,header,sheader.sh_name),".symtab")==0) *symTab=(Elf64_Shdr)sheader;
			if(strcmp(BuildName(file,header,sheader.sh_name),".strtab")==0) *strTab=(Elf64_Shdr)sheader;
		}
		else if(flag==2){
			if(strcmp(BuildName(file,header,sheader.sh_name),".dynsym")==0) *symTab=(Elf64_Shdr)sheader;
			if(strcmp(BuildName(file,header,sheader.sh_name),".dynstr")==0) *strTab=(Elf64_Shdr)sheader;
		}
	}
}

void ReadElfFile(FILE *file, Elf64_Shdr symTab, Elf64_Shdr strTab, int clientSocket){
	Elf64_Sym sym;
	int i=0;
	char sname[32], messageOut[4096], messageIn[8];
	for(i;i<symTab.sh_size/symTab.sh_entsize;i++){
		fseek(file,symTab.sh_offset+symTab.sh_entsize*i,SEEK_SET);
		fread(&sym,sizeof(Elf64_Sym),1,file);
		fseek(file,strTab.sh_offset+sym.st_name,SEEK_SET);
		fread(sname,1,32,file);
		memset(messageOut,0,4096);
		snprintf(messageOut,4096,"%d.\t%ld\t%u\t%u\t%hd\t%s\n",i,sym.st_size,ELF64_ST_TYPE(sym.st_info),ELF64_ST_BIND(sym.st_info),sym.st_shndx,sname);
		int lengthMessage=strlen(messageOut)+1;
		write(clientSocket,&lengthMessage,sizeof(lengthMessage));
		write(clientSocket,messageOut,lengthMessage);
		sleep(0.7);
	}
}

void MainDynTab(int clientSocket, FILE* file){
	Elf64_Shdr symTab, strTab;
	char *text="\n--dynsym--\n";
	int lengthMessage=strlen(text)+1;
	write(clientSocket,&lengthMessage,sizeof(lengthMessage));
	write(clientSocket,text,lengthMessage);
	FindTabs(file,&symTab,&strTab,2);
	ReadElfFile(file,symTab,strTab,clientSocket);
}

void MainSymTab(int clientSocket, FILE* file){
	Elf64_Shdr symTab, strTab;
	char *text="\n--symtab--\n";
	int lengthMessage=strlen(text)+1;
	write(clientSocket,&lengthMessage,sizeof(lengthMessage));
	write(clientSocket,text,lengthMessage);
	FindTabs(file,&symTab,&strTab,1);
	ReadElfFile(file,symTab,strTab,clientSocket);
}

void MainReadElfFile(int clientSocket, char *buffer){
	flagDynTab=0;
	flagSymTab=0;
	const char *filePath=BuildPath(buffer);
	FILE *file;
	fprintf(stdout,"FilePath - [%s]\n",filePath);
	if(fopen(filePath,"rb")==NULL){
		char *textError="Error: access to file.\n", *textEnd="errorRed";
		int length=strlen(textError)+1;
		write(clientSocket,&length,sizeof(length));
		write(clientSocket,textError,length);
		length=strlen(textEnd)+1;
		write(clientSocket,&length,sizeof(length));
		write(clientSocket,textEnd,length);
		fprintf(stdout,"Error - access to [%s]\n",filePath);
		return;
	}
	int tempSize=strlen(buffer)-9-strlen(filePath),startOpt=8+strlen(filePath)+1;
	char options[tempSize];
	int i=0;
	for(i;i<tempSize;i++) options[i]=buffer[startOpt+i];
	fprintf(stdout,"Options - [%s]",options);
	if(strlen(options)>2) if(CheckOption(options)){
		char *textError="Error: bad options", *textEnd="errorRed";
		int length=strlen(textError)+1;
		write(clientSocket,&length,sizeof(length));
		write(clientSocket,textError,length);
		length=strlen(textEnd)+1;
		write(clientSocket,&length,sizeof(length));
		write(clientSocket,textEnd,length);
		printf("Error - check option\n");
		return;
	}
	fprintf(stdout,"\ndyn - %d, sym - %d\n",flagDynTab,flagSymTab);
	file=fopen(filePath,"rb");
	Elf64_Shdr symTab, strTab;
	if(flagDynTab==flagSymTab){
		MainDynTab(clientSocket,file);
		fseek(file,0,SEEK_SET);
		MainSymTab(clientSocket,file);
	}
	else if(flagDynTab==1) MainDynTab(clientSocket,file);
	else if(flagSymTab==1) MainSymTab(clientSocket,file);
	char *endAnswer=ENDANSWER;
	int length=strlen(endAnswer)+1;
	write(clientSocket,&length,sizeof(length));
	write(clientSocket,endAnswer,length);
}
