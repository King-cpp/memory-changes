#include "utilities.h"

void* pVirtualMem = nullptr;
DWORD FreezeHack = FALSE;
DWORD GamePID = FALSE;

BYTE BytesOpcode[] = {
    0x00, 0x00, 0x00, 0x00, //0 ~ 3 = BOOL para verificar o estado do hacker 
    0x83, 0x3D, 0xAC, 0x0F, //Esse opcode é basicamente o assembly, porem aqui há algumas coisas a considerar.
    0x63, 0x00, 0x01, 0x74, //Como visto, em assembly é necessário definir o local de retorno em caso de hook's
    0x05, 0xFF, 0x47, 0x24, //Nesse caso eu faço um cast para definir
    0xEB, 0x07, 0x81, 0x47, //Uma coisa simples se torna chata simplesmente por ser em .exe, porem é bem útil entender isso
    0x24, 0xFF, 0xFF, 0x00, //Já que alguns antihackers fazem uma lógica similar para hookar api's dos app's abertos
    0x00, 0x8B, 0x47, 0x24,
    0x68, 0xC2, 0x58, 0x49,
    0x00, 0xC3
};

void ReadValue(DWORD Addr, void* Buffer, size_t size)
{
    if (auto hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GamePID))
    {
        ReadProcessMemory(hProc, (void*)Addr, Buffer, size, nullptr);
        CloseHandle(hProc);
    }
}

void WriteValue(DWORD Addr, void* pBuffer, size_t size)
{
    if (auto hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GamePID))
    {
        DWORD Old = 0;
        VirtualProtectEx(hProc, (void*)Addr, size, PAGE_EXECUTE_READWRITE, &Old);
        WriteProcessMemory(hProc, (void*)Addr, pBuffer, size, nullptr);
        VirtualProtectEx(hProc, (void*)Addr, size, Old, &Old);
        CloseHandle(hProc);
    }
}

int GetPointer(DWORD Addr, std::vector<int> vOffsets)
{
    if (!Addr) return FALSE;
    int pAddr = FALSE;
    ReadValue(Addr, &pAddr, sizeof(int));
    for (size_t i = 0; i < vOffsets.size(); i++)
    {
        pAddr += vOffsets[i];
        if (vOffsets[i] == vOffsets.back())
            return pAddr;
        ReadValue(pAddr, &pAddr, sizeof(int));
    }
    return pAddr;
}

void MainHack()
{
    if (auto hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GamePID))
    {
        if (pVirtualMem = VirtualAllocEx(hProc, nullptr, sizeof(BytesOpcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE)) //Aloca um bloco de memoria no game 
        {
            BYTE JmpOpcode[] = { 0x68, 0x00,0x00,0x00,0x00,0xC3 };

            *(DWORD*)&BytesOpcode[6] = (DWORD)pVirtualMem;
            *(DWORD*)&JmpOpcode[1] = (DWORD)pVirtualMem + 0x4;

            WriteProcessMemory(hProc, (void*)0x004958BC, &JmpOpcode, sizeof(JmpOpcode), nullptr);
            WriteProcessMemory(hProc, (void*)pVirtualMem, &BytesOpcode, sizeof(BytesOpcode), nullptr);
        }
        //Tudo que for alocação de memória que não fique em loop é feito aqui

        CloseHandle(hProc);
    }
}

