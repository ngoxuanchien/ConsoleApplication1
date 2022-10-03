#include "Volume.h"

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
