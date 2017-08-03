#ifndef ServerPart_h__
#define ServerPart_h__

namespace csmsg
{
	class TCSMessage;
}

class CServerSession;

class IServerPart 
{
public:
	virtual void HandlerMsg(const csmsg::TCSMessage* pMsg) = NULL;
	virtual bool Create(CServerSession* pServerSession) = NULL;
};

enum EServerPart 
{
	eServerPart_Common, 
	eServerPart_Count, 
};

#endif // ServerPart_h__
