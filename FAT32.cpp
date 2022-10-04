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

string hexToASCII(string hex)
{
	// initialize the ASCII code string as empty.
	string ascii = "";
	for (size_t i = 0; i < hex.length(); i += 2)
	{
		// extract two characters from hex string
		string part = hex.substr(i, 2);

		// change it into base 16 and
		// typecast as the character
		char ch = stoul(part, nullptr, 16);

		// add this char to final ASCII string
		ascii += ch;
	}
	return ascii;
}

int readSector(LPCWSTR drive, int readPoint, BYTE sector[512])
{
	

	DWORD bytesRead;
	HANDLE device = NULL;

    device = CreateFile(drive,              // Drive to open
		GENERIC_READ,                       // Access mode
		FILE_SHARE_READ | FILE_SHARE_WRITE, // Share Mode
	    NULL,                               // Security Descriptor
        OPEN_EXISTING,                      // How to 
		0,                                  // File attributes
	    NULL);                              // Handle to template
	
    if (device == INVALID_HANDLE_VALUE) // Open 
	{
		printf("CreateFile: %u\n", GetLastError());
		return 0;
	}

	SetFilePointer(device, readPoint, NULL, FILE_BEGIN); // Set a Point to Read	
    
	if (!ReadFile(device, sector, 512, &bytesRead, NULL))
	{
	    printf("ReadFile: %u\n", GetLastError());
		return 0;	    
	}
	else
	{
		printf("ReadSuccess\n");
		return 1;
	}
}

FAT32::FAT32(LPCWSTR drive)
{
	this->_fat = 0;
	this->_sizeFat = 0;
	this->_sizeBootSector = 0;
	this->_fatLocation = 0;
	this->_dataLocation = 0;

	long long readPoint = 0;
	
	BYTE sector[512];

	readSector(drive, readPoint, sector);

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
		case 26:
			this->_typeFat = cur;
			break;
		}

	}

	this->_dataLocation = this->_sizeBootSector + this->_fat * this->_sizeFat;
	this->_fatLocation = this->_sizeBootSector;

	Sleep(3000);
	
	
	readPoint = this->_fatLocation * this->_sizeSector;
	//cout << readPoint << endl;

	for (int i = 0; i < this->_sizeFat; i++)
	{
		readPoint += i * this->_sizeSector;
		readSector(drive, readPoint, sector);
		for (int j = 0; j < 512; j += 4)
		{
			if (j != 0 && j % 16 == 0)
			{
				cout << endl;
			}

			 //cout << toHex(sector[j + 3]) + toHex(sector[j + 2]) + toHex(sector[j + 1]) + toHex(sector[j]) << " ";

			if (j / 4 > 2)
			{
				int readPointCluster = this->_dataLocation * this->_sizeSector;
				BYTE sector1[512];

				readSector(drive, readPointCluster, sector1);

				for (int k = 0; k < 512; k++)
				{
					if (k != 0 && k % 16 == 0)
					{
						cout << endl;
					}
					cout << (char)sector1[k] << " ";

				}
				return;
			}
		}

		break;
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
