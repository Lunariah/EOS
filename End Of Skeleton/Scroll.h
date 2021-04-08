#pragma once
#include <fstream>

class Scroll
{
 public:
	Scroll(std::string filePath);
	~Scroll();

	enum class Command;
	Command ReadLine(int &arg);
	void Reload();
	void OpenEditor();

 private:
	std::string filePath; // See if useful to keep
	std::ifstream file;

	void LowerCase(std::string &string);
	void GetArg(const std::string &secondHalf, int &arg);

 public:
	 enum class Command
	 {
		 invalid,
		 wait,
		 up, down, left, right,
		 open,
		 eos
	 };
};



