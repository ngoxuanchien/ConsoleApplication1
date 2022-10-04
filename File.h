#pragma once
#include <string>

using namespace std;

class File
{
protected:
	string _name;
	int _size;
	bool _status;
	int64_t _indexSector;

public:
	File();
	~File();

	void setName(const string&);
	void setSize(const int&);
	void setStatus(const bool&);
	void setIndexSector(const int64_t&);

	void getName();
	void getSize();
	void getStatus();
	void getIndexSector();
};

