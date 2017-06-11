
// cgTest1View.cpp : CcgTest1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "cgTest1.h"
#endif

#include "cgTest1Doc.h"
#include "cgTest1View.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CcgTest1View

IMPLEMENT_DYNCREATE(CcgTest1View, CView)

BEGIN_MESSAGE_MAP(CcgTest1View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CcgTest1View::OnFilePrintPreview)
	
	ON_WM_TIMER()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	//ON_COMMAND(ID_POLYGON, &CcgTest1View::OnPolygon)
	//ON_COMMAND(ID_FILLPOLYGON, &CcgTest1View::OnFillpolygon)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_POLYGON, &CcgTest1View::OnDrawLastLine)
	ON_COMMAND(ID_FILLPOLYGON, &CcgTest1View::OnPainting)
	ON_COMMAND(ID_32791, &CcgTest1View::OnAnimate)
	ON_COMMAND(ID_DSA_32793, &CcgTest1View::OnExangeBig)
	ON_COMMAND(ID_DSA_32794, &CcgTest1View::OnExangeSmall)
	ON_COMMAND(ID_DSA_32795, &CcgTest1View::OnExangeSymmetry)
	ON_COMMAND(ID_DSA_32796, &CcgTest1View::OnExangeRotation)
	ON_COMMAND(ID_32801, &CcgTest1View::OnClean)
	ON_COMMAND(ID_32800, &CcgTest1View::OnMove)
END_MESSAGE_MAP()

// CcgTest1View ����/����
int state;
CcgTest1View::CcgTest1View()
{
	// TODO: �ڴ˴���ӹ������

	//m_pointNum =0;
	//m_point.clear();
}

CcgTest1View::~CcgTest1View()
{
}

BOOL CcgTest1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CcgTest1View ����

void CcgTest1View::OnDraw(CDC* pDC)
{
	CcgTest1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//���ڱ仯���ػ����һ�������
	if (polypoint2.size() != 0)
		OnPainting();
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if (state == 1)
	{
		pDC->Rectangle(100, 100, 400, 400);//����һ�������βü���
		clip(x0, y0, x2, y2, pDC);
	}
}


// CcgTest1View ��ӡ


/*void CcgTest1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}*/

BOOL CcgTest1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CcgTest1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CcgTest1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

//void CcgTest1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
/*{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}*/


// CcgTest1View ���

#ifdef _DEBUG
void CcgTest1View::AssertValid() const
{
	CView::AssertValid();
}

void CcgTest1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgTest1Doc* CcgTest1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgTest1Doc)));
	return (CcgTest1Doc*)m_pDocument;
}
#endif //_DEBUG


// CcgTest1View ��Ϣ�������


/*void CcgTest1View::OnPolygon()
{
	// TODO: �ڴ���������������
	m_graphType = 1;
}*/


/*void CcgTest1View::OnFillpolygon()
{
	// TODO: �ڴ���������������
	m_graphType =2;
}*/

void CcgTest1View::OnDrawLineByBresenham(int x1, int y1, int x2, int y2, COLORREF color)
{
	CDC *pDC = GetDC();
	int x, y, dx, dy, e;
	dx = x2 - x1;
	dy = y2 - y1;
	x = x1;
	y = y1;
	CString s;

	if (dx*dy >= 0)    //���k����0
	{
		if ((dx < 0) || (dx == 0 && dy < 0))	 //dxС��0˵���յ�x
		{
			dx = -dx;
			dy = -dy;
			x = x2;
			y = y2;

		}
		if (dy < dx)         //��һ�������k(0,1)
		{
			e = -dx;//e = -dx
			for (int i = 0; i < dx; i++)
			{
				pDC->SetPixel(x, y, color);
				x++;//xΪ���λ�Ʒ���
				e += (dy << 1);//e' = e+2dy
				if (e >= 0)
				{
					y++;//e����0��y ��һ��
					e -= (dx << 1);//e' = e+2dy-2dx
				}
			}
		}
		else           //�ڶ��������k-(1,max)
		{
			e = -dy;
			for (int i = 0; i < dy; i++)
			{
				pDC->SetPixel(x, y, color);
				y++;//yΪ���λ�Ʒ���
				e += (dx << 1);//e = e+2dx
				if (e >= 0)
				{
					x++;//e����
					e -= (dy << 1);// e' = e+2dx-2dy
				}
			}
		}
	}
	else                     //���kС��0
	{
		int fx, fy;    //����x��y�ľ���ֵ
		if (dx < 0)         //dxС��0˵���յ�x
		{
			fx = -dx;	//ȥһ�¾���ֵ
			fy = dy;
		}
		if (dy < 0)
		{
			fx = dx;
			fy = -dy;
		}

		if (fx > fy) //�����������k-(-1,0)
		{
			if (dx < 0)   //dxС��0˵���յ�x
			{
				dx = -dx;
				dy = -dy;
				x = x2;
				y = y2;
			}
			e = -dx;
			for (int i = 0; i < dx; i++)
			{
				pDC->SetPixel(x, y, color);
				x++;
				e -= (dy << 1);
				if (e >= 0)
				{
					y--;
					e -= (dx << 1);
				}
			}
		}
		else            //�����������k-(-1,min)
		{
			if (dy < 0)//dxС��0˵���յ�x
			{
				dx = -dx;
				dy = -dy;
				x = x2;
				y = y2;
			}
			e = -dy;
			for (int i = 0; i < dy; i++)
			{
				pDC->SetPixel(x, y, color);
				y++;
				e -= (dx << 1);
				if (e >= 0)
				{
					x--;
					e -= (dy << 1);
				}
			}
		}
	}
}
void CcgTest1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*if(m_graphType==1)
	{
	    m_point.push_back(point);
	    m_pointNum++;
	}
	CView::OnLButtonDown(nFlags, point);*/
	fpoint fpo;
	int size = polypoint.size();
	if (size >= 1)
	{
		OnDrawLineByBresenham(polypoint[size - 1].x, polypoint[size - 1].y, point.x, point.y, RGB(0, 0, 0));
		fpo.x = (float)point.x;
		fpo.y = (float)point.y;
		polypoint.push_back(fpo);
		size++;
	}
	else
	{
		fpo.x = (float)point.x;
		fpo.y = (float)point.y;
		polypoint.push_back(fpo);
		size = 1;
	}
}

void CcgTest1View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int size = polypoint.size();
	OnDrawLineByBresenham(polypoint[size - 1].x, polypoint[size - 1].y, polypoint[0].x, polypoint[0].y, RGB(0, 0, 0));
	state == 2;
}

/*void CcgTest1View::drawLineMid(CPoint p1,CPoint p2)
{
	CDC *pDC= GetWindowDC();

	for(int i=100;i<500;i++)
	{
	    pDC->SetPixel(CPoint(i,100),RGB(255,0,0));
	}
	pDC->MoveTo(p1);
	pDC->LineTo(p2);

}*/

void  CcgTest1View::OnDrawLastLine()
{
	int n = polypoint.size();
	if (n <= 2)
	{
		//MessageBox(_T("����С��3��������ɶ���Σ�"));
		polypoint.clear();
		return;
	}
	int x1 = polypoint[0].x, y1 = polypoint[0].y, x2 = polypoint[n - 1].x, y2 = polypoint[n - 1].y;
	OnDrawLineByBresenham(x2, y2, x1, y1, RGB(0, 0, 0));
	polypoint2 = polypoint;
	polypoint.clear();
}

void  CcgTest1View::OnPainting()
{
	CDC *pDC = GetDC();
	if (polypoint.size() > 2)
		OnDrawLastLine();
	int n = polypoint2.size();
	int MaxY = 0;
	int MinY = 100000;
	int i;
	for (i = 0; i<n; i++)//Ѱ����ߵ�Yֵ����͵�Yֵ
	{
		if (polypoint2[i].y>MaxY)
			MaxY = polypoint2[i].y;
		if (polypoint2[i].y<MinY)
			MinY = polypoint2[i].y;
	}
	ET *pET = new ET;
	pET->next = NULL;
	AEL **pAEL = new AEL*[MaxY + 1];
	for (i = 0; i <= MaxY; i++)
	{
		pAEL[i] = new AEL;
		pAEL[i]->next = NULL;
	}
	for (i = MinY; i <= MaxY; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (polypoint2[j].y == i)//��ɨ�����ཻ
			{
				if (polypoint2[(j - 1 + n) % n].y > polypoint2[j].y)//���߶˵��Ǹ���
				{
					AEL *p = new AEL;
					p->x = polypoint2[j].x;
					p->ymax = polypoint2[(j - 1 + n) % n].y;
					p->dx = (polypoint2[(j - 1 + n) % n].x - polypoint2[j].x) / (polypoint2[(j - 1 + n) % n].y - polypoint2[j].y);//��xl
					p->next = pAEL[i]->next;
					pAEL[i]->next = p;
				}
				if (polypoint2[(j + 1 + n) % n].y > polypoint2[j].y)
				{
					AEL *p = new AEL;
					p->x = polypoint2[j].x;
					p->ymax = polypoint2[(j + 1 + n) % n].y;
					p->dx = (polypoint2[(j + 1 + n) % n].x - polypoint2[j].x) / (polypoint2[(j + 1 + n) % n].y - polypoint2[j].y);
					p->next = pAEL[i]->next;
					pAEL[i]->next = p;
				}

			}
		}
	}

	//���������±߱�
	for (i = MinY; i <= MaxY; i++)
	{
		//�����µĽ���x,����AET
		AEL *p = pET->next;
		while (p)
		{
			p->x = p->x + p->dx;//i>ymaxɾ����С�ڵ���dx
			p = p->next;//��һ������
		}
		//���º���AET������
		ET *tq = pET;
		p = pET->next;
		tq->next = NULL;
		while (p)
		{
			while (tq->next && p->x >= tq->next->x)
				tq = tq->next;
			AEL *s = p->next;
			p->next = tq->next;
			tq->next = p;
			p = s;
			tq = pET;
		}
		//�ȴ�AET����ɾ��ymax==i�Ľ��
		ET *q = pET;
		p = q->next;
		while (p)
		{
			if (p->ymax == i)
			{
				q->next = p->next;
				delete p;
				p = q->next;
			}
			else
			{
				q = q->next;
				p = q->next;
			}
		}

		//��NET�е��µ����AET,���ò��뷨��Xֵ��������
		p = pAEL[i]->next;
		q = pET;
		while (p)
		{
			while (q->next && p->x >= q->next->x)
				q = q->next;//������
			AEL *s = p->next;
			p->next = q->next;
			q->next = p;//����ָ��

			p = s;
			q = pET;
		}

		//��������ɫ
		p = pET->next;
		while (p && p->next)
		{
			for (float j = p->x; j <= p->next->x; j++)
				pDC->SetPixel(int(j), i, RGB(0, 0, 0));
			p = p->next->next;//���Ƕ˵����
		}
	}
	for (int i = 0; i <= MaxY; i++)
	{
		delete[]pAEL[i];
		pAEL[i] = NULL;
	}
	delete[]pAEL;
	pAEL = NULL;
	delete[]pET;
	pET = NULL;
}

void CcgTest1View::code(float x, float y, int *code)
{
	int c = 0;
	if (x<xl)
		c = c | le;//0001
	else if (x>xr)
		c = c | ri;//0010
	if (y<yb)
		c = c | bo;//0100
	else if (y>yt)
		c = c | to;//1000
	*code = c;
}

void CcgTest1View::clip(float x0, float y0, float x2, float y2, CDC *pDC)
{
	float x = 0, y = 0;
	int c1, c2, c;
	//����˵����
	code(x0, y0, &c1);
	code(x2, y2, &c2);
	while ((c1 != 0) || (c2 != 0)){
		if ((c1&c2) != 0)return;//����������������㲻Ϊ1�����ڴ����ڲ�
		c = c1;
		if (c1 == 0)
			c = c2;
		if ((c&le) != 0)//�������
		{
			x = xl;
			y = y0 + (y2 - y0)*(xl - x0) / (x2 - x0);//���xl����������
		}else if ((c&ri) != 0){//�����Ҳ�
			x = xr;
			y = y0 + (y2 - y0)*(xr - x0) / (x2 - x0);
		}else if ((c&bo) != 0){
			y = yb; 
			x = x0 + (x2 - x0)*(yb - y0) / (y2 - y0);
		}else if ((c&to) != 0){
			y = yt;
			x = x0 + (x2 - x0)*(yt - y0) / (y2 - y0);
		}
		if (c == c1){
			x0 = x;
			y0 = y;
			code(x, y, &c1);
		}else{
			x2 = x;
			y2 = y;
			code(x, y, &c2);
		}
	}
	pDC->MoveTo(x0, y0);
	pDC->LineTo(x2, y2);
}


void CcgTest1View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default


	CClientDC dc(this);
	x2 = point.x;
	y2 = point.y;
	dc.MoveTo(x0, y0);
	dc.LineTo(x2, y2);
	Invalidate();
	CView::OnRButtonUp(nFlags, point);
}

void CcgTest1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	state = 1;
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	x0 = point.x;
	y0 = point.y;

	CView::OnRButtonDown(nFlags, point);
}

void CcgTest1View::OnAnimate()
{
	m_radius = 50;

	m_animX = m_radius;
	m_animY = m_radius;
	m_stepX = 10;
	m_stepY = 10;

	SetTimer(1, 50, NULL);
}


void CcgTest1View::OnTimer(UINT_PTR nIDEvent)
{
	CRect rect;
	CDC* m_pDC = GetWindowDC();
	GetClientRect(rect);//��ȡ�ͻ����Ĵ�С

	m_animX += m_stepX;
	m_animY += m_stepY;

	if (m_animX + m_radius >= rect.right - m_radius)
		m_stepX = -m_stepX;
	if (m_animX - m_radius <= rect.left)
		m_stepX = -m_stepX;
	if (m_animY + m_radius >= rect.bottom - m_radius)
		m_stepY = -m_stepY;
	if (m_animY - m_radius <= rect.top)
		m_stepY = -m_stepY;

	m_brush.CreateSolidBrush(RGB(0, 255, 0));//С����ɫ
	m_backbrush.CreateSolidBrush(RGB(255, 255, 255));//������ɫ

	m_pDC->FillRect(rect, &m_backbrush);
	m_pDC->SelectObject(m_brush);
	//����Բ��
	m_pDC->Ellipse(m_animX - m_radius, m_animY - m_radius, m_animX + m_radius, m_animY + m_radius);

	ReleaseDC(m_pDC);
	m_brush.DeleteObject();
	m_backbrush.DeleteObject();

	CView::OnTimer(nIDEvent);
}


//�Ŵ�
void CcgTest1View::OnExangeBig()
{
	// TODO:  �ڴ���������������
	CDC *pDC = GetDC();
	CPen pen(0, 1, RGB(255, 0, 0));
	pDC->SelectObject(&pen);
	int n = polypoint.size();
	float sx = 2.0, sy = 2.0;//����ϵ��
	CPoint p1, p2;
	float x = polypoint[0].x, y = polypoint[0].y;
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1){
			p1.x = (polypoint[0].x - x) * sx + x;
			p1.y = (polypoint[0].y - y) * sy + y;
			p2.x = (polypoint[i].x - x) * sx + x;
			p2.y = (polypoint[i].y - y) * sy + y;
			pDC->MoveTo(p1);
			pDC->LineTo(p2);
		}
		else{
			p1.x = (polypoint[i].x - x) * sx + x;
			p1.y = (polypoint[i].y - y) * sy + y;
			p2.x = (polypoint[i + 1].x - x) * sx + x;
			p2.y = (polypoint[i + 1].y - y) * sy + y;
			pDC->MoveTo(p1);
			pDC->LineTo(p2);
		}
	}
}

//��С
void CcgTest1View::OnExangeSmall()
{
	// TODO:  �ڴ���������������
	CDC *pDC = GetDC();
	CPen pen(0, 1, RGB(0, 255, 0));
	pDC->SelectObject(&pen);
	int n = polypoint.size();
	float sx = 0.5, sy = 0.5;//����ϵ��
	CPoint p1, p2;
	float x = polypoint[0].x, y = polypoint[0].y;
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1){
			p1.x = (polypoint[0].x - x) * sx + x;
			p1.y = (polypoint[0].y - y) * sy + y;
			p2.x = (polypoint[i].x - x) * sx + x;
			p2.y = (polypoint[i].y - y) * sy + y;
			pDC->MoveTo(p1);
			pDC->LineTo(p2);
		}
		else{
			p1.x = (polypoint[i].x - x) * sx + x;
			p1.y = (polypoint[i].y - y) * sy + y;
			p2.x = (polypoint[i + 1].x - x) * sx + x;
			p2.y = (polypoint[i + 1].y - y) * sy + y;
			pDC->MoveTo(p1);
			pDC->LineTo(p2);
		}
	}
}


void CcgTest1View::OnMove()
{
	// TODO:  �ڴ���������������
	CDC *pDC = GetDC();
	int n = polypoint.size();
	int tx = 200, ty = 100;
	CPoint p1, p2;
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1){
			p1.x = polypoint[0].x + tx;
			p1.y = polypoint[0].y + ty;
			p2.x = polypoint[i].x + tx;
			p2.y = polypoint[i].y + ty;
			pDC->MoveTo(p1);
			pDC->LineTo(p2);
		}
		else{
			p1.x = polypoint[i].x + tx;
			p1.y = polypoint[i].y + ty;
			p2.x = polypoint[i + 1].x + tx;
			p2.y = polypoint[i + 1].y + ty;
			pDC->MoveTo(p1);
			pDC->LineTo(p2);
		}
	}
}


//��Գ�
void CcgTest1View::OnExangeSymmetry()
{
	// TODO:  �ڴ���������������
	CDC *pDC = GetDC();
	int n = polypoint.size();
	CPoint p1, p2;
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1){
			p1.x = 1000 - polypoint[0].x;
			p1.y = polypoint[0].y;
			p2.x = 1000 - polypoint[i].x;
			p2.y = polypoint[i].y;
			pDC->MoveTo(p1);
			pDC->LineTo(p2);
		}
		else{
			p1.x = 1000 - polypoint[i].x;
			p1.y = polypoint[i].y;
			p2.x = 1000 - polypoint[i + 1].x;
			p2.y = polypoint[i + 1].y;
			pDC->MoveTo(p1);
			pDC->LineTo(p2);
		}
	}
}

//��ת
void CcgTest1View::OnExangeRotation()
{
	// TODO:  �ڴ���������������
	CDC *pDC = GetDC();
	CPen pen(0, 1, RGB(0, 0, 255));
	pDC->SelectObject(&pen);
	int n = polypoint.size();
	double pi = 3.1415926535;
	double c, a, b;
	c = pi / 3;//��ת�Ƕ�
	a = sin(c);
	b = cos(c);
	CPoint p1, p2;
	float x = polypoint[0].x, y = polypoint[0].y;
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1){
			p1.x = polypoint[0].x * b - polypoint[0].y * a;
			p1.y = polypoint[0].x * a + polypoint[0].y * b;
			p2.x = polypoint[i].x * b - polypoint[i].y * a;
			p2.y = polypoint[i].x * a + polypoint[i].y * b;
			pDC->MoveTo(p1);
			pDC->LineTo(p2);
		}
		else{
			p1.x = polypoint[i].x * b - polypoint[i].y * a;
			p1.y = polypoint[i].x * a + polypoint[i].y * b;
			p2.x = polypoint[i + 1].x * b - polypoint[i + 1].y * a;
			p2.y = polypoint[i + 1].x * a + polypoint[i + 1].y * b;
			pDC->MoveTo(p1);
			pDC->LineTo(p2);
		}
	}
}

void CcgTest1View::OnClean()
{
	// TODO:  �ڴ���������������
	CDC* pDC;
	pDC = GetWindowDC();

	polypoint.clear();
	state = 0;

	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));
}