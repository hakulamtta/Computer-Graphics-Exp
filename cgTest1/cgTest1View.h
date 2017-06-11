
// cgTest1View.h : CcgTest1View 类的接口
//
#if _MSC_VER > 1000
#pragma once
#endif 
// _MSC_VER > 1000
#define le 1
#define ri 2
#define bo 4
#define to 8
#define xl 100
#define xr 400
#define yb 100
#define yt 400
#include <vector>

using namespace std;
struct fpoint
{
	float x;
	float y; 
};
typedef struct XET
{
	float x;
	float dx; 
	float ymax;
	XET* next;
}ET, AEL;

class CcgTest1View : public CView
{
protected: // 仅从序列化创建
	CcgTest1View();
	DECLARE_DYNCREATE(CcgTest1View)

// 特性
public:
	CcgTest1Doc* GetDocument() const;

// 操作
public:
	int x0, y0, x2, y2;
	int m_radius;
	int m_animX, m_animY;
	int m_stepX, m_stepY;
	CBrush m_brush;
	CBrush m_backbrush;
// 重写
public:
	std::vector <fpoint> polypoint;
	std::vector <fpoint> polypoint2;
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDrawLineByBresenham(int x1, int y1, int x2, int y2, COLORREF color);
	afx_msg void OnDrawLastLine();
	afx_msg void OnPainting();
	afx_msg void OnAnimate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

// 实现
public:
	void clip(float x0, float y0, float x2, float y2, CDC* pDC);
	void code(float x, float y, int *code);
	virtual ~CcgTest1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	//afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//afx_msg void OnClipline(float x0, float y0, float x2, float y2, CDC *pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnExangeBig();
	afx_msg void OnExangeSmall();
	afx_msg void OnExangeSymmetry();
	afx_msg void OnExangeRotation();
	afx_msg void OnClean();
	afx_msg void OnMove();
};

#ifndef _DEBUG  // cgTest1View.cpp 中的调试版本
inline CcgTest1Doc* CcgTest1View::GetDocument() const
   { return reinterpret_cast<CcgTest1Doc*>(m_pDocument); }
#endif

