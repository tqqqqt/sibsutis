#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <vector>

class File
{
public:
    File();

    void saveInFile(std::string, const std::vector<std::string>&);
    void loadFromFile(std::string, std::vector<std::string>&);
};

#endif // FILE_H
