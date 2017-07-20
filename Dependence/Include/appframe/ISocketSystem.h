/********************************************************************
	created:	2012/6/14  14:59
	file base:	ISocketSystem
	file ext:	h
	author:		
	
	purpose:	socketsystem�ӿ��ļ�
*********************************************************************/

#ifndef __ISOCKETSYSTEM_H__
#define __ISOCKETSYSTEM_H__


class ITrace;

namespace socketsystem
{
	//  ��־
	enum LOG_LEVEL{
		LOGLV_FATAL = 0,   //��������, ���ܻᵼ�·���ֹͣ
		LOGLV_INFO_1,      //�Ƚ��ظ�����Ϣ, ����ִ�б������Ե�
		LOGLV_INFO_2,      //����ͨ����Ϣ,����ͻ�������, �Ͽ����¼�
	};

	//  �������ͷ�Ĵ�����
	enum EN_SPECPKG_HANDLER
	{
		enIgnorePkg,            //���Դ˰�
		enSendFlashPolicy,      //����flash����
	};
	
	//  socket����
	struct TSocketLimit
	{
		__int64 iRecvBufferBytes;   // ���ջ������ֽ���
		__int64 iSendBufferBytes;   // ���ͻ������ֽ���

		BOOL bSendBlockFix;            // �Ƿ���������������û�. 
		int iSendBlockStandard;                  // �����ӷ��Ͷ°�(����)����. �°�����������Ȼᱻ��
		BOOL bRecvBlockFix;              // �Ƿ���������������û�
		int iRecvBlockStandard;                  // �����ӽ��ն°�(����)����. ͨ���߳̽��յ����ݰ���, ÿһ��ֻ�����߼��߳�ת��iPkgPushPerFrame����, Ϊ�����ӻ�����ƽ����. ���Զ�˷�������, ��ᱻ����ȥ.
		int iRecvPkgMaxBytes;   // ������󳤶�, Զ�̶˷��ͳ���������ȵİ�, �ᱻ��
		int iPkgPushPerFrame;    //��һ֡��, ��ɰ����͸���. �������ֵ������߽���������, �����ڲ������ε�Զ������, ���ܻᷢ�ʹ������ݰ�,ƭȡCPUʱ��. ������ֵ<=0, ���ʾȫ����ͬʱ����
		BOOL  bForceRecycleSendBlock;    //��û�з��ͻ�����ʱ, �Ƿ�ǿ�ƻ���
		BOOL  bForceRecycleRecvBlock;    //��û�н��ջ�����ʱ, �Ƿ�ǿ�ƻ���
			
		//  ����Ĭ�ϲ���
		TSocketLimit()
		{
			iRecvBufferBytes = 512 * 1024 * 1024;
			iSendBufferBytes =  512 * 1024 * 1024;
			
			bSendBlockFix = FALSE;
			iSendBlockStandard = 3000;   
			bRecvBlockFix = FALSE;
			iRecvBlockStandard = 3000;               
			iRecvPkgMaxBytes = 4 * 1024 * 1024;  
			iPkgPushPerFrame = 0;
			bForceRecycleSendBlock = FALSE;
			bForceRecycleRecvBlock = FALSE;
		};
	};

	//  server socket��ͳ������
	struct TServerSocStat
	{
		__int64 iSendBytes;             // �����ֽ���
		__int64 iRecvBytes;             // �����ֽ���
		__int64 iSendPkgNums;           // ���Ͱ���
		__int64 iRecvPkgNums;           // ���հ���
		__int64 iSendBufferMaxBytes;    // ���ͻ������������
		__int64 iSendBufferCurBytes;   // ���ͻ�������ǰ����
		__int64 iRecvBufferMaxBytes;    // ���ջ������������
		__int64 iRecvBufferCurBytes;    // ���ջ�������ǰ����
		__int64 iAccumulateConnectNums;  // �ͻ����ۼ�������
		__int64 iCurConnectNums;         // ��ǰ������
	};

	//////////////////////////////////////////////////////////////////////////
	//����˱���ʵ�ֵĽӿ� 
	//���տͻ������ݻ��߿ͻ��˹ر�ʱ�ص�
	class IClientSink
	{
	public:
		// ���յ�����
		virtual void OnRecv(DWORD dwSocketID, LPCSTR Buf, int nLen) = NULL;

		// �ͻ��˶Ͽ����ӻص�
		virtual void OnCloseConnect(DWORD dwSocketID) = NULL;
	};

	//���пͻ��˽���ʱ�ص�
	class IServerSocketSink
	{
	public:
		// �ͻ��������ӻص�
		virtual void OnAccept(DWORD dwSocketID, IClientSink **ppClientSink) = NULL;		
	};


	//////////////////////////////////////////////////////////////////////////
	//�ͻ��˱���ʵ�ֵĽӿ�
	//
	class IClientSocket;
	class IClientSocketSink
	{
	public:
		// ���յ�����
		virtual void OnRecv(IClientSocket *pClientSocket, LPCSTR Buf, int nLen) = NULL;

		// �Ͽ����ӻص�,һ���Ƿ���˶Ͽ�
		virtual void OnCloseConnect(IClientSocket *pClientSocket) = NULL;

		// ���ӻص�
		virtual void OnConnect(IClientSocket *pClientSocket) = NULL;

		// ���Ӵ���
		virtual void OnConnectError(IClientSocket *pClientSocket, int nErrorCode) = NULL;
	};


	//      �������ÿ�����ݰ�����ʱ��Ҫ��һ������������, ����ʱ����Ҫ��һ��������н��
	//  socketsystem�ڲ��Ѿ�����һ�׹��� (����int + ������) , Ӧ�ÿ�ͨ���̳б��ӿ�, ��д��
	//  ���Ľ�������
	class IBinBuffer;   // ������, ���ڱ��漴������, ���߸ս��յ�������
	class IPackageRule   
	{
	public:
		//  ������
		enum En_Unpack_Result
		{
			enUnpackComplete,   // ���һ�����ݰ�
			enUnpackWait,       // ���ݲ���, ��Ҫ�ȴ�������
			enUnpackError,      // �������
		};

	public:
		
		//************************************
		// Method:    OnPackagePack                   socketsystem���ʱ���ô˺���
		// Returns:   bool
		// Qualifier:
		// Parameter: IBuffer * pOutBuffer            ���������
		// Parameter: LPCSTR pSrcData                 Դ����, �������Ӧ�ò����  Socket::Send() �������������
		// Parameter: int iLen                        Դ���ݵĳ���
		// Parameter: char * pErrorDesc               ��������������, �����������з�������, ���Խ���־д������
		// Parameter: int iErrLen                     ���󻺳�������
		//      memo: �������������������ɲ�ͬ���̵߳���.   Ӧ�ü̳������ʱ, ע���̰߳�ȫ. ��ò�Ҫ�����Ա
		//************************************
		virtual bool OnPackagePack(IBinBuffer *pOutBuffer, LPCSTR pSrcData, int iLen, char *pErrorDesc, int iErrLen) = 0;

		
		
		//************************************
		// Method:    OnPackageUnpack                 socketsystem���ʱ���ô˺���		
		// Returns:   socketsystem::IPackageRule::En_Unpack_Result      �������enUnpackWait, socketsystem�Ὣ�����ݴ�����;
		//                                                                  ����enUnpackComplete, socketsystem �Ժ�Ὣ�����ύ��Ӧ�ò�.ʣ�µ����ݻ���Ϊ��һ������������ʱ��������       
		//                                                                  ����enUnpackError, socketsystem ��Ͽ�����, ��Ϊ����������Ѿ��޷�����                                                      
		// Qualifier:
		// Parameter: IBinBuffer * pRecvBuffer                          ���ջ�����, ����ŵ���δ���������. �������δ�ܹ���һ����, Ӧ�ò�Ҫ�������������, �´����յ����ݻ��ۼ���β��
		// Parameter: IBinBuffer *pFinishPkgBuffer                      ���������, ��������enUnpackComplete����Ҫ��������д. ÿ�ε���, ֻ��1����. 
		// Parameter: bool bIsFirstPkg                                  �Ƿ�Ϊ��һ����. �кܶ�ϵͳҪ���һ�����������Ӧ��, ����flash�Ĳ�������, �����������, ����������ж��Ż�����
		// Parameter: char * pErrorDesc	                                ��������������, �����������з�������, ���Խ���־д������
		// Parameter: int iErrLen                                       ���󻺳�������
		//      memo: �������������������ɲ�ͬ���̵߳���.   Ӧ�ü̳������ʱ, ע���̰߳�ȫ. ��ò�Ҫ�����Ա
		//************************************
		virtual En_Unpack_Result OnPackageUnpack(IBinBuffer *pFinishPkgBuffer, IBinBuffer *pRecvBuffer, bool bIsFirstPkg, char *pErrorDesc, int iErrLen) = 0;
	};

	class IBinBuffer
	{
	public:
		//  ����������д������, ������� false, ���ʾ�����޷�д��(ͨ�����ڴ�ʹ�ôﵽָ���Ľ���ֵ)
		virtual bool WriteData(LPCSTR pBuffer, DWORD dwLen) = 0;

		//  ��ȡ���������ж��ٿ�������
		virtual DWORD GetAvalibleBytes() = 0;


		//************************************
		// Method:    ReadData                    ��ȡ�������е�����	
		// Returns:   char *                          ����ָ��.  ע��, �������ܿ���, ���Ҫ��ȡ����������, ���ֱ�ӷ���Դ����ָ��,����������ݸ��Ƶ��û������Ļ�������. 
		//                                        ��, �������ֵ��һ������pBuffer
		// Qualifier:
		// Parameter: char * pBuffer              ����װ�ط��ص�����, �����������������dwReadָ����ֵ
		// Parameter: DWORD dwRead                ������ȡ���ֽ���
		// Parameter: DWORD & dwActualRead        ʵ�ʶ�ȡ�����ֽ���
		//     memo :     ��ȡ����ʱ, ����Ӱ�컺�����ĵ�ǰλ��.  ���������������N��, ��ȡ���Ķ���һ��������. ������ȡ���������, ����PopFront()����
		//************************************
		virtual char *ReadData(char *pBuffer, DWORD dwRead, DWORD &dwActualRead) = 0;

	
		//************************************
		// Method:    PopFront                    �ӻ�����ǰ�浯��ָ���ֽ���
		// Returns:   void
		//
		// Parameter: DWORD dwBytes               �ֽ���
		//************************************
		virtual void PopFront(DWORD dwBytes) = 0;



		//************************************
		// Method:    MoveDataFromOtherBuffer        ����һ��CBlockBuffer��move���ݵ���CBlockBuffer��
		// Returns:   bool                           move�Ƿ�ɹ�
		// Qualifier:
		// Parameter: IBinBuffer * pSrcBuffer        Դ���ݻ�����.  ���������������Ӧ������ʵ�ֵ�, һ��Ҫ��socketsystem�ṩ��IBinBuffer����
		// Parameter: DWORD dwBytes                  ��Ҫ���Ƶ��ֽ���
		//************************************
		virtual bool MoveDataFromOtherBuffer(IBinBuffer *pSrcBuffer, DWORD dwBytes) = 0;
	};


	//�ͻ���Socket
	class IClientSocket 
	{
	public:
		// �ͷ�,������CloseConnect()�Ĳ���
		virtual void Release() = NULL;

		// ����
		virtual BOOL Connect(LPCSTR szServerIP, int iServerPort) = NULL;

		// �Ͽ�����
		virtual void CloseConnect() = NULL;

		// ��������
		virtual BOOL Send(LPCSTR Buf, int nLen) = NULL;

		// ����raw����, socketsystem����������ǰ��Ӱ�ͷ����Ϣ
		virtual BOOL SendRaw(LPCSTR Buf, int nLen) = NULL;

		// ��ȡSocketID, ���ID��client socket��ID.  ��ServerSocket�е�SocketID�ǲ�ͬ��"����ռ�"
		virtual DWORD GetSocketID() = NULL;		

		// ���ûص�Sink
		virtual void setSocketSink(IClientSocketSink* pSink) = NULL;

		// ��ǰ�Ƿ��������Ϸ���˵�
		virtual BOOL isConnected() = NULL;

		// ��ǰ�Ƿ��������ӷ����
		virtual BOOL isConnecting() = NULL;

		//  �������/�������
		virtual void SetPackageRule(IPackageRule *pCustomRule) = 0;

		//  ��ȡ���/�������
		virtual IPackageRule *GetPackageRule() = 0;
	};

	//�����Socket
	class IServerSocket
	{
	public:
		// �ͷ�
		virtual void Release() = NULL;

		// ��ʼ
		virtual BOOL Start(LPCSTR szServerIP, WORD wPort, int nConnectNum) = NULL;

		// ֹͣ�����Socket
		virtual void Stop() = NULL;

		// ����
		virtual BOOL Send(DWORD dwSocketID, LPCSTR Buf, int nLen) = NULL;

		// ����
		virtual BOOL Send(DWORD *pdwSocketIDs, int nIDNum, LPCSTR Buf, int nLen) = NULL;

		//�����رնԷ�������
		virtual BOOL CloseConnect(DWORD dwSocketID) = NULL;

		// ���÷���˻ص�Sink
		virtual void SetClientSink(DWORD dwSocketID, IClientSink *pClientSink) = NULL;

		//��ȡ�ͻ�����Ϣ
		virtual BOOL GetClientInfo(DWORD dwSocketID, char *szIP, int iBufferLen, int &iPort) = NULL;	

		//���пͻ��˽���ʱ�ص�
		virtual void setAcceptorSink(IServerSocketSink* pSink) = NULL;

		//��ȡ���һ�δ�����Ϣ
		virtual LPCSTR GetLastErrorDesc() = NULL;

		// �ƶ�socketϵͳ������Ϣ. ����д������Ϣ, ����TRUE; ���򷵻�FALSE
		//  bOnlyPushClient����ָ��, �Ƿ�ֻ�ƶ��ͻ�����Ϣ. ��ֻ��IClientSocket��sink���յ���Ϣ
		virtual BOOL ProcessSocketMsg() = 0;

		//  ��ȡsocket���Ʋ���
		virtual const TSocketLimit & GetSocketLimit() = 0;		
		virtual void SetSocketLimit(const TSocketLimit &stLimit) = 0;

		//  ��ȡͳ������
		virtual const TServerSocStat * GetStatistics() = 0;

		//  ���ͳ������
		virtual void ClearStatistics() = 0;

		//  ����flash��������. 
		virtual void SetFlashPolicyData(LPCSTR pPolicyData, DWORD dwLen) = 0;


		//************************************
		// Method:    ����Ӧ�������ͷ�Ĳ��� .  ����ӿ���Ҫ��Start()ǰ����, ����������.
		// Returns:   void
		// Qualifier:
		// Parameter: LPCSTR pStringPkg                     ���ݰ�����, ֻ֧����'\0'��β���ַ���
		// Parameter: EN_SPECPKG_HANDLER enHandler          �Դ����ݰ��Ĵ���
		//      memo:    (1)   ���������ֻ��Ե�1������Ч, �ڶ�������ʼ����Ϊ��ͨ���ݰ�����.
		//               (2)   Ŀǰ��ʹ�� memcmp �����ݰ���������ʶ��.  ����Ժ����Ҫ�Զ�̬���ݵ�ʶ��, ���Կ�����Ӧ��
		//            ����У�Ժ����԰����ݽ��м��.  
		//************************************
		virtual void AddSpecialPkgRule(LPCSTR szStringPkg, EN_SPECPKG_HANDLER enHandler) = 0;

		//  �������/�������
		virtual void SetPackageRule(IPackageRule *pCustomRule) = 0;

		//  ��ȡ���/�������
		virtual IPackageRule *GetPackageRule() = 0;
	};

	//  v2�汾��IServerSocket�ӿ�, 
	//  ���� CreateServerSocket()ʱʹ��V2�����õ���IServerSocket����, ����ʹ�þ�̬Ӱ����������
	class IServerSocketV2: public IServerSocket
	{
	public:
		struct TConnectionInfo
		{
			DWORD dwSocketID;
			int   iSessionID;   // �ỰID, ��ͻ���socket��Session��Ӧ
			DWORD dwChannelNums;   //  ��ͨChannel����, ���������Ϊ2
			DWORD vtChannelID[10];   //  ͨ��ID, ʵ�ʸ����ο�dwChannelNums�ֶ�
		};

	public:

		//  ��ȡ��ǰ���ӵ�����
		virtual DWORD GetConnectionNum() = 0;
		
		//  ��ȡ���ӵ���Ϣ
		virtual BOOL GetConnectionInfo( DWORD dwIndex , TConnectionInfo *pOut) = 0;

		//  �Ͽ�ĳ�����ӵ�ĳ��ͨ��(��������������������������ж�)
		//  ע��, ��0��������SocketID, ����Index.  Ӧ����ͨ��GetConnectionInfo()��ȡTConnectionInfo::dwSocketID.
		virtual BOOL DisconnChannel(DWORD dwSocketID, DWORD dwChannelIndex) = 0;

	};

	//  v2�汾��IClientSocket�ӿ�, 
	//  ���� CreateClientSocket()ʱʹ��V2�����õ���IClientSocket����, ����ʹ�þ�̬Ӱ����������
	class IClientSocketV2: public IClientSocket
	{
	public:
		struct TConnectionInfo
		{			
			int   iSessionID;   // �ỰID, ��ͻ���socket��Session��Ӧ
			DWORD dwChannelNums;   //  ��ͨChannel����, ���������Ϊ2
			DWORD vtChannelID[10];   //  ͨ��ID, ʵ�ʸ����ο�dwChannelNums�ֶ�
		};

	public:
		//  ��ȡ���ӵ���Ϣ
		virtual BOOL GetConnectionInfo(TConnectionInfo *pOut) = 0;

		//  �Ͽ�ĳ�����ӵ�ĳ��ͨ��(��������������������������ж�)
		virtual BOOL DisconnChannel(DWORD dwChannelIndex) = 0;

	};


	class ISocketSystem 
	{
	public:
		//   socket�汾��
		enum EN_VERSION
		{
			VER_1 = 0,    // ʵ�ֻ���ͨ�Ź���, ÿ��IScocket�ڲ�ά��1������, �ʺ����û����ͨ��
			VER_2,    // ÿ�������ڲ�ʹ��2������, һ������һ����������, �����л�����һ����.�ʺϷ�����֮��ͨ��.
		};


	public:
		
		//************************************
		// Method:    ��ʼ��SocketSystem
		// FullName:  socketsystem::ISocketSystem::Create
		// Parameter: DWORD dwMaxClientSocket       ��ͬʱ�����Ŀͻ���socket������. �����������, �Ͳ��ܴ���ClientSocket��
		//************************************
		virtual BOOL Create(DWORD dwMaxClientSocket = 128) = 0;
 

		// �ͷ�
		virtual void Release() = NULL;

		// ��  ��������һ�������Socket
		// ��  ����[����] IServerSocketSink *pServerSocketSink - �ص�����
		// ��  ����[����] BOOL bEncrypt - �Ƿ���Ҫ�ӽ��ܷ���
		// ����ֵ��IServerSocket* -	����������ɹ�����NULL
		virtual IServerSocket* CreateServerSocket(EN_VERSION enVersion = VER_1) = NULL;

		// �����ͻ���Socket
		virtual IClientSocket* CreateClientSocket(EN_VERSION enVersion = VER_1) = NULL;

		// �ƶ�socketϵͳ������Ϣ. ����д������Ϣ, ����TRUE; ���򷵻�FALSE
		virtual BOOL ProcessSocketMsg(BOOL bOnlyPushClient = FALSE) = 0;

		
		//************************************
		// Method:    �����־��Ϣ				
		// Returns:   BOOL                    ���������־, ����TRUE. ʧ�ܷ���FALSE, ��ȡ������������Ч.
		// Parameter: int & iLogLevel         ��־�ļ���, ����LOG_LEVEL
		// Parameter: char * pBuffer          ��־������, �������λ����������LOG��Ϣ, �����ض�
		// Parameter: int iLen                ��־��������С  
		//************************************
		virtual BOOL PopSocketSysLog(int &iLogLevel, char *pBuffer, int iLen) = 0;

		//  ��ȡsocket���Ʋ���
		virtual const TSocketLimit & GetClientSocketLimit() = 0;		
		virtual void SetClientSocketLimit(const TSocketLimit &stLimit) = 0;

		//////////////////  ��־����, ��Ҫ��socketϵͳ����(����start())ǰ����   /////////////////////		
		//    ��־����ʱĬ����LOGLV_FATAL, LOGLV_INFO_1 ��2���������־
		virtual void DisableAllLog() = 0;   //   ��ֹȫ����־
		virtual void ModifyLogLevel(LOG_LEVEL enLV, BOOL bEnable) = 0;   //   ����/��ֹĳһ�������־
		virtual BOOL IsLogLevelEnable(LOG_LEVEL enLV) = 0;   //   ���Ըü������־�Ƿ�������
	};


};




#endif//__ISOCKETSYSTEM_H__

