#include "jvm.h"
#include <Windows.h>
#include "../sdk/classes/classes.h"
#include <iostream>



//super important class
void jvm::load() {
	JNI_GetCreatedJavaVMs(&vm, 1l, nullptr);
	//if statement 
	if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_8) == JNI_EDETACHED) {
		vm->AttachCurrentThreadAsDaemon(reinterpret_cast<void**>(&env), nullptr);

	}

	setupClassLoader();
}



void jvm::setTitleAndMappings()
{
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
}


jobject classLoader;
jmethodID mid_findClass;

void jvm::setupClassLoader()
{
	jclass c_Thread = jvm::env->FindClass("java/lang/Thread");
	jclass c_Map = jvm::env->FindClass("java/util/Map");
	jclass c_Set = jvm::env->FindClass("java/util/Set");
	jclass c_ClassLoader = jvm::env->FindClass("java/lang/ClassLoader");

	jmethodID mid_getAllStackTraces = jvm::env->GetStaticMethodID(c_Thread, "getAllStackTraces", "()Ljava/util/Map;");
	jmethodID mid_keySet = jvm::env->GetMethodID(c_Map, "keySet", "()Ljava/util/Set;");
	jmethodID mid_toArray = jvm::env->GetMethodID(c_Set, "toArray", "()[Ljava/lang/Object;");
	jmethodID mid_getContextClassLoader = jvm::env->GetMethodID(c_Thread, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
	mid_findClass = jvm::env->GetMethodID(c_ClassLoader, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	jmethodID mid_currentThread = jvm::env->GetStaticMethodID(c_Thread, "currentThread", "()Ljava/lang/Thread;");

	jobject obj_stackTracesMap = jvm::env->CallStaticObjectMethod(c_Thread, mid_getAllStackTraces);
	jobject obj_threadsSet = jvm::env->CallObjectMethod(obj_stackTracesMap, mid_keySet);

	jobjectArray threads = (jobjectArray)jvm::env->CallObjectMethod(obj_threadsSet, mid_toArray);
	jint szThreads = jvm::env->GetArrayLength(threads);

	for (int i = 0; i < szThreads; i++)
	{
		jobject thread = jvm::env->GetObjectArrayElement(threads, i);
		jobject classLoaderObj = jvm::env->CallObjectMethod(thread, mid_getContextClassLoader);

		if (classLoaderObj) {

			jstring className = jvm::env->NewStringUTF("net.minecraft.client.Minecraft");
			jobject minecraftClass = jvm::env->CallObjectMethod(classLoaderObj, mid_findClass, className);

			if (minecraftClass)
			{
				classLoader = classLoaderObj;

				jvm::env->DeleteLocalRef(minecraftClass);

				break;
			}
		}

		jvm::env->DeleteLocalRef(thread);
	}

	jvm::env->DeleteLocalRef(threads);
	jvm::env->DeleteLocalRef(obj_stackTracesMap);
	jvm::env->DeleteLocalRef(obj_threadsSet);
	jvm::env->DeleteLocalRef(c_Thread);
	jvm::env->DeleteLocalRef(c_Map);
	jvm::env->DeleteLocalRef(c_Set);
	jvm::env->DeleteLocalRef(c_ClassLoader);

}




bool jvm::AssignClass(std::string name, jclass& out)
{
	jstring className = jvm::env->NewStringUTF(name.c_str());
	jobject findClass = jvm::env->CallObjectMethod(classLoader, mid_findClass, className);

	if (findClass)
	{
		out = (jclass)findClass;
		return true;
	}

	return false;
}



jclass jvm::ForgeFindClass(const char* name)
{
	if (classes::LaunchWrapperClassLoaderClass == NULL)
	{
		classes::LaunchWrapperClassLoaderClass = jvm::env->FindClass("net/minecraft/launchwrapper/LaunchClassLoader");
		if (classes::LaunchWrapperClassLoaderClass == NULL) {
			printf("Launchwarpperclassloader error");
			return NULL;
		}
	}

	if (classes::FindClassMethodID == NULL)
	{
		classes::FindClassMethodID = jvm::env->GetMethodID(classes::LaunchWrapperClassLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
		if (classes::FindClassMethodID == NULL) { 
			printf("FindClassMethodID error");

			return NULL; }
	}

	if (classes::LaunchClass == NULL)
	{
		classes::LaunchClass = jvm::env->FindClass("net/minecraft/launchwrapper/Launch");
		if (classes::LaunchClass == NULL) return NULL;
	}

	if (classes::ClassLoaderFieldID == NULL)
	{
		classes::ClassLoaderFieldID = jvm::env->GetStaticFieldID(classes::LaunchClass, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
		if (classes::ClassLoaderFieldID == NULL) return NULL;
	}

	if (classes::ClassLoaderObject == NULL)
	{
		classes::ClassLoaderObject = jvm::env->GetStaticObjectField(classes::LaunchClass, classes::ClassLoaderFieldID);
		if (classes::ClassLoaderObject == NULL) return NULL;
	}

	jstring jname = jvm::env->NewStringUTF(name);
	jclass cls = (jclass)jvm::env->CallObjectMethod(classes::ClassLoaderObject, classes::FindClassMethodID, jname);

	jvm::env->DeleteLocalRef(jname);

	return cls;
}


jclass jvm::LunarFindClass(const char* clsName, JNIEnv* env)
{
	

	jclass thread_clazz = env->FindClass("java/lang/Thread");
	static jmethodID curthread_mid = env->GetStaticMethodID(thread_clazz, "currentThread", "()Ljava/lang/Thread;");
	jobject thread = env->CallStaticObjectMethod(thread_clazz, curthread_mid);
	jmethodID threadgroup_mid = env->GetMethodID(thread_clazz, "getThreadGroup", "()Ljava/lang/ThreadGroup;");
	jclass threadgroup_clazz = env->FindClass("java/lang/ThreadGroup");
	jobject threadgroup_obj = env->CallObjectMethod(thread, threadgroup_mid);
	jmethodID groupactivecount_mid = env->GetMethodID(threadgroup_clazz, "activeCount", "()I");
	jfieldID count_fid = env->GetFieldID(threadgroup_clazz, "nthreads", "I");
	jint activeCount = env->GetIntField(threadgroup_obj, count_fid);
	jobjectArray arrayD = env->NewObjectArray(activeCount, thread_clazz, NULL);
	jmethodID enumerate_mid = env->GetMethodID(threadgroup_clazz, "enumerate", "([Ljava/lang/Thread;)I");
	jint enumerate = env->CallIntMethod(threadgroup_obj, enumerate_mid, arrayD);
	jmethodID mid_getname = env->GetMethodID(thread_clazz, "getName", "()Ljava/lang/String;");
	jobject array_elements = env->GetObjectArrayElement(arrayD, 0);
	jmethodID threadclassloader = env->GetMethodID(thread_clazz, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
	if (threadclassloader != 0)
	{
		auto class_loader = env->CallObjectMethod(array_elements, threadclassloader);
		jclass launch_clazz = env->FindClass("net/minecraft/launchwrapper/Launch");
		jclass class_loader_class = env->GetObjectClass(class_loader);
		jmethodID find_class_id = env->GetMethodID(class_loader_class, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");

		env->DeleteLocalRef(launch_clazz);
		jstring name = env->NewStringUTF(clsName);

		jclass res = (jclass)env->CallObjectMethod(class_loader, find_class_id, name);

		env->DeleteLocalRef(name);
		env->DeleteLocalRef(class_loader_class);
		env->DeleteLocalRef(array_elements);
		env->DeleteLocalRef(thread_clazz);
		env->DeleteLocalRef(thread);
		env->DeleteLocalRef(threadgroup_clazz);
		env->DeleteLocalRef(threadgroup_obj);
		env->DeleteLocalRef(arrayD);

		return res;
	}

	env->DeleteLocalRef(array_elements);
	env->DeleteLocalRef(thread_clazz);
	env->DeleteLocalRef(thread);
	env->DeleteLocalRef(threadgroup_clazz);
	env->DeleteLocalRef(arrayD);
	env->DeleteLocalRef(threadgroup_obj);

	return env->FindClass(clsName);
}



jclass jvm::findClass(JNIEnv* p_env, jvmtiEnv* p_tienv, const std::string& path)
{
	jint class_count = 0;
	jclass* classes = nullptr;
	jclass foundclass = nullptr;
	p_tienv->GetLoadedClasses(&class_count, &classes);
	for (int i = 0; i < class_count; ++i)
	{
		char* signature_buffer = nullptr;
		p_tienv->GetClassSignature(classes[i], &signature_buffer, nullptr);
		std::string signature = signature_buffer;
		p_tienv->Deallocate((unsigned char*)signature_buffer);
		signature = signature.substr(1);
		signature.pop_back();
		
		if (signature.starts_with("com.moonsworth.lunar.")) {
			jvm::isLunar = true;
		}
		if (signature == path)
		{
			foundclass = (jclass)p_env->NewLocalRef(classes[i]);
		}
		p_env->DeleteLocalRef(classes[i]);
	}
	std::cout << "Found " << class_count << " Unique Classes In game!";
	p_tienv->Deallocate((unsigned char*)classes);
	return foundclass;
}


bool jvm::isForge()
{
	if (!jvm::AlreadyCheckedForge)
	{
		jvm::AlreadyCheckedForge = true;
		jclass forgeClass = jvm::env->FindClass("net/minecraftforge/common/ForgeVersion");
		if (forgeClass != NULL)
		{
			jvm::env->DeleteLocalRef(forgeClass);
			jvm::IsForgeExisting = true;
		}
	}
	return jvm::IsForgeExisting;
}

c_jobject::c_jobject(jobject object_in)
{
	this->cached_object = object_in;
}

c_jobject::~c_jobject()
{
	if (this->cached_object != nullptr)
	{
		jvm::env->DeleteLocalRef(this->cached_object);
	}

}



//jvm load already existed also player method get alr exists
