/********************************************************************
	created:	2011/09/11  9:53
	file base:	ITrace
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/




#ifndef __ITRACE_0083_H__
#define __ITRACE_0083_H__

//#include "ISocketSystem.h"
namespace socketsystem
{
	class ISocketSystem;
};
using namespace socketsystem;



//   ��Ч����־����ID
const static DWORD INVALID_LOGCATID = 0xffffffff;


//   ��־���õĽṹ (��ǰ����)
class ILogCategoryConfig;

namespace DLog
{
	enum DLOG_WRITE_FLAG
	{
		DLOG_WRITE_FLAG_GENERAL = 0,
		DLOG_WRITE_FLAG_NEWLINE = 1,
		DLOG_WRITE_FLAG_TIME = 2,
	};



	enum DLOG_ERROR_NUMBER
	{
		DLOG_ERROR_CONFIG,
		DLOG_ERROR_INIT,
		DLOG_ERROR_SOCKET_SYSTEM,
		DLOG_ERROR_SOCKET_CREATE,
		DLOG_ERROR_SOCKET_CONNECT,
		DLOG_ERROR_SOCKET_SEND,
	};
};



//   ITrace��־�ӿ�
class ITrace
{
public:
	//  ��ʼ����־ϵͳ
	virtual BOOL Create() = 0;
	virtual void Release() = 0;

	//  ��¼��־
	//  ����:
	//      dwCatID  :  ��־����ID
	//          iID  :  ��־id, Ӧ�ó�����, ����Ϊ��������
	//       iClass  :  ��־����, Ӧ�ó�����, ����Ϊ��������
	//       pBuffer :  Ҫ��¼������
	//   iBufferSize :  ���ݳ���
	//        ����ֵ :
	//                  ��¼�ɹ�����TRUE, ���򷵻�FALSE.
	virtual BOOL LogBuffer(DWORD dwCatID, int iID,  unsigned int uiClass, const char* pBuffer, DWORD iBufferSize) = 0;


	//  ��¼��־
	//  ����:
	//      szCatName:  ��־����
	//          iID  :  ��־id, Ӧ�ó�����, ����Ϊ��������
	//       iClass  :  ��־����, Ӧ�ó�����, ����Ϊ��������
	//       pBuffer :  Ҫ��¼������
	//   iBufferSize :  ���ݳ���
	//        ����ֵ :  ��¼�ɹ�����TRUE, ���򷵻�FALSE.
	//          ��ע :  �������ܿ��� ,������ʹ���������.  Ӧ��ʹ��QueryCatIDFromCatName()���ҳ���Ӧ��ID��, ʹ��ID��Ϊ����
	virtual BOOL LogBuffer(LPCSTR szCatName, int iID,  unsigned int uiClass, const char* pBuffer, DWORD iBufferSize) = 0;


	//  ��¼��־
	//  ����:
	//      dwCatID  :  ��־����ID
	//          iID  :  ��־id, Ӧ�ó�����, ����Ϊ��������
	//       iClass  :  ��־����, Ӧ�ó�����, ����Ϊ��������
	//         szFmt :  ��ʽ��, ͬsprint() �Ⱥ���ʹ�÷�����ͬ
	//           ... :  ��ʽ����, ͬsprint() �Ⱥ���ʹ�÷�����ͬ
	//   
	//        ����ֵ :
	//                  ��¼�ɹ�����TRUE, ���򷵻�FALSE.
	virtual BOOL Log(DWORD dwCatID, int iID,  unsigned int uiClass,  LPCSTR szFmt, ...) = 0;
	

	//  ��¼��־
	//  ����:
	//      szCatName:  ��־����
	//          iID  :  ��־id, Ӧ�ó�����, ����Ϊ��������
	//       iClass  :  ��־����, Ӧ�ó�����, ����Ϊ��������
	//         szFmt :  ��ʽ��, ͬsprint() �Ⱥ���ʹ�÷�����ͬ
	//           ... :  ��ʽ����, ͬsprint() �Ⱥ���ʹ�÷�����ͬ
	//
	//        ����ֵ :  ��¼�ɹ�����TRUE, ���򷵻�FALSE.
	//
	//          ��ע :  �������ܿ��� ,������ʹ���������.  Ӧ��ʹ��QueryCatIDFromCatName()���ҳ���Ӧ��ID��, ʹ��ID��Ϊ����
	virtual BOOL Log(LPCSTR szCatName, int iID,  unsigned int uiClass, LPCSTR szFmt, ...) = 0;




	//  ��¼��־
	//  ����:
	//      dwFlag   :  ����� DLOG_WRITE_FLAG
	//      dwCatID  :  ��־����ID
	//          iID  :  ��־id, Ӧ�ó�����, ����Ϊ��������
	//       iClass  :  ��־����, Ӧ�ó�����, ����Ϊ��������
	//         szFmt :  ��ʽ��, ͬsprint() �Ⱥ���ʹ�÷�����ͬ
	//           ... :  ��ʽ����, ͬsprint() �Ⱥ���ʹ�÷�����ͬ
	//   
	//        ����ֵ :
	//                  ��¼�ɹ�����TRUE, ���򷵻�FALSE.
	virtual BOOL Log(DWORD dwFlag, DWORD dwCatID, int iID,  unsigned int uiClass,  LPCSTR szFmt, ...) = 0;


	//  ��¼��־
	//  ����:
	//      dwFlag   :  ����� DLOG_WRITE_FLAG
	//      szCatName:  ��־����
	//          iID  :  ��־id, Ӧ�ó�����, ����Ϊ��������
	//       iClass  :  ��־����, Ӧ�ó�����, ����Ϊ��������
	//         szFmt :  ��ʽ��, ͬsprint() �Ⱥ���ʹ�÷�����ͬ
	//           ... :  ��ʽ����, ͬsprint() �Ⱥ���ʹ�÷�����ͬ
	//
	//        ����ֵ :  ��¼�ɹ�����TRUE, ���򷵻�FALSE.
	//
	//          ��ע :  �������ܿ��� ,������ʹ���������.  Ӧ��ʹ��QueryCatIDFromCatName()���ҳ���Ӧ��ID��, ʹ��ID��Ϊ����
	virtual BOOL Log(DWORD dwFlag, LPCSTR szCatName, int iID,  unsigned int uiClass, LPCSTR szFmt, ...) = 0;


	//  ͨ����־����, ��ѯ��־����ID
	//  ����:
	//      szCatName:  ��־����
	//   
	//        ����ֵ :
	//                  ���ָ�������ƴ���, ���ض�Ӧ����־����ID; ���򷵻� INVALID_LOGCATID;
	virtual DWORD QueryCatIDFromCatName(LPCSTR szCatName) = 0;



	//  �������ļ�������־����
	//  ����:
	//      szConfigFile:   �����ļ�����
	//          
	//   
	//  ����ֵ :
	//                  ��¼�ɹ�����TRUE, ���򷵻�FALSE.	    
	//    ��ע :  ��������������Ὣ��ǰ���������, �Ὣ���õ���.
	virtual BOOL LoadCategoryFromFile(LPCSTR szConfigFile) = 0;

	//  ����־��������д���ļ�
	//  ����:
	//      szConfigFile:   �����ļ�����
	//   
	//  ����ֵ :
	//                  ��¼�ɹ�����TRUE, ���򷵻�FALSE.	    
	virtual BOOL SaveCategoryToFile(LPCSTR szConfigFile) = 0;



	//  ��ȡ���һ�γ�����Ϣ����. ��ִ��ĳ����������ʧ�ܺ�, ����ͨ�����������ȡ����ԭ��.
	//  ����:
	//          
	//   
	//  ����ֵ :
	//                  ���һ�εĳ�����Ϣ����
	virtual LPCSTR GetLastErrorMsg() = 0;

			
	//  ɾ��ȫ����־��������, �������������, ȫ����־������Ϣ���ᱻ���.
	//  ����:
	//   
	//  ����ֵ :
	//                 
	virtual void ClearCategory() = 0;

	
	//  ������־����
	//  ����:
	//         szCatName:   ��־��������
	//   
	//  ����ֵ :
	//                  ��¼�ɹ�������־�����ID, ���򷵻� INVALID_LOGCATID. ����ͨ��GetLastErrorMsg()��ȡ����ԭ��
	virtual ILogCategoryConfig * CreateCategory(LPCSTR szCatName) = 0;

	

	//  ��ȡ��־��������
	//  ����:
	//         dwCatID:   ��־�����ID
	//         pConfig:   ��־������Ϣ, �������
	//  ����ֵ :
	//                    �ɹ��Ļ�����TRUE, ����pConfig�������Ӧ��������Ϣ; ʧ�ܷ���FALSE, pConfig�е�������Ч.
	virtual ILogCategoryConfig * GetCategoryConfig(DWORD dwCatID) = 0;

	
	//  ������־����
	//  ����:
	//         dwCatID:   ��־�����ID
	//         pConfig:   ��־������Ϣ
	//  ����ֵ :
	//                    �ɹ��Ļ�����TRUE; ʧ�ܷ���FALSE
	virtual BOOL SetCategoryConfig(ILogCategoryConfig *pConfig) = 0;

	
	//  ����Ƿ�ȫ��������
	//  ����ֵ :
	//                    ȫ������Ϊ��ʱ����TRUE;
	virtual BOOL IsIdle() = 0;
	
	//  ��������UI����� RichEdit �� hWnd
	//  ����Ϊ NULL ʱ��ʾȡ�� RichEdit ���
	virtual void SetRichEditHWnd(HWND hWnd) = 0;

	//  ��ȡ����UI����� RichEdit �� hWnd	
	virtual HWND GetRichEditHWnd() = 0;

	//  �������� Socket ����� ISocketSystem
	virtual void SetSocketSystem(ISocketSystem* pSocketSystem) = 0;

};




#endif // __ITRACE_0083_H__
