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

#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
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
DWORD				m_dScnW		= 800;				// Screen Width
DWORD				m_dScnH		= 600;				// Screen Height

LPDIRECT3D9			m_pD3D		= NULL;				// D3D
LPDIRECT3DDEVICE9	m_pd3dDevice= NULL;				// Device
LPD3DXSPRITE		m_pd3dSprite= NULL;				// 2D Sprite
LPDIRECT3DSURFACE9	m_pBackBuffer= NULL;			// Backbuffer point
BOOL				m_bWindow	= TRUE;				// Window mode

int				WinCreate(HINSTANCE);
int				WinRun();
void			WinCleanup();
LRESULT WINAPI	WinProc(HWND,UINT,WPARAM,LPARAM);	// Message Function

// Basic Function
int				GameInit();							// 데이터 초기와
void			GameDestroy();						// 데이터 해제
int				GameFrameMove();					// 데이터 갱신
int				GameRender();						// 데이터 렌더링


BYTE*				m_pBmp;				// Bmp Data
BYTE*				m_pPixel;			// Pixel Data
BITMAPINFOHEADER*	m_pBmpH;			// Bmp Info Header
INT					m_iImgW;			// Image Width
INT					m_iImgH;			// Image Height





// Basic Implementation
////////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int)
{
	if(FAILED(WinCreate(hInst)))
		return -1;

	return WinRun();
}





int WinCreate(HINSTANCE hInst)
{
	m_hInst	= hInst;
	strcpy(m_sCls, "Puzzle Game");

	// Register the window class
	WNDCLASS wc =
	{
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

	//Create the application's window
	RECT rc;

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

	D3DPRESENT_PARAMETERS d3dpp;
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
	::ShowCursor(TRUE);


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


LRESULT WINAPI WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch( msg )
	{
		case WM_KEYDOWN:
		{
			switch(wParam)
			{
				case VK_ESCAPE:
				{
					SendMessage(hWnd, WM_CLOSE, 0,0);
					break;
				}
			}

			return 0;
		}

		case WM_CLOSE:
		case WM_DESTROY:
		{
			WinCleanup();
			PostQuitMessage( 0 );
			return 0;
		}
	}

	return DefWindowProc(hWnd,msg,wParam,lParam );
}



int WinRun()
{
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
			if(FAILED(GameFrameMove()))
				SendMessage(m_hWnd, WM_QUIT,0,0);

			if(FAILED(GameRender()))
				SendMessage(m_hWnd, WM_QUIT,0,0);
		}
	}

	UnregisterClass( m_sCls, m_hInst);

	return 0;
}




// Apllication Implementation
////////////////////////////////////////////////////////////////////////////////
int GameInit()
{
	FILE*	fp;
	long	lSize;

	fp= fopen("Texture/img1.bmp", "rb");

	fseek(fp, 0, SEEK_END);
	lSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	m_pBmp =(BYTE*)malloc(lSize);

	fread(m_pBmp, sizeof(BYTE), lSize, fp);
	fclose(fp);

	BITMAPFILEHEADER*	fh		= (BITMAPFILEHEADER *)m_pBmp;

	m_pBmpH	= (BITMAPINFOHEADER *)(m_pBmp + sizeof(BITMAPFILEHEADER));
	m_iImgW	= m_pBmpH->biWidth;
	m_iImgH	= m_pBmpH->biHeight;
	m_pPixel= m_pBmp + fh->bfOffBits;

	return 0;
}

void GameDestroy()
{
	if(m_pBmp)
	{
		free(m_pBmp);
		m_pBmp= NULL;
	}
}

int GameFrameMove()
{
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

	m_pd3dDevice->EndScene();


	// Backbuffer 그리기
	if(m_pBackBuffer)
	{
		m_pBackBuffer->GetDC(&m_hDC);

		if(m_hDC)
		{
			if (m_pPixel)
			{
				SetDIBitsToDevice(
					m_hDC					// handle to DC
					, 0						// x-coord of destination upper-left corner
					, 0						// y-coord of destination upper-left corner
					, m_iImgW				// source rectangle width
					, m_iImgH				// source rectangle height
					, 0						// x-coord of source lower-left corner
					, 0						// y-coord of source lower-left corner
					, 0						// first scan line in array
					, m_iImgH				// number of scan lines
					, m_pPixel				// array of DIB bits
					,(BITMAPINFO *)m_pBmpH	// bitmap information
					, DIB_RGB_COLORS		// RGB or palette indexes
					);
			}


			char sBuffer[128]="후면 버퍼에서 얻은 DC에 이미지와 문자열 출력";
			SetBkMode(m_hDC, TRANSPARENT);
			SetTextColor(m_hDC, RGB(255, 0, 0));
			TextOut(m_hDC, 10,5, sBuffer, strlen(sBuffer));

			m_pBackBuffer->ReleaseDC(m_hDC);
		}
	}

	return m_pd3dDevice->Present( 0, 0, 0, 0);
}

