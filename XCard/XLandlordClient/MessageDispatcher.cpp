#include "StdAfx.h"
#include "MessageDispatcher.h"

CMessageDispatcher::CMessageDispatcher(void)
{
	m_pDefaultMessageHandler = NULL;
}

CMessageDispatcher::~CMessageDispatcher(void)
{
}

void CMessageDispatcher::HandlerMessage( const csmsg::TCSMessage*  pMsgPkg )
{
	csmsg::ECSMessageID eMsgID = pMsgPkg->emsgid();
	TMap_MessageHandler::iterator it = m_mapMessageHandler.find(eMsgID);
	if (it == m_mapMessageHandler.end())
	{
		if (NULL != m_pDefaultMessageHandler)
		{
			m_pDefaultMessageHandler->OnRecvMessage(pMsgPkg);
		}
		else
		{
			Error(__FUNCTION__<<" 消息"<<eMsgID<<"未指定消息处理器");
		}
		return;	
	}
	else 
	{
		it->second->OnRecvMessage(pMsgPkg);
	}

}

bool CMessageDispatcher::AttachMessageHandler( int nMsgID, IMessageHandler* pMsgHandler )
{
	if (NULL == pMsgHandler)
	{
		return false;
	}
	m_mapMessageHandler[nMsgID] = pMsgHandler;
	return true; 
}

bool CMessageDispatcher::DetachMessageHandler( int nMsgID, IMessageHandler* pMsgHandler)
{
	m_mapMessageHandler.erase(nMsgID);
	return true;
}

void CMessageDispatcher::SetDefaultMessageHandler( IMessageHandler* pMsgHandler )
{
	m_pDefaultMessageHandler = pMsgHandler;
}
