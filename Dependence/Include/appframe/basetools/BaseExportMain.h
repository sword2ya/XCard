

#pragma once

// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 BASE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// BASE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
// #ifdef BASE_EXPORTS
// #define BASE_API __declspec(dllexport)
// #else
// #define BASE_API __declspec(dllimport)
// #endif

#include <windows.h>
//#include <tchar.h>


#include "IEventServer.h"
#include "ITimerHelper.h"
#include "IFileSystem.h"
#include "IScriptManager.h"


namespace basetools
{

class IBasetoolsLib
{
public:
	//   创建事件服对象	
	virtual IEventServer * CreateEventServer(void) = 0;


	//   创建时间轴对象
	virtual ITimerAxis * CreateTimerAxis(void) = 0;


	//   计算MD5摘要, 如果遇到失败, 缓冲区中会填充'\0'
	virtual BOOL GenerateMD5(char *pMD5, int iMD5Len, const char *pSrcData, int iSrcLen) = 0;


	//************************************
	// Method:    创建文件系统
	// Returns:   BASE_API BOOL
	// Qualifier:
	// Parameter: DWORD dwVer              保留参数, 填0; 以后扩展可以根据这个值不同,可以创建内存文件系统等
	//************************************
	virtual IFileSystem * CreateFileSystem(DWORD dwVer) = 0;


	//************************************
	// Method:    创建ZIP助手
	// Returns:   IZipHelper               
	// Qualifier:
	//************************************
	virtual IZipHelper * CreateZipHelper() = 0;


	//************************************
	// Method:    创建一个树型脚本
	// Parameter: DWORD dwMaxID              树型脚本中, 结点ID的最大值. 如果没有特殊需求, 填0
	// Returns:   IResScript
	// Qualifier:
	//************************************
	virtual IResScript2 * CreateResScript(DWORD dwMaxID) = 0;


	//  释放
	virtual void Release() = 0;

};

	




};     //  namespace


/*

class BASE_API Cbase {
public:
	Cbase(void);

};

extern BASE_API int nbase;


*/