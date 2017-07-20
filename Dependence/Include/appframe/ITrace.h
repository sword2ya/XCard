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



//   无效的日志种类ID
const static DWORD INVALID_LOGCATID = 0xffffffff;


//   日志配置的结构 (向前声明)
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



//   ITrace日志接口
class ITrace
{
public:
	//  初始化日志系统
	virtual BOOL Create() = 0;
	virtual void Release() = 0;

	//  记录日志
	//  参数:
	//      dwCatID  :  日志分类ID
	//          iID  :  日志id, 应用程序定义, 可作为过滤条件
	//       iClass  :  日志类型, 应用程序定义, 可作为过滤条件
	//       pBuffer :  要记录胡数据
	//   iBufferSize :  数据长度
	//        返回值 :
	//                  记录成功返回TRUE, 否则返回FALSE.
	virtual BOOL LogBuffer(DWORD dwCatID, int iID,  unsigned int uiClass, const char* pBuffer, DWORD iBufferSize) = 0;


	//  记录日志
	//  参数:
	//      szCatName:  日志名称
	//          iID  :  日志id, 应用程序定义, 可作为过滤条件
	//       iClass  :  日志类型, 应用程序定义, 可作为过滤条件
	//       pBuffer :  要记录胡数据
	//   iBufferSize :  数据长度
	//        返回值 :  记录成功返回TRUE, 否则返回FALSE.
	//          备注 :  基于性能考虑 ,不建议使用这个方法.  应该使用QueryCatIDFromCatName()查找出对应的ID号, 使用ID号为索引
	virtual BOOL LogBuffer(LPCSTR szCatName, int iID,  unsigned int uiClass, const char* pBuffer, DWORD iBufferSize) = 0;


	//  记录日志
	//  参数:
	//      dwCatID  :  日志分类ID
	//          iID  :  日志id, 应用程序定义, 可作为过滤条件
	//       iClass  :  日志类型, 应用程序定义, 可作为过滤条件
	//         szFmt :  格式串, 同sprint() 等函数使用方法相同
	//           ... :  格式参数, 同sprint() 等函数使用方法相同
	//   
	//        返回值 :
	//                  记录成功返回TRUE, 否则返回FALSE.
	virtual BOOL Log(DWORD dwCatID, int iID,  unsigned int uiClass,  LPCSTR szFmt, ...) = 0;
	

	//  记录日志
	//  参数:
	//      szCatName:  日志名称
	//          iID  :  日志id, 应用程序定义, 可作为过滤条件
	//       iClass  :  日志类型, 应用程序定义, 可作为过滤条件
	//         szFmt :  格式串, 同sprint() 等函数使用方法相同
	//           ... :  格式参数, 同sprint() 等函数使用方法相同
	//
	//        返回值 :  记录成功返回TRUE, 否则返回FALSE.
	//
	//          备注 :  基于性能考虑 ,不建议使用这个方法.  应该使用QueryCatIDFromCatName()查找出对应的ID号, 使用ID号为索引
	virtual BOOL Log(LPCSTR szCatName, int iID,  unsigned int uiClass, LPCSTR szFmt, ...) = 0;




	//  记录日志
	//  参数:
	//      dwFlag   :  填充标记 DLOG_WRITE_FLAG
	//      dwCatID  :  日志分类ID
	//          iID  :  日志id, 应用程序定义, 可作为过滤条件
	//       iClass  :  日志类型, 应用程序定义, 可作为过滤条件
	//         szFmt :  格式串, 同sprint() 等函数使用方法相同
	//           ... :  格式参数, 同sprint() 等函数使用方法相同
	//   
	//        返回值 :
	//                  记录成功返回TRUE, 否则返回FALSE.
	virtual BOOL Log(DWORD dwFlag, DWORD dwCatID, int iID,  unsigned int uiClass,  LPCSTR szFmt, ...) = 0;


	//  记录日志
	//  参数:
	//      dwFlag   :  填充标记 DLOG_WRITE_FLAG
	//      szCatName:  日志名称
	//          iID  :  日志id, 应用程序定义, 可作为过滤条件
	//       iClass  :  日志类型, 应用程序定义, 可作为过滤条件
	//         szFmt :  格式串, 同sprint() 等函数使用方法相同
	//           ... :  格式参数, 同sprint() 等函数使用方法相同
	//
	//        返回值 :  记录成功返回TRUE, 否则返回FALSE.
	//
	//          备注 :  基于性能考虑 ,不建议使用这个方法.  应该使用QueryCatIDFromCatName()查找出对应的ID号, 使用ID号为索引
	virtual BOOL Log(DWORD dwFlag, LPCSTR szCatName, int iID,  unsigned int uiClass, LPCSTR szFmt, ...) = 0;


	//  通过日志名称, 查询日志种类ID
	//  参数:
	//      szCatName:  日志名称
	//   
	//        返回值 :
	//                  如果指定的名称存在, 返回对应的日志种类ID; 否则返回 INVALID_LOGCATID;
	virtual DWORD QueryCatIDFromCatName(LPCSTR szCatName) = 0;



	//  从配置文件加载日志种类
	//  参数:
	//      szConfigFile:   配置文件名称
	//          
	//   
	//  返回值 :
	//                  记录成功返回TRUE, 否则返回FALSE.	    
	//    备注 :  调用这个方法不会将当前的配置清除, 会将配置叠加.
	virtual BOOL LoadCategoryFromFile(LPCSTR szConfigFile) = 0;

	//  将日志种类配置写入文件
	//  参数:
	//      szConfigFile:   配置文件名称
	//   
	//  返回值 :
	//                  记录成功返回TRUE, 否则返回FALSE.	    
	virtual BOOL SaveCategoryToFile(LPCSTR szConfigFile) = 0;



	//  获取最后一次出错信息描述. 当执行某个方法返回失败后, 可以通过这个方法获取错误原因.
	//  参数:
	//          
	//   
	//  返回值 :
	//                  最后一次的出错信息描述
	virtual LPCSTR GetLastErrorMsg() = 0;

			
	//  删除全部日志种类配置, 调用这个方法后, 全部日志配置信息都会被清空.
	//  参数:
	//   
	//  返回值 :
	//                 
	virtual void ClearCategory() = 0;

	
	//  创建日志类型
	//  参数:
	//         szCatName:   日志配置名称
	//   
	//  返回值 :
	//                  记录成功返回日志种类的ID, 否则返回 INVALID_LOGCATID. 可以通过GetLastErrorMsg()获取错误原因
	virtual ILogCategoryConfig * CreateCategory(LPCSTR szCatName) = 0;

	

	//  获取日志类型配置
	//  参数:
	//         dwCatID:   日志种类的ID
	//         pConfig:   日志配置信息, 输出参数
	//  返回值 :
	//                    成功的话返回TRUE, 并且pConfig中填入对应的配置信息; 失败返回FALSE, pConfig中的数据无效.
	virtual ILogCategoryConfig * GetCategoryConfig(DWORD dwCatID) = 0;

	
	//  设置日志配置
	//  参数:
	//         dwCatID:   日志种类的ID
	//         pConfig:   日志配置信息
	//  返回值 :
	//                    成功的话返回TRUE; 失败返回FALSE
	virtual BOOL SetCategoryConfig(ILogCategoryConfig *pConfig) = 0;

	
	//  检查是否全部处理完
	//  返回值 :
	//                    全部队列为空时返回TRUE;
	virtual BOOL IsIdle() = 0;
	
	//  设置用于UI输出的 RichEdit 的 hWnd
	//  设置为 NULL 时表示取消 RichEdit 输出
	virtual void SetRichEditHWnd(HWND hWnd) = 0;

	//  获取用于UI输出的 RichEdit 的 hWnd	
	virtual HWND GetRichEditHWnd() = 0;

	//  设置用于 Socket 输出的 ISocketSystem
	virtual void SetSocketSystem(ISocketSystem* pSocketSystem) = 0;

};




#endif // __ITRACE_0083_H__
