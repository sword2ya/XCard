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
	void SetCardSize(const QSize& oSize);	// 设置卡牌大小
	QSize CardSize() const;	// 获取卡牌大小
	void SetOverlap(float fOverlap);	// 设置重叠比例
	float Overlap() const;	// 重叠比例

public slots:
	void Slot_CardClicked();
protected:
	size_t _GetCardCnt() const ;
	void _ResetCards();// 重新设置所有卡牌的位置大小

protected:
	virtual QPoint _CalcCardPos(size_t nIdx) const = NULL;
	virtual CCardView* _CreateCardView();
	virtual void _OnCardClicked(size_t nIdx);


protected:
	static const char* s_szCardIndexPropName;

private:
	TVec_CardView m_vtCardView;

	QSize m_oCardSize;
	float m_fOverlap;	// 重叠比例
};
