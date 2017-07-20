/********************************************************************	
	created:	
	filename: 	itimerhelper.h
	
	author:		
	purpose:	
	memo   :     
*********************************************************************/



#ifndef __ITIMERHELPER_H__
#define  __ITIMERHELPER_H__

namespace basetools
{



class ITimerSink {
public:
	virtual void OnTimer(int iEventID) = 0;
};


class ITimerAxis{
public:
	virtual BOOL SetTimer(ITimerSink *pSink, int iEventID, int iElapse, LPCTSTR szDesc = _T("")) = 0;

	virtual BOOL KillTimer(ITimerSink *pSink, int iEventID) = 0;

	virtual BOOL ExistTimer(ITimerSink *pSink, int iEventID) = 0;

	virtual void CheckTimer(void) = 0;

	virtual void SetCurrentTick( DWORD dwTick )= 0;

	virtual DWORD GetCurrentTick( )= 0;

	virtual void Release()= 0;
};


};  //  namespace

#endif