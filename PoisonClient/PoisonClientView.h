
// PoisonClientView.h : CPoisonClientView ��Ľӿ�
//

#pragma once


class CPoisonClientView : public CView
{
protected: // �������л�����
	CPoisonClientView();
	DECLARE_DYNCREATE(CPoisonClientView)

// ����
public:
	CPoisonClientDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPoisonClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PoisonClientView.cpp �еĵ��԰汾
inline CPoisonClientDoc* CPoisonClientView::GetDocument() const
   { return reinterpret_cast<CPoisonClientDoc*>(m_pDocument); }
#endif

