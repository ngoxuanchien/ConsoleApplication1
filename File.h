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

	void setName(const string& name);
	void setSize(const int& size);
	void setStatus(const bool& status);
	void setIndexSector(const int64_t& indexSector);

	string getName();
	int getSize();
	bool getStatus();
	int64_t getIndexSector();
};

