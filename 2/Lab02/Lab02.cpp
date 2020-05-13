#include <cstdlib>
#include <clocale>
#include <cstdio>
#include <windows.h>
#include <tchar.h>
#include <iostream>

BOOL FindFileByClaster(TCHAR* volume, LONGLONG cluster) {

    HANDLE hDevice = CreateFile(volume,      // drive to open
        GENERIC_READ,                       // access to the drive
        FILE_SHARE_READ | FILE_SHARE_WRITE,  // share mode
        NULL,                                // default security attributes
        OPEN_EXISTING,                       // disposition
        FILE_FLAG_BACKUP_SEMANTICS,          // file attributes
        NULL);

    if (hDevice == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    LOOKUP_STREAM_FROM_CLUSTER_INPUT input = { 0 };
    input.NumberOfClusters = 1;
    input.Cluster[0].QuadPart = cluster;

    BYTE output[5000] = {};
    DWORD dwRes = 0;
    LOOKUP_STREAM_FROM_CLUSTER_OUTPUT result = { 0 };

    BOOL bRes = DeviceIoControl((HANDLE)hDevice,   // handle to file, directory, or volume 
        FSCTL_LOOKUP_STREAM_FROM_CLUSTER, // dwIoControlCode
        (LPVOID)&input,        // input buffer 
        (DWORD)sizeof(input),     // size of input buffer 
        (LPVOID)output,       // output buffer 
        (DWORD)5000,    // size of output buffer 
        (LPDWORD)&dwRes,   // number of bytes returned 
        NULL);    // OVERLAPPED structure

    if (bRes == FALSE) {
        return FALSE;
    }

    memcpy(&result, output, sizeof(LOOKUP_STREAM_FROM_CLUSTER_OUTPUT));

    if (result.NumberOfMatches == 0) {
        wprintf(L"Файл не найден\n");
        return FALSE;
    }

    wprintf(L"Информация о файле\n");

    BYTE* p = (BYTE*)output + result.Offset;
    LOOKUP_STREAM_FROM_CLUSTER_ENTRY* pentry = (LOOKUP_STREAM_FROM_CLUSTER_ENTRY*)p;

    wprintf(L"Flags: 0x%x ", (UINT)pentry->Flags);

    if ((pentry->Flags & LOOKUP_STREAM_FROM_CLUSTER_ENTRY_FLAG_PAGE_FILE) > 0) wprintf(L"(Pagefile)");
    else if ((pentry->Flags & LOOKUP_STREAM_FROM_CLUSTER_ENTRY_FLAG_FS_SYSTEM_FILE) > 0)  wprintf(L"(Internal filesystem file)");
    else if ((pentry->Flags & LOOKUP_STREAM_FROM_CLUSTER_ENTRY_FLAG_TXF_SYSTEM_FILE) > 0) wprintf(L"(Internal TXF file)");
    else wprintf(L"(Normal file)");

    wprintf(L"\nFile: %s\n", pentry->FileName);
    return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "Russian");

    LONGLONG inp = 0;
    wprintf(L"Введите номер кластера: \n");
    scanf_s("%llu", &inp);

    FindFileByClaster((TCHAR*)L"\\\\.\\D:", inp);

    system("PAUSE");
    return 0;
}