
// PoisonClientView.cpp : CPoisonClientView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PoisonClient.h"
#endif

#include "PoisonClientDoc.h"
#include "PoisonClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPoisonClientView

IMPLEMENT_DYNCREATE(CPoisonClientView, CView)

BEGIN_MESSAGE_MAP(CPoisonClientView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPoisonClientView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPoisonClientView ����/����

CPoisonClientView::CPoisonClientView()
{
	// TODO: �ڴ˴���ӹ������

}

CPoisonClientView::~CPoisonClientView()
{
}

BOOL CPoisonClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPoisonClientView ����

void CPoisonClientView::OnDraw(CDC* /*pDC*/)
{
	CPoisonClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPoisonClientView ��ӡ


void CPoisonClientView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPoisonClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPoisonClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPoisonClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CPoisonClientView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPoisonClientView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPoisonClientView ���

#ifdef _DEBUG
void CPoisonClientView::AssertValid() const
{
	CView::AssertValid();
}

void CPoisonClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPoisonClientDoc* CPoisonClientView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoisonClientDoc)));
	return (CPoisonClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CPoisonClientView ��Ϣ�������
