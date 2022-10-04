#pragma once
#include <vector>
#include <windows.h>
#include <iostream>
#include "Volume.h"

using namespace std;

class FAT32 : public Volume
{
private:
	int _fat;
	long long _sizeFat;
	long long _sizeBootSector;
	string _typeFat;
	long long _fatLocation;
	long long _dataLocation;

public:
	FAT32();
	FAT32(LPCWSTR);
	~FAT32();
	
	void setFAT(const int&);
	void setSizeFAT(const long long&);
	void setSizeBootSector(const long long&);
	void setTypeFAT(const string&);
	void setFatLocation(const long long&);
	void setDataLocation(const long long&);

	void xuat();

	int getFAT();
	long long getSizeFAT();
	long long getSizeBootSector();
	string getTypeFAT();
	long long getFatLocation();
	long long getDataLocaiton();

};

