#pragma once
#include <jni.h>
#include <unordered_map>
#include <jvmti.h>
#include <string>


namespace jvm {
	void load();
	jvmtiEnv* jvenv;


	bool AssignClass(std::string name, jclass& out);
	void setupClassLoader();

	jclass ForgeFindClass(const char* name);
	jclass LunarFindClass(const char* clsName, JNIEnv* env);
	bool isForge();
	bool isLunar = false;
	jclass findClass(JNIEnv* p_env, jvmtiEnv* p_tienv, const std::string& path);


	bool AlreadyCheckedForge;
	bool IsForgeExisting;


	inline JavaVM* vm = nullptr;
	inline JNIEnv* env = nullptr;



	// Attach to JVM
	static bool AttachToJVM();




	// Get Player Object
	jobject GetMinecraftPlayer();



	
}


class c_jobject
{
public:
	c_jobject(jobject object_in);
	~c_jobject();


	jobject cached_object = nullptr;
};