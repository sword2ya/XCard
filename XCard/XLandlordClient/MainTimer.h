#pragma once

class CMainTimer : public QObject
{
	Q_OBJECT 
public:
	CMainTimer(void);
	~CMainTimer(void);

	bool Create();

private slots:
	void slot_PushTick();

private:
	QTimer m_oTimer;
};
