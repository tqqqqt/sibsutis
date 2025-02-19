#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<elf.h>
#include<unistd.h>
#include<errno.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int CheckReadBuffer(char *buffer);
int CheckOption(char *buffer);
const char* BuildPath(char *buffer);
const char* BuildName(FILE *file, Elf64_Ehdr header, uint32_t sh_name);
void FindTabs(FILE *file, Elf64_Shdr *symTab, Elf64_Shdr *strTab, int flag);
void ReadElfFile(FILE *file, Elf64_Shdr symTab, Elf64_Shdr strTab, int clientSocket);
void MainDynTab(int clientSocket, FILE* file);
void MainSymTab(int clientSocket, FILE* file);
void MainReadElfFile(int clientSocket, char *buffer);
