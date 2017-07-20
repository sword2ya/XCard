

#pragma once

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� BASE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// BASE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
	//   �����¼�������	
	virtual IEventServer * CreateEventServer(void) = 0;


	//   ����ʱ�������
	virtual ITimerAxis * CreateTimerAxis(void) = 0;


	//   ����MD5ժҪ, �������ʧ��, �������л����'\0'
	virtual BOOL GenerateMD5(char *pMD5, int iMD5Len, const char *pSrcData, int iSrcLen) = 0;


	//************************************
	// Method:    �����ļ�ϵͳ
	// Returns:   BASE_API BOOL
	// Qualifier:
	// Parameter: DWORD dwVer              ��������, ��0; �Ժ���չ���Ը������ֵ��ͬ,���Դ����ڴ��ļ�ϵͳ��
	//************************************
	virtual IFileSystem * CreateFileSystem(DWORD dwVer) = 0;


	//************************************
	// Method:    ����ZIP����
	// Returns:   IZipHelper               
	// Qualifier:
	//************************************
	virtual IZipHelper * CreateZipHelper() = 0;


	//************************************
	// Method:    ����һ�����ͽű�
	// Parameter: DWORD dwMaxID              ���ͽű���, ���ID�����ֵ. ���û����������, ��0
	// Returns:   IResScript
	// Qualifier:
	//************************************
	virtual IResScript2 * CreateResScript(DWORD dwMaxID) = 0;


	//  �ͷ�
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