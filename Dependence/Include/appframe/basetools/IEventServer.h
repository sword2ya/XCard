#ifndef __IEVENTSERVER_H__
#define __IEVENTSERVER_H__

namespace basetools
{



class IEvent
{
public:
	/**
	* 获取事件的提供者. 
	*
	* @param param1 	
	* @return   事件提供者对象. 如果即使订阅消息时使用了null作为提供者, 这个值会返回真正触发消息的对象		
	* @see IEventServer
	*/	
	virtual void* GetProvider( void ) = 0;

	/**
	* 获取事件发派的源结点ID
	*
	* @param param1  		
	* @return    事件派发的源结点ID		
	* @see IActionEventSink
	*/
	virtual DWORD GetSrcNode( void ) = 0;

	/**
	* 获取事件现场
	*
	* @param param1  		
	* @return    事件的现场, 这个对象就是Fire消息时, 传入的现场. 
	*/
	virtual void* GetContext( void ) = 0;

	/**
	* 获取事件现场的长度
	*
	* @param param1  		
	* @return    事件的现场的长度
	*/
	virtual DWORD GetContextLen( void ) = 0;

	/**
	* 获取事件ID
	*
	* @param param1  		
	* @return    事件ID			
	*/
	virtual DWORD GetMsgID( void ) = 0;
};


class IActionEventSink
{
public:

	/**
	* Action事件发生回调 
	*
	* @param param1   对应的事件对象pEvent	
	* @return        无		
	* @see IEvent
	*/	
	virtual void  OnAction( IEvent* pEvent ) = 0;
};


class IVoteEventSink
{
public:
	/**
	* Vote事件发生回调 
	*
	* @param param1   对应的事件对象pEvent	
	* @return        是否需要对事件投反对票, 如果返回值为false, 这个事件不会通知后一个监听者		
	* @see IEvent
	*/	
	virtual BOOL OnVote( IEvent* pEvent ) = 0;
};


class IResponseEventSink
{
public:
	/**
	* Response事件发生回调 
	*
	* @param param1   对应的事件对象pEvent	
	* @return         无
	* @see IEvent
	*/	
	virtual BOOL OnResponse( IEvent* pEvent ) = 0;
};




/**	
*  事件服务器接口, 通过它来订阅消息, 发布消息, 退订消息
*/

class IEventServer
{
public:


	/**
	* 用pSink来订阅一个投票消息 
	*
	* @param param1 当事件发生时, 用于回调的sink 
	* @param param2 消息码, 应用层自行制定并使用
	* @param param3 消息路径ID, 即消息树中的某一结点的ID. 消息在当前结点分派完后, 会沿着父结点向上分发, 直到遇到根结点为止.
	* @param param4 提供消息的对象. 如果这个对象为null, 则事件服会忽略消息提供对象, 直接给监听器发送消息.	
	* @param param5 描述, 这个值需要传一个全局字符串常量. 用于在事件服出错时, 可根据这个描述输出跟踪信息
	* @return   如果pSink不为空, 且没有在nMsgNode结点中订阅过这个消息. 则返回true; 否则返回false.		
	* @see IVoteEventSink
	*/		
	virtual BOOL AddVoteListener( IVoteEventSink* pSink, DWORD dwMsgID,DWORD dwMsgNode, void* pProvider, const char* szDesc = NULL) = 0;

	/**
	* 用pSink来订阅一个动作消息 , 
	*
	* @param param1 当事件发生时, 用于回调的sink 
	* @param param2 消息码, 应用层自行制定并使用
	* @param param3 消息路径ID, 即消息树中的某一结点的ID. 消息在当前结点分派完后, 会沿着父结点向上分发, 直到遇到根结点为止.
	* @param param4 提供消息的对象. 如果这个对象为null, 则事件服会忽略消息提供对象, 直接给监听器发送消息.
	* @param param5 描述, 这个值需要传一个全局字符串常量. 用于在事件服出错时, 可根据这个描述输出跟踪信息
	* @return       如果pSink不为空, 且没有在nMsgNode结点中订阅过这个消息. 则返回true; 否则返回false.		
	* @see IActionEventSink
	*/		
	virtual BOOL AddActionListener( IActionEventSink* pSink,DWORD  dwMsgID ,DWORD  dwMsgNode, void* pProvider, const char* szDesc = NULL) = 0;

	/**
	* 用pSink来订阅一个动作消息 , 
	*
	* @param param1 当事件发生时, 用于回调的sink 
	* @param param2 消息码, 应用层自行制定并使用
	* @param param3 消息路径ID, 即消息树中的某一结点的ID. 消息在当前结点分派完后, 会沿着父结点向上分发, 直到遇到根结点为止.
	* @param param4 提供消息的对象. 如果这个对象为null, 则事件服会忽略消息提供对象, 直接给监听器发送消息.
	* @param param5 描述, 这个值需要传一个全局字符串常量. 用于在事件服出错时, 可根据这个描述输出跟踪信息
	* @return       如果pSink不为空, 且没有在nMsgNode结点中订阅过这个消息. 则返回true; 否则返回false.		
	* @see IResponseEventSink
	*/		
	virtual BOOL AddResponseListener( IResponseEventSink* pSink,DWORD  dwMsgID ,DWORD  dwMsgNode, void* pProvider, const char* szDesc = NULL) = 0;


	/**
	* 发布一个投票消息 
	* 如果其中一个订阅者投了反对(false)票, 则后继的订阅者都不会再收到消息 
	*  
	* @param param1 消息码, 应用层自行制定并使用
	* @param param2 消息现场, 应用层自行制定并使用
	* @param param3 消息路径ID, 即消息树中的某一结点的ID. 消息在当前结点分派完后, 会沿着父结点向上分发, 直到遇到根结点为止.
	* @param param4 提供消息的对象. 如果这个对象为null, 只有订阅null的监听器都会收到响应.		
	* @return      如果全部监听器都返回true, 则FireVoteEvent()返回true; 否则返回false
	* @see IVoteEventSink
	*/		
	virtual BOOL FireVoteEvent( DWORD  dwMsgID  , void* pContext, DWORD dwContextLen, DWORD  dwMsgNode, void* pProvider ) = 0;

	/**
	* 用pSink来订阅一个动作消息 
	* 与Vote不同, Action监听器的消息无法取消, 会广播至全部的监听器
	*
	* @param param1 消息码, 应用层自行制定并使用
	* @param param2 消息现场, 应用层自行制定并使用
	* @param param3 消息路径ID, 即消息树中的某一结点的ID. 消息在当前结点分派完后, 会沿着父结点向上分发, 直到遇到根结点为止.
	* @param param4 提供消息的对象. 如果这个对象为null, 只有订阅null的监听器都会收到响应.	
	* @return       无	
	* @see IActionEventSink
	*/		
	virtual void FireActionEvent( DWORD  dwMsgID  , void* pContext, DWORD dwContextLen, DWORD  dwMsgNode, void* pProvider ) = 0;

	
	/**
	* 用pSink来订阅一个动作消息 
	* 与Vote不同, Response监听器的消息无法取消, 会广播至全部的监听器
	*
	* @param param1 消息码, 应用层自行制定并使用
	* @param param2 消息现场, 应用层自行制定并使用
	* @param param3 消息路径ID, 即消息树中的某一结点的ID. 消息在当前结点分派完后, 会沿着父结点向上分发, 直到遇到根结点为止.
	* @param param4 提供消息的对象. 如果这个对象为null, 只有订阅null的监听器都会收到响应.	
	* @return       无	
	* @see IActionEventSink
	*/		
	virtual void FireResponseEvent( DWORD  dwMsgID  , void* pContext, DWORD dwContextLen, DWORD  dwMsgNode, void* pProvider ) = 0;

	/**
	* 取消订阅一个投票消息 
	*
	* @param param1 当事件发生时, 用于回调的sink 
	* @param param2 消息码, 应用层自行制定并使用
	* @param param3 消息路径ID, 即消息树中的某一结点的ID. 消息在当前结点分派完后, 会沿着父结点向上分发, 直到遇到根结点为止.
	* @param param4 提供消息的对象. 如果这个对象为null, 则事件服会忽略消息提供对象, 直接给监听器发送消息.	
	* @return   如果pSink不为空, 且没有在nMsgNode结点中订阅过这个消息. 则返回true; 否则返回false.		
	* @see IVoteEventSink
	*/		
	virtual void RemoveVoteListener(  IVoteEventSink* pSink, DWORD  dwMsgID ,DWORD  dwMsgNode, void* pProvider) = 0;

	/**
	* 取消订阅一个动作消息 
	*
	* @param param1 当事件发生时, 用于回调的sink 
	* @param param2 消息码, 应用层自行制定并使用
	* @param param3 消息路径ID, 即消息树中的某一结点的ID. 消息在当前结点分派完后, 会沿着父结点向上分发, 直到遇到根结点为止.
	* @param param4 提供消息的对象. 如果这个对象为null, 则事件服会忽略消息提供对象, 直接给监听器发送消息.
	* @return   如果pSink不为空, 且没有在nMsgNode结点中订阅过这个消息. 则返回true; 否则返回false.		
	* @see IActionEventSink
	*/		
	virtual void RemoveActionListener( IActionEventSink* pSink, DWORD  dwMsgID ,DWORD  dwMsgNode, void* pProvider ) = 0;

	/**
	* 取消订阅一个动作消息 
	*
	* @param param1 当事件发生时, 用于回调的sink 
	* @param param2 消息码, 应用层自行制定并使用
	* @param param3 消息路径ID, 即消息树中的某一结点的ID. 消息在当前结点分派完后, 会沿着父结点向上分发, 直到遇到根结点为止.
	* @param param4 提供消息的对象. 如果这个对象为null, 则事件服会忽略消息提供对象, 直接给监听器发送消息.
	* @return   如果pSink不为空, 且没有在nMsgNode结点中订阅过这个消息. 则返回true; 否则返回false.		
	* @see IResponseEventSink
	*/		
	virtual void RemoveResponseListener( IResponseEventSink* pSink, DWORD  dwMsgID ,DWORD  dwMsgNode, void* pProvider ) = 0;


	/**
	* 使用一个数组创建消息路由树
	*
	* @param param1    描述消息树的数组. 也可以填入null, 于用恢复默认路由模式.
	*         1     数组可看作是一个Key-value的映射表.  KEY代表消息路径中的结点, VALUE是这个结点的父结点的ID
	*         2     根结点的ID为0, 消息在根结点派发完后, 会结束派发循环. 应用层在定义结点ID的值时, 尽量从0开始累进往上增加.
	*         3    对于传入的Array, 内部会将数据保留一份, 不用担心pMsgTree外部修改后消息路径会被改变.
	*         4    消息树默认为null, 这个时候消息只会在本结点传播, 连根结点(0)都不会传播.  
	* @return    设置成功返回true, 失败返回false		
	*/		
	virtual BOOL  CreateMsgDispatchTree( DWORD* pMsgTree ,  DWORD dwSize ) = 0 ;


	/**
	* 释放事件服
	*
	* @param param1    无	
	* @return          无
	*/		
	virtual void Release() = 0;
};

};  //  namespace

#endif