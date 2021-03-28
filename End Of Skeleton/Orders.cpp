#include "stdafx.h"
#include "Orders.h"
#include <windows.h>
#include <shellapi.h>
#include <iostream>

using namespace std;
const int MAX_COMMAND_REPEAT = 30;

Scroll::Scroll(string filePath) // Should string be const& ?
	: filePath(filePath)
{
	file.open(filePath);
	if (!file.is_open())
	{
		// Create file
		ofstream newFile(filePath);
		newFile.close();
		file.open(filePath);
		if (!file.is_open())
			throw "Failed to open or create " + filePath;
	}

	//ShellExecuteA(NULL, "edit", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL); // Works, but I�m getting tired of closing windows
}

Scroll::Command Scroll::ReadLine(int& arg) // Worth giving its own thread ?
{
	string newLine;

	getline(file, newLine);
	LowerCase(newLine);
	cout << newLine;

	if (newLine.compare(0, 2, "up") == 0) {
		GetArg(newLine.substr(2), arg);
		return Scroll::Command::up;
	}
	if (newLine.compare(0, 4, "down") == 0) {
		GetArg(newLine.substr(4), arg);
		return Scroll::Command::down;
	}
	if (newLine.compare(0, 4, "left") == 0) {
		GetArg(newLine.substr(4), arg);
		return Scroll::Command::left;
	}
	if (newLine.compare(0, 5, "right") == 0) {
		GetArg(newLine.substr(5), arg);
		return Scroll::Command::right;
	}

	return Scroll::Command::invalid;
}

void Scroll::LowerCase(string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
}

void Scroll::GetArg(const string& secondHalf, int& arg)
{
	try {
		arg = stoi(secondHalf, nullptr);
		if (arg > MAX_COMMAND_REPEAT)
			arg = MAX_COMMAND_REPEAT;
		//if (arg < 0) {
		//	arg = 1;
		//	cout << "\nNice try, smartass\n"; // Actually no, let�s roll with it
		//}
	}
	catch (...) {
		arg = 1;
	}
}
