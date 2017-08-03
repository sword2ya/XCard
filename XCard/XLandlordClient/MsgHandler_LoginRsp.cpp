#include "StdAfx.h"
#include "MsgHandler_LoginRsp.h"
#include "LoginManager.h"
#include "IGlobalClient.h"

CMsgHandler_LoginRsp::CMsgHandler_LoginRsp(void)
{
}

CMsgHandler_LoginRsp::~CMsgHandler_LoginRsp(void)
{
}

void CMsgHandler_LoginRsp::OnRecvMessage( const csmsg::TCSMessage* pMsgPkg )
{
	if (!pMsgPkg->has_stloginrsp())
	{
		Error(__FUNCTION__<<" µÇÂ¼»Ø¸´×Ö¶ÎÎ´ÉèÖÃ¡£");
		return;
	}
	const csmsg::TMSG_LOGIN_RSP& oLoginRsp = pMsgPkg->stloginrsp();
	
	CLoginManager* pLoginManager = static_cast<CLoginManager*>(g_pGlobalClient->GetLoginManager());
	if (!pLoginManager->IsDoingLogin() || pLoginManager->GetLoginUserData() != oLoginRsp.nuserdata() )
	{
		Warning(__FUNCTION__<<" ·Ç±¾´ÎµÇÂ¼»Ø¸´");
		return;
	}
	
	int nErrCode = __TranslateErrCode(oLoginRsp.nerrcode());
	

	ILoginCallback::TLoginData stLoginData;
	lstrcpyn(stLoginData.szActorName, pLoginManager->GetUserName(), _countof(stLoginData.szActorName));
	lstrcpyn(stLoginData.szUserName, pLoginManager->GetUserName(), _countof(stLoginData.szUserName));
	stLoginData.nUserID = 0;
	stLoginData.nActorID = 0;

	ILoginCallback* pLoginCallback = pLoginManager->GetFirstLoginCallback();
	while (NULL != pLoginCallback)
	{
		pLoginCallback->OnLoginRsp(nErrCode, &stLoginData);
		pLoginCallback = pLoginManager->GetNextLoginCallback();
	}
	pLoginManager->ResetLoginStatu();
}

int CMsgHandler_LoginRsp::__TranslateErrCode( int nProtoErr )
{
	if (nProtoErr != 0)
	{
		return ILoginCallback::eLoginErr_UserNameOrPsw;
	}
	return ILoginCallback::eLoginErr_NoErr;
}
