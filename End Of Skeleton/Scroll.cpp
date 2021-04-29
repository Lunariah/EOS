#include "stdafx.h"
#include "Scroll.h"
#include "Global.h"
#include "Utils.h"
#include <windows.h>
#include <shellapi.h>
#include <iostream>

using namespace std;

Scroll* Scroll::instance = nullptr;

Scroll* Scroll::GetInstance()
{
	if (instance == nullptr)
		instance = new Scroll();
	return instance;
}

Scroll::Scroll()
{	
	file.open(INPUT_PATH);
	if (!file.is_open())
	{
		// Create file if it doesn’t exist yet
		ofstream newFile(INPUT_PATH);
		newFile.close();
		file.open(INPUT_PATH);
		if (!file.is_open())
			throw "Failed to open or create " + INPUT_PATH;
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
	file.open(INPUT_PATH);
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

	cout << "Invalid\n";
	return Scroll::Command::invalid;
}

void Scroll::GetArg(const string& secondHalf, int& arg)
{
	try {
		arg = stoi(secondHalf, nullptr);
		if (arg > MAX_COMMANDS_STACK)
			arg = MAX_COMMANDS_STACK;
	}
	catch (...) {
		arg = 1;
	}
}

void Scroll::OpenEditor()
{
	ShellExecuteA(NULL, "edit", INPUT_PATH.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
