
// LifeGameView.h: CLifeGameView 类的接口
//

#pragma once


class CLifeGameView : public CView
{
protected: // 仅从序列化创建
	CLifeGameView() noexcept;
	DECLARE_DYNCREATE(CLifeGameView)

// 特性
public:
	CLifeGameDoc* GetDocument() const;

	afx_msg void OnTimer(UINT_PTR id);

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CLifeGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void NEXTSTEP();
	afx_msg void STARTGAME();
	afx_msg void PAUSE();
	afx_msg void slow();
	afx_msg void MIDDLE();
	afx_msg void FAST();
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // LifeGameView.cpp 中的调试版本
inline CLifeGameDoc* CLifeGameView::GetDocument() const
   { return reinterpret_cast<CLifeGameDoc*>(m_pDocument); }
#endif

