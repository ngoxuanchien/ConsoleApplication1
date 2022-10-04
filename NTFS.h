#pragma once
#include "Volume.h"
#include <vector>
#include <windows.h>
#include <iostream>

using namespace std;

class NTFS: public Volume
{
private:
	long long _sizeNTFS;
	long long _sizeVBR;
	long long _sizeMFT;
	long long _sizeMFT_Reserved;
	long long _sizeData;
	long long _sizeNotUsed;

	long long MFT_location;
	long long MFT_Reserved_location;
	long long Data_location;
	long long NotUsed_location;
public:
	NTFS();
	NTFS(LPCWSTR);
	~NTFS();

	// Get
	/*
	void getSize_NTFS(const long long&);
	void getSize_VBR(const long long&);
	void getSize_MFT(const long long&);
	void getSize_MFT_Reserved(const long long&);
	void getSize_Data(const long long&);
	void getSize_NotUsed(const long long&);

	void getLocation_MFT(const long long&);
	void getSize_NTFS(const long long&);
	void getSize_NTFS(const long long&);
	void getSize_NTFS(const long long&);
	*/
};

