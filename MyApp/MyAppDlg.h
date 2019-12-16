
// MyAppDlg.h : ��� ����
//

#pragma once


// CMyAppDlg ��ȭ ����
class CMyAppDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMyAppDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MYAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL m_bConnected;
	HANDLE m_hComm;
	afx_msg void OnBnClickedBtnCommConfig();
	afx_msg void OnBnClickedBtnCommOpenClose();
	afx_msg void OnClose();
	afx_msg void OnBnClickedAuto();
	bool m_bAutoCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg  LRESULT OnMyBusRecvFrame(WPARAM wParam, LPARAM lParam);
};
