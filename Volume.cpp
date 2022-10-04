#include "Volume.h"

const int _ntfs[22] = { 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 4, 4, 4, 8, 8, 8, 1, 3, 1, 3, 8, 4 };
string list[16] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F" };
char hexmap[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

Volume::Volume()
{
	_sizeSector = 0;
	_sizeCluster = 0;
	_sizeVolume = 0;
}

Volume::~Volume()
{
	_sizeSector = 0;
	_sizeCluster = 0;
	_sizeVolume = 0;
}

void Volume::setSizeSector(const long long& data)
{
	this->_sizeSector = data;
}

void Volume::setSizeCluster(const long long& data)
{
	this->_sizeCluster = data;
}

void Volume::setSizeVolume(const long long& data)
{
	this->_sizeVolume = data;
}


long long Volume::getSizeSector()
{
	return this->_sizeSector;
}

long long Volume::getSizeCluster()
{
	return this->_sizeCluster;
}

long long Volume::getSizeVolume()
{
	return this->_sizeVolume;
}

string Volume::toHex(int data)
{
    string result = "";

    while (data > 0)
    {
        int cur = data % 16;
        result = hexmap[cur] + result;
        data = data / 16;
    }

    while (result.length() < 2)
    {
        result = "0" + result;
    }

    return result;
}

long long Volume::hexToDec(string data)
{
    long long result = 0;

    int len = data.length();
    int base = 1;
    for (int i = len - 1; i >= 0; i--)
    {
        if (data[i] >= '0' && data[i] <= '9')
        {
            result += ((int)data[i] - 48) * base;
            base *= 16;
        }
        else if (data[i] >= 'A' && data[i] <= 'F')
        {
            result += ((int)data[i] - 55) * base;
            base *= 16;
        }
    }

    return result;
}
