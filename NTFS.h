#pragma once
#include "Volume.h"
#include <vector>
#include <windows.h>
#include <iostream>
#include "Volume.h"
#include<string>

using namespace std;

# define ll long long
class NTFS : public Volume
{
private:
	ll _mediaDescriptor;
	ll _sectorsPerTrack;
	ll _numberOfHeads;
	ll _hiddenSectors;
	ll _clusterMFT;
	ll _clusterMFTMirr;
	ll _clusterPerFileRecord;
	ll _clusterPerIndexBlock;
	string _serialNnumberVolume;

	long long MFT_location;
	long long MFT_Reserved_location;
	long long Data_location;
	long long NotUsed_location;
public:
	NTFS();
	NTFS(LPCWSTR);
	~NTFS();

	void setMediaDescriptor(const ll&);
	void setSectorsPerTrack(const ll&);
	void setNumberOfHeads(const ll&);
	void setHiddenSectors(const ll&);
	void setClusterMFT(const ll&);
	void setClusterMFTMirr(const ll&);
	void setClusterPerFileRecord(const ll&);
	void setClusterPerIndexBlock(const ll&);
	void setSerialNnumberVolume(const string&);

	void xuat();

	ll getMediaDescriptor();
	ll getSectorsPerTrack();
	ll getNumberOfHeads();
	ll getHiddenSectors();
	ll getClusterMFT();
	ll getClusterMFTMirr();
	ll getClusterPerFileRecord();
	ll getClusterPerIndexBlock();
	string getSerialNnumberVolume();
};

