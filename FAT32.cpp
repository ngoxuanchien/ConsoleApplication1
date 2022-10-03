#include "FAT32.h"

FAT32::FAT32()
{
	this->_fat = 0;
	this->_sizeFat = 0;
	this->_sizeBootSector = 0;
	this->_fatLocation = 0;
	this->_dataLocation = 0;
}

FAT32::~FAT32()
{
	this->_fat = 0;
	this->_sizeFat = 0;
	this->_sizeBootSector = 0;
	this->_fatLocation = 0;
	this->_dataLocation = 0;
}

void FAT32::setFAT(const int& data)
{
	this->_fat = data;
}

void FAT32::setSizeFAT(const long long& data)
{
	this->_sizeFat = data;
}

void FAT32::setSizeBootSector(const long long& data)
{
	this->_sizeBootSector = data;
}

void FAT32::setTypeFAT(const string& data)
{
	this->_typeFat = data;
}

void FAT32::setFatLocation(const long long& data)
{
	this->_fatLocation = data;
}

void FAT32::setDataLocation(const long long& data)
{
	this->_dataLocation = data;
}

void FAT32::addFile(const string& fileName)
{
	this->_listFile.push_back(fileName);
}

void FAT32::xuat()
{
	/*cout << "Loai FAT: " << this->_typeFat << endl;
	cout << "So byte cho 1 sector: " << this->_sizeSector << endl;
	cout << "So sector cho 1 cluster: " << this->_sizeCluster << endl;
	cout << "So sector danh rieng (so sector vung Bootsector): " << this->_sizeBootSector << endl;
	cout << "So bang FAT: " << this->_fat << endl;
	cout << "Tong so sector tren dia: " << this->_sizeVolume << endl;
	cout << "So sector cho 1 bang FAT: " << this->_sizeFat << endl;
	cout << "Sector dau tien cua bang FAT1: " << this->_fatLocation << endl;
	cout << "Sector dau tien cua bang RDET: " << this->_dataLocation << endl;
	cout << "Sector dau tien cua vung data: " << this->_dataLocation << endl;*/

	for (int i = 0; i < this->_listFile.size(); i++)
	{
		cout << this->_listFile[i] << endl;
	}
}

int FAT32::getFAT()
{
	return this->_fat;
}

long long FAT32::getSizeFAT()
{
	return this->_sizeFat;
}

long long FAT32::getSizeBootSector()
{
	return this->_sizeBootSector;
}

string FAT32::getTypeFAT()
{
	return string(this->_typeFat);
}

long long FAT32::getFatLocation()
{
	return this->_fatLocation;
}

long long FAT32::getDataLocaiton()
{
	return this->_dataLocation;
}
