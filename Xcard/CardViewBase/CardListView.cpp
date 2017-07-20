#include "CardListView.h"
#include "CardView.h"
#include <QVariant>


const char* CCardListView::s_szCardIndexPropName = "CardListView_Index";


CCardListView::CCardListView(void)
{
	setWindowFlags(Qt::FramelessWindowHint);
	m_oCardSize = QSize(105,150);
	m_fOverlap = 2.f/3;
}

CCardListView::~CCardListView(void)
{
}

void CCardListView::Clear()
{
	TVec_CardView::iterator it = m_vtCardView.begin();
	for (; it != m_vtCardView.end(); ++it)
	{
		(*it)->setParent(NULL);
		delete *it;
	}
	m_vtCardView.clear();
}

void CCardListView::PushbackCard( const TCardInfo* arrCardInfo, int nCount )
{
	for (int i = 0; i < nCount; ++i)
	{
		CCardView* pCardView = _CreateCardView();
		pCardView->SetCard(arrCardInfo[i].ePoint, arrCardInfo[i].eSuit);
		pCardView->setFixedSize(m_oCardSize);
		pCardView->setParent(this);
		m_vtCardView.push_back(pCardView);
		size_t nIdx = m_vtCardView.size()-1;
		QPoint oPos = _CalcCardPos(nIdx);
		pCardView->move(oPos);
		pCardView->show();
		pCardView->setProperty(s_szCardIndexPropName, QVariant(nIdx));

		connect(pCardView, SIGNAL(clicked()), this, SLOT(Slot_CardClicked()));
	}
	QSize oSize = sizeHint();
	setFixedSize(oSize);
}


CCardView* CCardListView::GetCardView( size_t nIdx ) const
{
	if (nIdx >= _GetCardCnt())
	{
		return NULL;
	}
	return m_vtCardView[nIdx];
}

void CCardListView::SetCardSize( const QSize& oSize )
{
	m_oCardSize = oSize;
	_ResetCards();
}

QSize CCardListView::CardSize() const
{
	return m_oCardSize;
}

void CCardListView::SetOverlap( float fOverlap )
{
	m_fOverlap = fOverlap;
	_ResetCards();
}

float CCardListView::Overlap() const
{
	return m_fOverlap;
}

size_t CCardListView::_GetCardCnt() const
{
	return m_vtCardView.size();
}

CCardView* CCardListView::_CreateCardView()
{
	return new CCardView;
}

void CCardListView::_OnCardClicked(size_t nIdx)
{

}

void CCardListView::_ResetCards()
{
	TVec_CardView::iterator it = m_vtCardView.begin();
	for (size_t nIdx = 0; nIdx < m_vtCardView.size(); ++nIdx)
	{
		CCardView *pCardView = m_vtCardView[nIdx];
		QPoint oPos = _CalcCardPos(nIdx);
		pCardView->setFixedSize(m_oCardSize);
		pCardView->move(oPos);
	}
	QSize oSize = sizeHint();
	setFixedSize(oSize);
}

void CCardListView::Slot_CardClicked()
{
	QObject* pSender = sender();
	if (NULL == pSender )
	{
		return ;
	}
	QVariant oIndexProperty = pSender->property(s_szCardIndexPropName);
	if (oIndexProperty.isNull())
	{
		return;
	}
	QList<QByteArray> x = pSender->dynamicPropertyNames();
	int nIdx = oIndexProperty.toInt();
	_OnCardClicked(nIdx);
}