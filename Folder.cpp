#include "Folder.h"

Folder::Folder()
{
	_nFile = 0;
}

Folder::~Folder()
{
	_nFile = 0;
}

void Folder::addFile(const File& file)
{
	_list.push_back(file);
}

vector<File> Folder::getFile()
{
	return _list;
}
