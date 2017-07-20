#ifndef __IEVENTSERVER_H__
#define __IEVENTSERVER_H__

namespace basetools
{



class IEvent
{
public:
	/**
	* ��ȡ�¼����ṩ��. 
	*
	* @param param1 	
	* @return   �¼��ṩ�߶���. �����ʹ������Ϣʱʹ����null��Ϊ�ṩ��, ���ֵ�᷵������������Ϣ�Ķ���		
	* @see IEventServer
	*/	
	virtual void* GetProvider( void ) = 0;

	/**
	* ��ȡ�¼����ɵ�Դ���ID
	*
	* @param param1  		
	* @return    �¼��ɷ���Դ���ID		
	* @see IActionEventSink
	*/
	virtual DWORD GetSrcNode( void ) = 0;

	/**
	* ��ȡ�¼��ֳ�
	*
	* @param param1  		
	* @return    �¼����ֳ�, ����������Fire��Ϣʱ, ������ֳ�. 
	*/
	virtual void* GetContext( void ) = 0;

	/**
	* ��ȡ�¼��ֳ��ĳ���
	*
	* @param param1  		
	* @return    �¼����ֳ��ĳ���
	*/
	virtual DWORD GetContextLen( void ) = 0;

	/**
	* ��ȡ�¼�ID
	*
	* @param param1  		
	* @return    �¼�ID			
	*/
	virtual DWORD GetMsgID( void ) = 0;
};


class IActionEventSink
{
public:

	/**
	* Action�¼������ص� 
	*
	* @param param1   ��Ӧ���¼�����pEvent	
	* @return        ��		
	* @see IEvent
	*/	
	virtual void  OnAction( IEvent* pEvent ) = 0;
};


class IVoteEventSink
{
public:
	/**
	* Vote�¼������ص� 
	*
	* @param param1   ��Ӧ���¼�����pEvent	
	* @return        �Ƿ���Ҫ���¼�Ͷ����Ʊ, �������ֵΪfalse, ����¼�����֪ͨ��һ��������		
	* @see IEvent
	*/	
	virtual BOOL OnVote( IEvent* pEvent ) = 0;
};


class IResponseEventSink
{
public:
	/**
	* Response�¼������ص� 
	*
	* @param param1   ��Ӧ���¼�����pEvent	
	* @return         ��
	* @see IEvent
	*/	
	virtual BOOL OnResponse( IEvent* pEvent ) = 0;
};




/**	
*  �¼��������ӿ�, ͨ������������Ϣ, ������Ϣ, �˶���Ϣ
*/

class IEventServer
{
public:


	/**
	* ��pSink������һ��ͶƱ��Ϣ 
	*
	* @param param1 ���¼�����ʱ, ���ڻص���sink 
	* @param param2 ��Ϣ��, Ӧ�ò������ƶ���ʹ��
	* @param param3 ��Ϣ·��ID, ����Ϣ���е�ĳһ����ID. ��Ϣ�ڵ�ǰ���������, �����Ÿ�������Ϸַ�, ֱ�����������Ϊֹ.
	* @param param4 �ṩ��Ϣ�Ķ���. ����������Ϊnull, ���¼����������Ϣ�ṩ����, ֱ�Ӹ�������������Ϣ.	
	* @param param5 ����, ���ֵ��Ҫ��һ��ȫ���ַ�������. �������¼�������ʱ, �ɸ�������������������Ϣ
	* @return   ���pSink��Ϊ��, ��û����nMsgNode����ж��Ĺ������Ϣ. �򷵻�true; ���򷵻�false.		
	* @see IVoteEventSink
	*/		
	virtual BOOL AddVoteListener( IVoteEventSink* pSink, DWORD dwMsgID,DWORD dwMsgNode, void* pProvider, const char* szDesc = NULL) = 0;

	/**
	* ��pSink������һ��������Ϣ , 
	*
	* @param param1 ���¼�����ʱ, ���ڻص���sink 
	* @param param2 ��Ϣ��, Ӧ�ò������ƶ���ʹ��
	* @param param3 ��Ϣ·��ID, ����Ϣ���е�ĳһ����ID. ��Ϣ�ڵ�ǰ���������, �����Ÿ�������Ϸַ�, ֱ�����������Ϊֹ.
	* @param param4 �ṩ��Ϣ�Ķ���. ����������Ϊnull, ���¼����������Ϣ�ṩ����, ֱ�Ӹ�������������Ϣ.
	* @param param5 ����, ���ֵ��Ҫ��һ��ȫ���ַ�������. �������¼�������ʱ, �ɸ�������������������Ϣ
	* @return       ���pSink��Ϊ��, ��û����nMsgNode����ж��Ĺ������Ϣ. �򷵻�true; ���򷵻�false.		
	* @see IActionEventSink
	*/		
	virtual BOOL AddActionListener( IActionEventSink* pSink,DWORD  dwMsgID ,DWORD  dwMsgNode, void* pProvider, const char* szDesc = NULL) = 0;

	/**
	* ��pSink������һ��������Ϣ , 
	*
	* @param param1 ���¼�����ʱ, ���ڻص���sink 
	* @param param2 ��Ϣ��, Ӧ�ò������ƶ���ʹ��
	* @param param3 ��Ϣ·��ID, ����Ϣ���е�ĳһ����ID. ��Ϣ�ڵ�ǰ���������, �����Ÿ�������Ϸַ�, ֱ�����������Ϊֹ.
	* @param param4 �ṩ��Ϣ�Ķ���. ����������Ϊnull, ���¼����������Ϣ�ṩ����, ֱ�Ӹ�������������Ϣ.
	* @param param5 ����, ���ֵ��Ҫ��һ��ȫ���ַ�������. �������¼�������ʱ, �ɸ�������������������Ϣ
	* @return       ���pSink��Ϊ��, ��û����nMsgNode����ж��Ĺ������Ϣ. �򷵻�true; ���򷵻�false.		
	* @see IResponseEventSink
	*/		
	virtual BOOL AddResponseListener( IResponseEventSink* pSink,DWORD  dwMsgID ,DWORD  dwMsgNode, void* pProvider, const char* szDesc = NULL) = 0;


	/**
	* ����һ��ͶƱ��Ϣ 
	* �������һ��������Ͷ�˷���(false)Ʊ, ���̵Ķ����߶��������յ���Ϣ 
	*  
	* @param param1 ��Ϣ��, Ӧ�ò������ƶ���ʹ��
	* @param param2 ��Ϣ�ֳ�, Ӧ�ò������ƶ���ʹ��
	* @param param3 ��Ϣ·��ID, ����Ϣ���е�ĳһ����ID. ��Ϣ�ڵ�ǰ���������, �����Ÿ�������Ϸַ�, ֱ�����������Ϊֹ.
	* @param param4 �ṩ��Ϣ�Ķ���. ����������Ϊnull, ֻ�ж���null�ļ����������յ���Ӧ.		
	* @return      ���ȫ��������������true, ��FireVoteEvent()����true; ���򷵻�false
	* @see IVoteEventSink
	*/		
	virtual BOOL FireVoteEvent( DWORD  dwMsgID  , void* pContext, DWORD dwContextLen, DWORD  dwMsgNode, void* pProvider ) = 0;

	/**
	* ��pSink������һ��������Ϣ 
	* ��Vote��ͬ, Action����������Ϣ�޷�ȡ��, ��㲥��ȫ���ļ�����
	*
	* @param param1 ��Ϣ��, Ӧ�ò������ƶ���ʹ��
	* @param param2 ��Ϣ�ֳ�, Ӧ�ò������ƶ���ʹ��
	* @param param3 ��Ϣ·��ID, ����Ϣ���е�ĳһ����ID. ��Ϣ�ڵ�ǰ���������, �����Ÿ�������Ϸַ�, ֱ�����������Ϊֹ.
	* @param param4 �ṩ��Ϣ�Ķ���. ����������Ϊnull, ֻ�ж���null�ļ����������յ���Ӧ.	
	* @return       ��	
	* @see IActionEventSink
	*/		
	virtual void FireActionEvent( DWORD  dwMsgID  , void* pContext, DWORD dwContextLen, DWORD  dwMsgNode, void* pProvider ) = 0;

	
	/**
	* ��pSink������һ��������Ϣ 
	* ��Vote��ͬ, Response����������Ϣ�޷�ȡ��, ��㲥��ȫ���ļ�����
	*
	* @param param1 ��Ϣ��, Ӧ�ò������ƶ���ʹ��
	* @param param2 ��Ϣ�ֳ�, Ӧ�ò������ƶ���ʹ��
	* @param param3 ��Ϣ·��ID, ����Ϣ���е�ĳһ����ID. ��Ϣ�ڵ�ǰ���������, �����Ÿ�������Ϸַ�, ֱ�����������Ϊֹ.
	* @param param4 �ṩ��Ϣ�Ķ���. ����������Ϊnull, ֻ�ж���null�ļ����������յ���Ӧ.	
	* @return       ��	
	* @see IActionEventSink
	*/		
	virtual void FireResponseEvent( DWORD  dwMsgID  , void* pContext, DWORD dwContextLen, DWORD  dwMsgNode, void* pProvider ) = 0;

	/**
	* ȡ������һ��ͶƱ��Ϣ 
	*
	* @param param1 ���¼�����ʱ, ���ڻص���sink 
	* @param param2 ��Ϣ��, Ӧ�ò������ƶ���ʹ��
	* @param param3 ��Ϣ·��ID, ����Ϣ���е�ĳһ����ID. ��Ϣ�ڵ�ǰ���������, �����Ÿ�������Ϸַ�, ֱ�����������Ϊֹ.
	* @param param4 �ṩ��Ϣ�Ķ���. ����������Ϊnull, ���¼����������Ϣ�ṩ����, ֱ�Ӹ�������������Ϣ.	
	* @return   ���pSink��Ϊ��, ��û����nMsgNode����ж��Ĺ������Ϣ. �򷵻�true; ���򷵻�false.		
	* @see IVoteEventSink
	*/		
	virtual void RemoveVoteListener(  IVoteEventSink* pSink, DWORD  dwMsgID ,DWORD  dwMsgNode, void* pProvider) = 0;

	/**
	* ȡ������һ��������Ϣ 
	*
	* @param param1 ���¼�����ʱ, ���ڻص���sink 
	* @param param2 ��Ϣ��, Ӧ�ò������ƶ���ʹ��
	* @param param3 ��Ϣ·��ID, ����Ϣ���е�ĳһ����ID. ��Ϣ�ڵ�ǰ���������, �����Ÿ�������Ϸַ�, ֱ�����������Ϊֹ.
	* @param param4 �ṩ��Ϣ�Ķ���. ����������Ϊnull, ���¼����������Ϣ�ṩ����, ֱ�Ӹ�������������Ϣ.
	* @return   ���pSink��Ϊ��, ��û����nMsgNode����ж��Ĺ������Ϣ. �򷵻�true; ���򷵻�false.		
	* @see IActionEventSink
	*/		
	virtual void RemoveActionListener( IActionEventSink* pSink, DWORD  dwMsgID ,DWORD  dwMsgNode, void* pProvider ) = 0;

	/**
	* ȡ������һ��������Ϣ 
	*
	* @param param1 ���¼�����ʱ, ���ڻص���sink 
	* @param param2 ��Ϣ��, Ӧ�ò������ƶ���ʹ��
	* @param param3 ��Ϣ·��ID, ����Ϣ���е�ĳһ����ID. ��Ϣ�ڵ�ǰ���������, �����Ÿ�������Ϸַ�, ֱ�����������Ϊֹ.
	* @param param4 �ṩ��Ϣ�Ķ���. ����������Ϊnull, ���¼����������Ϣ�ṩ����, ֱ�Ӹ�������������Ϣ.
	* @return   ���pSink��Ϊ��, ��û����nMsgNode����ж��Ĺ������Ϣ. �򷵻�true; ���򷵻�false.		
	* @see IResponseEventSink
	*/		
	virtual void RemoveResponseListener( IResponseEventSink* pSink, DWORD  dwMsgID ,DWORD  dwMsgNode, void* pProvider ) = 0;


	/**
	* ʹ��һ�����鴴����Ϣ·����
	*
	* @param param1    ������Ϣ��������. Ҳ��������null, ���ûָ�Ĭ��·��ģʽ.
	*         1     ����ɿ�����һ��Key-value��ӳ���.  KEY������Ϣ·���еĽ��, VALUE��������ĸ�����ID
	*         2     ������IDΪ0, ��Ϣ�ڸ�����ɷ����, ������ɷ�ѭ��. Ӧ�ò��ڶ�����ID��ֵʱ, ������0��ʼ�۽���������.
	*         3    ���ڴ����Array, �ڲ��Ὣ���ݱ���һ��, ���õ���pMsgTree�ⲿ�޸ĺ���Ϣ·���ᱻ�ı�.
	*         4    ��Ϣ��Ĭ��Ϊnull, ���ʱ����Ϣֻ���ڱ���㴫��, �������(0)�����ᴫ��.  
	* @return    ���óɹ�����true, ʧ�ܷ���false		
	*/		
	virtual BOOL  CreateMsgDispatchTree( DWORD* pMsgTree ,  DWORD dwSize ) = 0 ;


	/**
	* �ͷ��¼���
	*
	* @param param1    ��	
	* @return          ��
	*/		
	virtual void Release() = 0;
};

};  //  namespace

#endif