/********************************************************************
	created:	2011/05/19
	filename: 	IAppFrame
	file path:	E:\ws\cardsoul_proj\server\SrcScene\Include
	author:		
	
	purpose:	Ӧ�ó����ܽӿ�

*********************************************************************/

#ifndef  __IAPPFRAME_H__
#define __IAPPFRAME_H__

#include "DAppFramework.h"

class IClientSession;  
class IAppFrameworkServices;
class IAppConfig;
namespace socketsystem
{
	class ISocketSystem;
};


class ITrace;
class IScriptManager;

class IAppModule
{
public:
	//  ���崦����
	enum enProcessRes
	{
		enProcess = 0,       //	�¼����������������� ������û���С�����յ��˷��غ� ������Ź���
		enIdle,              //	�¼�����û���й���������յ��˷��غ󣬻�sleepһС��ʱ�䡣
		enFinish,            // �¼������Ѿ����������񡣿���յ��˷��غ󣬻��˳�����ִ�з���ʼ������
	};

	virtual TAppCtrlCommandRst OnControlCmd(const TAppCtrlCommand& stCommand) = 0;
	
	//  ֪ͨ��Ϸ�ͻ��ˣ�ϵͳ��Tick�Ѿ������ı�;
	virtual void OnTickChanged(unsigned int uiCurTick) = 0;

	//  ��������д��������ع���״̬
	virtual enProcessRes OnProc() = 0;

	//  ģ���ʼ������
	virtual BOOL  OnInit(IAppFrameworkServices *pAFS) = 0;

	//  �ͷ�ģ��
	virtual void Release() = 0;

	//  ��ȡ���һ�δ����ַ���
	virtual LPCSTR GetLastErrorMsg() = 0;
};

//       Ӧ�ó������, Ŀǰֻ�ṩһ��ϵͳ��ǰTick�Ĳ���.
//   ��Ӧ�ó�������ʱ, IAppModule::OnTickChanged����Ĳ������������TickΪ������
struct TAppParam
{
	unsigned int uiAppStartupTick;   //Ӧ�ó������𶯵�Tick(ms)
};



class IAppFrameworkServices
{
public:

	//  ��ȡӦ�ó���������Ϣ
	virtual IAppConfig *GetAppConfig() = 0;

	//  ��ȡsocketsystem
	virtual socketsystem::ISocketSystem *GetSocketSystem() = 0;

	//  ��ȡTrace����
	virtual ITrace *GetTrace() = 0;

	//   ��ȡ��ܲ���
	virtual TAppParam* GetAppParam() = 0;

	//  ��ȡ�ű�����������, �ű������������ڼ���xml����
	virtual IScriptManager *GetScriptManager() = 0;

};



#endif
