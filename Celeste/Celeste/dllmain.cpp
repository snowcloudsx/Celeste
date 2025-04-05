
#include <Windows.h>
#include <jvm.h>
#include "me/snow/sdk/classes/classes.h"
#include "me/snow/sdk/minecraft/Minecraft.h"
#include "me/snow/gui/Hook.h"
#include <iostream>
#include "includes/MinHook.h"
#include "me/snow/eventbus/eventbus.h"
#include "includes/ImGui/imgui.h"
#include "includes/Fonts/icons.h"
#include "includes/Fonts/mFont.h"
#include <io.h>

typedef BOOL(WINAPI* tWriteConsoleA)(HANDLE, const VOID*, DWORD, LPDWORD, LPVOID);
tWriteConsoleA oWriteConsoleA = nullptr;

BOOL WINAPI hkWriteConsoleA(HANDLE hConsoleOutput, const VOID* lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved) {
    // Check if the output contains log-like strings (e.g., "Saving world")
    const char* buffer = (const char*)lpBuffer;
    if (strstr(buffer, "Saving world") || strstr(buffer, "[INFO]")) {
        *lpNumberOfCharsWritten = nNumberOfCharsToWrite; // Pretend it wrote successfully
        return TRUE; // Silently discard
    }
    return oWriteConsoleA(hConsoleOutput, lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten, lpReserved);
}

void InitializeHook() {
    MH_Initialize();
    MH_CreateHookApi(L"kernel32.dll", "WriteConsoleA", &hkWriteConsoleA, (LPVOID*)&oWriteConsoleA);
    MH_EnableHook(MH_ALL_HOOKS);
}

void startThread(HMODULE mod) {
    

    FILE* buf = nullptr;
    AllocConsole();
    freopen_s(&buf, "CONOUT$", "w", stdout);



    jvm::load();
    

   jvm::setTitleAndMappings();



    if (Hook::init())
        goto _shutdown;


    while (!GetAsyncKeyState(VK_END)) {


        InitializeHook();

        CheckForKeys();
        Sleep(1000);


    }


    if (buf) {
        fclose(buf);
    }

  
    _shutdown:
        Hook::shutdown();
    
    FreeConsole();
    FreeLibraryAndExitThread(mod, 0ul);




}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
   
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        HANDLE thread_handle = CreateThread(nullptr, 0ull, reinterpret_cast<LPTHREAD_START_ROUTINE>(startThread), hModule, 0ul, nullptr);

        if (thread_handle && thread_handle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(thread_handle);
        }

        break;
    }

    return TRUE;
}


//Here lies the test commit
