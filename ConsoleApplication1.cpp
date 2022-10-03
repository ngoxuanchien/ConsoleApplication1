#include <windows.h>
#include <iostream>
#include <iomanip>
#include "FAT32.h"

using namespace std;

//http://www.cs.rpi.edu/courses/fall01/os/ReadFile.html

string list[17] = {"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F"};
int _fat32[29] = {3, 8, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 4, 4, 4, 2, 2, 4, 2, 2, 12, 1, 1, 1, 4, 11, 8, 420, 2};
int _ntfs[22] = { 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 4, 4, 4, 8, 8, 8, 1, 3, 1, 3, 8, 4 };
char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

string toHex(int data)
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

long long hexToDec(string data)
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

FAT32 ReadSectorFAT32(LPCWSTR drive, long long readPoint, BYTE sector[512])
{
    FAT32 result;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFile(drive,                              // Drive to open
                        GENERIC_READ,                       // Access mode
                        FILE_SHARE_READ | FILE_SHARE_WRITE, // Share Mode
                        NULL,                               // Security Descriptor
                        OPEN_EXISTING,                      // How to create
                        0,                                  // File attributes
                        NULL);                              // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        return result;
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
                result.setSizeSector(hexToDec(cur));
                //cout << "So byte tren sector: " << result.getSizeSector() << endl;
                break;
            case 3:
                result.setSizeCluster(hexToDec(cur));
                //cout << "So sector tren cluster: " << result.getSizeCluster() << endl;
                break;
            case 4:
                result.setSizeBootSector(hexToDec(cur));
                //cout << "So sector thuoc vung Bootsector (nhu FAT): " << result.getSizeBootSector() << endl;
                break;
            case 5:
                result.setFAT(hexToDec(cur));
                //cout << "So bang FAT: " << result.getFAT() << endl;
                break;
            case 13:
                result.setSizeVolume(hexToDec(cur));
                //cout << "Kich thuoc volume: " << result.getSizeVolume() << endl;
                break;
            case 14:
                result.setSizeFAT(hexToDec(cur));
                //cout << "Kich thuoc moi bang FAT: " << result.getSizeFAT() << endl;
                break;
            case 17:
                //cout << "Cluster bat dau cua RDET: " << hexToDec(cur) << endl;
                break;
            case 18:
                //cout << "Sector chua thong tin phu (ve cluster trong), thuong la 1: " << hexToDec(cur) << endl;
                break;
            case 19:
                //cout << "Sector chua ban luu cua Boot Sector: " << hexToDec(cur) << endl;
                break;
            case 26:
                result.setTypeFAT(cur);
                //cout << "Loai FAT: " << cur << endl;
                break;
            }

        }

        result.setDataLocation(result.getSizeBootSector() + result.getFAT() * result.getSizeFAT());
        result.setFatLocation(result.getSizeBootSector());
    }

    readPoint = result.getDataLocaiton() * result.getSizeSector();
    
    int k = 0;
    while (readPoint < result.getSizeVolume() * result.getSizeSector())
    {
        //k++;
        SetFilePointer(device, readPoint, NULL, FILE_BEGIN);
        //cout << result.getSizeVolume() * result.getSizeSector() << endl;

        if (!ReadFile(device, sector, 512, &bytesRead, NULL))
        {
            printf("ReadFile: %u\n", GetLastError());
        }
        else
        {
            /*for (int i = 0; i < 512; i++)
            {
                if ((i + 1) % 16 == 0)
                {
                    if ((i + 1) % 32 == 0)
                    {
                        cout << endl;
                    }
                    cout << endl;
                }
                else
                {
                    cout << (char)sector[i] << " ";
                }
                
            }*/

            string cur = "";
            for (int i = 0; i < 512; i += 32)
            {
                //cout << toHex(sector[i + 11]) << endl;
                
                if (toHex(sector[i + 11]).compare("0F") == 0)
                {
                    cur = "";
                    //cout << 1;
                    for (int j = i + 1; j < i + 11; j++)
                    {
                        cur = cur + (char)sector[j];
                    }

                    for (int j = i + 14; j < i + 26; j++)
                    {
                        cur = cur + (char)sector[j];
                    }

                    for (int j = i + 28; j < i + 32; j++)
                    {
                        cur = cur + (char)sector[j];
                    }
                    result.addFile(cur);
                }
                else if (toHex(sector[i + 11]).compare("20") == 0)
                {
                    cur = "";
                    for (int j = i; j < i + 11; j++)
                    {
                        cur = cur + (char)sector[j];
                    }
                    result.addFile(cur);
                }
                
            }
          /*  cout << endl;
            cout << dem << endl;*/
        }

        readPoint += 512 * result.getSizeSector();
        //return result;
    }

    return result;
}

int ReadSectorNTFS(LPCWSTR drive, int readPoint, BYTE sector[512])
{
    DWORD bytesRead;
    HANDLE device = NULL;

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
        return 1;
    }

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN); // Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        string cur = "";
        int k = 11;
        for (int i = 0; i < 22; i++)
        {
            cur = "";

            for (int j = 0; j < _ntfs[i]; j++)
            {

                switch (i)
                {
                case 0: case 1: case 6: case 8: case 9: case 10: case 13: case 14: case 15: case 16: case 18: case 20:
                    cur = toHex((int)sector[k]) + cur;
                    break;
                }

                k++;
            }

            switch (i)
            {
            case 0: 
                cout << "Kich thuoc mot sector: " << hexToDec(cur) << endl;
                break;
            case 1: 
                cout << "So sector trong mot cluster: " << hexToDec(cur) << endl;
                break;
            case 6: 
                cout << "Ma xac dinh loai dia: " << cur << endl;
                break;
            case 8:
                cout << "So sector/track: " << hexToDec(cur) << endl;
                break;
            case 9:
                cout << "So mat dia: " << hexToDec(cur) << endl;
                break;
            case 10: 
                cout << "Sector bat dau cua o dia goc: " << hexToDec(cur) << endl;
                break;
            case 13: 
                cout << "So sector cua o dia logic: " << hexToDec(cur) << endl;
                break;
            case 14: 
                cout << "Cluster bat dau cua MFT: " << hexToDec(cur) << endl;
                break;
            case 15:
                cout << "Cluster bat dau cua MFT du phong: " << hexToDec(cur) << endl;
                break;
            case 16:
                cout << "Kich thuoc cua ban ghi trong MFT (MFT entry). don vi tinh la byte: " << hexToDec(cur) << endl;
                break;
            case 18: 
                cout << "So cluster cua Index Bufffer: " << hexToDec(cur) << endl;
                break;
            case 20: 
                cout << "So seri cua o dia: " << cur << endl;
                break;
            }
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    BYTE sector[512];
    FAT32 result = ReadSectorFAT32(L"\\\\.\\D:", 0, sector);
    result.xuat();
    //cout << endl;
    //ReadSectorNTFS(L"\\\\.\\E:", 0, sector);
    //cout << hexToDec("50");

    
    return 0;
}
