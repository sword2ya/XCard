/********************************************************************
	created:	2012/6/14  14:59
	file base:	ISocketSystem
	file ext:	h
	author:		
	
	purpose:	socketsystem接口文件
*********************************************************************/

#ifndef __ISOCKETSYSTEM_H__
#define __ISOCKETSYSTEM_H__


class ITrace;

namespace socketsystem
{
	//  日志
	enum LOG_LEVEL{
		LOGLV_FATAL = 0,   //致命错误, 可能会导致服务停止
		LOGLV_INFO_1,      //比较重根的信息, 例如执行保护策略等
		LOGLV_INFO_2,      //很普通的信息,例如客户端连接, 断开等事件
	};

	//  对特殊包头的处理器
	enum EN_SPECPKG_HANDLER
	{
		enIgnorePkg,            //忽略此包
		enSendFlashPolicy,      //发送flash策略
	};
	
	//  socket限制
	struct TSocketLimit
	{
		__int64 iRecvBufferBytes;   // 接收缓冲区字节数
		__int64 iSendBufferBytes;   // 发送缓冲区字节数

		BOOL bSendBlockFix;            // 是否清除发送阻塞的用户. 
		int iSendBlockStandard;                  // 单连接发送堵包(个数)限制. 堵包超过这个长度会被踢
		BOOL bRecvBlockFix;              // 是否清除接收阻塞的用户
		int iRecvBlockStandard;                  // 单连接接收堵包(个数)限制. 通信线程接收到数据包后, 每一轮只会向逻辑线程转出iPkgPushPerFrame个包, 为各连接获利公平处理. 如果远端发包过快, 则会被踢下去.
		int iRecvPkgMaxBytes;   // 单包最大长度, 远程端发送超过这个长度的包, 会被踢
		int iPkgPushPerFrame;    //在一帧中, 完成包推送个数. 增大这个值可以提高接收吞吐量, 但对于不可信任的远程连接, 可能会发送大量数据包,骗取CPU时间. 如果这个值<=0, 则表示全部包同时推送
		BOOL  bForceRecycleSendBlock;    //在没有发送缓冲区时, 是否强制回收
		BOOL  bForceRecycleRecvBlock;    //在没有接收缓冲区时, 是否强制回收
			
		//  设置默认参数
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

	//  server socket的统计数据
	struct TServerSocStat
	{
		__int64 iSendBytes;             // 发送字节数
		__int64 iRecvBytes;             // 接收字节数
		__int64 iSendPkgNums;           // 发送包数
		__int64 iRecvPkgNums;           // 接收包数
		__int64 iSendBufferMaxBytes;    // 发送缓冲区最大容量
		__int64 iSendBufferCurBytes;   // 发送缓冲区当前容量
		__int64 iRecvBufferMaxBytes;    // 接收缓冲区最大容量
		__int64 iRecvBufferCurBytes;    // 接收缓冲区当前容量
		__int64 iAccumulateConnectNums;  // 客户端累计连接数
		__int64 iCurConnectNums;         // 当前连接数
	};

	//////////////////////////////////////////////////////////////////////////
	//服务端必须实现的接口 
	//接收客户端数据或者客户端关闭时回调
	class IClientSink
	{
	public:
		// 接收到数据
		virtual void OnRecv(DWORD dwSocketID, LPCSTR Buf, int nLen) = NULL;

		// 客户端断开连接回调
		virtual void OnCloseConnect(DWORD dwSocketID) = NULL;
	};

	//当有客户端接入时回调
	class IServerSocketSink
	{
	public:
		// 客户端新连接回调
		virtual void OnAccept(DWORD dwSocketID, IClientSink **ppClientSink) = NULL;		
	};


	//////////////////////////////////////////////////////////////////////////
	//客户端必须实现的接口
	//
	class IClientSocket;
	class IClientSocketSink
	{
	public:
		// 接收到数据
		virtual void OnRecv(IClientSocket *pClientSocket, LPCSTR Buf, int nLen) = NULL;

		// 断开连接回调,一般是服务端断开
		virtual void OnCloseConnect(IClientSocket *pClientSocket) = NULL;

		// 连接回调
		virtual void OnConnect(IClientSocket *pClientSocket) = NULL;

		// 连接错误
		virtual void OnConnectError(IClientSocket *pClientSocket, int nErrorCode) = NULL;
	};


	//      组包规则每个数据包发送时需要按一定规则进行组包, 接收时都需要按一定规则进行解包
	//  socketsystem内部已经带有一套规则 (包长int + 包内容) , 应用可通过继承本接口, 重写自
	//  己的解包和组包
	class IBinBuffer;   // 缓冲区, 用于保存即将发送, 或者刚接收到的数据
	class IPackageRule   
	{
	public:
		//  解包结果
		enum En_Unpack_Result
		{
			enUnpackComplete,   // 完成一个数据包
			enUnpackWait,       // 数据不足, 需要等待新数据
			enUnpackError,      // 解包错误
		};

	public:
		
		//************************************
		// Method:    OnPackagePack                   socketsystem组包时调用此函数
		// Returns:   bool
		// Qualifier:
		// Parameter: IBuffer * pOutBuffer            输出缓冲区
		// Parameter: LPCSTR pSrcData                 源数据, 这个是由应用层调用  Socket::Send() 方法传入的数据
		// Parameter: int iLen                        源数据的长度
		// Parameter: char * pErrorDesc               错误描述缓冲区, 如果解包过程中发生错误, 可以将日志写在这里
		// Parameter: int iErrLen                     错误缓冲区长度
		//      memo: 解包函数和组包函数会由不同的线程调用.   应用继承这个类时, 注意线程安全. 最好不要有类成员
		//************************************
		virtual bool OnPackagePack(IBinBuffer *pOutBuffer, LPCSTR pSrcData, int iLen, char *pErrorDesc, int iErrLen) = 0;

		
		
		//************************************
		// Method:    OnPackageUnpack                 socketsystem解包时调用此函数		
		// Returns:   socketsystem::IPackageRule::En_Unpack_Result      如果返回enUnpackWait, socketsystem会将数据暂存起来;
		//                                                                  返回enUnpackComplete, socketsystem 稍后会将数据提交给应用层.剩下的数据会作为下一个包的内容暂时保存起来       
		//                                                                  返回enUnpackError, socketsystem 会断开连接, 因为后面的数据已经无法解释                                                      
		// Qualifier:
		// Parameter: IBinBuffer * pRecvBuffer                          接收缓冲区, 里面放的是未组包的数据. 如果数据未能构成一个包, 应用不要弹出里面的数据, 下次再收到数据会累加在尾部
		// Parameter: IBinBuffer *pFinishPkgBuffer                      输出缓冲区, 本参数在enUnpackComplete才需要往里面填写. 每次调用, 只组1个包. 
		// Parameter: bool bIsFirstPkg                                  是否为第一个包. 有很多系统要求第一个包是特殊的应答, 例如flash的策略请求, 加入这个参数, 帮助解包器判断优化处理
		// Parameter: char * pErrorDesc	                                错误描述缓冲区, 如果解包过程中发生错误, 可以将日志写在这里
		// Parameter: int iErrLen                                       错误缓冲区长度
		//      memo: 解包函数和组包函数会由不同的线程调用.   应用继承这个类时, 注意线程安全. 最好不要有类成员
		//************************************
		virtual En_Unpack_Result OnPackageUnpack(IBinBuffer *pFinishPkgBuffer, IBinBuffer *pRecvBuffer, bool bIsFirstPkg, char *pErrorDesc, int iErrLen) = 0;
	};

	class IBinBuffer
	{
	public:
		//  往缓冲区中写入数据, 如果返回 false, 则表示数据无法写入(通常是内存使用达到指定的界限值)
		virtual bool WriteData(LPCSTR pBuffer, DWORD dwLen) = 0;

		//  获取缓冲区中有多少可用数据
		virtual DWORD GetAvalibleBytes() = 0;


		//************************************
		// Method:    ReadData                    读取缓冲区中的数据	
		// Returns:   char *                          数据指针.  注意, 出于性能考虑, 如果要提取的数据连续, 则会直接返回源数据指针,并不会把数据复制到用户给定的缓冲区中. 
		//                                        即, 这个返回值不一定会是pBuffer
		// Qualifier:
		// Parameter: char * pBuffer              用于装载返回的数据, 这个缓冲区不能少于dwRead指定的值
		// Parameter: DWORD dwRead                期望读取的字节数
		// Parameter: DWORD & dwActualRead        实际读取到的字节数
		//     memo :     读取数据时, 不会影响缓冲区的当前位置.  连续调用这个方法N次, 读取到的都是一样的内容. 如果想读取后面的内容, 调用PopFront()方法
		//************************************
		virtual char *ReadData(char *pBuffer, DWORD dwRead, DWORD &dwActualRead) = 0;

	
		//************************************
		// Method:    PopFront                    从缓冲区前面弹出指定字节数
		// Returns:   void
		//
		// Parameter: DWORD dwBytes               字节数
		//************************************
		virtual void PopFront(DWORD dwBytes) = 0;



		//************************************
		// Method:    MoveDataFromOtherBuffer        从另一个CBlockBuffer中move数据到本CBlockBuffer中
		// Returns:   bool                           move是否成功
		// Qualifier:
		// Parameter: IBinBuffer * pSrcBuffer        源数据缓冲区.  这个缓冲区不能是应用自行实现的, 一定要是socketsystem提供的IBinBuffer对象
		// Parameter: DWORD dwBytes                  需要搬移的字节数
		//************************************
		virtual bool MoveDataFromOtherBuffer(IBinBuffer *pSrcBuffer, DWORD dwBytes) = 0;
	};


	//客户端Socket
	class IClientSocket 
	{
	public:
		// 释放,会隐含CloseConnect()的操作
		virtual void Release() = NULL;

		// 连接
		virtual BOOL Connect(LPCSTR szServerIP, int iServerPort) = NULL;

		// 断开连接
		virtual void CloseConnect() = NULL;

		// 发送数据
		virtual BOOL Send(LPCSTR Buf, int nLen) = NULL;

		// 发送raw数据, socketsystem不会在数据前添加包头等信息
		virtual BOOL SendRaw(LPCSTR Buf, int nLen) = NULL;

		// 获取SocketID, 这个ID是client socket的ID.  与ServerSocket中的SocketID是不同的"编码空间"
		virtual DWORD GetSocketID() = NULL;		

		// 设置回调Sink
		virtual void setSocketSink(IClientSocketSink* pSink) = NULL;

		// 当前是否是连接上服务端的
		virtual BOOL isConnected() = NULL;

		// 当前是否正在连接服务端
		virtual BOOL isConnecting() = NULL;

		//  设置组包/解包策略
		virtual void SetPackageRule(IPackageRule *pCustomRule) = 0;

		//  获取组包/解包策略
		virtual IPackageRule *GetPackageRule() = 0;
	};

	//服务端Socket
	class IServerSocket
	{
	public:
		// 释放
		virtual void Release() = NULL;

		// 开始
		virtual BOOL Start(LPCSTR szServerIP, WORD wPort, int nConnectNum) = NULL;

		// 停止服务端Socket
		virtual void Stop() = NULL;

		// 发送
		virtual BOOL Send(DWORD dwSocketID, LPCSTR Buf, int nLen) = NULL;

		// 发送
		virtual BOOL Send(DWORD *pdwSocketIDs, int nIDNum, LPCSTR Buf, int nLen) = NULL;

		//主动关闭对方的连接
		virtual BOOL CloseConnect(DWORD dwSocketID) = NULL;

		// 设置服务端回调Sink
		virtual void SetClientSink(DWORD dwSocketID, IClientSink *pClientSink) = NULL;

		//获取客户端信息
		virtual BOOL GetClientInfo(DWORD dwSocketID, char *szIP, int iBufferLen, int &iPort) = NULL;	

		//当有客户端接入时回调
		virtual void setAcceptorSink(IServerSocketSink* pSink) = NULL;

		//获取最后一次错误信息
		virtual LPCSTR GetLastErrorDesc() = NULL;

		// 推动socket系统接收消息. 如果有处理过消息, 返回TRUE; 否则返回FALSE
		//  bOnlyPushClient参数指明, 是否只推动客户端消息. 即只有IClientSocket的sink会收到消息
		virtual BOOL ProcessSocketMsg() = 0;

		//  获取socket限制参数
		virtual const TSocketLimit & GetSocketLimit() = 0;		
		virtual void SetSocketLimit(const TSocketLimit &stLimit) = 0;

		//  获取统计数据
		virtual const TServerSocStat * GetStatistics() = 0;

		//  清空统计数据
		virtual void ClearStatistics() = 0;

		//  设置flash策略数据. 
		virtual void SetFlashPolicyData(LPCSTR pPolicyData, DWORD dwLen) = 0;


		//************************************
		// Method:    设置应对特殊包头的策略 .  这个接口需要在Start()前调用, 否则不起作用.
		// Returns:   void
		// Qualifier:
		// Parameter: LPCSTR pStringPkg                     数据包内容, 只支持以'\0'结尾的字符串
		// Parameter: EN_SPECPKG_HANDLER enHandler          对此数据包的处理
		//      memo:    (1)   特殊包处理只会对第1个包有效, 第二个包开始将作为普通数据包处理.
		//               (2)   目前会使用 memcmp 对数据包进行内容识别.  如果以后出现要对动态内容的识别, 可以考虑让应用
		//            传入校对函数对包内容进行检查.  
		//************************************
		virtual void AddSpecialPkgRule(LPCSTR szStringPkg, EN_SPECPKG_HANDLER enHandler) = 0;

		//  设置组包/解包策略
		virtual void SetPackageRule(IPackageRule *pCustomRule) = 0;

		//  获取组包/解包策略
		virtual IPackageRule *GetPackageRule() = 0;
	};

	//  v2版本的IServerSocket接口, 
	//  调用 CreateServerSocket()时使用V2参数得到的IServerSocket对象, 可以使用静态影射成这个对象
	class IServerSocketV2: public IServerSocket
	{
	public:
		struct TConnectionInfo
		{
			DWORD dwSocketID;
			int   iSessionID;   // 会话ID, 与客户端socket的Session对应
			DWORD dwChannelNums;   //  连通Channel数量, 正常情况下为2
			DWORD vtChannelID[10];   //  通道ID, 实际个数参考dwChannelNums字段
		};

	public:

		//  获取当前连接的数量
		virtual DWORD GetConnectionNum() = 0;
		
		//  获取连接的信息
		virtual BOOL GetConnectionInfo( DWORD dwIndex , TConnectionInfo *pOut) = 0;

		//  断开某个连接的某个通道(测试用例中用这个方法将连接切断)
		//  注意, 第0个参数是SocketID, 不是Index.  应该先通过GetConnectionInfo()获取TConnectionInfo::dwSocketID.
		virtual BOOL DisconnChannel(DWORD dwSocketID, DWORD dwChannelIndex) = 0;

	};

	//  v2版本的IClientSocket接口, 
	//  调用 CreateClientSocket()时使用V2参数得到的IClientSocket对象, 可以使用静态影射成这个对象
	class IClientSocketV2: public IClientSocket
	{
	public:
		struct TConnectionInfo
		{			
			int   iSessionID;   // 会话ID, 与客户端socket的Session对应
			DWORD dwChannelNums;   //  连通Channel数量, 正常情况下为2
			DWORD vtChannelID[10];   //  通道ID, 实际个数参考dwChannelNums字段
		};

	public:
		//  获取连接的信息
		virtual BOOL GetConnectionInfo(TConnectionInfo *pOut) = 0;

		//  断开某个连接的某个通道(测试用例中用这个方法将连接切断)
		virtual BOOL DisconnChannel(DWORD dwChannelIndex) = 0;

	};


	class ISocketSystem 
	{
	public:
		//   socket版本号
		enum EN_VERSION
		{
			VER_1 = 0,    // 实现基本通信功能, 每个IScocket内部维护1个连接, 适合与用户间的通信
			VER_2,    // 每个连接内部使用2个连接, 一但其中一个发生故障, 立即切换到另一连接.适合服务器之间通信.
		};


	public:
		
		//************************************
		// Method:    初始化SocketSystem
		// FullName:  socketsystem::ISocketSystem::Create
		// Parameter: DWORD dwMaxClientSocket       能同时创建的客户端socket的数量. 超过这个数量, 就不能创建ClientSocket了
		//************************************
		virtual BOOL Create(DWORD dwMaxClientSocket = 128) = 0;
 

		// 释放
		virtual void Release() = NULL;

		// 描  述：创建一个服务端Socket
		// 参  数：[输入] IServerSocketSink *pServerSocketSink - 回调函数
		// 参  数：[输入] BOOL bEncrypt - 是否需要加解密发送
		// 返回值：IServerSocket* -	如果不操作成功返回NULL
		virtual IServerSocket* CreateServerSocket(EN_VERSION enVersion = VER_1) = NULL;

		// 创建客户端Socket
		virtual IClientSocket* CreateClientSocket(EN_VERSION enVersion = VER_1) = NULL;

		// 推动socket系统接收消息. 如果有处理过消息, 返回TRUE; 否则返回FALSE
		virtual BOOL ProcessSocketMsg(BOOL bOnlyPushClient = FALSE) = 0;

		
		//************************************
		// Method:    输出日志信息				
		// Returns:   BOOL                    如果还有日志, 返回TRUE. 失败返回FALSE, 提取出来的数据无效.
		// Parameter: int & iLogLevel         日志的级别, 对照LOG_LEVEL
		// Parameter: char * pBuffer          日志缓冲区, 如果不够位置容纳整个LOG信息, 则发生截断
		// Parameter: int iLen                日志缓冲区大小  
		//************************************
		virtual BOOL PopSocketSysLog(int &iLogLevel, char *pBuffer, int iLen) = 0;

		//  获取socket限制参数
		virtual const TSocketLimit & GetClientSocketLimit() = 0;		
		virtual void SetClientSocketLimit(const TSocketLimit &stLimit) = 0;

		//////////////////  日志管理, 需要在socket系统启动(调用start())前设置   /////////////////////		
		//    日志启动时默认有LOGLV_FATAL, LOGLV_INFO_1 这2个级别的日志
		virtual void DisableAllLog() = 0;   //   禁止全部日志
		virtual void ModifyLogLevel(LOG_LEVEL enLV, BOOL bEnable) = 0;   //   允许/禁止某一级别的日志
		virtual BOOL IsLogLevelEnable(LOG_LEVEL enLV) = 0;   //   测试该级别的日志是否在运行
	};


};




#endif//__ISOCKETSYSTEM_H__

