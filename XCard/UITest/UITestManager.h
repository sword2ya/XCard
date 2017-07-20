#pragma once
#include "UITestBase.h"
#include "UITestObjectFactory.h"

class CUITestManager
{
	typedef vector<CUITestBase *> TVec_TestObjs;
public:
	CUITestManager(void);
	~CUITestManager(void);

	void Start();
	void Stop();
	bool Next();
	bool HasMore();
	bool HasPre();
	bool Pre();
	bool IsRunning();

public:
	CUITestObjectFactory* GetTestObjectFactory();
	void AddTestObj(CUITestBase * pTestObj);

private:
	void _TestCurObj();
	void _StopCurObj();
	bool _IsValid(size_t nIdx);

private:
	TVec_TestObjs m_vtTestObjs;
	size_t m_nCurTestIdx;
	bool m_bRunning;
	CUITestObjectFactory m_oTestObjectFactory;
	
};

extern CUITestManager g_oUITestManager;



