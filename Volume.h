#pragma once
#include <string>

using namespace std;

class Volume
{
protected:
    long long _sizeSector;
    long long _sizeCluster;
    long long _sizeVolume;
    


public:
    Volume();
    ~Volume();
    void setSizeSector(const long long&);
    void setSizeCluster(const long long&);
    void setSizeVolume(const long long&);
 
    long long getSizeSector();
    long long getSizeCluster();
    long long getSizeVolume();
    long long hexToDec(string);
    string toHex(int);
};



