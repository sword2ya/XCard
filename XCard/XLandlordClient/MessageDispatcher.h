#pragma once
#include "IMessageDispatcher.h"
#include "IMessageHandler.h"

class CMessageDispatcher : public IMessageDispatcher
{
public:
	CMessageDispatcher(void);
	~CMessageDispatcher(void);

public: // IMessageDispatcher
	virtual void HandlerMessage(const csmsg::TCSMessage* pMsgPkg);
	virtual bool AttachMessageHandler(int nMsgID,IMessageHandler* pMsgHandler);
	virtual bool DetachMessageHandler(int nMsgID, IMessageHandler* pMsgHandler);
	virtual void SetDefaultMessageHandler(IMessageHandler* pMsgHandler);

private:
	typedef map<int, IMessageHandler*> TMap_MessageHandler;
	
	TMap_MessageHandler m_mapMessageHandler;
	IMessageHandler* m_pDefaultMessageHandler;
};
