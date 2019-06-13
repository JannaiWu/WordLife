
// LifeGameDoc.h: CLifeGameDoc 类的接口
//


#pragma once

#include<vector>

using namespace std;

class CLifeGameDoc : public CDocument
{
protected: // 仅从序列化创建
	CLifeGameDoc() noexcept;
	DECLARE_DYNCREATE(CLifeGameDoc)

// 特性
public:
	vector<vector<int>> v;
	vector<vector<int>> nextv;
// 操作
public:
	virtual void getfile();//虚构函数获取输入
	virtual int get_neightbor_cells(int index_x,int index_y);
	virtual int nextlife(int now,int count);
	virtual void getnext();

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CLifeGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
