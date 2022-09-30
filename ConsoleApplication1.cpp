#include <windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

#include <stdio.h>

void decToHexa(int n) { cout << hex << n; }

string list[17] = {"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F" };

int _fat32[] = { 3, 8, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2 };

constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

string toHex(int data)
{
    string result = "";

    //cout << data << endl;

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

int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512])
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFile(drive,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        return 1;
    }

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        int temp = (int)sector[19];
        //cout << setw(2) << setfill('0') << temp;
        
        //for (int i = 0; i < 17; i++)
        //{
        //    cout << list[i] << " ";
        //}
        //cout << endl;

        //for (int i = 0; i < 512; i++)
        //{
        //    if ((i + 1) % 17 == 0)
        //    {
        //        cout << endl;
        //    }
        //    else
        //    {
        //        //cout << (char)sector[i] << " ";
        //        cout << toHex((int)sector[i]) << " ";
        //        //cout << hex << setw(2) << setfill('0') << (int)sector[i] << " ";
        //    }
        //}
        int _index = 72;
        int _size = 8;

        for (int i = 0; i < _size; i++)
        {
            cout << toHex((int)sector[_index + i]) << " ";
        }

        //cout << setw(2) << setfill('0') << (int)sector[11] << " " << setw(2) << setfill('0') << (int)sector[12] << endl;
        //cout << toHex((int)sector[11]) << " " << toHex((int)sector[12]);
    }
    cout << endl;
}

int main(int argc, char** argv)
{

    BYTE sector[512];
    ReadSector(L"\\\\.\\E:",0, sector);
    return 0;
}