
// MyAppDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MyApp.h"
#include "MyAppDlg.h"
#include "afxdialogex.h"
#include "MyBusDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyAppDlg ��ȭ ����



CMyAppDlg::CMyAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyAppDlg::IDD, pParent)
	, m_bConnected(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyAppDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_COMM_CONFIG, &CMyAppDlg::OnBnClickedBtnCommConfig)
	ON_BN_CLICKED(IDC_BTN_COMM_OPEN_CLOSE, &CMyAppDlg::OnBnClickedBtnCommOpenClose)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_AUTO, &CMyAppDlg::OnBnClickedAuto)
	ON_MESSAGE(WM_MYBUS_RECV_FRAME, &CMyAppDlg::OnMyBusRecvFrame)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMyAppDlg �޽��� ó����

BOOL CMyAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_bConnected = FALSE;
	m_hComm = NULL;

	m_bAutoCtrl = FALSE;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMyAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMyAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMyAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyAppDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CMyAppDlg::OnBnClickedBtnCommConfig()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CallCommSetDlg();
}


void CMyAppDlg::OnBnClickedBtnCommOpenClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
  // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�
  CString str;			// ��ſ��� ����ǥ�ÿ� ���ڿ�
  char cParity;			// �и�Ƽ ǥ�ÿ� ���ں���
  char* cStopBits;	// Stop bit ǥ�ÿ� ���ڿ� ������
  CommConfigData *pCommCfg = new CommConfigData;

// �����Ʈ ���Ῡ�� Ȯ��
  if(!m_bConnected){
    GetCommCfgData(pCommCfg);
    pCommCfg->hOwner = m_hWnd;
    if((m_hComm=CommOpen(*pCommCfg)) != NULL){

       m_bConnected = TRUE;

       if(pCommCfg->Parity == EVENPARITY) cParity = 'E';
       else if(pCommCfg->Parity == ODDPARITY) cParity = 'O';
       else cParity = 'N';

       if(pCommCfg->StopBits == TWOSTOPBITS) cStopBits = "2";
       else if(pCommCfg->StopBits == ONE5STOPBITS) cStopBits = "1.5";
       else cStopBits = "1";

       str.Format(_T("COM%d,%d,%c,%d,%s"), pCommCfg->PortNum,
          pCommCfg->BaudRate,cParity,pCommCfg->ByteSize,cStopBits);

       GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
       GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("��Ʈ�ݱ�"));
       GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(false);
    } // if
   else{
       str.Format(_T("Open Error COM%d"),pCommCfg->PortNum);
       GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
    }
  }// if
  // �����Ʈ��������
 else{
     CommClose();
     m_bConnected = FALSE;
     str.Format(_T(" Closed "));
     GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
     GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("��Ʈ����"));
     GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(true);
  }
  delete pCommCfg;
}


void CMyAppDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(m_bConnected){
		CommClose();
	}

	CDialogEx::OnClose();
}


void CMyAppDlg::OnBnClickedAuto()
{
	// TODO: Add your control notification handler code here
	_MyBusFrame Query;
	BOOL static First = TRUE;

	if (m_bConnected == TRUE) {
		if (First == TRUE) {
			First = FALSE;
			// ADC Ȱ��ȭ
			Query.ui8Func = FC_WOR;
			Query.ui8Addr = VC_ADC_INTERVAL;
			Query.ui8DataH = 500 >> 8;
			Query.ui8DataL = 500 & 0xff;
			MyBusSendFrame(&Query);
			// Motor Off
			Query.ui8Func = FC_WOP;
			Query.ui8Addr = VC_PORTE;
			Query.ui8DataH = BIT3;
			Query.ui8DataL = 0x00;
			MyBusSendFrame(&Query);
			// Motor Port Enable
			Query.ui8Func = FC_WOP;
			Query.ui8Addr = VC_DDRE;
			Query.ui8DataH = BIT3;
			Query.ui8DataL = 0xff;
			MyBusSendFrame(&Query);
		}
		if (m_bAutoCtrl == FALSE) {
			SetTimer(0, 500, NULL);
			m_bAutoCtrl = TRUE;
			GetDlgItem(IDC_AUTO)->SetWindowText(_T("�ڵ�����Off"));
		} else {
			KillTimer(0);
			m_bAutoCtrl = FALSE;
			GetDlgItem(IDC_AUTO)->SetWindowText(_T("�ڵ�����On"));
		}
	} //first-if
}

void CMyAppDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	_MyBusFrame Query;
	// ����µ� ��û
	if (m_bConnected == TRUE) {
		Query.ui8Func = FC_RIR;
		Query.ui8Addr = VC_ADC2;
		MyBusSendFrame(&Query);
	}

	CDialogEx::OnTimer(nIDEvent);
}


afx_msg  LRESULT CMyAppDlg::OnMyBusRecvFrame(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your implementation code here.
	BOOL static bMotorRun = FALSE;
	_MyBusFrame Query;
	UINT8 Func;
	UINT8 Addr;
	INT16 i16Temp, i16SetTemp;
	CString str;
	float Temp;

	Func = (lParam >> 24) & 0xff;
	Addr = (lParam >> 16) & 0xff;

	if ((Func == FC_RIR) && (Addr == VC_ADC2)) {
		i16Temp = lParam & 0xffff;

		// 10��Ʈ ADC�� STEP�� ���� 2.5mV(2.5E-3)
		// MCP9700A�� 0���� �� ������� 500mV, 
		// MCP9700A�� �µ��� ������� 10mV/1��

		Temp = ((float)i16Temp * 2.5E-3 - 0.5) / 10.0E-3;
		i16Temp = (INT16)Temp;
		str.Format(_T("%d"), (int)Temp);
		GetDlgItem(IDC_CURR_TEMP)->SetWindowText(str);

		// �����µ� �б�
		i16SetTemp = GetDlgItemInt(IDC_SET_TEMP);

		Query.ui8Func = FC_WOP;
		Query.ui8Addr = VC_PORTE;
		Query.ui8DataH = BIT3;

		if (i16SetTemp < i16Temp) {
			Query.ui8DataL = 0xff;
			MyBusSendFrame(&Query);
		}
		else if (i16SetTemp > i16Temp) {
			Query.ui8DataL = 0x00;
			MyBusSendFrame(&Query);
		}
	}
	return afx_msg  LRESULT();
}
