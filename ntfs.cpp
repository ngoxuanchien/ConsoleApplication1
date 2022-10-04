#include "NTFS.h"

const int _ntfs[24] = {3, 8, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 4, 4, 4, 8, 8, 8, 1, 3, 1, 3, 8, 4 };

NTFS::NTFS() {
	//_mediaDescriptor = "";
	_sectorsPerTrack = 0;
	_numberOfHeads = 0;
	_hiddenSectors = 0;
	_clusterMFT = 0;
	_clusterMFTMirr = 0;
	_clusterPerFileRecord = 0;
	_clusterPerIndexBlock = 0;
	//_serialNnumberVolume = "";
}

NTFS::NTFS(LPCWSTR drive)
{
	int readPoint = 11; //0Bh

	DWORD bytesRead;
	HANDLE device = NULL;
	BYTE* sector = new BYTE[512];

	device = CreateFile(drive,              // Drive to open
		GENERIC_READ,                       // Access mode
		FILE_SHARE_READ | FILE_SHARE_WRITE, // Share Mode
		NULL,                               // Security Descriptor
		OPEN_EXISTING,                      // How to create
		0,                                  // File attributes
		NULL);                              // Handle to template

	if (device == INVALID_HANDLE_VALUE) // Open Error
	{
		printf("CreateFile: %u\n", GetLastError());
		return;
	}

	SetFilePointer(device, readPoint, NULL, FILE_BEGIN); // Set a Point to Read

	if (!ReadFile(device, sector, 512, &bytesRead, NULL))
	{
		printf("ReadFile: %u\n", GetLastError());
	}
	else
	{
		string cur;
		int k = 0;
		for (int i = 0; i < 24; i++)
		{
			cur = "";

			for (int j = 0; j < _ntfs[i]; j++)
			{
				switch (i)
				{
				case 22:
					cur = cur + (char)sector[k];
					break;
				case 2: case 3: case 8: case 10: case 11: case 12:
				case 15: case 16: case 17: case 18: case 20: 
					cur = toHex((int)sector[k]) + cur;
					break;
				}

				k++;
			}

			switch (i)
			{
			case 2:
				this->_sizeSector = hexToDec(cur);
				break;
			case 3:
				this->_sizeCluster = hexToDec(cur);
				break;
			case 8:
				this->_mediaDescriptor = hexToDec(cur);
				break;
			case 10:
				this->_sectorsPerTrack = hexToDec(cur);
				break;
			case 11:
				this->_numberOfHeads = (hexToDec(cur));
				break;
			case 12:
				this->_hiddenSectors = (hexToDec(cur));
				break;
			case 15:
				this->_sizeVolume = (hexToDec(cur));
				break;
			case 16:
				this->_clusterMFT = (hexToDec(cur));
				break;
			case 17:
				this->_clusterMFTMirr = (hexToDec(cur));
				break;
			case 18:
				this->_clusterPerFileRecord = (hexToDec(cur));
				break;
			case 20:
				this->_clusterPerIndexBlock = (hexToDec(cur));
				break;
			case 22:
				string tmp;
				for (int  i = 0; i < 8; i++)
				{
					int a = (int)cur[i];
					a = a > 0 ? a : a + 256;
					tmp += toHex(a);
				}
				this->_serialNnumberVolume = tmp;
				break;
			}

		}

		//this->_dataLocation = this->_sizeBootSector + this->_fat * this->_sizeFat;
		//this->_fatLocation = this->_sizeBootSector;
	}
}

NTFS::~NTFS(){}

void NTFS::setMediaDescriptor(const ll& data) {
	this->_mediaDescriptor = data;
}
void NTFS::setSectorsPerTrack(const ll& data) {
	this->_sectorsPerTrack = data;
}
void NTFS::setNumberOfHeads(const ll& data) {
	this->_numberOfHeads = data;
}
void NTFS::setHiddenSectors(const ll& data) {
	this->_hiddenSectors = data;
}
void NTFS::setClusterMFT(const ll& data) {
	this->_clusterMFT = data;
}
void NTFS::setClusterMFTMirr(const ll& data) {
	this->_clusterMFTMirr = data;
}
void NTFS::setClusterPerFileRecord(const ll& data) {
	this->_clusterPerFileRecord = data;
}
void NTFS::setClusterPerIndexBlock(const ll& data) {
	this->_clusterPerIndexBlock = data;
}
void NTFS::setSerialNnumberVolume(const string& data) {
	this->_serialNnumberVolume = data;
}

ll NTFS::getMediaDescriptor() {
	return this->_mediaDescriptor;
}
ll NTFS::getSectorsPerTrack() {
	return this->_sectorsPerTrack;
}
ll NTFS::getNumberOfHeads() {
	return this->_numberOfHeads;
}
ll NTFS::getHiddenSectors() {
	return this->_hiddenSectors;
}
ll NTFS::getClusterMFT() {
	return this->_clusterMFT;
}
ll NTFS::getClusterMFTMirr() {
	return this->_clusterMFTMirr;
}
ll NTFS::getClusterPerFileRecord() {
	return this->_clusterPerFileRecord;
}
ll NTFS::getClusterPerIndexBlock() {
	return this->_clusterPerIndexBlock;
}
string NTFS::getSerialNnumberVolume() {
	return this->_serialNnumberVolume;
	;
}

void NTFS::xuat() {
	cout << "Bytes Per Sector: " << this->_sizeSector << "\n";
	cout << "Sectors Per Cluster: " << this->_sizeCluster << "\n";
	cout << "Total Sectors: " << this->_sizeVolume << "\n";
	cout << "Media Descriptor: " << this->_mediaDescriptor << "\n";
	cout << "Number Of Heads: " << this->_numberOfHeads << "\n";
	cout << "Hidden Sectors: " << this->_hiddenSectors << "\n";
	cout << "$MFT Cluster number: " << this->_clusterMFT << "\n";
	cout << "$MFTMirr Cluster number: " << this->_clusterMFTMirr << "\n";
	cout << "Cluster Per File Record: " << this->_clusterPerFileRecord << "\n";
	cout << "Cluster Per Index Block: " << this->_clusterPerIndexBlock << "\n";
	cout << "Serial Nnumber Volume: " << this->_serialNnumberVolume << "\n";
}