#ifndef ILoginManager_h__
#define ILoginManager_h__



class ILoginCallback
{
public:
	
	enum ELoginErr
	{
		eLoginErr_NoErr, 
		eLoginErr_UserNameOrPsw,
		eLoginErr_OverTime, 
	};

	struct TLoginData 
	{
		__int64 nUserID;
		__int64 nActorID;
		char szActorName[MAX_ACTOR_NAME_SIZE];
		char szUserName[MAX_USER_NAME_SIZE];
	};

public:
	virtual bool OnLoginRsp(int nErrCode, const TLoginData* pstLoginData ) = NULL ;
};

class ILoginManager 
{
public:
	virtual bool RequestLogin(const char* szUserName, const char* szPsw) = NULL;

	virtual void AddLoginCallback(ILoginCallback* pLoginCallback) = NULL;

	virtual void RemoveLoginCallback(ILoginCallback* pLoginCallback) = NULL;

	virtual void ResetLoginStatu() = NULL;

};

#endif // ILoginManager_h__
