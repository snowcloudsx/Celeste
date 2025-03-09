#include "Minecraft.h"
#include "../classes/classes.h"
c_minecraft::c_minecraft(jobject object_in) : c_jobject(object_in)
{

}

c_minecraft c_minecraft::get_minecraft() {
	static jmethodID getMCmethod = jvm::isForge() ? jvm::env->GetStaticMethodID(classes::minecraft_class, "func_71410_x", "()Lnet/minecraft/client/Minecraft;") :  !jvm::isForge() && jvm::env->FindClass("ave") == nullptr ? jvm::env->GetStaticMethodID(classes::minecraft_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;") : jvm::env->GetStaticMethodID(classes::minecraft_class, "A", "()Lave;"); // () + class name + | ()F


	return c_minecraft(jvm::env->CallStaticObjectMethod(classes::minecraft_class, getMCmethod));
}