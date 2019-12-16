#pragma once

/*
 2015.09.02일 소스 수정
*/
/* JBusDLL 임포트용 라이브러파일을 포함*/
#pragma comment(lib, "MyBusDll.lib")

/*********************************
윈도우 메시지
*********************************/

#define WM_COMM_BREAK_DETECTED		WM_USER+1	// A break was detected on input.
#define WM_COMM_CTS_DETECTED		WM_USER+2	// The CTS (clear-to-send) signal changed state. 
#define WM_COMM_DSR_DETECTED		WM_USER+3	// The DSR (data-set-ready) signal changed state. 
#define WM_COMM_ERR_DETECTED		WM_USER+4	// A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. 
#define WM_COMM_RING_DETECTED		WM_USER+5	// A ring indicator was detected. 
#define WM_COMM_RLSD_DETECTED		WM_USER+6	// The RLSD (receive-line-signal-detect) signal changed state. 
#define WM_COMM_RXCHAR				WM_USER+7	// A character was received and placed in the input buffer. 
#define WM_COMM_RXFLAG_DETECTED		WM_USER+8	// The event character was received and placed in the input buffer.  
#define WM_COMM_TXEMPTY_DETECTED	WM_USER+9	// The last character in the output buffer was sent.
#define WM_COMM_TIMER_ERROR			WM_USER+10	// Waitable Timer Setting Error

#define WM_MYBUS_COMM_CLOSE		WM_USER + 1000

// Query Frame에 대한 윈도우 메시지
#define WM_MYBUS_SEND_FRAME		WM_USER + 100	
// Response Frame에 대한 윈도우 메시지
#define WM_MYBUS_RECV_FRAME		WM_USER + 101
// 
#define WM_MYBUS_LED_UPDATE		WM_USER + 200

#define WM_MYBUS_FND_UPDATE		WM_USER + 201

// A/D 컨버터 변환완료 이벤트 메시지
#define WM_MYBUS_ADC_VALUE		WM_USER + 202
// 입력포트 변화 감지 이벤트 메시지
#define WM_MYBUS_SWITCH_UPDATE	WM_USER + 203


/*********************************************************

	JBus 명령 코드 정의

*********************************************************/

// JBUS Function Code
#define FC_ROP			1		// Read Output Port
#define FC_RIP			2		// Read Input Port
#define FC_ROR			3		// Read Output Register
#define FC_RIR			4		// Read Input	Register
#define FC_WOP			5		// Write Output Port
#define FC_WOR			6		// Write Output Register


/*********************************************************

	JBus 이벤트 코드 정의

*********************************************************/

//#define FC_PSE			32		// PINs Status Change Event
#define FC_SCE			32		// PINs Status Change Event
#define FC_ACE			33		// A/D Complete Event
#define FC_USE			34		// Ultrasonic Event (거리측정 완료이벤트) 



/*********************************************************

	JBus 어드레스 정의

*********************************************************/
// 비트 번호 정의
#define BIT0		0
#define BIT1		1
#define BIT2		2
#define BIT3		3
#define BIT4		4
#define BIT5		5
#define BIT6		6
#define BIT7		7


// AVR I/O PORTs
#define VC_PORTA	0
#define VC_PORTB	1
#define VC_PORTC	2
#define VC_PORTD	3
#define VC_PORTE	4
#define VC_PORTF	5

// AVR PINs
#define VC_PINA		0
#define VC_PINB		1
#define VC_PINC		2
#define VC_PIND		3
#define VC_PINE		4
#define VC_PINF		5

// AVR DDRs
#define VC_DDRA		16
#define VC_DDRB		17
#define VC_DDRC		18
#define VC_DDRD		19
#define VC_DDRE		20
#define VC_DDRF		21

// Input status change event Mask
// bit 0 : PINA Unmask/ Mask (1/0)
// bit 1 : PINB Unmask/ Mask (1/0)
// bit 2 : PINC Unmask/ Mask (1/0)
// bit 3 : PIND Unmask/ Mask (1/0)
// bit 4 : PINE Unmask/ Mask (1/0)
// bit 5 : PINA Unmask/ Mask (1/0)
#define VC_PIN_EVENT_MASK		32			

// FND Value Address
#define VC_FND		48

// ADC Channel0~3 Address
#define VC_ADC0		64
#define VC_ADC1		65
#define VC_ADC2		66
#define VC_ADC3		67

// ADC Event Enable
// bit 0 : ADC Channel 0
// bit 1 : ADC Channel 1
// bit 2 : ADC Channel 2
// bit 3 : ADC Channel 3
#define VC_ADC_EVENT_MASK	72

// ADC Update Interval 0 ~ 65535ms, 0:stop update
#define VC_ADC_INTERVAL	73

// RGB LED PWM OUT Control
#ifdef _IWS_506_RGB_K3_
#define VC_RED_LED			80
#define VC_GREEN_LED		81
#define VC_BLUE_LED			82

#else

#define VC_RED_LED			81
#define VC_GREEN_LED		82
#define VC_BLUE_LED			80

#endif


// RGB LED Enable 
// 0 : Disable 1 : Enable
#define VC_RGB_LED_ENABLE	83


// Ultrasonic 
#define VC_ULTRASONIC_ENABLE		96	
#define VC_ULTRASONIC_INTERVAL		97
#define VC_ULTRASONIC_EVENT_MASK	98
#define VC_ULTRASONIC_DISTANCE		104

// PIZEO
#define VC_PIEZO_ENABLE		112
#define VC_PIEZO_TONE		113



#pragma pack(1)
struct CommConfigData{
//	HANDLE	hComm;				// 시리얼 포트 핸들
	HWND	hOwner;				// DLL의 오너 
	BYTE	PortNum;			// 시리얼 통신 포트 번호 1 ~ 
	DWORD	BaudRate;			// 통신 속도 2400 ~ 115200 기본 38400
	BYTE	ByteSize;			// Byte 크기 5,6,7,8  기본 8비트
	BYTE	StopBits;			// Stop Bit수 1, 1.5 2 기본 1
	BYTE	Parity;				// 홀수,짝수,없음
};
#pragma pack()


typedef struct{
	UINT8	ui8Func;		// MyBus 명령코드
	UINT8	ui8Addr;		// MyBus 주소
	UINT8	ui8DataH;		// MyBus 상위 데이터
	UINT8	ui8DataL;		// MyBus 하위 데이터
}_MyBusFrame;



extern "C" __declspec(dllimport)	BOOL CallCommSetDlg(void);							// 통신포트 설정 대화상자 호출
extern "C" __declspec(dllimport)	void SetCommCfgData(CommConfigData CfgData);		// 통신 포트 설정용 데이터 쓰기
extern "C" __declspec(dllimport)	void GetCommCfgData(CommConfigData* pCfgData);		// 통신 포트 설정용 데이터 얻기

extern "C" __declspec(dllimport)	HANDLE CommOpen(CommConfigData CfgData);			// 통신포트를 연결함
extern "C" __declspec(dllimport)	BOOL CommClose(void);								// 통신포트를 해제함
extern "C" __declspec(dllimport)	BOOL CommPutChar(UINT8 Ch);							// 송신용 Q에 한바이트의 데이터를 저장함
extern "C" __declspec(dllimport)	BOOL CommPutData(UINT8* pData, UINT16 Size);		// 송신용 Q에 여러 바이트의 데이터를 저장함

extern "C" __declspec(dllimport)	BOOL MyBusSendFrame(_MyBusFrame* pFrame);				// MyBus 프레임을 송신함

extern "C" __declspec(dllimport)	BOOL MyBusLED_OnOff(UINT8 OnOff);				// MyBus 프레임을 송신함


