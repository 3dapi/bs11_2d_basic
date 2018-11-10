// Implementation of the CLcInput class.
//
////////////////////////////////////////////////////////////////////////////////

// 휠마우스를 쓰려면 이 구문은 반드시 필요.
#define _WIN32_WINNT 0x0400


#include <windows.h>
#include <d3dx9.h>

#include "ILcInput.h"


namespace LcsLib
{


class CLcInput : public ILcInput
{
public:
	HWND		m_hWnd;

	BYTE		m_KeyCur[ILcInput::MAX_INPUT_KEY];	// 키보드 현재 상태
	BYTE		m_KeyOld[ILcInput::MAX_INPUT_KEY];	// 키보드 이전 상태
	BYTE		m_KeyMap[ILcInput::MAX_INPUT_KEY];	// 키보드 맵

	BYTE		m_BtnCur[ILcInput::MAX_INPUT_BTN];	// 마우스 현재 상태
	BYTE		m_BtnOld[ILcInput::MAX_INPUT_BTN];	// 마우스 이전 상태
	BYTE		m_BtnMap[ILcInput::MAX_INPUT_BTN];	// 마우스 맵

	D3DXVECTOR3	m_vcCur;					// 휠 마우스 Z
	D3DXVECTOR3 m_vcOld;
	D3DXVECTOR3 m_vcEps;

	DWORD		m_dTimeDC;					// Double Click Time Interval
	DWORD		m_dBtnBgn[ILcInput::MAX_INPUT_BTN];	// Double Click Start
	INT			m_dBtnCnt[ILcInput::MAX_INPUT_BTN];	// Double Click Count


public:
	CLcInput();
	virtual ~CLcInput();

	virtual	INT		Create(void* p1=NULL,void* p2=NULL,void* p3=NULL,void* p4=NULL);
	virtual INT		FrameMove();
	virtual void	Destroy();
	virtual LRESULT	MsgProc(HWND,UINT,WPARAM,LPARAM);

public:
	virtual BOOL	KeyDown	(INT nKey);
	virtual BOOL	KeyUp	(INT nKey);
	virtual BOOL	KeyPress(INT nKey);
	virtual INT		KeyState(INT nKey);

	virtual BOOL	BtnDown	 (INT nBtn);
	virtual BOOL	BtnUp	 (INT nBtn);
	virtual BOOL	BtnPress (INT nBtn);
	virtual INT		BtnState (INT nBtn);

	virtual const FLOAT* GetMousePos();
	virtual const FLOAT* GetMouseEps();

	virtual const BYTE* GetKeyMap();
	virtual const BYTE* GetBtnMap();
};




CLcInput::CLcInput()
{
	m_hWnd		= NULL; // for Mouse

	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	memset(m_BtnCur, 0, sizeof(m_BtnCur));
	memset(m_BtnOld, 0, sizeof(m_BtnOld));
	memset(m_BtnMap, 0, sizeof(m_BtnMap));

	m_vcCur = D3DXVECTOR3( 0, 0, 0);
	m_vcOld = D3DXVECTOR3( 0, 0, 0);
	m_vcEps = D3DXVECTOR3( 0, 0, 0);


	m_dTimeDC	= 0;
	memset(m_dBtnBgn, 0, sizeof(m_dBtnBgn));
	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	BYTE	sKey[256]={0};
	::SetKeyboardState(sKey);
}

CLcInput::~CLcInput()
{
	Destroy();
}


void CLcInput::Destroy()
{
}



INT CLcInput::Create(void* p1,void* p2,void* p3,void* p4)
{
	m_hWnd		= (HWND)p1;

	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	memset(m_BtnCur, 0, sizeof(m_BtnCur));
	memset(m_BtnOld, 0, sizeof(m_BtnOld));
	memset(m_BtnMap, 0, sizeof(m_BtnMap));

	m_vcCur = D3DXVECTOR3( 0, 0, 0);
	m_vcOld = D3DXVECTOR3( 0, 0, 0);
	m_vcEps = D3DXVECTOR3( 0, 0, 0);


	m_dTimeDC	= GetDoubleClickTime();

	memset(m_dBtnBgn, 0, sizeof(m_dBtnBgn));
	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	m_dBtnBgn[0]	= GetTickCount();

	for(INT i=1; i<ILcInput::MAX_INPUT_BTN; ++i)
	{
		m_dBtnBgn[i]	= m_dBtnBgn[0];
	}

	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	//UINT ucNumLines=3;  // 3 is the default
	UINT ucNumLines=0;  // 3 is the default
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &ucNumLines, 0);

	return 0;
}


INT CLcInput::FrameMove()	// Mouse
{
	INT i	= 0;

	// 1. current 값을 old에 복사, 이전 상태를 저장한다.
	memcpy(m_KeyOld, m_KeyCur, sizeof(m_KeyOld));
	memcpy(m_BtnOld, m_BtnCur, sizeof(m_BtnOld));		// Mouse


	// 2. Current 와 Map의 값을 0으로 초기화
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	memset(m_BtnCur, 0, sizeof(m_BtnCur));				// Mouse
	memset(m_BtnMap, 0, sizeof(m_BtnMap));


	//3. current 이벤트 를 가져옴
	GetKeyboardState(m_KeyCur);


	// Keyboard
	for(i=0; i<ILcInput::MAX_INPUT_KEY; ++i)
	{
		BYTE	vKey = m_KeyCur[i] & 0x80;		// 현재의 키보드 상태를 읽어온다.
		m_KeyCur[i] = (vKey)? 1: 0;				// 키보드 상태를 0과 1로 정한다.

		INT nOld = m_KeyOld[i];
		INT nCur = m_KeyCur[i];

		if		(0 == nOld && 1 ==nCur) m_KeyMap[i] = ILcInput::EINPUT_DOWN;	// Down
		else if (1 == nOld && 0 ==nCur) m_KeyMap[i] = ILcInput::EINPUT_UP;		// UP
		else if (1 == nOld && 1 ==nCur) m_KeyMap[i] = ILcInput::EINPUT_PRESS;	// PRESS
		else							m_KeyMap[i] = ILcInput::EINPUT_NONE;	// NONE
	}


	// Mouse button
	m_BtnCur[0] = m_KeyCur[VK_LBUTTON];	// Left Button
	m_BtnCur[1] = m_KeyCur[VK_RBUTTON];	// Right Button
	m_BtnCur[2] = m_KeyCur[VK_MBUTTON];	// Middle Button


	for(i=0; i<ILcInput::MAX_INPUT_BTN; ++i)
	{
		INT nOld = m_BtnOld[i];
		INT nCur = m_BtnCur[i];

		if		(0 == nOld && 1 ==nCur) m_BtnMap[i] = ILcInput::EINPUT_DOWN;	// Down
		else if (1 == nOld && 0 ==nCur) m_BtnMap[i] = ILcInput::EINPUT_UP;		// UP
		else if (1 == nOld && 1 ==nCur) m_BtnMap[i] = ILcInput::EINPUT_PRESS;	// PRESS
		else							m_BtnMap[i] = ILcInput::EINPUT_NONE;	// NONE
	}



	// 4. Update Mouse Position
	POINT pt;
	::GetCursorPos(&pt);
	::ScreenToClient(m_hWnd, &pt);

	m_vcCur.x = FLOAT(pt.x);
	m_vcCur.y = FLOAT(pt.y);

	m_vcEps = m_vcCur - m_vcOld;

	m_vcOld = m_vcCur;



	//5. Double Check
	DWORD dBtnCur = GetTickCount();

	for(i=0; i<ILcInput::MAX_INPUT_BTN; ++i)
	{
		if(ILcInput::EINPUT_DOWN == m_BtnMap[i])
		{
			if( 1== m_dBtnCnt[i])
			{
				if( (dBtnCur - m_dBtnBgn[i]) >= m_dTimeDC)
				{
					m_dBtnCnt[i] = 0;
				}
			}


			++m_dBtnCnt[i];

			if(1 == m_dBtnCnt[i])
			{
				m_dBtnBgn[i]	= dBtnCur;
			}
		}


		if(ILcInput::EINPUT_UP == m_BtnMap[i])
		{
			if( 1== m_dBtnCnt[i])
			{
				if( (dBtnCur - m_dBtnBgn[i]) >= m_dTimeDC)
				{
					m_dBtnCnt[i] = 0;
				}
			}

			else if( 2 == m_dBtnCnt[i])
			{
				if( (dBtnCur- m_dBtnBgn[i]) <= m_dTimeDC)
				{
					m_BtnMap[i] = ILcInput::EINPUT_DBCLC;
				}

				m_dBtnCnt[i] =0;
			}
		}

	}

//
//	mouse_event(MOUSEEVENTF_MOVE, -1, 0, 0,0);

	return 0;
}


BOOL CLcInput::KeyDown(INT nKey)
{
	return m_KeyMap[nKey] == ILcInput::EINPUT_DOWN;
}

BOOL CLcInput::KeyUp(INT nKey)
{
	return m_KeyMap[nKey] == ILcInput::EINPUT_UP;
}

BOOL CLcInput::KeyPress(INT nKey)
{
	return m_KeyMap[nKey] == ILcInput::EINPUT_PRESS;
}

INT CLcInput::KeyState(INT nKey)
{
	return m_KeyMap[nKey];
}

// Mouse

BOOL CLcInput::BtnDown(INT nBtn)
{
	return m_BtnMap[nBtn] == ILcInput::EINPUT_DOWN;
}

BOOL CLcInput::BtnUp(INT nBtn)
{
	return m_BtnMap[nBtn] == ILcInput::EINPUT_UP;
}

BOOL CLcInput::BtnPress(INT nBtn)
{
	return m_BtnMap[nBtn] == ILcInput::EINPUT_PRESS;
}

INT CLcInput::BtnState(INT nBtn)
{
	return m_BtnMap[nBtn];
}

const FLOAT* CLcInput::GetMousePos()
{
	return &m_vcCur[0];
}


const FLOAT* CLcInput::GetMouseEps()
{
	return &m_vcEps[0];
}


const BYTE* CLcInput::GetKeyMap()
{
	return &m_KeyMap[0];
}


const BYTE* CLcInput::GetBtnMap()
{
	return &m_BtnMap[0];
}




LRESULT CLcInput::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch( msg )
	{
		case WM_MOUSEWHEEL:
		{
			INT c= HIWORD(wParam);
			INT d= LOWORD(wParam);

			c = short( c );
			m_vcCur.z += FLOAT(c)/120.f;
			break;
		}
	}

	return 0;
}





INT LcDev_InputCreate(char* sCmd, ILcInput** pData, void* hWnd)
{
	*pData = NULL;

	CLcInput* pObj = new CLcInput;

	if(pObj->Create(hWnd))
	{
		delete pObj;
		return -1;
	}

	*pData = pObj;

	return 0;
}

};// namespace LcsLib
////////////////////////////////////////////////////////////////////////////////



