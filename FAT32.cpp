#include "FAT32.h"

const int _fat32[29] = { 3, 8, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 4, 4, 4, 2, 2, 4, 2, 2, 12, 1, 1, 1, 4, 11, 8, 420, 2 };

FAT32::FAT32()
{
	this->_fat = 0;
	this->_sizeFat = 0;
	this->_sizeBootSector = 0;
	this->_fatLocation = 0;
	this->_dataLocation = 0;
}

FAT32::FAT32(LPCWSTR drive)
{
	this->_fat = 0;
	this->_sizeFat = 0;
	this->_sizeBootSector = 0;
	this->_fatLocation = 0;
	this->_dataLocation = 0;
	int readPoint = 0;

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
		for (int i = 0; i < 29; i++)
		{
			cur = "";

			for (int j = 0; j < _fat32[i]; j++)
			{
				switch (i)
				{
				case 26:
					cur = cur + (char)sector[k];
					break;
				case 2: case 3: case 4: case 5: case 13: case 14: case 17: case 18: case 19:
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
			case 4:
				this->_sizeBootSector = hexToDec(cur);
				break;
			case 5:
				this->_fat = hexToDec(cur);
				break;
			case 13:
				this->_sizeVolume = hexToDec(cur);
				break;
			case 14:
				this->_sizeFat = (hexToDec(cur));
				break;
				//case 17:
				//    //cout << "Cluster bat dau cua RDET: " << hexToDec(cur) << endl;
				//    break;
				//case 18:
				//    //cout << "Sector chua thong tin phu (ve cluster trong), thuong la 1: " << hexToDec(cur) << endl;
				//    break;
				//case 19:
				//    //cout << "Sector chua ban luu cua Boot Sector: " << hexToDec(cur) << endl;
				//    break;
			case 26:
				this->_typeFat = cur;
				break;
			}

		}

		this->_dataLocation = this->_sizeBootSector + this->_fat * this->_sizeFat;
		this->_fatLocation = this->_sizeBootSector;
	}
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



void FAT32::xuat()
{
	cout << "Loai FAT: " << this->_typeFat << endl;
	cout << "So byte cho 1 sector: " << this->_sizeSector << endl;
	cout << "So sector cho 1 cluster: " << this->_sizeCluster << endl;
	cout << "So sector danh rieng (so sector vung Bootsector): " << this->_sizeBootSector << endl;
	cout << "So bang FAT: " << this->_fat << endl;
	cout << "Tong so sector tren dia: " << this->_sizeVolume << endl;
	cout << "So sector cho 1 bang FAT: " << this->_sizeFat << endl;
	cout << "Sector dau tien cua bang FAT1: " << this->_fatLocation << endl;
	cout << "Sector dau tien cua bang RDET: " << this->_dataLocation << endl;
	cout << "Sector dau tien cua vung data: " << this->_dataLocation << endl;


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
