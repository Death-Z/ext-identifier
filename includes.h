#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <filesystem>
#include <fstream>

struct fileExtIdStruct {
	std::string id;
	std::string ext;
};

std::vector<fileExtIdStruct> fileEIVec;