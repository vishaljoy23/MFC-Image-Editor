
// MFCApplication11Dlg.h : header file
//

#pragma once


// CMFCApplication11Dlg dialog
class CMFCApplication11Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication11Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION11_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	CStatic picture;
	afx_msg void OnBnClickedButton2();
	CButton Btn_Buff;
//	CString ed;
//	CString ed2;
	afx_msg void OnBnClickedButton3();
	CString ed;
	CString ed2;
	CStatic picture_2;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnStnClickedStaticPic2();
};
