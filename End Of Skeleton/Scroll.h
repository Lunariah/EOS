#pragma once
#include <fstream>

class Scroll
{
 public:
	static Scroll* GetInstance();
	~Scroll();

	enum class Command;
	Command ReadLine(int &arg);
	void Reload();
	static void OpenEditor();

 private:
	Scroll();
	static Scroll* instance;

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



