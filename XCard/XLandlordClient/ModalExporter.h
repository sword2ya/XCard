#pragma once 


#if (defined(_WIN32) || defined(_WIN64))
extern "C" __declspec(dllexport)  void* GetModuleInterface(const char* pszInterfaceName);
#else
extern "C" void* GetModuleInterface(const char* pszInterfaceName);
#endif
