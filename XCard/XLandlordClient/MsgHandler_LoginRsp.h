#pragma once
#include "imessagehandler.h"

class CMsgHandler_LoginRsp :
	public IMessageHandler
{
public:
	CMsgHandler_LoginRsp(void);
	~CMsgHandler_LoginRsp(void);

public:// IMessageHandler
	virtual void OnRecvMessage(const csmsg::TCSMessage* pMsgPkg);

private:
	int __TranslateErrCode(int nProtoErr);
};
