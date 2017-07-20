#include "stdafx.h"
#include "CardView.h"
#include <QPainter>


typedef map<TCardInfo, string> TMapResources;

static TMapResources g_mapCardResouces;
static bool g_bCardResourcesInit = false;


static void InitACard(ECardPoint ePoint, ECardSuit eSuit, string strUrl)
{
	TCardInfo stCardInfo = {ePoint, eSuit};
	g_mapCardResouces[stCardInfo] = strUrl;
}

static void InitCardResources()
{
	InitACard(eCardPoint_A, eCardSuit_Spade, ":/XCard/Resources/Card/7.jpg");
	InitACard(eCardPoint_2, eCardSuit_Spade, ":/XCard/Resources/Card/8.jpg");
	InitACard(eCardPoint_3, eCardSuit_Spade, ":/XCard/Resources/Card/24.jpg");
	InitACard(eCardPoint_4, eCardSuit_Spade, ":/XCard/Resources/Card/35.jpg");
	InitACard(eCardPoint_5, eCardSuit_Spade, ":/XCard/Resources/Card/46.jpg");
	InitACard(eCardPoint_6, eCardSuit_Spade, ":/XCard/Resources/Card/52.jpg");
	InitACard(eCardPoint_7, eCardSuit_Spade, ":/XCard/Resources/Card/53.jpg");
	InitACard(eCardPoint_8, eCardSuit_Spade, ":/XCard/Resources/Card/54.jpg");
	InitACard(eCardPoint_9, eCardSuit_Spade, ":/XCard/Resources/Card/1.jpg");
	InitACard(eCardPoint_10, eCardSuit_Spade, ":/XCard/Resources/Card/3.jpg");
	InitACard(eCardPoint_J, eCardSuit_Spade, ":/XCard/Resources/Card/4.jpg");
	InitACard(eCardPoint_Q, eCardSuit_Spade, ":/XCard/Resources/Card/5.jpg");
	InitACard(eCardPoint_K, eCardSuit_Spade, ":/XCard/Resources/Card/6.jpg");
	InitACard(eCardPoint_Kinglet, eCardSuit_Spade, ":/XCard/Resources/Card/13.jpg");
	InitACard(eCardPoint_King, eCardSuit_Spade, ":/XCard/Resources/Card/2.jpg");
	InitACard(eCardPoint_A, eCardSuit_Heart, ":/XCard/Resources/Card/21.jpg");
	InitACard(eCardPoint_2, eCardSuit_Heart, ":/XCard/Resources/Card/22.jpg");
	InitACard(eCardPoint_3, eCardSuit_Heart, ":/XCard/Resources/Card/9.jpg");
	InitACard(eCardPoint_4, eCardSuit_Heart, ":/XCard/Resources/Card/10.jpg");
	InitACard(eCardPoint_5, eCardSuit_Heart, ":/XCard/Resources/Card/11.jpg");
	InitACard(eCardPoint_6, eCardSuit_Heart, ":/XCard/Resources/Card/12.jpg");
	InitACard(eCardPoint_7, eCardSuit_Heart, ":/XCard/Resources/Card/14.jpg");
	InitACard(eCardPoint_8, eCardSuit_Heart, ":/XCard/Resources/Card/15.jpg");
	InitACard(eCardPoint_9, eCardSuit_Heart, ":/XCard/Resources/Card/16.jpg");
	InitACard(eCardPoint_10, eCardSuit_Heart, ":/XCard/Resources/Card/17.jpg");
	InitACard(eCardPoint_J, eCardSuit_Heart, ":/XCard/Resources/Card/18.jpg");
	InitACard(eCardPoint_Q, eCardSuit_Heart, ":/XCard/Resources/Card/19.jpg");
	InitACard(eCardPoint_K, eCardSuit_Heart, ":/XCard/Resources/Card/20.jpg");
	InitACard(eCardPoint_Kinglet, eCardSuit_Heart, ":/XCard/Resources/Card/13.jpg");
	InitACard(eCardPoint_King, eCardSuit_Heart, ":/XCard/Resources/Card/2.jpg");
	InitACard(eCardPoint_A, eCardSuit_Club, ":/XCard/Resources/Card/36.jpg");
	InitACard(eCardPoint_2, eCardSuit_Club, ":/XCard/Resources/Card/37.jpg");
	InitACard(eCardPoint_3, eCardSuit_Club, ":/XCard/Resources/Card/23.jpg");
	InitACard(eCardPoint_4, eCardSuit_Club, ":/XCard/Resources/Card/25.jpg");
	InitACard(eCardPoint_5, eCardSuit_Club, ":/XCard/Resources/Card/26.jpg");
	InitACard(eCardPoint_6, eCardSuit_Club, ":/XCard/Resources/Card/27.jpg");
	InitACard(eCardPoint_7, eCardSuit_Club, ":/XCard/Resources/Card/28.jpg");
	InitACard(eCardPoint_8, eCardSuit_Club, ":/XCard/Resources/Card/29.jpg");
	InitACard(eCardPoint_9, eCardSuit_Club, ":/XCard/Resources/Card/30.jpg");
	InitACard(eCardPoint_10, eCardSuit_Club, ":/XCard/Resources/Card/31.jpg");
	InitACard(eCardPoint_J, eCardSuit_Club, ":/XCard/Resources/Card/32.jpg");
	InitACard(eCardPoint_Q, eCardSuit_Club, ":/XCard/Resources/Card/33.jpg");
	InitACard(eCardPoint_K, eCardSuit_Club, ":/XCard/Resources/Card/34.jpg");
	InitACard(eCardPoint_Kinglet, eCardSuit_Club, ":/XCard/Resources/Card/13.jpg");
	InitACard(eCardPoint_King, eCardSuit_Club, ":/XCard/Resources/Card/2.jpg");
	InitACard(eCardPoint_A, eCardSuit_Diamond, ":/XCard/Resources/Card/50.jpg");
	InitACard(eCardPoint_2, eCardSuit_Diamond, ":/XCard/Resources/Card/51.jpg");
	InitACard(eCardPoint_3, eCardSuit_Diamond, ":/XCard/Resources/Card/38.jpg");
	InitACard(eCardPoint_4, eCardSuit_Diamond, ":/XCard/Resources/Card/39.jpg");
	InitACard(eCardPoint_5, eCardSuit_Diamond, ":/XCard/Resources/Card/40.jpg");
	InitACard(eCardPoint_6, eCardSuit_Diamond, ":/XCard/Resources/Card/41.jpg");
	InitACard(eCardPoint_7, eCardSuit_Diamond, ":/XCard/Resources/Card/42.jpg");
	InitACard(eCardPoint_8, eCardSuit_Diamond, ":/XCard/Resources/Card/43.jpg");
	InitACard(eCardPoint_9, eCardSuit_Diamond, ":/XCard/Resources/Card/44.jpg");
	InitACard(eCardPoint_10, eCardSuit_Diamond, ":/XCard/Resources/Card/45.jpg");
	InitACard(eCardPoint_J, eCardSuit_Diamond, ":/XCard/Resources/Card/47.jpg");
	InitACard(eCardPoint_Q, eCardSuit_Diamond, ":/XCard/Resources/Card/48.jpg");
	InitACard(eCardPoint_K, eCardSuit_Diamond, ":/XCard/Resources/Card/49.jpg");
	InitACard(eCardPoint_Kinglet, eCardSuit_Diamond, ":/XCard/Resources/Card/13.jpg");
	InitACard(eCardPoint_King, eCardSuit_Diamond, ":/XCard/Resources/Card/2.jpg");

}


CCardView::CCardView(void)
{
	if (!g_bCardResourcesInit)
	{
		InitCardResources();
		g_bCardResourcesInit = true;
	}
	m_uiCard.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint );
	setFixedSize(sizeHint());
	m_bMouseDown = false;
}

CCardView::~CCardView(void)
{
}

void CCardView::SetCard( ECardPoint ePoint, ECardSuit eSuit )
{
	m_stCardInfo.ePoint = ePoint;
	m_stCardInfo.eSuit = eSuit;
	_UpdateBackImage();
}

QSize CCardView::sizeHint() const
{
	return QSize(105,150);
}

void CCardView::paintEvent( QPaintEvent * p)
{
	QWidget::paintEvent(p);
	QPainter oPainter(this);
	
	const QRect rcPixmap(0, 0, 105, 150);
	oPainter.drawPixmap(rect() , m_oPixmap,rcPixmap);
}

void CCardView::_UpdateBackImage()
{
	m_oPixmap.detach();
	TMapResources::iterator it = g_mapCardResouces.find(m_stCardInfo);
	
	if (it != g_mapCardResouces.end())
	{
		m_oPixmap.load(QString((it->second).c_str()));
	}
	update();
}
