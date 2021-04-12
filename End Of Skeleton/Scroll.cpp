#include "stdafx.h"
#include "Scroll.h"
#include "Utils.h"
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
}

Scroll::~Scroll()
{
	file.close();
}

void Scroll::Reload()
{
	if (file.is_open())
		file.close();
	file.open(filePath);
}

Scroll::Command Scroll::ReadLine(int& arg) // Worth giving its own thread ?
{
	string newLine;

	getline(file, newLine);
	Utils::lowerCase(newLine);
	//cout << newLine << endl;

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
	if (newLine.compare(0, 4, "wait") == 0) {
		GetArg(newLine.substr(4), arg);
		return Scroll::Command::wait;
	}
	if (newLine.compare(0, 4, "open") == 0) {
		arg = 1;
		return Scroll::Command::open;
	}

	if (file.eof())
		return Scroll::Command::eos;

	return Scroll::Command::invalid;
}

void Scroll::OpenEditor()
{
	ShellExecuteA(NULL, "edit", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void Scroll::GetArg(const string& secondHalf, int& arg)
{
	try {
		arg = stoi(secondHalf, nullptr);
		if (arg > MAX_COMMAND_REPEAT)
			arg = MAX_COMMAND_REPEAT;
		//if (arg < 0) {
		//	arg = 1;
		//	cout << "\nMoonwalk is currently unsupported\n"; // Fix this in a later update
		//}
	}
	catch (...) {
		arg = 1;
	}
}
