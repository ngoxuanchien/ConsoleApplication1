#include <windows.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

string list[17] = {"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F"};

int _fat32[29] = {3, 8, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 4, 4, 4, 2, 2, 4, 2, 2, 12, 1, 1, 1, 4, 11, 8, 420, 2};

constexpr char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

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

int ReadSector(LPCWSTR drive, int readPoint, BYTE sector[512])
{
    int retCode = 0;
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
        return 1;
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
                cout << "So byte tren sector: " << hexToDec(cur) << endl;
                break;
            case 3:
                cout << "So sector tren cluster: " << hexToDec(cur) << endl;
                break;
            case 4:
                cout << "So sector thuoc vung Bootsector (nhu FAT): " << hexToDec(cur) << endl;
                break;
            case 5:
                cout << "So bang FAT: " << hexToDec(cur) << endl;
                break;
            case 13:
                cout << cur << endl;
                cout << "Kich thuoc volume: " << hexToDec(cur) << endl;
                break;
            case 14:
                cout << "Kich thuoc moi bang FAT: " << hexToDec(cur) << endl;
                break;
            case 17:
                cout << "Cluster bat dau cua RDET: " << hexToDec(cur) << endl;
                break;
            case 18:
                cout << "Sector chua thong tin phu (ve cluster trong), thuong la 1: " << hexToDec(cur) << endl;
                break;
            case 19:
                cout << "Sector chua ban luu cua Boot Sector: " << hexToDec(cur) << endl;
                break;
            case 26:
                cout << "Loai FAT: " << cur << endl;
                break;
            }

        }

    }
}

int main(int argc, char **argv)
{
    BYTE sector[512];
    ReadSector(L"\\\\.\\E:", 0, sector);
    return 0;
}
