#include "stdafx.h"
#include "Orders.h"
#include <windows.h>
#include <shellapi.h>

using namespace std;

Orders::Orders(string filePath) // Should string be const& ?
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
			throw "Failed to open or create Orders file";
	}

	ShellExecuteA(NULL, "edit", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
