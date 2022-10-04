#pragma once
#include <string>
#include <vector>
#include "File.h"

using namespace std;

class Folder : protected File
{
private:
	vector<File> _list;
	int _nFile;

public:
	Folder();
	~Folder();

	void addFile(const File&);

	vector<File> getFile();
};

