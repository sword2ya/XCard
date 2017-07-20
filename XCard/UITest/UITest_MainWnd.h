#pragma once

class Ui_TestControl;

class CUITest_MainWnd : public QWidget
{
	Q_OBJECT
public:
	CUITest_MainWnd(void);
	~CUITest_MainWnd(void);

public slots:
	void Slot_Start();
	void Slot_Stop();
	void Slot_Next();
	void Slot_Pre();

private:
	void _InitSubWndPoint(const Ui_TestControl &oUiTestControl );
	void _InitButtonSlot();

	void _UpdateBtnState();

private:
	QPushButton* m_pBtnStart;
	QPushButton* m_pBtnStop;
	QPushButton* m_pBtnNext;
	QPushButton* m_pBtnPre;
};
