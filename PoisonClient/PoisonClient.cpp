
// PoisonClient.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PoisonClient.h"
#include "MainFrm.h"

#include "PoisonClientDoc.h"
#include "PoisonClientView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void dbg_dump(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    wsprintf
        (buff,
            "CRASH CODE:0x%.8x ADDR=0x%.8x FLAGS=0x%.8x PARAMS=0x%.8x\n"
            "eax=%.8x ebx=%.8x ecx=%.8x\nedx=%.8x esi=%.8x edi=%.8x\neip=%.8x esp=%.8x ebp=%.8x\n",
            ExceptionInfo->ExceptionRecord->ExceptionCode,
            ExceptionInfo->ExceptionRecord->ExceptionAddress,
            ExceptionInfo->ExceptionRecord->ExceptionFlags,
            ExceptionInfo->ExceptionRecord->NumberParameters,
            ExceptionInfo->ContextRecord->Eax,
            ExceptionInfo->ContextRecord->Ebx,
            ExceptionInfo->ContextRecord->Ecx,
            ExceptionInfo->ContextRecord->Edx,
            ExceptionInfo->ContextRecord->Esi,
            ExceptionInfo->ContextRecord->Edi,
            ExceptionInfo->ContextRecord->Eip,
            ExceptionInfo->ContextRecord->Esp,
            ExceptionInfo->ContextRecord->Ebp
            );

    MessageBox(NULL, buff, "Client RAT Exception", MB_OK);
}

LONG WINAPI bad_exception(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
    dbg_dump(ExceptionInfo);
    // ���˳�
    return true;
    /*ExitProcess(0);*/
}
// CPoisonClientApp

BEGIN_MESSAGE_MAP(CPoisonClientApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPoisonClientApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CPoisonClientApp ����

CPoisonClientApp::CPoisonClientApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("PoisonClient.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CPoisonClientApp ����

CPoisonClientApp theApp;


// CPoisonClientApp ��ʼ��

BOOL CPoisonClientApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
    SetUnhandledExceptionFilter(bad_exception);
	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPoisonClientDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CPoisonClientView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ�������  ���
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

    //����IOCP������
    int nPort = m_IniFile.GetInt("Settings", "ListenPort");
    int nMaxConnection = m_IniFile.GetInt("Settings", "MaxConnection");
    if (nPort == 0)
        nPort = 8080;
    if (nMaxConnection = 0)
        nMaxConnection = 8000;
    ((CMainFrame*)m_pMainWnd)->ActivateIOCP(nPort, nMaxConnection);
	return TRUE;
}

int CPoisonClientApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CPoisonClientApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CPoisonClientApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPoisonClientApp �Զ������/���淽��

void CPoisonClientApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CPoisonClientApp::LoadCustomState()
{
}

void CPoisonClientApp::SaveCustomState()
{
}

// CPoisonClientApp ��Ϣ�������



