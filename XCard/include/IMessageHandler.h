#ifndef IMessageHandler_h__
#define IMessageHandler_h__

namespace csmsg
{
	class TCSMessage;
}

class IMessageHandler 
{
public:
	virtual void OnRecvMessage(const csmsg::TCSMessage* pMsgPkg) = NULL;
};


#endif // IMessageHandler_h__
