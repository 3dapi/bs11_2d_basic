// Implementation of the CLcSpriteX class.
//
////////////////////////////////////////////////////////////////////////////////


#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "ILcTexture.h"
#include "ILcSpriteX.h"


#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


typedef D3DXVECTOR2			VEC2;
typedef D3DXVECTOR3			VEC3;
typedef D3DXVECTOR4			VEC4;
typedef D3DXCOLOR			DXCOL;
typedef LPDIRECT3DTEXTURE9	DXTX;

namespace LcsLib
{


class CLcSpriteX : public ILcSpriteX
{
public:
	struct VtxRHWUV1
	{
		VEC2	p;
		FLOAT	z;
		FLOAT	w;
		VEC2	t0;

		VtxRHWUV1()	: p(0,0), z(0), w(1), t0(0,0){}
		VtxRHWUV1(FLOAT X,FLOAT Y,FLOAT Z
					,FLOAT U0,FLOAT V0
					,FLOAT U1,FLOAT V1
					):p(X,Y), z(Z), w(1), t0(U0,V0){}

		enum {FVF = (D3DFVF_XYZRHW|D3DFVF_TEX1),};
	};

public:
	LPDIRECT3DDEVICE9				m_pDev;			// Device
	LPDIRECT3DVERTEXDECLARATION9	m_pFVF;
	ID3DXEffect*					m_pEft;			// ID3DXEffect
	VtxRHWUV1						m_pVtx[4];		// Vertex Buffer

	INT				m_nScnW;
	INT				m_nScnH;

	INT				m_Alphblend;

public:
	CLcSpriteX();
	virtual ~CLcSpriteX();

	virtual INT		Create(void* =0, void* =0, void* =0, void* =0);
	virtual void	Destroy();

	virtual	INT		Begin(DWORD=0);
	virtual	INT		End(DWORD=0);

	virtual	INT		OnResetDevice();
	virtual	INT		OnLostDevice();

	virtual	INT		Draw( void* pTex				// Texture
						, RECT* pRct				// Draw Region
						, void* pScl=NULL			// Scaling
						, void* pTrn=NULL			// Position
						, DWORD dColor=0xFFFFFFFF	// color
						, INT   bMono=0				// Monotone
						);

	virtual	INT		DrawEx( void* pTex				// Texture
						, RECT* pRct				// Draw Region
						, void* pScl				// Scaling
						, void* pTrn				// Position
						, void* pRot				// Rotation Center
						, FLOAT	fAngle				// Rotation Angle(Radian)
						, DWORD dColor=0xFFFFFFFF	// color
						, INT   bMono=0				// Monotone
						);

	virtual	void	AlphaOption(INT opt=0);
protected:
	INT		DrawExt(	void* pTex
						, RECT* pRct
						, VEC2* pScl
						, VEC2* pRot
						, FLOAT fRot
						, VEC2* pTrn
						, DWORD dColor
						, INT bMono);
};




CLcSpriteX::CLcSpriteX()
{
	m_pDev		= NULL;
	m_pFVF		= NULL;
	m_pEft		= NULL;

	m_nScnW		= 1024;
	m_nScnH		= 768;

	m_Alphblend	= 0;


	m_pVtx[0].t0 = VEC2(0, 0);
	m_pVtx[1].t0 = VEC2(1, 0);
	m_pVtx[2].t0 = VEC2(1, 1);
	m_pVtx[3].t0 = VEC2(0, 1);
}


CLcSpriteX::~CLcSpriteX()
{
	Destroy();
}


void CLcSpriteX::Destroy()
{
	SAFE_RELEASE(	m_pEft		);
	SAFE_RELEASE(	m_pFVF		);
}


INT CLcSpriteX::Create(void* p1, void* p2, void* p3, void* p4)
{
	HRESULT	hr=0;

	m_pDev	= (LPDIRECT3DDEVICE9)p1;

	char	sShader[]=
		" int     m_bMono;                              \n"
		" float4  m_Diff;                               \n"
		"                                               \n"
		" sampler smp0 : register(s0);                  \n"
		"                                               \n"
		"                                               \n"
		" float4 PxlProc(float4 Pos0: POSITION          \n"
		"             , float2 Tex0: TEXCOORD0):COLOR0  \n"
		" {                                             \n"
		"     float4  Out= 0;                           \n"
		"     float4  t0 = tex2D(smp0, Tex0);           \n"
		"                                               \n"
		"         Out = t0;                             \n"
		"                                               \n"
		"     Out *= m_Diff;                            \n"
		"     if(0 != m_bMono)                          \n"
		"     {                                         \n"
		"         Out.a *= m_Diff.a;                    \n"
		"         Out.r  = m_Diff.r;                    \n"
		"         Out.g  = m_Diff.g;                    \n"
		"         Out.b  = m_Diff.b;                    \n"
		"     }                                         \n"
		"                                               \n"
		"     return Out;                               \n"
		" }                                             \n"
		"                                               \n"
		" technique Tech                                \n"
		" {                                             \n"
		"    pass P0                                    \n"
		"    {                                          \n"
		"      PixelShader  = compile ps_2_0 PxlProc(); \n"
		"    }                                          \n"
		" };                                            \n"
		;


	LPD3DXBUFFER	pError	= NULL;
	DWORD			dFlag=0;

	#if defined( _DEBUG ) || defined( DEBUG )
	dFlag |= D3DXSHADER_DEBUG;
	#endif

	// 컴파일
	hr = D3DXCreateEffect(	m_pDev
							, sShader
							, strlen(sShader)-4
							, NULL
							, NULL
							, dFlag
							, NULL
							, &m_pEft
							, &pError);
	if(FAILED(hr))
	{
		MessageBox(GetActiveWindow()
					, (char*)pError->GetBufferPointer()
					, "Error", 0);
		return -1;
	}

	// 정점 선언 생성
	D3DVERTEXELEMENT9 pVertexElement[MAX_FVF_DECL_SIZE]={0};
	D3DXDeclaratorFromFVF(CLcSpriteX::VtxRHWUV1::FVF, pVertexElement);
	m_pDev->CreateVertexDeclaration(pVertexElement, &m_pFVF);

	return 0;
}



INT CLcSpriteX::Begin(DWORD dVal){	return 0;	}
INT CLcSpriteX::End(DWORD dVal)	{	return 0;	}

INT CLcSpriteX::OnResetDevice()
{
	LPDIRECT3DSURFACE9	pSfc;
	D3DSURFACE_DESC		desc;

	m_pDev->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &pSfc);
	pSfc->GetDesc(&desc);

	m_nScnW = desc.Width;
	m_nScnH = desc.Height;
	pSfc->Release();


	return m_pEft->OnResetDevice();
}

INT CLcSpriteX::OnLostDevice()
{
	return m_pEft->OnLostDevice();
}

INT CLcSpriteX::Draw(void* pTex				// Texture
					, RECT* pRct			// Draw Region
					, void* pScl			// Scaling
					, void* pTrn			// Position
					, DWORD dColor			// color
					, INT   bMono			// Monotone
					)
{
	return DrawExt(pTex, pRct, (VEC2*)pScl, NULL, 0, (VEC2*)pTrn, dColor, bMono);
}

INT CLcSpriteX::DrawEx( void* pTex			// Texture
						, RECT* pRct		// Draw Region
						, void* pScl		// Scaling
						, void* pTrn		// Position
						, void* pRot		// Rotation Center
						, FLOAT	fAngle		// Rotation Angle(Radian)
						, DWORD dColor		// color
						, INT   bMono		// Monotone
						)
{
	return DrawExt(pTex, pRct, (VEC2*)pScl, (VEC2*)pRot, fAngle, (VEC2*)pTrn, dColor, bMono);
}



INT CLcSpriteX::DrawExt(  void* pTex
						, RECT* pRct
						, VEC2* pScl
						, VEC2* pRot
						, FLOAT fRot
						, VEC2* pTrn
						, DWORD dColor
						, INT bMono)
{
	HRESULT hr=0;

	ILcTexture*	pLcTx= (ILcTexture*)pTex;
	DXTX		pDxTx = NULL;

	DXCOL	dDiff = 0XFFFFFFFF;
	VEC2	vScl(1,1);
	VEC2	vRot(0,0);
	VEC2	vTrn(0,0);

	RECT	rc1	 = {0, 0, 2048, 2048};

	VEC2	uv00(0,0);
	VEC2	uv01(1,1);
	VEC2	uv10(0,0);
	VEC2	uv11(1,1);

	FLOAT	rcW1 = 0;
	FLOAT	rcH1 = 0;
	FLOAT	rcW2 = 0;
	FLOAT	rcH2 = 0;

	FLOAT	PosL = 0;
	FLOAT	PosT = 0;
	FLOAT	PosR = 0;
	FLOAT	PosB = 0;



	// 텍스처가 없으면 빠져 나감.
	if(NULL == pLcTx || NULL == (pDxTx = (DXTX)pLcTx->GetTexture()) )
		return 0;



	// 1. 입력 값 복사
	dDiff = dColor;
	bMono = bMono;


	// 1.1 이미지 소스 1 영역 복사
	if(pRct)
	{
		rc1.left  = pRct->left  ;
		rc1.right = pRct->right ;
		rc1.top	  = pRct->top	 ;
		rc1.bottom= pRct->bottom;
	}
	else
	{
		rc1.right = pLcTx->GetImageWidth();
		rc1.bottom= pLcTx->GetImageHeight();
	}


	// 영역 재 지정
	if(rc1.left<0)							rc1.left  = 0;
	if(rc1.right>pLcTx->GetImageWidth() )	rc1.right = pLcTx->GetImageWidth();
	if(rc1.top<0)							rc1.top   = 0;
	if(rc1.bottom>pLcTx->GetImageHeight())	rc1.bottom= pLcTx->GetImageHeight();


	// 영역을 잘못 설정한 경우임
	if(rc1.top>=rc1.bottom || rc1.left>=rc1.right)
		return 0;


	// uv 설정
	uv00.x = FLOAT(rc1.left  )/FLOAT(pLcTx->GetSurfaceWidth());
	uv00.y = FLOAT(rc1.top   )/FLOAT(pLcTx->GetSurfaceHeight());
	uv01.x = FLOAT(rc1.right )/FLOAT(pLcTx->GetSurfaceWidth());
	uv01.y = FLOAT(rc1.bottom)/FLOAT(pLcTx->GetSurfaceHeight());



	if(pScl)	vScl = *pScl;
	if(pRot)	vRot = *pRot;
	if(pTrn)	vTrn = *pTrn;


	rcW1	= FLOAT(rc1.right - rc1.left);
	rcH1	= FLOAT(rc1.bottom- rc1.top );



	// Scaling 적용
	if(vScl.x>=0.f)
	{
		PosL =  vTrn.x;
		PosR = PosL + rcW1 * vScl.x;
	}
	else
	{
		PosR =  vTrn.x;
		PosL = PosR - rcW1 * vScl.x;
	}


	if(vScl.y>=0.f)
	{
		PosT = vTrn.y;
		PosB = PosT + rcH1 * vScl.y;
	}
	else
	{
		PosB = vTrn.y;
		PosT = PosB - rcH1 * vScl.y;
	}

	// 정점 설정
	m_pVtx[0].p = VEC2(PosL, PosT);
	m_pVtx[1].p = VEC2(PosR, PosT);
	m_pVtx[2].p = VEC2(PosR, PosB);
	m_pVtx[3].p = VEC2(PosL, PosB);

	m_pVtx[0].t0= VEC2(uv00.x, uv00.y);
	m_pVtx[1].t0= VEC2(uv01.x, uv00.y);
	m_pVtx[2].t0= VEC2(uv01.x, uv01.y);
	m_pVtx[3].t0= VEC2(uv00.x, uv01.y);


	// 회전 설정
	if(pRot)
	{
		FLOAT	fCos = cosf(-fRot);
		FLOAT	fSin = sinf(-fRot);

		VEC2	t;

		for(int i=0; i<4; ++i)
		{
			t = m_pVtx[i].p - vRot;

			m_pVtx[i].p.x = t.x * fCos - t.y * fSin + vRot.x;
			m_pVtx[i].p.y = t.x * fSin + t.y * fCos + vRot.y;
		}
	}


	m_pDev->SetSamplerState(0,D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pDev->SetSamplerState(0,D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// 단색일 경우 부드럽게 처리
	if(bMono)
	{
		m_pDev->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_pDev->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_pDev->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
	else
	{
		m_pDev->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_NONE);
		m_pDev->SetSamplerState(0,D3DSAMP_MINFILTER, D3DTEXF_NONE);
		m_pDev->SetSamplerState(0,D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	}

	m_pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);


	if(1 == m_Alphblend)
	{
		m_pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
	}
	else
	{
		m_pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}


	m_pDev->SetTexture(0, pDxTx);

	hr = m_pDev->SetVertexDeclaration(m_pFVF);

	hr = m_pEft->SetTechnique("Tech");
	hr = m_pEft->SetInt("m_bMono", bMono);
	hr = m_pEft->SetVector("m_Diff", (D3DXVECTOR4*)&dDiff);

	hr = m_pEft->Begin(NULL, 0);
	hr = m_pEft->BeginPass(0);

		hr = m_pDev->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, m_pVtx, sizeof(CLcSpriteX::VtxRHWUV1));

	m_pEft->EndPass();
	m_pEft->End();

	m_pDev->SetTexture(0, NULL);
	m_pDev->SetVertexDeclaration(NULL);
	m_pDev->SetVertexShader(NULL);
	m_pDev->SetPixelShader(NULL);
	m_pDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	return 0;
}


void CLcSpriteX::AlphaOption(INT opt)
{
	m_Alphblend = opt;
}


INT LcDev_SpriteCreate(char* sCmd
					, ILcSpriteX** pData
					, void* p1
					, void* p2
					, void* p3
					, void* p4
					)
{
	*pData = NULL;

	CLcSpriteX*	pObj = new CLcSpriteX;

	if(FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return -1;
	}

	*pData = pObj;
	return 0;
}

};// namespace LcsLib
////////////////////////////////////////////////////////////////////////////////
