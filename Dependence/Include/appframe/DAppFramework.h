/********************************************************************
	created:	2011/05/19
	filename: 	DAppFramework
	file path:	E:\ws\cardsoul_proj\server\SrcScene\Include
	author:		Safish
	
	purpose:	Ӧ�ó������п���ʹ�õ��ĳ���

*********************************************************************/


#ifndef __DAPPFRAMEWORK_H__
#define __DAPPFRAMEWORK_H__



//  Ӧ�ó����������
enum EN_APPCMDTYPE
{
	enCmdMin = 0,
	enCmdStop = enCmdMin,   //ֹͣ����
	enCmdReload,            //���¼�������
	enCmdGet_Statistics,	//ȡͳ����Ϣ
	enCmdQeury_RunState,	//��ѯ����״̬
	enCmdForceStop,         //ǿ��ֹͣ����(��appframe�������ǿ�ƹرյİ�ť����)
	enCmdMax,
};

//�������
enum EN_APPCMD_RST{
	enAppCtrlCmdRst_Unkown = -1,
	enAppCtrlCmdRst_OK = 0,
	enAppCtrlCmdRst_Fail,
};




//  ֹͣ������ֳ� 
struct TStopCmdContext
{

};

//  ���¼������������ֳ�
struct TReloadContext
{
	char szCfgFile[512];
};


//ȡͳ����Ϣ
struct TGetStatistics
{
	void* pAppStatistics;//IAppStatistics�ӿ�
	//IAppStatistics* pAppStatistics;//
};

// ��ѯ����״̬
struct TQueryRunStateReq
{
	int nTransID;
};
struct TQueryRunStateRsp
{
	int nTransID;
	int nState;
};
//����״̬
enum EN_RUN_STATE{
	enAppRunState_OK = 0,//����
	enAppRunState_NotRun = 1,//δ����
	enAppRunState_Unkown = 2,//δ֪
	enAppRunState_NotRsp = 3,//����Ӧ
	enAppRunState_Err = 4,//�д���

	//��������������Ӧ�����
	enAppRunState_DB_Disconnect= 101, //DB��δ����
	enAppRunState_Center_Disconnect = 102, //���ķ�δ����
};





struct TAppCtrlCommand
{
	EN_APPCMDTYPE enType;
	__int64  iCmdID;   // ����ID, ���ؽ���д���.  ����Զ���д,Ӧ�ò㲻��Ҫ�������ֶ�.

	//  ����������ֳ�
	union TContext
	{
		TStopCmdContext stStopCtx;
		TReloadContext stReloadCtx;
		TGetStatistics stGetStatistics;
		TQueryRunStateReq stQueryRunStateReq;
	} stContext;
}; 

//�������
struct TAppCtrlCommandRst
{
	EN_APPCMDTYPE enType;        //  ��ܻ��Զ���д, Ӧ�ò���Ҫ���
	__int64  iCmdID;             //  ����Զ���д,   Ӧ�ò���Ҫ���
	EN_APPCMD_RST nResult;	    

	//����ֳ�
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