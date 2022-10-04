#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;
struct FAT32_BOOT {
    BYTE JMP_instruction[3];
    char OEM_name[8];
    int bytes_per_sector;
    int sectors_per_cluster;
    int reserved_sectors; 
    int num_FATs;
    BYTE media; //Loai volume
    int sectors_per_track;
    int num_heads;
    int hidden_sectors; //So sector an truoc volume
    int total_sectors; 
    int sectors_per_FAT;
    int root_cluster;
    char FilSysType[8];
    BYTE drive_num;
};
struct NTFS_BOOT {
    BYTE JMP_instruction[3];
    char OEM_name[8];
    int bytes_per_sector;
    int sectors_per_cluster;
    BYTE media; //Loai volume
    int sectors_per_track;
    int num_heads;
    int hidden_sectors; //So sector an truoc volume
    int total_sectors;
    int MTF_clusterr;
    int MFTMirr_cluster;
    int clusters_per_fileRecSeg;
    int clusters_per_indexBlock;
    BYTE volume_serial[8];
    int checksum;
};
char* getbits(BYTE x)
{
    char* s=new char[8];
    for (int i = 7; i >= 0; i--)
        s[7-i] = (x & (1 << i)) ? 1 : 0;
    return s;
}
int BinToDec(char s[],int size)
{
    int res = 0;
    for (int i = 0; i < size; i++)
    {
        if((int)s[i]==1)
            res += pow(2, size - 1 - i);
    }
    return res;
}
int getReverseBytes(BYTE sector[512], int index_start, int num_bytes)
{
    char* bit = new char[num_bytes*8];
    
    bit = getbits(sector[index_start+num_bytes-1]);
    for (int i = 1; i < num_bytes; i++)
    {
        char* t = new char[8];
        t = getbits(sector[index_start+num_bytes-1-i]);
        for (int j = 0; j < 8; j++)
            bit[i*8 + j] = t[j];
    }
    return BinToDec(bit, num_bytes*8);
}
int ReadSector(LPCWSTR drive, int readPoint, BYTE sector[512])
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
        printf("Success!\n");
    }
}

FAT32_BOOT ReadHeadBootSectorFAT32(BYTE sector[512])
{
    FAT32_BOOT FAT32;
    for (int i = 0; i < 3; i++)
        FAT32.JMP_instruction[i] = sector[i];
    for (int i = 3; i < 11; i++)
    {
        FAT32.OEM_name[i - 3] = (char)sector[i];
    }
    FAT32.bytes_per_sector = getReverseBytes(sector, 11, 2);
    FAT32.sectors_per_cluster = sector[13];
    FAT32.num_FATs = sector[16];
    FAT32.media = sector[21];
    FAT32.sectors_per_track = getReverseBytes(sector, 24, 2);
    FAT32.num_heads = getReverseBytes(sector, 26, 2);
    FAT32.hidden_sectors = getReverseBytes(sector, 28, 4);
    FAT32.total_sectors = getReverseBytes(sector, 32, 4);
    FAT32.sectors_per_FAT = getReverseBytes(sector, 36, 2);
    FAT32.root_cluster = getReverseBytes(sector, 44, 4);
    for (int i = 82; i < 90; i++)
    {
        FAT32.FilSysType[i - 82] = (char)sector[i];
    }
    FAT32.drive_num = sector[64];
    return FAT32;
    
}
void PrintInformationVolumeFAT32(FAT32_BOOT FAT32)
{
    cout << "Lenh nhay den dau bootsector: ";
    for (int i = 0; i < 3; i++)
        cout << (int)FAT32.JMP_instruction[i];
    cout << endl;
    cout << "Ten cong ty/version cua he dieu hanh: ";
    for (int i = 0; i < 8; i++)
        cout << FAT32.OEM_name[i];
    cout << endl;
    cout << "So bytes/sector: " << FAT32.bytes_per_sector << endl;
    cout << "So sectors/cluster: " << FAT32.sectors_per_cluster << endl;
    cout << "So sector truoc bang FAT: " << FAT32.reserved_sectors << endl;
    cout << "So bang FAT: " << FAT32.num_FATs << endl;
    cout << "Loai volume: ";
    printf("%.4X", FAT32.media);
    cout << endl;
    cout << "So sector/track: " << FAT32.sectors_per_track << endl;
    cout << "So heads: " << FAT32.num_heads << endl;
    cout << "So sector an truoc volume: " << FAT32.hidden_sectors << endl;
    cout << "Tong so sector: " << FAT32.total_sectors << endl;
    cout << "So sector moi bang FAT: " << FAT32.sectors_per_FAT << endl;
    cout << "Chi so cluster bat dau cua bang RDET: " << FAT32.root_cluster << endl;
    cout << "Loai FAT: ";
    for (int i = 0; i < 8; i++)
        cout << FAT32.FilSysType[i];
    cout << endl;
    cout << "Ky hieu vat ly dia: ";
    printf("%.4X", FAT32.drive_num);
    if (FAT32.drive_num == 0x80)
        cout << " Hard disk" << endl;
    else cout << " Floppy disk" << endl;
}

NTFS_BOOT ReadPartitionBootSectorNTFS(BYTE sector[512])
{
    NTFS_BOOT NTFS;
    for (int i = 0; i < 3; i++)
        NTFS.JMP_instruction[i] = sector[i];
    for (int i = 3; i < 11; i++)
    {
        NTFS.OEM_name[i - 3] = (char)sector[i];
    }
    NTFS.bytes_per_sector = getReverseBytes(sector, 11, 2);
    NTFS.sectors_per_cluster = sector[13];
    NTFS.media = sector[21];
    NTFS.sectors_per_track = getReverseBytes(sector, 24, 2);
    NTFS.num_heads = getReverseBytes(sector, 26, 2);
    NTFS.hidden_sectors = getReverseBytes(sector, 28, 4);
    NTFS.total_sectors = getReverseBytes(sector, 40, 8);
    NTFS.MTF_clusterr = getReverseBytes(sector, 48, 8);
    NTFS.MFTMirr_cluster = getReverseBytes(sector, 56, 8);
    NTFS.clusters_per_fileRecSeg = getReverseBytes(sector, 64, 4);
    NTFS.clusters_per_indexBlock = getReverseBytes(sector, 68, 4);
    for (int i = 72; i < 80; i++)
        NTFS.volume_serial[i - 72] = sector[i];
    NTFS.checksum = getReverseBytes(sector, 80, 4);
    return NTFS;
}
void PrintInformationVolumeNTFS(NTFS_BOOT NTFS)
{
    cout << "Lenh nhay den dau bootsector: ";
    for (int i = 0; i < 3; i++)
        cout << (int)NTFS.JMP_instruction[i];
    cout << endl;
    cout << "Ten cong ty/version cua he dieu hanh: ";
    for (int i = 0; i < 8; i++)
        cout << NTFS.OEM_name[i];
    cout << endl;
    cout << "So bytes/sector: " << NTFS.bytes_per_sector << endl;
    cout << "So sectors/cluster: " << NTFS.sectors_per_cluster << endl;
    cout << "Loai volume: ";
    printf("%.4X", NTFS.media);
    cout << endl;
    cout << "So sector/track: " << NTFS.sectors_per_track << endl;
    cout << "So heads: " << NTFS.num_heads << endl;
    cout << "So sector an truoc volume/ sector bat dau cua o dia logic: " << NTFS.hidden_sectors << endl;
    cout << "Tong so sector: " << NTFS.total_sectors << endl;
    cout << "Cluster bat dau cua MFT: " << NTFS.MTF_clusterr << endl;
    cout << "Cluster bat dau cua MFT du phong: " << NTFS.MFTMirr_cluster << endl;
    cout << "Kich thuoc mot ban ghi trong MFT (MFT entry): " << NTFS.clusters_per_fileRecSeg << endl;
    cout << "So cluster cua index buffer: " << NTFS.clusters_per_indexBlock << endl;
    cout << "So seri cua o dia: ";
    for (int i = 0; i < 8; i++) 
        printf("%.X", NTFS.volume_serial[i]);
    cout << endl;
    cout << "Checksum: " << NTFS.checksum << endl;
}

int main(int argc, char** argv)
{
    BYTE sector[512];
    FAT32_BOOT fat32;
    NTFS_BOOT ntfs;
    ReadSector(L"\\\\.\\F:", 0, sector);
    //cout << (int)sector[11] << endl;
    //fat32 = ReadHeadBootSectorFAT32(sector);
    //PrintInformationVolumeFAT32(fat32);
    //ReadSector(L"\\\.\\F", fat32.bytes_per_sector * fat32.sectors_per_cluster * fat32.root_cluster, sector);
    ntfs = ReadPartitionBootSectorNTFS(sector);
    PrintInformationVolumeNTFS(ntfs);

}