#ifndef IServerTerminal_h__
#define IServerTerminal_h__


class IServerTerminal 
{
public:
	virtual bool Send(csmsg::TCSMessage* pMsg) = NULL;
};

#endif // IServerTerminal_h__
