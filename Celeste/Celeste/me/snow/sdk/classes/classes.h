#pragma once
#include <jni.h>
#include <vector>

namespace classes
{
	void load();

	void loadLunar();
	//classes

	inline jclass minecraft_class = nullptr;
	inline jclass LaunchWrapperClassLoaderClass = nullptr;
	inline jclass LaunchClass = nullptr;



	//methods 

	inline jmethodID FindClassMethodID = nullptr;




	//fields

	inline jfieldID ClassLoaderFieldID = nullptr;



	//objects

	inline jobject ClassLoaderObject = nullptr;




}