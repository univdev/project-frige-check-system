
// MyAppDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MyApp.h"
#include "MyAppDlg.h"
#include "afxdialogex.h"
#include "MyBusDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMyAppDlg 대화 상자



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


// CMyAppDlg 메시지 처리기

BOOL CMyAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_bConnected = FALSE;
	m_hComm = NULL;

	m_bAutoCtrl = FALSE;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMyAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyAppDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CMyAppDlg::OnBnClickedBtnCommConfig()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CallCommSetDlg();
}


void CMyAppDlg::OnBnClickedBtnCommOpenClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
  // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
  CString str;			// 통신연결 상태표시용 문자열
  char cParity;			// 패리티 표시용 문자변수
  char* cStopBits;	// Stop bit 표시용 문자열 포인터
  CommConfigData *pCommCfg = new CommConfigData;

// 통신포트 연결여부 확인
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
       GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("포트닫기"));
       GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(false);
    } // if
   else{
       str.Format(_T("Open Error COM%d"),pCommCfg->PortNum);
       GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
    }
  }// if
  // 통신포트연결해제
 else{
     CommClose();
     m_bConnected = FALSE;
     str.Format(_T(" Closed "));
     GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
     GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("포트열기"));
     GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(true);
  }
  delete pCommCfg;
}


void CMyAppDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
			// ADC 활성화
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
			GetDlgItem(IDC_AUTO)->SetWindowText(_T("자동제어Off"));
		} else {
			KillTimer(0);
			m_bAutoCtrl = FALSE;
			GetDlgItem(IDC_AUTO)->SetWindowText(_T("자동제어On"));
		}
	} //first-if
}

void CMyAppDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	_MyBusFrame Query;
	// 현재온도 요청
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
	UINT16 piezoTone = 988;
	UINT16 piezoDuration = 1000;
	float Temp;

	Func = (lParam >> 24) & 0xff;
	Addr = (lParam >> 16) & 0xff;

	if ((Func == FC_RIR) && (Addr == VC_ADC2)) {
		i16Temp = lParam & 0xffff;

		// 10비트 ADC의 STEP당 전압 2.5mV(2.5E-3)
		// MCP9700A의 0℃일 때 출력전압 500mV, 
		// MCP9700A의 온도당 출력전압 10mV/1℃

		Temp = ((float)i16Temp * 2.5E-3 - 0.5) / 10.0E-3;
		i16Temp = (INT16)Temp;
		str.Format(_T("%d"), (int)Temp);
		GetDlgItem(IDC_CURR_TEMP)->SetWindowText(str);

		// 설정온도 읽기
		i16SetTemp = GetDlgItemInt(IDC_SET_TEMP);

		Query.ui8Func = FC_WOP;
		Query.ui8Addr = VC_PORTE;
		Query.ui8DataH = BIT3;

		updateFNDValue(i16Temp);

		if (i16SetTemp < i16Temp) {
			Query.ui8DataL = 0xff;
			MyBusSendFrame(&Query);
			playPiezo(piezoTone, piezoDuration);
		}
		else if (i16SetTemp > i16Temp) {
			Query.ui8DataL = 0x00;
			MyBusSendFrame(&Query);
		}
	}
	return afx_msg  LRESULT();
}


void CMyAppDlg::updateFNDValue(UINT ui32Value)
{
	// TODO: Add your implementation code here.
	_MyBusFrame Query;

	if (m_bConnected == FALSE) return;

	Query.ui8Func = FC_WOR;
	Query.ui8Addr = VC_FND;
	Query.ui8DataH = (ui32Value >> 8) & 0xff;
	Query.ui8DataL = ui32Value & 0xff;

	MyBusSendFrame(&Query);
}


void CMyAppDlg::playPiezo(UINT16 ui16Freq, UINT16 ui16Duration)
{
	// TODO: Add your implementation code here.
	_MyBusFrame Query;

	UINT16 ui16Value;

	if (m_bConnected == FALSE) return;

	ui16Value = ui16Freq & 0x0fff; // 0 ~ 4.096KHz
	ui16Value |= ((ui16Duration / 100) & 0x000f) << 12; // 0 ~ 1.6sec 
														   // 200/200= 2(0.2초 출력)
	Query.ui8Func = FC_WOR;
	Query.ui8Addr = VC_PIEZO_TONE;
	Query.ui8DataH = (ui16Value >> 8) & 0xff;
	Query.ui8DataL = ui16Value & 0xff;

	MyBusSendFrame(&Query);
}
