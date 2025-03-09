#include "classes.h"

#include <jvm.h>


void classes::loadLunar()
{
    jvm::AssignClass("net.minecraft.client.Minecraft", classes::minecraft_class);

}

void classes::load()
{

    
	minecraft_class = jvm::isForge() ? jvm::ForgeFindClass("net.minecraft.client.Minecraft") : jvm::env->FindClass("ave");


}
