// D3D Sprite tutorial
//
////////////////////////////////////////////////////////////////////////////////

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>

#include <d3d9.h>
#include <d3dx9.h>


TCHAR				m_sCls[128]		;
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
BOOL				m_bShowCursor= TRUE;		// Show Cursor


D3DXIMAGE_INFO		m_Img1;
LPDIRECT3DTEXTURE9	m_pTx1	= NULL;				// ��� �ؽ�ó
RECT				m_ImgRc1;

D3DXIMAGE_INFO		m_Img2;
LPDIRECT3DTEXTURE9	m_pTx2	= NULL;				// �ִ� �ؽ�ó
RECT				m_ImgRc2 = {0,0,0, 32};		// RECT �ִ� �̹���

DWORD				m_dTimeBegin;				// ���� Ÿ��
DWORD				m_dTimeEnd;					// �� Ÿ��

D3DXVECTOR3			m_vcPosImg2;



//Window+Device���� �Լ���
INT		Create(HINSTANCE hInst);
INT		Run();
void	Cleanup();

//���� ���� ���� �Լ���
INT		Init();
void	Destroy();
INT		FrameMove();
INT		Render();

LRESULT MsgProc			( HWND, UINT, WPARAM, LPARAM);
LRESULT WINAPI WndProc	( HWND, UINT, WPARAM, LPARAM);





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
		, ( iScnSysW - (rc.right-rc.left) )/2
		, ( iScnSysH - (rc.bottom-rc.top) )/2
		, ( rc.right - rc.left )
		, ( rc.bottom - rc.top )
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
	::ShowCursor(m_bShowCursor);


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
	// ��� �ؽ�ó ����
	if( FAILED( D3DXCreateTextureFromFileEx(
		m_pd3dDevice				// ����̽� ������
		, "Texture/earth.bmp"		// �ؽ�ó �̸�
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1							// �� ����(2D�� ��� �ݵ�� 1)
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, 0x0000001					// ���͸�
		, 0x0000001					// �� ����
		, 0x00FFFFFF				// �÷� Ű
		, &m_Img1					// �ؽ�ó �������̼�
		, NULL
		, &m_pTx1					// �ؽ�ó ������
		)) )
	{
		MessageBox(m_hWnd
			, "earth.bmp file Could not find"
			, "Err", 0);

		m_pTx1 = NULL;
		return -1;
	}


	// ��� �ؽ�ó�� ������ �ؽ�ó ������ ��Ȯ�� ��ġ��Ų��.
	::SetRect(&m_ImgRc1, 0,0, m_Img1.Width, m_Img1.Height);


	// �ִ� �ؽ�ó ����
	if( FAILED( D3DXCreateTextureFromFileEx(
		m_pd3dDevice
		, "Texture/animate.bmp"
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, 0x01
		, 0x01
		, 0xFF000000
		, &m_Img2
		, NULL
		, &m_pTx2
		)) )
	{
		MessageBox(m_hWnd
			, "animate.bmp file Could not find"
			, "Err", 0);
		m_pTx2 = NULL;
		return -1;
	}

	m_dTimeBegin	=timeGetTime();

	return 0;
}

void Destroy()
{
	// ����̽� ���� ������ �ؽ�ó�� ����
	SAFE_RELEASE(	m_pTx1	);
	SAFE_RELEASE(	m_pTx2	);
}

INT FrameMove()
{
	m_dTimeEnd	= timeGetTime();

	if( (m_dTimeEnd-m_dTimeBegin)>12)
	{
		m_ImgRc2.left +=32;

		if(m_ImgRc2.left +32 >=960)
			m_ImgRc2.left = 0;

		m_ImgRc2.right =m_ImgRc2.left +32;
		m_dTimeBegin = m_dTimeEnd;
	}

	m_vcPosImg2 = D3DXVECTOR3( 2* cosf(D3DX_PI*m_dTimeBegin*0.0001f)
								, sinf(D3DX_PI*m_dTimeBegin*0.0003f)
								, 0.0F
								);

	m_vcPosImg2 *= 100.f;
	m_vcPosImg2 += D3DXVECTOR3(300 , 300, 0.F);

	return 0;
}


INT Render()
{
	if( NULL == m_pd3dDevice )
		return -1;

	// ���������δ� ����(�ĸ� ����: ����, ����, ���ٽ�)�� ����� ���� �ƴ϶� ä��� ���̴�.
	// D3DCLEAR_TARGET: ���� ���۸� �����.
	// D3DCLEAR_ZBUFFER: ���� ���۸� �����.
	// Clear���� D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER ������ ���� ���� ����̴�.

	m_pd3dDevice->Clear( 0
						, NULL
						, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER
						, D3DCOLOR_XRGB(0,120,160)
						, 1.0f
						, 0 );


	// BeginScene�� EndScene�� �������� �ɾ��־�� �ȴ�.
	if( FAILED( m_pd3dDevice->BeginScene() ) )
		return -1;


	m_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);

	m_pd3dSprite->Draw(m_pTx1, &m_ImgRc1, NULL, &D3DXVECTOR3(100, 50,0), D3DXCOLOR(1,1,0.3F,0.6F));
	m_pd3dSprite->Draw(m_pTx2, &m_ImgRc2, NULL, &m_vcPosImg2, D3DXCOLOR(1,1,1,0.7F));


	m_pd3dSprite->End();


	// EndScene
	m_pd3dDevice->EndScene();

	// �ĸ���� ������� ��ü( flipping)
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