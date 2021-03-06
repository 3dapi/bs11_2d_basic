// D3D Sprite Tutorial
//
////////////////////////////////////////////////////////////////////////////////

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

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
DWORD				m_dScnW		= 640;				// Screen Width
DWORD				m_dScnH		= 480;				// Screen Height

LPDIRECT3D9			m_pD3D		= NULL;				// D3D
LPDIRECT3DDEVICE9	m_pd3dDevice= NULL;				// Device
LPD3DXSPRITE		m_pd3dSprite= NULL;				// 2D Sprite
LPDIRECT3DSURFACE9	m_pBackBuffer= NULL;			// Backbuffer point
BOOL				m_bWindow	= TRUE;				// Window mode
BOOL				m_bShowCusor= TRUE;				// Show Cusor

int				WinCreate(HINSTANCE);
int				WinRun();
void			WinCleanup();
LRESULT WINAPI	WinProc(HWND,UINT,WPARAM,LPARAM);	// Message Function

// Basic Function
int				GameInit();							// 데이터 초기와
void			GameDestroy();						// 데이터 해제
int				GameFrameMove();					// 데이터 갱신
int				GameRender();						// 데이터 렌더링




// Application
////////////////////////////////////////////////////////////////////////////////

#define TX_NUM			1

struct MapBit
{
	int		nIdx;
	RECT	rc;							// Region
};

struct MapImg
{
	int		nIdx;
	float	x;							// Position x
	float	y;							// Position y
};

char				m_KeyOld[256];		// Old Key
char				m_KeyCur[256];		// Current Key

LPDIRECT3DTEXTURE9	m_pTx[TX_NUM];		// 배경 텍스처

int					m_nCntRow=4;		// Number of Row
int					m_nCntCol=3;		// Number of column
int					m_nImg=0;			// Index of Image
int					m_iCntSf=4;			// Shuffle Count
int					m_iCntKey=1;		// Keybord 움직인거..
int					m_iScore=100;		// 점수
int					m_iBlockX;			// block image x size
int					m_iBlockY;			// block image y size

MapBit*				m_pMapBit;			// MapBit m_pMapBit[m_iNumMap];
MapImg**			m_pMapImg;			// corespond the Bitmap...

int					m_iNumMap;			// total block number(실제 1개 더 많음)
int					m_nBlankI;
int					m_nBlankJ;
BOOL				m_bSuccess=FALSE;

int		PlayFrameMove();				// 플레이 갱신
void	PlayRender();					// 플레이 렌더링
void	PlayRndBck();					// 플레이 Back buffer 렌더링

int		ImgArrayInit();					// Image Array Init
void	ImgArrayDestroy();				// Image Array Delete
void	ImgArrayShuffle();				// Image Array Shuffle





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

char* m_sImg[] =
{
	"Texture/img1.bmp",
};


int GameInit()
{
	int	i;
	D3DXIMAGE_INFO	pImgInf;

	for(i=0; i<TX_NUM; ++i)
	{
		if( FAILED( D3DXCreateTextureFromFileEx(
			m_pd3dDevice
			, m_sImg[i]
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, 0x0000001
			, 0x0000001
			, 0xFF000000
			, &pImgInf
			, NULL
			, &m_pTx[i]
			)) )
		{
			m_pTx[i] = NULL;
			return -1;
		}
	}

	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));

	ImgArrayInit();

	return 0;
}

void GameDestroy()
{
	int i;

	// 텍스처 해제
	for(i=0; i<TX_NUM; ++i)
		SAFE_RELEASE(	m_pTx[i]	);

	// Image Array Destroy
	ImgArrayDestroy();
}

int GameFrameMove()
{
	// Update Keyboard Data
	memcpy(m_KeyOld, m_KeyCur, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));

//	if(HIBYTE(GetAsyncKeyState(VK_LEFT)))
//		m_KeyCur[VK_END] = 1;

	for(int i=0; i<256; ++i)
	{
		if( GetAsyncKeyState(i) &0x8000)
			m_KeyCur[i] = 1;
	}


	PlayFrameMove();

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

	// Begin the scene
	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;

	// 2D 데이터는 Begin/End 안에 와야
	m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);

	PlayRender();

	m_pd3dSprite->End();

	// End the scene
	m_pd3dDevice->EndScene();


	// Backbuffer 그리기
	if(m_pBackBuffer)
	{
		m_pBackBuffer->GetDC(&m_hDC);

		if(m_hDC)
		{
			PlayRndBck();
			m_pBackBuffer->ReleaseDC(m_hDC);
		}
	}

	// 후면버퍼 전면버퍼 교체( flipping)
	return m_pd3dDevice->Present( 0, 0, 0, 0);
}


////////////////////////////////////////////////////////////////////////////////
// Desc: Action..

int PlayFrameMove()
{
	int	i,j;
	int	nCntSuccess=0;

	if(0 == m_KeyOld[VK_HOME] && m_KeyCur[VK_HOME] )
	{
		ImgArrayDestroy();
		return 0;
	}


	// 우측 이동...
	if(0 == m_KeyOld[VK_RIGHT] && m_KeyCur[VK_RIGHT] )
	{
		if	(m_nBlankJ<1)
			m_nBlankJ=0;

		else
		{
			m_pMapImg[m_nBlankI][m_nBlankJ].nIdx
				= m_pMapImg[m_nBlankI][m_nBlankJ-1].nIdx;

			m_pMapImg[m_nBlankI][m_nBlankJ-1].nIdx =m_iNumMap ;

			--m_nBlankJ;

			// 점수에 쓸 key 움직임을 증가
			++m_iCntKey;
		}
	}

	// 좌측 이동...
	if(0 == m_KeyOld[VK_LEFT] && m_KeyCur[VK_LEFT] )
	{
		if	(m_nBlankJ>=m_nCntCol-1)
			m_nBlankJ=m_nCntCol-1;

		else
		{
			m_pMapImg[m_nBlankI][m_nBlankJ].nIdx
				= m_pMapImg[m_nBlankI][m_nBlankJ+1].nIdx;

			m_pMapImg[m_nBlankI][m_nBlankJ+1].nIdx =m_iNumMap ;

			++m_nBlankJ;
			++m_iCntKey;
		}
	}

	// 하측 이동...
	if(0 == m_KeyOld[VK_DOWN] && m_KeyCur[VK_DOWN] )
	{
		if	(m_nBlankI<1)
			m_nBlankI=0;

		else
		{
			m_pMapImg[m_nBlankI][m_nBlankJ].nIdx
				= m_pMapImg[m_nBlankI-1][m_nBlankJ].nIdx;

			m_pMapImg[m_nBlankI-1][m_nBlankJ].nIdx =m_iNumMap ;

			--m_nBlankI;
			++m_iCntKey;
		}
	}

	// 상측 이동...
	if(0 == m_KeyOld[VK_UP] && m_KeyCur[VK_UP] )
	{
		if	(m_nBlankI>=m_nCntRow-1)
			m_nBlankI=m_nCntRow-1;

		else
		{
			m_pMapImg[m_nBlankI][m_nBlankJ].nIdx
				= m_pMapImg[m_nBlankI+1][m_nBlankJ].nIdx;

			m_pMapImg[m_nBlankI+1][m_nBlankJ].nIdx =m_iNumMap ;

			++m_nBlankI;
		}
	}


	for(i=0; i< m_nCntRow; ++i)
	{
		for(j=0; j< m_nCntCol; ++j)
		{
			// 인덱스가 같으면...
			if( m_pMapImg[i][j].nIdx == m_pMapBit[i*m_nCntCol + j].nIdx)
				++nCntSuccess;
		}
	}

	// 그림을 다 맞추었는가?
	if (nCntSuccess == (m_iNumMap+1))
	{
		++m_iCntKey;

		// 점수를 만든다.
		m_iScore	= m_iCntKey / m_iNumMap;
		m_bSuccess	= TRUE;
	}

	return 0;
}


void PlayRender()
{
	int i;
	int j;

	if(FALSE == m_bSuccess)
	{
		for(i=0; i< m_nCntRow; ++i)
		{
			for(j=0; j< m_nCntCol; ++j)
			{
				if( m_pMapImg[i][j].nIdx != m_iNumMap )
				{
					m_pd3dSprite->Draw(	m_pTx[m_nImg]
						, &m_pMapBit[ m_pMapImg[i][j].nIdx ].rc
						, NULL
						, &D3DXVECTOR3(m_pMapImg[i][j].x, m_pMapImg[i][j].y, 0.0F)
						, 0xFFFFFFFF);
				}
			}
		}
	}

	else
	{
		RECT rc={0,0, m_dScnW, m_dScnH};
		m_pd3dSprite->Draw(	m_pTx[m_nImg], &rc, NULL, NULL, 0xFFFFFFFF);
	}
}


void PlayRndBck()
{
	if(m_bSuccess)
	{
		char sBuffer[128];
		SetBkMode(m_hDC, TRANSPARENT);
		sprintf(sBuffer, "%s", "성공!!!!");
		TextOut(m_hDC, 100,60, sBuffer, strlen(sBuffer));
	}
}



////////////////////////////////////////////////////////////////////////////////
// Desc: Puzzle Data Setting

void ImgArrayDestroy()
{
	int i;

	SAFE_DELETE_ARRAY(m_pMapBit);

	if(m_pMapImg)
	{
		for(i=0; i< m_nCntRow; ++i)
		{
			SAFE_DELETE_ARRAY(m_pMapImg[i]);
		}

		SAFE_DELETE_ARRAY(m_pMapImg);
	}
}


int ImgArrayInit()
{
	int i,j;

	RECT rcImg={0,0,640,480};

	m_bSuccess	= FALSE;
	m_iNumMap = m_nCntCol * m_nCntRow -1;
	m_iBlockX = rcImg.right/m_nCntCol ;
	m_iBlockY = rcImg.bottom/m_nCntRow ;
	m_nBlankI = m_nCntRow-1;
	m_nBlankJ = m_nCntCol-1;


	//기준이 될 이미지 맵을 만든다.
	m_pMapImg = new MapImg*[m_nCntRow];


	//열생성
	for(i=0; i< m_nCntRow; ++i)
		m_pMapImg[i] = new MapImg[m_nCntCol];


	// 이미지를 맵과 동일하게 설정한다.
	m_pMapBit = new MapBit[m_iNumMap+1];

	for(i=0; i<= m_iNumMap; ++i)
	{
		m_pMapBit[i].nIdx   = i;
		m_pMapBit[i].rc.left  = m_iBlockX * (i%m_nCntCol);
		m_pMapBit[i].rc.top   = m_iBlockY * (i/m_nCntCol);
		m_pMapBit[i].rc.right = m_pMapBit[i].rc.left + m_iBlockX -1;
		m_pMapBit[i].rc.bottom= m_pMapBit[i].rc.top  + m_iBlockY -1;
	}

	//이미지의 인덱스를 이미지 맵에 쓴다.
	for(i=0; i< m_nCntRow; ++i)
	{
		for(j=0; j< m_nCntCol; ++j)
		{
			m_pMapImg[i][j].nIdx = m_pMapBit[i*m_nCntCol + j].nIdx;
			m_pMapImg[i][j].x = float(m_iBlockX * j);
			m_pMapImg[i][j].y = float(m_iBlockY * i);
		}
	}

	for(i=0; i<m_iNumMap; ++i)
		for(j=0; j<m_iNumMap; ++j)
			ImgArrayShuffle();

	return 0;
}


void ImgArrayShuffle()
{
	int i, nRand;

	srand( (unsigned int)time(0) );
	m_iCntSf = 100*m_nCntRow *m_nCntCol + rand()%(10*m_nCntRow *m_nCntCol);

	for(i=0; i<m_iCntSf; ++i)
	{
		nRand = rand()%4;

		// 우측 이동...
		if(nRand==0)
		{
			if	(m_nBlankJ<1)
				m_nBlankJ=0;

			else
			{
				m_pMapImg[m_nBlankI][m_nBlankJ].nIdx
					= m_pMapImg[m_nBlankI][m_nBlankJ-1].nIdx;

				m_pMapImg[m_nBlankI][m_nBlankJ-1].nIdx =m_iNumMap;

				--m_nBlankJ;
			}
		}

		// 좌측 이동...
		else if(nRand==1)
		{
			if	(m_nBlankJ>=m_nCntCol-1)
				m_nBlankJ=m_nCntCol-1;

			else
			{
				m_pMapImg[m_nBlankI][m_nBlankJ].nIdx
					= m_pMapImg[m_nBlankI][m_nBlankJ+1].nIdx;

				m_pMapImg[m_nBlankI][m_nBlankJ+1].nIdx =m_iNumMap;

				++m_nBlankJ;
			}
		}

		// 상측 이동...
		else if(nRand==2)
		{
			if	(m_nBlankI<1)
				m_nBlankI=0;

			else
			{
				m_pMapImg[m_nBlankI][m_nBlankJ].nIdx
					= m_pMapImg[m_nBlankI-1][m_nBlankJ].nIdx;

				m_pMapImg[m_nBlankI-1][m_nBlankJ].nIdx =m_iNumMap;

				--m_nBlankI;
			}
		}

		// 하측 이동...
		else if(nRand==3)
		{
			if	(m_nBlankI>=m_nCntRow-1)
				m_nBlankI=m_nCntRow-1;

			else
			{
				m_pMapImg[m_nBlankI][m_nBlankJ].nIdx
					= m_pMapImg[m_nBlankI+1][m_nBlankJ].nIdx;

				m_pMapImg[m_nBlankI+1][m_nBlankJ].nIdx =m_iNumMap;

				++m_nBlankI;
			}
		}
	}
}