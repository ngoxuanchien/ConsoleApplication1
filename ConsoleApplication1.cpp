#include "FAT32.h"

using namespace std;

//http://www.cs.rpi.edu/courses/fall01/os/ReadFile.html


//int ReadSectorNTFS(LPCWSTR drive, int readPoint, BYTE sector[512])
//{
//    DWORD bytesRead;
//    HANDLE device = NULL;
//
//    device = CreateFile(drive,              // Drive to open
//        GENERIC_READ,                       // Access mode
//        FILE_SHARE_READ | FILE_SHARE_WRITE, // Share Mode
//        NULL,                               // Security Descriptor
//        OPEN_EXISTING,                      // How to create
//        0,                                  // File attributes
//        NULL);                              // Handle to template
//
//    if (device == INVALID_HANDLE_VALUE) // Open Error
//    {
//        printf("CreateFile: %u\n", GetLastError());
//        return 1;
//    }
//
//    SetFilePointer(device, readPoint, NULL, FILE_BEGIN); // Set a Point to Read
//
//    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
//    {
//        printf("ReadFile: %u\n", GetLastError());
//    }
//    else
//    {
//        string cur = "";
//        int k = 11;
//        for (int i = 0; i < 22; i++)
//        {
//            cur = "";
//
//            for (int j = 0; j < _ntfs[i]; j++)
//            {
//
//                switch (i)
//                {
//                case 0: case 1: case 6: case 8: case 9: case 10: case 13: case 14: case 15: case 16: case 18: case 20:
//                    cur = toHex((int)sector[k]) + cur;
//                    break;
//                }
//
//                k++;
//            }
//
//            switch (i)
//            {
//            case 0: 
//                cout << "Kich thuoc mot sector: " << hexToDec(cur) << endl;
//                break;
//            case 1: 
//                cout << "So sector trong mot cluster: " << hexToDec(cur) << endl;
//                break;
//            case 6: 
//                cout << "Ma xac dinh loai dia: " << cur << endl;
//                break;
//            case 8:
//                cout << "So sector/track: " << hexToDec(cur) << endl;
//                break;
//            case 9:
//                cout << "So mat dia: " << hexToDec(cur) << endl;
//                break;
//            case 10: 
//                cout << "Sector bat dau cua o dia goc: " << hexToDec(cur) << endl;
//                break;
//            case 13: 
//                cout << "So sector cua o dia logic: " << hexToDec(cur) << endl;
//                break;
//            case 14: 
//                cout << "Cluster bat dau cua MFT: " << hexToDec(cur) << endl;
//                break;
//            case 15:
//                cout << "Cluster bat dau cua MFT du phong: " << hexToDec(cur) << endl;
//                break;
//            case 16:
//                cout << "Kich thuoc cua ban ghi trong MFT (MFT entry). don vi tinh la byte: " << hexToDec(cur) << endl;
//                break;
//            case 18: 
//                cout << "So cluster cua Index Bufffer: " << hexToDec(cur) << endl;
//                break;
//            case 20: 
//                cout << "So seri cua o dia: " << cur << endl;
//                break;
//            }
//        }
//    }
//    return 1;
//}

int main()
{
    FAT32 result(L"\\\\.\\D:");
    result.xuat();

    return 0;
}