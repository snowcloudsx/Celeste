
#include <Windows.h>
#include <jvm.h>
#include "me/snow/sdk/classes/classes.h"
#include "me/snow/sdk/minecraft/Minecraft.h"
#include <iostream>

void startThread(HMODULE mod) {
    FILE* buf = nullptr;
    AllocConsole();
    freopen_s(&buf, "CONOUT$", "w", stdout);


    


    jvm::load();

    if (jvm::env->FindClass("net/minecraftforge/common/ForgeVersion") != nullptr) {
        classes::load();
        SetConsoleTitle("Celeste b0.01 - forge 1.8.9 |  snow.rip ");
    }

    if (jvm::env->FindClass("ave") != nullptr && jvm::env->FindClass("net/minecraftforge/common/ForgeVersion") == nullptr) {
        classes::load();
        SetConsoleTitle("Celeste b0.01 - Vanilla 1.8.9 |  snow.rip ");
    }

    else if(jvm::env->FindClass("ave") == nullptr && jvm::env->FindClass("net/minecraftforge/common/ForgeVersion") == nullptr){
        classes::loadLunar();
        SetConsoleTitle("Celeste b0.01 - Lunar 1.8.9 |  snow.rip ");
    }
   //if (jvm::isLunar) {


   // }


    



    while (!GetAsyncKeyState(VK_END)) {
       
        std::cout << "Minecraft Instace: " << c_minecraft::get_minecraft().cached_object << "\n";


        Sleep(1000);


    }


    if (buf) {
        fclose(buf);
    }
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

