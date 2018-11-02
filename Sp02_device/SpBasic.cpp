// D3D Sprite Tutorial
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning( disable : 4996)


#pragma comment(lib, "d3d9.lib")

#include <windows.h>

#include <d3d9.h>


char				m_sCls[128]		;
HINSTANCE			m_hInst		= NULL;
HWND				m_hWnd		= NULL;
DWORD				m_dWinStyle	= WS_OVERLAPPEDWINDOW| WS_VISIBLE;
DWORD				m_dScnX		= 800;			// Screen Width
DWORD				m_dScnY		= 600;			// Screen Height

// 항상 포인터들은 NULL로 초기화
LPDIRECT3D9			m_pD3D		= NULL;			// D3D
LPDIRECT3DDEVICE9	m_pd3dDevice= NULL;			// Device

BOOL				m_bWindow	= TRUE;			// Window mode
BOOL				m_bShowCusor= TRUE;			// Show Cusor


//Window+Device관련 함수들
INT		Create(HINSTANCE hInst);
INT		Run();
void	Cleanup();

//게임 실행 관련 함수들
INT		Init();
void	Destroy();
INT		FrameMove();
INT		Render();

LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );



INT Create( HINSTANCE hInst)
{
	m_hInst	= hInst;
	strcpy(m_sCls, "D3D Tutorial");

	WNDCLASS wc =								// Register the window class
	{
		CS_CLASSDC
			, WndProc
			, 0L
			, 0L
			, m_hInst
			, NULL
			, LoadCursor(NULL,IDC_ARROW)
			, (HBRUSH)GetStockObject(LTGRAY_BRUSH)
			, NULL
			, m_sCls
	};

	RegisterClass( &wc );

	RECT rc;									//Create the application's window

	SetRect( &rc, 0, 0, m_dScnX, m_dScnY);
	AdjustWindowRect( &rc, m_dWinStyle, FALSE );

	int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);

	m_hWnd = CreateWindow( m_sCls
		, m_sCls
		, m_dWinStyle
		, (iScnSysW - (rc.right - rc.left))/2
		, (iScnSysH - (rc.bottom - rc.top))/2
		, (rc.right - rc.left)
		, (rc.bottom - rc.top)
		, GetDesktopWindow()
		, NULL
		, m_hInst
		, NULL );


	// D3D생성
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return -1;

	// 디바이스를 생성하기 위해서는 프리젠트 파라메터 구조체가 필요
	// 전부 0으로 셋팅한다음 일부만 변수세팅

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.Windowed				= m_bWindow;
	d3dpp.SwapEffect			= D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil= TRUE;
	d3dpp.AutoDepthStencilFormat= D3DFMT_D16;


	// D3DADAPTER_DEFAULT: 대부분의 그래픽카드는 모노 듀얼일 경우 이부분을 수정
	// D3DDEVTYPE_HAL : 하드웨어 가속(가장 큰 속도)을 받을 것인가.. 하드웨어 지
	// 원이 없을 경우 D3D는 소프트웨어로 이를 대체 할 수 있다.

	if( FAILED( m_pD3D->CreateDevice(	D3DADAPTER_DEFAULT
									,	D3DDEVTYPE_HAL
									,	m_hWnd
									,	D3DCREATE_MIXED_VERTEXPROCESSING
									,	&d3dpp
									,	&m_pd3dDevice ) ) )
	{
		if( FAILED( m_pD3D->CreateDevice(	D3DADAPTER_DEFAULT
										,	D3DDEVTYPE_HAL
										,	m_hWnd
										,	D3DCREATE_SOFTWARE_VERTEXPROCESSING
										,	&d3dpp
										,	&m_pd3dDevice ) ) )
		{
			m_pD3D->Release();
			return -1;
		}
	}

	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );
	::ShowCursor(m_bShowCusor);


	if(FAILED(Init()))
		return -1;


	return 0;
}


void Cleanup()
{
	Destroy();

	if(m_pd3dDevice)
	{
		m_pd3dDevice->Release();
		m_pd3dDevice	= NULL;
	}

	if(m_pD3D)
	{
		m_pD3D->Release();
		m_pD3D	= NULL;
	}
}


LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		case WM_KEYDOWN:
		{
			switch(wParam)
			{
				case VK_ESCAPE:
				{
					SendMessage(hWnd, WM_DESTROY, 0,0);
					break;
				}
			}

			return 0;
		}

		case WM_DESTROY:
		{
			Cleanup();
			PostQuitMessage( 0 );
			return 0;
		}
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}



INT Run()
{
	// Enter the message loop
	MSG msg;
	memset( &msg, 0, sizeof(msg) );

	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			if(FAILED(FrameMove()))
				SendMessage(m_hWnd, WM_QUIT,0,0);

			if(FAILED(Render()))
				SendMessage(m_hWnd, WM_QUIT,0,0);
		}
	}

	UnregisterClass( m_sCls, m_hInst);

	return 0;
}



INT Init()
{
	////////////////////////////////////////////////////////////////////////////
	//

	// 게임 데이터 생성

	//
	////////////////////////////////////////////////////////////////////////////

	return 0;
}

void Destroy()
{
	////////////////////////////////////////////////////////////////////////////
	//

	// 게임 데이터 해제

	//
	////////////////////////////////////////////////////////////////////////////
}

INT FrameMove()
{
	return 0;
}


INT Render()
{
	if( NULL == m_pd3dDevice )
		return -1;

	// 실질적으로는 버퍼(후면 버퍼: 색상, 깊이, 스텐실)를 지우는 것이 아니라 채우는 것이다.
	// D3DCLEAR_TARGET: 색상 버퍼를 지운다.
	// D3DCLEAR_ZBUFFER: 깊이 버퍼를 지운다.
	// Clear에서 D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER 설정은 가장 흔한 방법이다.
	m_pd3dDevice->Clear( 0
					, NULL
					, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER
					, D3DCOLOR_XRGB(0,120,160)
					, 1.0f, 0 );


	// BeginScene과 EndScene에 렌더링을 걸어주어야 된다.
	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;

	////////////////////////////////////////////////////////////////////////////
	//

	// 렌더링

	//
	////////////////////////////////////////////////////////////////////////////


	// EndScene
	m_pd3dDevice->EndScene();

	// 후면버퍼 전면버퍼 교체( flipping)
	return m_pd3dDevice->Present( 0, 0, 0, 0);
}



LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return MsgProc(hWnd, msg, wParam, lParam);
}



INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	if(FAILED(Create(hInst)))
		return -1;

	return Run();
}