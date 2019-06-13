
// LifeGameDoc.cpp: CLifeGameDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LifeGame.h"
#endif

#include "LifeGameDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//传入参数的初始化
#include<vector>
#include<string>
#include<fstream>



// CLifeGameDoc
//
IMPLEMENT_DYNCREATE(CLifeGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CLifeGameDoc, CDocument)
	//ON_COMMAND(ID_APP_ABOUT, &CLifeGameDoc::Start)
END_MESSAGE_MAP()


// CLifeGameDoc 构造/析构

CLifeGameDoc::CLifeGameDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	getfile();
}

CLifeGameDoc::~CLifeGameDoc()
{
}

//获取读入文件
void CLifeGameDoc::getfile()
{
	vector<vector<int>> v;
	string filename = "test.txt";
	ifstream in;
	in.open(filename);
	string line;
	if (!in)
	{
		return;
	}
	vector<int> tep;
	while (getline(in, line))
	{
		tep.clear();
		for (int i = 0; i < line.length(); i++)
		{
			switch (line[i])
			{
			case '1':
				tep.push_back(1);
				break;
			case '0':
				tep.push_back(0);
				break;
			default:
				break;
			}
		}
		v.push_back(tep);
	}
	this->v=v;
	return;
}

int CLifeGameDoc::get_neightbor_cells(int index_x, int index_y)
{
	int count = 0;
	int posx[8] = { -1,-1,-1,0,0,1,1,1 };
	int posy[8] = { -1,0,1,-1,1,-1,0,1 };
	for (int i = 0; i < 8; i++)
	{
		int x = index_x + posx[i];
		int y = index_y + posy[i];
		if (x < 0 || x >= this->v.size() || y < 0 || y >= this->v[0].size())
			continue;
		count += this->v[x][y];
	}

	return count;
}

int CLifeGameDoc::nextlife(int now,int count)
{
	if (count < 2 || count >3)
		return 0;
	if (now == 0 && count == 3)
		return 1;
	return now;
}

void CLifeGameDoc::getnext()
{
	this->nextv = this -> v;
	int w = this->v.size();
	int l = this->v[0].size();
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < l; j++)
		{
			int count = get_neightbor_cells(i, j);
			this->nextv[i][j] = nextlife(this->v[i][j], count);
		}
	}
	this->v = this->nextv;
	return;
}

BOOL CLifeGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLifeGameDoc 序列化

void CLifeGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CLifeGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CLifeGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CLifeGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CLifeGameDoc 诊断

#ifdef _DEBUG
void CLifeGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLifeGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


