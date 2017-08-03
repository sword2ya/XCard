#include "StdAfx.h"
#include "MessageHandlerRegister.h"
#include "MsgHandler_LoginRsp.h"
#include "IMessageDispatcher.h"
#include "IGlobalClient.h"

CMessageHandlerRegister::CMessageHandlerRegister(void)
{
}

CMessageHandlerRegister::~CMessageHandlerRegister(void)
{
}

void CMessageHandlerRegister::InitMessageHandlers()
{
	__RegisterMessageHandler(csmsg::eMsgID_LoginRsp, new CMsgHandler_LoginRsp);

}

void CMessageHandlerRegister::UnInitMessageHandlers()
{
	for (TMap_MessageHandler::iterator it = m_mapMessageHandler.begin(); it != m_mapMessageHandler.end(); ++it )
	{
		IMessageDispatcher* pMessageDispatcher = g_pGlobalClient->GetMessageDispatcher();
		pMessageDispatcher->DetachMessageHandler(it->first, it->second);
		delete it->second;
	}
	m_mapMessageHandler.clear();
}

void CMessageHandlerRegister::__RegisterMessageHandler( int nMsgID, IMessageHandler* pMsgHandler )
{
	m_mapMessageHandler[nMsgID] = pMsgHandler;

	IMessageDispatcher* pMessageDispatcher = g_pGlobalClient->GetMessageDispatcher();
	pMessageDispatcher->AttachMessageHandler(nMsgID, pMsgHandler);
}
