// D3D Sprite Tutorial
//
////////////////////////////////////////////////////////////////////////////////

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>

#include <stdio.h>
#include <time.h>

#include <d3d9.h>
#include <d3dx9.h>

// Window+Device 데이터
////////////////////////////////////////////////////////////////////////////////

char				m_sCls[128]		;				// Class Name
HINSTANCE			m_hInst		= NULL;				// Window Instance
HDC					m_hDC		= NULL;				// Backbuffer DC
HWND				m_hWnd		= NULL;				// Window Handle
DWORD				m_dWinStyle	= WS_VISIBLE | WS_CAPTION | WS_SYSMENU;		// Window Style
INT					m_dScnW		= 1024;				// Screen Width
INT					m_dScnH		= 768;				// Screen Height

LPDIRECT3D9			m_pD3D		= NULL;				// D3D
LPDIRECT3DDEVICE9	m_pd3dDevice= NULL;				// Device
LPD3DXSPRITE		m_pd3dSprite= NULL;				// 2D Sprite
LPDIRECT3DSURFACE9	m_pBackBuffer= NULL;			// Backbuffer point
BOOL				m_bWindow	= 0;				// Window mode
BOOL				m_bShowCusor= TRUE;				// Show Cusor

char				m_KeyOld[256];		// Old Key
char				m_KeyCur[256];		// Current Key


int				WinCreate(HINSTANCE);
int				WinRun();
void			WinCleanup();
LRESULT WINAPI	WinProc(HWND,UINT,WPARAM,LPARAM);	// Message Function

// Basic Function
int				GameInit();							// 데이터 초기와
void			GameDestroy();						// 데이터 해제
int				GameFrameMove();					// 데이터 갱신
int				GameRender();						// 데이터 렌더링


int				ParticleInit();
int				ParticleFrameMove();
void			ParticleRender();
void			ParticleSet(int);




// Implementation
////////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, int )
{
	if(FAILED(WinCreate(hInst)))
		return -1;

	return WinRun();
}




int WinCreate( HINSTANCE hInst)
{
	m_hInst	= hInst;
	strcpy(m_sCls, "D3D Tutorial");

	WNDCLASS wc ={					// Register the window class
		CS_CLASSDC
			, WinProc
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

	RECT rc;						//Create the application's window

	SetRect( &rc, 0, 0, m_dScnW, m_dScnH);
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

	D3DPRESENT_PARAMETERS d3dpp;	//이부분을 좀더 정교하게 수정
	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.hDeviceWindow				= m_hWnd;
	d3dpp.Windowed					= m_bWindow;
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferCount			= 1;
	d3dpp.BackBufferFormat			= D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth			= m_dScnW;
	d3dpp.BackBufferHeight			= m_dScnH;
	d3dpp.FullScreen_RefreshRateInHz= m_bWindow? 0: 60;
	d3dpp.EnableAutoDepthStencil	= TRUE;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;
	d3dpp.Flags						= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

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
			SAFE_RELEASE(	m_pd3dDevice	);
			SAFE_RELEASE(	m_pD3D			);
			return -1;
		}
	}

	// DX의 스프라이트는 디바이스가 생성된 후에
	if(FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pd3dSprite)))
	{
		SAFE_RELEASE(	m_pd3dDevice	);
		SAFE_RELEASE(	m_pD3D			);
		return -1;
	}

	// DC를 이용하려면 Backbuffer를 가져와야
	if(FAILED(m_pd3dDevice->GetBackBuffer(
		0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBuffer )))
	{
		SAFE_RELEASE(	m_pd3dSprite	);
		SAFE_RELEASE(	m_pd3dDevice	);
		SAFE_RELEASE(	m_pD3D			);
	}

	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );
	::ShowCursor(m_bShowCusor);


	if(FAILED(GameInit()))
		return -1;


	return 0;
}


void WinCleanup()
{
	GameDestroy();

	SAFE_RELEASE(	m_pBackBuffer	);
	SAFE_RELEASE(	m_pd3dSprite	);
	SAFE_RELEASE(	m_pd3dDevice	);
	SAFE_RELEASE(	m_pD3D			);
}


LRESULT WINAPI WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch( uMsg )
	{
		case WM_KEYDOWN:
		{
			switch(wParam)
			{
				case VK_ESCAPE:
				SendMessage(hWnd, WM_CLOSE, 0,0);
				break;
			}

			return 0;
		}

		case WM_CLOSE:
		case WM_DESTROY:
			WinCleanup();
			PostQuitMessage( 0 );
			return 0;
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam );
}


int WinRun()
{
	MSG msg;						// Enter the message loop
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
			if(FAILED(GameFrameMove()))
				SendMessage(m_hWnd, WM_QUIT,0,0);

			if(FAILED(GameRender()))
				SendMessage(m_hWnd, WM_QUIT,0,0);
		}
	}

	UnregisterClass( m_sCls, m_hInst);

	return 0;
}



int GameInit()
{
	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));

	ParticleInit();

	return 0;
}

void GameDestroy()
{
}

int GameFrameMove()
{
	// Update Keyboard Data
	memcpy(m_KeyOld, m_KeyCur, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));

	if(HIBYTE(GetAsyncKeyState(VK_SPACE)))
		m_KeyCur[VK_SPACE] = 1;

	if(HIBYTE(GetAsyncKeyState(VK_LEFT)))
		m_KeyCur[VK_LEFT] = 1;

	if(HIBYTE(GetAsyncKeyState(VK_RIGHT)))
		m_KeyCur[VK_RIGHT] = 1;

	if(HIBYTE(GetAsyncKeyState(VK_UP)))
		m_KeyCur[VK_UP] = 1;

	if(HIBYTE(GetAsyncKeyState(VK_DOWN)))
		m_KeyCur[VK_DOWN] = 1;

	ParticleFrameMove();

	return 0;
}


int GameRender()
{
	if( NULL == m_pd3dDevice )
		return -1;

	m_pd3dDevice->Clear( 0
						, NULL
						, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER
						, 0x00000000
						, 1.0f
						, 0 );

	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;

	m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);			// 2D 데이터는 Begin/End 안에 와야


	m_pd3dSprite->End();
	m_pd3dDevice->EndScene();

	if(m_pBackBuffer)
	{
		ParticleRender();

		m_pBackBuffer->GetDC(&m_hDC);

		if(m_hDC)
		{
			char	sMsg[] = "Particle Rendering with Device Surface DC";
			SetBkMode(m_hDC, TRANSPARENT);
			SetTextColor(m_hDC, RGB(255,255,0));
			TextOut(m_hDC, 10, 5, sMsg, strlen(sMsg));
			m_pBackBuffer->ReleaseDC(m_hDC);
		}
	}

	return m_pd3dDevice->Present( 0, 0, 0, 0);
}






struct SPos
{
	float	x;
	float	y;
};

struct SParticle
{
	float	px;										// Position
	float	py;
	float	vx;										// Velocity
	float	vy;
	float	ax;										// Accelation
	float	ay;
	DWORD	dC;										// Color
};


#define		NUM_PRT			4000

SParticle	g_pPrt[NUM_PRT];
SPos		g_Pos;






int ParticleInit()
{
	srand( (unsigned)time( NULL ) );

	g_Pos.x = m_dScnW/2.f;
	g_Pos.y = m_dScnH/2.f;

	for(int i=0; i<NUM_PRT; ++i)
		ParticleSet(i);

	return 0;
}


int ParticleFrameMove()
{
	if(m_KeyCur[VK_LEFT])
		g_Pos.x -=4.F;

	if(m_KeyCur[VK_RIGHT])
		g_Pos.x +=4.F;


	if(m_KeyCur[VK_UP])
		g_Pos.y -=4.F;

	if(m_KeyCur[VK_DOWN])
		g_Pos.y +=4.F;



	for(int i=0; i<NUM_PRT; ++i)
	{
		g_pPrt[i].vx += g_pPrt[i].ax;
		g_pPrt[i].vy += g_pPrt[i].ay;
		g_pPrt[i].px += g_pPrt[i].vx;
		g_pPrt[i].py += g_pPrt[i].vy;

		if(	0>=g_pPrt[i].px || m_dScnW<=g_pPrt[i].px ||
			0>=g_pPrt[i].py || m_dScnH<=g_pPrt[i].py )
		{
			ParticleSet(i);
		}
	}

	return 0;
}

void ParticleRender()
{
	D3DLOCKED_RECT	rc;
	DWORD*	pPxl;

	m_pBackBuffer->LockRect(&rc, 0, 0);

	pPxl = (DWORD*) rc.pBits;


	for(int i=0; i<NUM_PRT; ++i)
	{
		int idx = int(g_pPrt[i].py) * m_dScnW + int(g_pPrt[i].px);

		if(	0<int(g_pPrt[i].px) && m_dScnW>int(g_pPrt[i].px) &&
			0<int(g_pPrt[i].py) && m_dScnH>int(g_pPrt[i].py) )
		{
			pPxl[idx]= g_pPrt[i].dC;
		}
	}

	m_pBackBuffer->UnlockRect();
}


void ParticleSet(int nIdx)
{
	FLOAT	fA1 = rand()%10000 * 2 * D3DX_PI * 0.0001f;
	FLOAT	fRp = rand()%3000 * .01f;
	FLOAT	fRv = (3000+rand()%30000) * .001f;


	g_pPrt[nIdx].ax = -fRv * cosf(fA1) * 0.01f;
	g_pPrt[nIdx].ay = -fRv * sinf(fA1) * 0.01f;

	g_pPrt[nIdx].vx = fRv * cosf(fA1) * 1.f;
	g_pPrt[nIdx].vy = fRv * sinf(fA1) * 1.f;

	g_pPrt[nIdx].px = g_Pos.x + fRp * cosf(fA1);
	g_pPrt[nIdx].py = g_Pos.y + fRp * sinf(fA1);



	g_pPrt[nIdx].dC = D3DCOLOR_XRGB( 100+rand()%156, 100+rand()%156, 100+rand()%256);
}