#pragma once

class CBasetoolsLoader
{
public:
	CBasetoolsLoader(void);
	~CBasetoolsLoader(void);

	bool Create();
	void Close();

	ITimerAxis* LoadTimerAxis();

private:
	CModalLoader m_oModalLoader;
	IBasetoolsLib* m_pBasetoolsLib;
};
