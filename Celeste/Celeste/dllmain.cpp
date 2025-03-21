
#include <Windows.h>
#include <jvm.h>
#include "me/snow/sdk/classes/classes.h"
#include "me/snow/sdk/minecraft/Minecraft.h"
#include "me/snow/gui/Hook.h"
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
        jclass test = nullptr;
        jvm::AssignClass("net.minecraft.client.Minecraft", test);

        if (jvm::env->GetStaticMethodID(test, "getInstance", "()Lnet/minecraft/client/Minecraft;") != nullptr) {
            classes::load1_24();
            SetConsoleTitle("Celeste b0.01 - Lunar 1.21.4 |  snow.rip ");



        }
        else {
            classes::loadLunar();
            SetConsoleTitle("Celeste b0.01 - Lunar 1.8.9 |  snow.rip ");


        }
    }
   


    if (Hook::init())
        goto _shutdown;



    while (!GetAsyncKeyState(VK_DELETE)) {


        std::cout << " Server Instance: " << c_minecraft::get_minecraft().getServerData().cached_object << "\n";


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

