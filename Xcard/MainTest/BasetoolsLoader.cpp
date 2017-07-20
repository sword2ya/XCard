#include "StdAfx.h"
#include "BasetoolsLoader.h"

CBasetoolsLoader::CBasetoolsLoader(void)
{
	m_pBasetoolsLib = NULL;
}

CBasetoolsLoader::~CBasetoolsLoader(void)
{
	Close();
}

bool CBasetoolsLoader::Create()
{
	const char* szBasetoolsDll = ".\\basetoolsA.dll";
	if ( !m_oModalLoader.LoadModal(szBasetoolsDll))
	{
		Error("����basetools dllʧ��.error:"<< m_oModalLoader.GetErrorMsg());
		return false;
	}
	const char* szBasetoolsInterface = "IBasetoolsLib";
	m_pBasetoolsLib = static_cast<IBasetoolsLib*>( m_oModalLoader.GetInterface("IBasetoolsLib"));
	if (NULL == m_pBasetoolsLib)
	{
		Error("����basetools�ӿ�ʧ��");
		return false;
	}
	return true;
}

void CBasetoolsLoader::Close()
{
	SafeRelease(m_pBasetoolsLib);
	m_oModalLoader.FreeModal();
}

ITimerAxis* CBasetoolsLoader::LoadTimerAxis()
{
	if (NULL == m_pBasetoolsLib)
	{
		return NULL;
	}
	return m_pBasetoolsLib->CreateTimerAxis();
}
