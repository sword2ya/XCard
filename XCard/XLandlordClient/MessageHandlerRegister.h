#pragma once

class IMessageHandler;

class CMessageHandlerRegister
{
	typedef map<int, IMessageHandler*> TMap_MessageHandler;
public:
	CMessageHandlerRegister(void);
	~CMessageHandlerRegister(void);

	void InitMessageHandlers();
	void UnInitMessageHandlers();

private:
	void __RegisterMessageHandler(int nMsgID, IMessageHandler* pMsgHandler);
	
private:
	TMap_MessageHandler m_mapMessageHandler;
};
