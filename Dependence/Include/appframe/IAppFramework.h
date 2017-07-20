/********************************************************************
	created:	2011/05/19
	filename: 	IAppFrame
	file path:	E:\ws\cardsoul_proj\server\SrcScene\Include
	author:		
	
	purpose:	应用程序框架接口

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
	//  定义处理结果
	enum enProcessRes
	{
		enProcess = 0,       //	事件函数进行了事务处理 ，代表没空闲。框架收到此返回后， 会紧接着工作
		enIdle,              //	事件函数没进行过处理。框架收到此返回后，会sleep一小段时间。
		enFinish,            // 事件函数已经处理完事务。框架收到此返回后，会退出程序（执行反初始化）。
	};

	virtual TAppCtrlCommandRst OnControlCmd(const TAppCtrlCommand& stCommand) = 0;
	
	//  通知游戏客户端，系统的Tick已经发生改变;
	virtual void OnTickChanged(unsigned int uiCurTick) = 0;

	//  对事务进行处理，并返回工作状态
	virtual enProcessRes OnProc() = 0;

	//  模块初始化调用
	virtual BOOL  OnInit(IAppFrameworkServices *pAFS) = 0;

	//  释放模块
	virtual void Release() = 0;

	//  获取最后一次错误字符串
	virtual LPCSTR GetLastErrorMsg() = 0;
};

//       应用程序参数, 目前只提供一个系统当前Tick的参数.
//   在应用程序运行时, IAppModule::OnTickChanged传入的参数都是以这个Tick为基础的
struct TAppParam
{
	unsigned int uiAppStartupTick;   //应用程序框架起动的Tick(ms)
};



class IAppFrameworkServices
{
public:

	//  获取应用程序配置信息
	virtual IAppConfig *GetAppConfig() = 0;

	//  获取socketsystem
	virtual socketsystem::ISocketSystem *GetSocketSystem() = 0;

	//  获取Trace对象
	virtual ITrace *GetTrace() = 0;

	//   获取框架参数
	virtual TAppParam* GetAppParam() = 0;

	//  获取脚本管理器对象, 脚本管理器可用于加载xml对象
	virtual IScriptManager *GetScriptManager() = 0;

};



#endif
