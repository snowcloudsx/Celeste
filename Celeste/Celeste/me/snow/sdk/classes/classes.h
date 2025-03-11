#pragma once
#include <jni.h>
#include <vector>

namespace classes
{
	void load();

	void loadLunar();


	void load1_24();
	//classes

	inline jclass minecraft_class = nullptr;
	inline jclass LaunchWrapperClassLoaderClass = nullptr;
	inline jclass LaunchClass = nullptr;
	inline jclass snifferClassUwU = nullptr;


	//methods 

	inline jmethodID FindClassMethodID = nullptr;




	//fields

	inline jfieldID ClassLoaderFieldID = nullptr;



	//objects

	inline jobject ClassLoaderObject = nullptr;




}