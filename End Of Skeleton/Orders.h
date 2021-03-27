#pragma once
#include <fstream>

class Orders
{
 public:
	Orders(std::string filePath);

	//OpenFile();

 private:
	std::string filePath;
	std::ifstream file;
};

