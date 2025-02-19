#include <libclient/helpfunction.h>

int CheckBuffer(char *buffer){
	if((long)((char*)strstr(buffer,"help")-buffer)!=0) return 1;
	if(strlen(buffer)>5) return 1;
	return 0;
}

void PrintHelp(){
	fprintf(stdout,"-------------------------------\n");
	fprintf(stdout,"Commands:\n\t 'quit' - program end command\n\t 'readelf [path] [options]' - command to read a elf file\n");
	fprintf(stdout,"\t\t Options:\n");
	fprintf(stdout,"\t\t\t '-d' - show .dynsym.\n");
	fprintf(stdout,"\t\t\t '-s' - show .symtab.\n");
	fprintf(stdout,"\t 'help' - display help about commands\n");
	fprintf(stdout,"-------------------------------\n");
}

void MainHelp(char *buffer){
	if(CheckBuffer(buffer)){
		fprintf(stdout,"Unknown command '%s', use 'help' to see comands.\n",buffer);
		return;
	}
	PrintHelp();
}
