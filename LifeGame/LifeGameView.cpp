
// LifeGameView.cpp: CLifeGameView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LifeGame.h"
#endif

#include<string>

#define MAXM 100
#define MAXN 100
#define Width 20

int initime = 1000;
int timestep=1000;

#include "LifeGameDoc.h"
#include "LifeGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLifeGameView

IMPLEMENT_DYNCREATE(CLifeGameView, CView)

BEGIN_MESSAGE_MAP(CLifeGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLifeGameView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CLifeGameView::NEXTSTEP)
	ON_COMMAND(ID_32772, &CLifeGameView::STARTGAME)
	ON_COMMAND(ID_32773, &CLifeGameView::PAUSE)
	ON_COMMAND(ID_32774, &CLifeGameView::slow)
	ON_COMMAND(ID_32775, &CLifeGameView::MIDDLE)
	ON_COMMAND(ID_32776, &CLifeGameView::FAST)
	ON_COMMAND(ID_FILE_OPEN, &CLifeGameView::OnFileOpen)
END_MESSAGE_MAP()

// CLifeGameView 构造/析构

CLifeGameView::CLifeGameView() noexcept
{
	// TODO: 在此处添加构造代码

}

CLifeGameView::~CLifeGameView()
{
}

BOOL CLifeGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLifeGameView 绘图

void CLifeGameView::OnDraw(CDC* pDC)
{
	CLifeGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);//���滭��
	int len = Width;
	for (int i = 0; i <= MAXM; i++)
	{
		pDC->MoveTo(i * len, 0);
		pDC->LineTo(i * len, MAXM * len);
	}
	for (int j = 0; j <= MAXN; j++)
	{
		pDC->MoveTo(0, j * len);
		pDC->LineTo(MAXN * len, j * len);
	}
	pDC->SelectObject(pOldPen);

	CBrush brush(RGB(0, 0, 0));//
	CBrush* oldbrush = pDC->SelectObject(&brush);//
	CRect rect(0, 0, 0, 0);
	POINT lefttop, rightbottom;
	for (int i = 0; i < pDoc->v.size(); i++)
	{
		for (int j = 0; j < pDoc->v[i].size(); j++)
		{
			lefttop.y = i * Width;
			lefttop.x = j * Width;
			rightbottom.y = lefttop.y + Width;
			rightbottom.x = lefttop.x + Width;
			rect.SetRect(lefttop, rightbottom);
			if (pDoc->v[i][j] == 1)
				pDC->Rectangle(rect);
		}
	}
	// TODO: 在此处为本机数据添加绘制代码
}


// CLifeGameView 打印


void CLifeGameView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLifeGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLifeGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLifeGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CLifeGameView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLifeGameView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLifeGameView 诊断

#ifdef _DEBUG
void CLifeGameView::AssertValid() const
{
	CView::AssertValid();
}

void CLifeGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLifeGameDoc* CLifeGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLifeGameDoc)));
	return (CLifeGameDoc*)m_pDocument;
}
#endif //_DEBUG


void CLifeGameView::OnTimer(UINT_PTR id)
{
	switch (id)
	{
	case 1:
		NEXTSTEP();
		break;
	}
	CView::OnTimer(id);
}

// CLifeGameView 消息处理程序


void CLifeGameView::NEXTSTEP()
{
	// TODO: 在此添加命令处理程序代码
	CLifeGameDoc* pDoc = GetDocument();
	CDC* pDC = GetDC();
	pDoc->getnext();
	Invalidate(1);
}


void CLifeGameView::STARTGAME()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, initime, NULL);
}


void CLifeGameView::PAUSE()
{
	KillTimer(1);
}


void CLifeGameView::slow()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
	timestep *= 2;
	SetTimer(1, timestep, NULL);
}


void CLifeGameView::MIDDLE()
{
	KillTimer(1);
	timestep = initime;
	SetTimer(1, timestep, NULL);
}


void CLifeGameView::FAST()
{
	KillTimer(1);
	timestep /= 2;
	if (timestep == 0)
		timestep = 1;
	SetTimer(1, timestep, NULL);
}


void CLifeGameView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CString FilePathName;
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		NULL,
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName(); //文件名保存在了FilePathName里
		string filename;
		filename = CT2A(FilePathName);
		CLifeGameDoc* pDoc = GetDocument();
		pDoc->getfile(filename);
		Invalidate(1);
	}
	else
	{
		return;
	}

}
