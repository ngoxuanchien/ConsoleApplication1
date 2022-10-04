#include "File.h"

File::File() {
	_name = "";
	_size = 0;
	_status = 0;
	_indexSector = 0;
}

File::~File() {
	_name = "";
	_size = 0;
	_status = 0;
	_indexSector = 0;
}

void File::setName(const string& name) {
	_name = name;
}

void File::setSize(const int& size)
{
	_size = size;
}

void File::setStatus(const bool& status)
{
	_status = status;
}

void File::setIndexSector(const int64_t& indexSector)
{
	_indexSector = indexSector;
}

string File::getName()
{
	return _name;
}

int File::getSize()
{
	return _size;
}

bool File::getStatus()
{
	return _status;
}

int64_t File::getIndexSector()
{
	return _indexSector;
}



