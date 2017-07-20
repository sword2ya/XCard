#pragma once
#include "XCommon.h"

class CCardView;

class CCardListView : public QWidget
{
	Q_OBJECT 

	typedef vector<CCardView*> TVec_CardView;
public:
	CCardListView(void);
	~CCardListView(void);
	
	virtual void Clear();
	void PushbackCard(const TCardInfo* arrCardInfo, int nCount);
	CCardView* GetCardView(size_t nIdx) const;
	void SetCardSize(const QSize& oSize);	// ���ÿ��ƴ�С
	QSize CardSize() const;	// ��ȡ���ƴ�С
	void SetOverlap(float fOverlap);	// �����ص�����
	float Overlap() const;	// �ص�����

public slots:
	void Slot_CardClicked();
protected:
	size_t _GetCardCnt() const ;
	void _ResetCards();// �����������п��Ƶ�λ�ô�С

protected:
	virtual QPoint _CalcCardPos(size_t nIdx) const = NULL;
	virtual CCardView* _CreateCardView();
	virtual void _OnCardClicked(size_t nIdx);


protected:
	static const char* s_szCardIndexPropName;

private:
	TVec_CardView m_vtCardView;

	QSize m_oCardSize;
	float m_fOverlap;	// �ص�����
};
