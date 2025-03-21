#include "Minecraft.h"
#include "../classes/classes.h"
c_minecraft::c_minecraft(jobject object_in) : c_jobject(object_in)
{

}

c_minecraft c_minecraft::get_minecraft() {
	static jmethodID getMCmethod = nullptr;

	getMCmethod = jvm::isForge() ? jvm::env->GetStaticMethodID(classes::minecraft_class, "func_71410_x", "()Lnet/minecraft/client/Minecraft;") :  !jvm::isForge() && jvm::env->FindClass("ave") == nullptr ? jvm::env->GetStaticMethodID(classes::minecraft_class, "getInstance", "()Lnet/minecraft/client/Minecraft;") : jvm::env->GetStaticMethodID(classes::minecraft_class, "A", "()Lave;"); // () + class name + | ()F
	if (getMCmethod == nullptr) {
		getMCmethod = jvm::env->GetStaticMethodID(classes::minecraft_class, "getInstance", "()Lnet/minecraft/client/Minecraft;");
	}


	return c_minecraft(jvm::env->CallStaticObjectMethod(classes::minecraft_class, getMCmethod));
}



c_entity c_minecraft::get_local_player()
{
	static jfieldID thePlayerField = nullptr;
	thePlayerField = jvm::isForge() ? jvm::env->GetFieldID(classes::minecraft_class, "field_71439_g", "Lnet.minecraft.client.entity;") : !jvm::isForge() && jvm::env->FindClass("ave") == nullptr ? jvm::env->GetFieldID(classes::minecraft_class, "thePlayer", "Lnet.minecraft.client.entity;") : jvm::env->GetFieldID(classes::minecraft_class, "h", "Lbew;");
	if (thePlayerField == nullptr) {
		thePlayerField = jvm::env->GetFieldID(classes::minecraft_class, "player", "Lnet.minecraft.client.entity;");
	}


	return c_entity(jvm::env->GetObjectField(this->cached_object, thePlayerField));
}

c_server c_minecraft::getServerData()
{
	static jfieldID serverdataField = nullptr;
	serverdataField = jvm::env->GetFieldID(classes::minecraft_class, "currentServerData", "Lnet.minecraft.client.multiplayer.ServerData;");

	return c_server(jvm::env->GetObjectField(this->cached_object, serverdataField));
}