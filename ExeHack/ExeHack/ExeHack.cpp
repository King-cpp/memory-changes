// ExeHack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <processthreadsapi.h>
#include <winuser.h>
#include <handleapi.h>

void* pVirtualMem = nullptr;
DWORD GamePID = FALSE;
DWORD FreezeHack = FALSE;
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

template < class T >
void WriteValue(DWORD Addr, T* Value, size_t size)
{
    if (auto hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GamePID))
    {
        DWORD Old = 0;
        VirtualProtectEx(hProc, (void*)Addr, size, PAGE_EXECUTE_READWRITE, &Old);
        WriteProcessMemory(hProc, (void*)Addr, Value, size, nullptr);
        VirtualProtectEx(hProc, (void*)Addr, size, Old, &Old);
    }
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

bool LoopHack()
{
    if (GetAsyncKeyState(VK_F9))
    {        
        FreezeHack = !FreezeHack;
        WriteValue<DWORD>((DWORD)pVirtualMem, &FreezeHack, sizeof(FreezeHack)); //Altera diretamente na memoria alocada dentro do game o valor da boolean que ativa o hacker
        std::cout << "FreezeHack: " << (FreezeHack ? "Ativado" : "Desativado") << std::endl;        
    }
    return true;
}
int main()
{
    while (!GetWindowThreadProcessId(FindWindow(NULL, "Plants vs. Zombies"), &GamePID))
    {
        Sleep(1000);
        std::cout << "Game não encontrado!" << std::endl;
    }
    std::cout << ">>>> Game encontrado! <<<<" << std::endl;
    MainHack();
    while (LoopHack())Sleep(100);    
}