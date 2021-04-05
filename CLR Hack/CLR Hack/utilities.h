#pragma once
#include <Windows.h>
#include <vector>
extern DWORD FreezeHack;
extern DWORD GamePID;
extern BYTE BytesOpcode[];
extern void* pVirtualMem;

extern void MainHack();
extern void ReadValue(DWORD Addr, void* Buffer, size_t size);
extern void WriteValue(DWORD Addr, void* pBuffer, size_t size);
extern int	GetPointer(DWORD Addr, std::vector<int> vOffsets);



