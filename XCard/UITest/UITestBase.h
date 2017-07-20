#pragma once

class CUITestBase
{
public:
	CUITestBase(void);
	~CUITestBase(void);

	virtual void SetUp();
	virtual void TearDown();
	virtual bool IsRunning();

private:
	bool m_bRunning;
};
