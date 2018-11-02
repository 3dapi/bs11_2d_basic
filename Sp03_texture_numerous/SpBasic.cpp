// D3D Sprite Tutorial
//
////////////////////////////////////////////////////////////////////////////////

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>


char				m_sCls[128]		;
HINSTANCE			m_hInst		= NULL;
HWND				m_hWnd		= NULL;
DWORD				m_dWinStyle	= WS_OVERLAPPEDWINDOW| WS_VISIBLE;
DWORD				m_dScnX		= 800;			// Screen Width
DWORD				m_dScnY		= 600;			// Screen Height

												// �׻� �����͵��� NULL�� �ʱ�ȭ
LPDIRECT3D9			m_pD3D		= NULL;			// D3D
LPDIRECT3DDEVICE9	m_pd3dDevice= NULL;			// Device
LPD3DXSPRITE		m_pd3dSprite= NULL;			// 2D Sprite
BOOL				m_bWindow	= TRUE;			// Window mode
BOOL				m_bShowCusor= TRUE;			// Show Cusor


//Window+Device���� �Լ���
INT		Create(HINSTANCE hInst);
INT		Run();
void	Cleanup();

//���� ���� ���� �Լ���
INT		Init();
void	Destroy();
INT		FrameMove();
INT		Render();

LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);



D3DXIMAGE_INFO		m_Img[256]={0};		// �̹��� ����
LPDIRECT3DTEXTURE9	m_Tex[256]={0};		// �ؽ�ó ������



char* m_TexName[] =						// Texture Name
{
	"Texture/mario_cloud.png"	,
	"Texture/mario_bush2.png"	,
	"Texture/mario_bush1.png"	,
	"Texture/mario_tile1.png"	,
	"Texture/mario_all.png"		,
	"",
};



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


	// D3D����
	if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return -1;

	// ����̽��� �����ϱ� ���ؼ��� ������Ʈ �Ķ���� ����ü�� �ʿ�
	// ���� 0���� �����Ѵ��� �Ϻθ� ��������

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.Windowed				= m_bWindow;
	d3dpp.SwapEffect			= D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat		= D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth		= m_dScnX;
	d3dpp.BackBufferHeight		= m_dScnY;
	d3dpp.EnableAutoDepthStencil= TRUE;
	d3dpp.AutoDepthStencilFormat= D3DFMT_D16;


	// D3DADAPTER_DEFAULT: ��κ��� �׷���ī��� ��� ����� ��� �̺κ��� ����
	// D3DDEVTYPE_HAL : �ϵ���� ����(���� ū �ӵ�)�� ���� ���ΰ�.. �ϵ���� ��
	// ���� ���� ��� D3D�� ����Ʈ����� �̸� ��ü �� �� �ִ�.

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

	// DX�� ��������Ʈ�� ����̽��� ������ �Ŀ� ������ �Ѵ�.
	if(FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pd3dSprite)))
	{
		SAFE_RELEASE(	m_pd3dDevice	);
		SAFE_RELEASE(	m_pD3D			);
		return -1;
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

	SAFE_RELEASE(	m_pd3dSprite	);
	SAFE_RELEASE(	m_pd3dDevice	);
	SAFE_RELEASE(	m_pD3D			);
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
	HRESULT hr=-1;
	int		i=0;

	// �ؽ�ó ����

	while( m_TexName[i] &&
			4<strlen(m_TexName[i])
			)
	{
		hr = D3DXCreateTextureFromFileEx(
			m_pd3dDevice				// ����̽� ������
			, m_TexName[i]				// �ؽ�ó �̸�
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, 0x0000001
			, 0x0000001
			, 0x00FFFFFF				// �÷� Ű
			, &m_Img[i]					// �ؽ�ó �������̼�
			, NULL
			, &m_Tex[i]					// �ؽ�ó ������
			);


		if( FAILED(hr) )
		{
			MessageBox(m_hWnd, "Texture Create Failed", "Err", 0);
			return -1;
		}// if


		++i;
	}

	return 0;
}

void Destroy()
{
	int		i=0;

	// �ؽ�ó ����
	while( m_Tex[i])
	{
		SAFE_RELEASE(	m_Tex[i]	);
	}
}

INT FrameMove()
{
	return 0;
}


INT Render()
{
	if( NULL == m_pd3dDevice )
		return -1;

	m_pd3dDevice->Clear( 0
						, NULL
						, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER
						, D3DCOLOR_XRGB(0,120,160)
						, 1.0f
						, 0 );


	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;



	m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);




	// ������ �׸���.
	RECT	rcCloud1 = {0,0, 136, 128};
	m_pd3dSprite->Draw(	m_Tex[0]
						, &rcCloud1
						, NULL
						, &D3DXVECTOR3(200, 50, 0)
						, D3DXCOLOR(1,1,1,1)	);

	RECT	rcCloud2 = {144,0, 336, 128};
	m_pd3dSprite->Draw(	m_Tex[0]
						, &rcCloud2
						, NULL
						, &D3DXVECTOR3(500, 50, 0)
						, D3DXCOLOR(1,1,1,1)	);


	// ����2�� �׸���.
	RECT	rcBush1 = {0,0, m_Img[1].Width, m_Img[1].Height};
	m_pd3dSprite->Draw(	m_Tex[1]
						, &rcBush1
						, NULL
						, &D3DXVECTOR3(100, 286, 0)
						, D3DXCOLOR(1,1,1,1)	);

	m_pd3dSprite->Draw(	m_Tex[1]
						, &rcBush1
						, NULL
						, &D3DXVECTOR3(700, 286, 0)
						, D3DXCOLOR(1,1,1,1)	);

	// ����1�� �׸���.
	RECT	rcBush2 = {0,0, m_Img[2].Width, m_Img[2].Height};

	m_pd3dSprite->Draw(	m_Tex[2]
						, &rcBush2
						, NULL
						, &D3DXVECTOR3(-50, 400, 0)
						, D3DXCOLOR(1,1,1,1)	);

	m_pd3dSprite->Draw(	m_Tex[2]
						, &rcBush2
						, NULL
						, &D3DXVECTOR3(300, 400, 0)
						, D3DXCOLOR(1,1,1,1)	);

	m_pd3dSprite->Draw(	m_Tex[2]
						, &rcBush2
						, NULL
						, &D3DXVECTOR3(600, 400, 0)
						, D3DXCOLOR(1,1,1,1)	);


	// �ٴ��� �׸���.
	RECT	rcTile1= {0,0, m_Img[3].Width, m_Img[3].Height};
	RECT	rcTile2= {0,66, m_Img[3].Width, m_Img[3].Height};

	for(int i=0; i<7; ++i)
	{
		m_pd3dSprite->Draw(   m_Tex[3]
							, &rcTile1
							, NULL
							, &D3DXVECTOR3(i* m_Img[3].Width* 1.f, 440.f, 0)
							, D3DXCOLOR(1,1,1,1)	);

		m_pd3dSprite->Draw(   m_Tex[3]
							, &rcTile2
							, NULL
							, &D3DXVECTOR3(i* m_Img[3].Width* 1.f, 550, 0)
							, D3DXCOLOR(1,1,1,1)	);
	}

	// �������� �׸���.
	FLOAT		fX1 = m_Img[4].Width/8.f  * (1+0);
	FLOAT		fY1 = m_Img[4].Height/4.f * (3+0);

	FLOAT		fX2 = m_Img[4].Width/8.f  * (1+1);
	FLOAT		fY2 = m_Img[4].Height/4.f * (3+1);


	RECT	rcMario= { LONG(fX1), LONG(fY1), LONG(fX2), LONG(fY2) };
	m_pd3dSprite->Draw(   m_Tex[4]
							, &rcMario
							, NULL
							, &D3DXVECTOR3(500, 362, 0)
							, D3DXCOLOR(1,1,1,1)	);


	m_pd3dSprite->End();





	m_pd3dDevice->EndScene();

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