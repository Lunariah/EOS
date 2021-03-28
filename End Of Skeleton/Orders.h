#pragma once
#include <fstream>

class Scroll
{
 public:
	Scroll(std::string filePath);

	enum class Command;
	Command ReadLine(int &arg);

 private:
	std::string filePath; // See if useful to keep
	std::ifstream file;

	void LowerCase(std::string &string);
	void GetArg(const std::string &secondHalf, int &arg);

 public:
	 enum class Command
	 {
		 invalid,
		 up, down, left, right
	 };
};



