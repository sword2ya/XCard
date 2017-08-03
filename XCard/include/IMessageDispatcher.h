#ifndef IMessageDispatcher_h__
#define IMessageDispatcher_h__

#include "IMessageHandler.h"

class IMessageDispatcher
{
public:
	virtual void HandlerMessage(const csmsg::TCSMessage* pMsgPkg) = NULL ;
	virtual bool AttachMessageHandler(int nMsgID, IMessageHandler* pMsgHandler) = NULL ;
	virtual bool DetachMessageHandler(int nMsgID, IMessageHandler* pMsgHandler) = NULL ;
	virtual void SetDefaultMessageHandler(IMessageHandler* pMsgHandler) = NULL;
};

#endif // IMessageDispatcher_h__
