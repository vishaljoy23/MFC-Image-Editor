
// MFCApplication11Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication11.h"
#include "MFCApplication11Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBitmap srcCBitmap;
unsigned char* buf;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMFCApplication11Dlg dialog



CMFCApplication11Dlg::CMFCApplication11Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION11_DIALOG, pParent)
	, ed(_T(""))
	, ed2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_PIC, picture);

	/*DDX_Text(pDX, IDC_EDIT1, ed);
	DDX_Text(pDX, IDC_EDIT2, ed2);*/
	DDX_Text(pDX, IDC_EDIT1, ed);
	DDX_Text(pDX, IDC_EDIT2, ed2);
	DDX_Control(pDX, IDC_STATIC_PIC2, picture_2);
}

BEGIN_MESSAGE_MAP(CMFCApplication11Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication11Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication11Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication11Dlg::OnBnClickedButton4)
	ON_STN_CLICKED(IDC_STATIC_PIC2, &CMFCApplication11Dlg::OnStnClickedStaticPic2)
END_MESSAGE_MAP()


// CMFCApplication11Dlg message handlers

BOOL CMFCApplication11Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication11Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication11Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication11Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication11Dlg::OnBnClickedButton1() //Load
{
	// TODO: Add your control notification handler code here
	CImage image;
	char s[500];
	CString fn;

	sprintf_s(s, "..\\test.bmp");

	fn = s;

	image.Load(fn);
	srcCBitmap.Detach();   // No check required?
	srcCBitmap.Attach(image.Detach());
	picture.SetBitmap(srcCBitmap);

}


void CMFCApplication11Dlg::OnBnClickedButton3() //Edit
{
	BITMAP p;
	int num_bytes;
	char s[250];
	CImage image;

	srcCBitmap.GetBitmap(&p);
	int g_h = p.bmHeight;
	int g_w = p.bmWidth;
	int g_n = p.bmBitsPixel / 8;
	num_bytes = g_h * g_w * g_n;

	if (buf != NULL) {
		free(buf);
	}

	buf = (unsigned char*)malloc(num_bytes);
	if (buf == NULL) {
		ed = "Not enough space";
		UpdateData(0);
		return;
	}

	CString cs;
	sprintf_s(s, "Height %d", g_h);
	cs = s;
	ed.SetString(cs);
	UpdateData(0);



	int r = srcCBitmap.GetBitmapBits(num_bytes, buf); // src_buf gets loaded.

	//Greyscaler and Inverter
	for (int i = 0; i < num_bytes/3;  i++){
		//Greyscale:
		*(buf + i*3)= *(buf + i * 3 +1) = *(buf + i*3+2);
		//Invert
		//*(buf + i) = 255 - *(buf + i);
	}

	//Monochrome
	//for (int i = 0; i < num_bytes; i++) {

	//	if (i % 3 == 0) {
	//		//*(buf + i) = 255;
	//		*(buf + i + 1) = 80;
	//		*(buf + i + 2) = 0;
	//	}
	//}

	
	for (int i = 0; i < num_bytes; i++) {
		
		if (i % 3 == 0) {
			*(buf + i + 2) = i / 2941;
			*(buf + i + 1) = i / 2941;
			//*(buf + i + 1) = 0;
			//*(buf + i + 2) = 0;
		}
	}

	srcCBitmap.SetBitmapBits(num_bytes, buf);
	picture_2.SetBitmap(srcCBitmap);


	
}




void CMFCApplication11Dlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	//CImage image;
}


void CMFCApplication11Dlg::OnStnClickedStaticPic2()
{
	// TODO: Add your control notification handler code here
}
