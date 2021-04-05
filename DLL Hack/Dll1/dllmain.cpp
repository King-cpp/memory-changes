// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <string>
#include <iostream>
#include <vector>
#include <thread>
void HookFunc(DWORD NewFunc, DWORD LocalAddr)
{
	DWORD Old;

	VirtualProtect((void*)LocalAddr, 5, PAGE_EXECUTE_READWRITE, &Old);
	*(BYTE*)(LocalAddr) = 0xE9;
	*(DWORD*)(LocalAddr + 1) = NewFunc - LocalAddr - 5;
	VirtualProtect((void*)LocalAddr, 5, Old, &Old);
}

template < class T >
void WriteValue(DWORD Addr, T Value)
{
	DWORD Old;
	VirtualProtect((void*)Addr, sizeof(T), PAGE_EXECUTE_READWRITE, &Old);
	*(T*)(Addr) = Value;
	VirtualProtect((void*)Addr, sizeof(T), Old, &Old);
}

DWORD PtrSun = 0;
DWORD GetPtrSun = 0;
DWORD BaseAddr = 0;
DWORD ReturnFreeze = 0;
BOOL  FreezeHack = FALSE;
BOOL  FreezeSun = FALSE;
void __declspec(naked) HookFreezeTime()
{
	__asm
	{
		CMP FreezeHack, 1
		JE Hack
		INC DWORD PTR DS : [EDI + 0x24]
		JMP Retorno
		Hack :
		ADD DWORD PTR DS : [EDI + 0x24] , 0xFFFF
			Retorno :
			MOV EAX, DWORD PTR DS : [EDI + 0x24]
			JMP ReturnFreeze
	}
}

void __declspec(naked) HookGetPtrSun()
{
	__asm
	{
		MOV PtrSun, EAX
		add dword ptr ds : [eax + 0x00005578] , ecx
		JMP GetPtrSun
	}
}

int* GetPointer(int Addr, std::vector<int> vOffets)
{
	if (!Addr) return nullptr;

	if (auto pAddrBase = (int*)Addr)
	{
		for (int& Offset : vOffets)
		{
			if (!*pAddrBase) return nullptr;

			pAddrBase = (int*)(*pAddrBase + Offset);
		}
		return pAddrBase;
	}
	return nullptr;
}
struct sPlants
{
	char Unk[0x5578];
	int Sun;

};

struct sGetPlants
{
	char Unk[0x868];
	sPlants* pPlants;
};

void ThreadKey()
{
	while (true)
	{
		Sleep(100);
		if (GetAsyncKeyState(VK_F9))
		{
			FreezeHack = !FreezeHack;
			std::cout << "Freeze Hack: " << ((FreezeHack) ? "Ativado" : "Desativado") << std::endl;
		}

		if (GetAsyncKeyState(VK_F10))
		{
			FreezeSun = !FreezeSun;
			WriteValue<short>(BaseAddr + 0x1F4E5, (FreezeSun) ? 0x9090 : 0x0A7E);
			std::cout << "Freeze Sun 9990: " << ((FreezeSun) ? "Ativado" : "Desativado") << std::endl;
		}

		if (GetAsyncKeyState(VK_F11))
		{
			if (sGetPlants* pGetPlants = (sGetPlants*)*(int*)0x00731C50)
			{
				pGetPlants->pPlants->Sun += 1000;
				std::cout << "Sun: +1000" << std::endl;
			}
		}
	}
}

void allocConsole()
{
	AllocConsole();

	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

	std::cout << "By Printa" << std::endl;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		BaseAddr = (DWORD)GetModuleHandle("popcapgame1.exe");
		ReturnFreeze = BaseAddr + 0x958C2;
		GetPtrSun = BaseAddr + 0x1F4D6;
		HookFunc((DWORD)HookFreezeTime, BaseAddr + 0x958BC);
		//HookFunc((DWORD)HookGetPtrSun, BaseAddr + 0x1F4D0);		
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)allocConsole, 0, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadKey, 0, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

