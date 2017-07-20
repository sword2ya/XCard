/********************************************************************
	created:	2011/05/19
	filename: 	DAppFramework
	file path:	E:\ws\cardsoul_proj\server\SrcScene\Include
	author:		Safish
	
	purpose:	应用程序框架中可能使用到的常量

*********************************************************************/


#ifndef __DAPPFRAMEWORK_H__
#define __DAPPFRAMEWORK_H__



//  应用程序控制命令
enum EN_APPCMDTYPE
{
	enCmdMin = 0,
	enCmdStop = enCmdMin,   //停止运行
	enCmdReload,            //重新加载配置
	enCmdGet_Statistics,	//取统计信息
	enCmdQeury_RunState,	//查询运行状态
	enCmdForceStop,         //强制停止运行(在appframe主界面点强制关闭的按钮触发)
	enCmdMax,
};

//命令处理结果
enum EN_APPCMD_RST{
	enAppCtrlCmdRst_Unkown = -1,
	enAppCtrlCmdRst_OK = 0,
	enAppCtrlCmdRst_Fail,
};




//  停止命令的现场 
struct TStopCmdContext
{

};

//  重新加载配置命令现场
struct TReloadContext
{
	char szCfgFile[512];
};


//取统计信息
struct TGetStatistics
{
	void* pAppStatistics;//IAppStatistics接口
	//IAppStatistics* pAppStatistics;//
};

// 查询运行状态
struct TQueryRunStateReq
{
	int nTransID;
};
struct TQueryRunStateRsp
{
	int nTransID;
	int nState;
};
//运行状态
enum EN_RUN_STATE{
	enAppRunState_OK = 0,//良好
	enAppRunState_NotRun = 1,//未运行
	enAppRunState_Unkown = 2,//未知
	enAppRunState_NotRsp = 3,//无响应
	enAppRunState_Err = 4,//有错误

	//下面的内容与具体应用相关
	enAppRunState_DB_Disconnect= 101, //DB服未连接
	enAppRunState_Center_Disconnect = 102, //中心服未连接
};





struct TAppCtrlCommand
{
	EN_APPCMDTYPE enType;
	__int64  iCmdID;   // 命令ID, 返回结果中带回.  框架自动填写,应用层不需要理会这个字段.

	//  各种命令的现场
	union TContext
	{
		TStopCmdContext stStopCtx;
		TReloadContext stReloadCtx;
		TGetStatistics stGetStatistics;
		TQueryRunStateReq stQueryRunStateReq;
	} stContext;
}; 

//命令处理结果
struct TAppCtrlCommandRst
{
	EN_APPCMDTYPE enType;        //  框架会自动填写, 应用不需要理会
	__int64  iCmdID;             //  框架自动填写,   应用不需要理会
	EN_APPCMD_RST nResult;	    

	//结果现场
	union TContext
	{
		void* pAppStatistics;//IAppStatistics*
		TQueryRunStateRsp stQueryRunStateRsp;
	}stRstContext;

	TAppCtrlCommandRst()
	{
		enType = enCmdMax;
		memset(&stRstContext, 0, sizeof(stRstContext) );
		//stRstContext.pAppStatistics = NULL;	
		nResult = enAppCtrlCmdRst_Unkown;
	}


};



#endif