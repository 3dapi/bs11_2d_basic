
#include <vector>

#include <windows.h>
#include <stdio.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "ILcTexture.h"


#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }



namespace LcsLib
{

class CLcTexture : public ILcTexture
{
protected:
	INT					m_nID;
	char				m_sFile[128];
	LPDIRECT3DTEXTURE9	m_pTex;
	D3DXIMAGE_INFO		m_pImg;

	INT					m_SrfW;
	INT					m_SrfH;

public:
	CLcTexture();
	virtual	~CLcTexture();

	virtual	INT		Create(void* p1=NULL,void* p2=NULL,void* p3=NULL,void* p4=NULL);
	virtual	void	Destroy();
	virtual	INT		GetID();

	virtual	INT		GetImageWidth();
	virtual	INT		GetImageHeight();
	virtual	INT		GetSurfaceWidth();
	virtual	INT		GetSurfaceHeight();

	virtual	void*	GetTexture();
	virtual	void	GetImageRect(void* rc);

	char*	GetName();

	static	INT					m_nIDTex;		// Texture ID
	static	LPDIRECT3DDEVICE9	m_pDevice;		// Direct3DDevice
};




INT					CLcTexture::m_nIDTex	= 0;			// Texture ID
LPDIRECT3DDEVICE9	CLcTexture::m_pDevice	= NULL;			// Direct3DDevice

CLcTexture::CLcTexture()
{
	m_nID	= -1;
	m_pTex	= NULL;

	memset(&m_pImg, 0, sizeof m_pImg);
	memset(m_sFile, 0, sizeof m_sFile);
}

CLcTexture::~CLcTexture()
{
	Destroy();
}

INT CLcTexture::GetID()
{
	return m_nID;
}

INT CLcTexture::Create(void* p1,void* p2,void* p3,void* p4)
{
	char*	sFile	= (char*)p1;
	DWORD	dc		= *((DWORD*)p2);
	if(FAILED(D3DXCreateTextureFromFileEx(
		CLcTexture::m_pDevice
		, sFile
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_FILTER_NONE
		, dc
		, &m_pImg
		, NULL
		, &m_pTex
		)) )
	{
		printf("Create Texture Failed: %s\n", sFile);
		m_pTex = NULL;
		return -1;
	}

	D3DSURFACE_DESC dsc;
	m_pTex->GetLevelDesc(0, &dsc);
	m_SrfW = dsc.Width;
	m_SrfH = dsc.Height;

	// 새로운 아이디 부여

	INT _nID = CLcTexture::m_nIDTex;
	++_nID;

	// overflow....
	if(_nID<0)
	{
		printf("Overflow Texture List\n");
		m_pTex->Release();
		m_pTex = NULL;
		return -1;
	}

	CLcTexture::m_nIDTex = _nID;
	m_nID = _nID;

	return 0;
}

void CLcTexture::Destroy()
{
	SAFE_RELEASE(	m_pTex	);
	memset(&m_pImg, 0, sizeof m_pImg);
	memset(m_sFile, 0, sizeof m_sFile);
}


INT CLcTexture::GetImageWidth()
{
	return m_pImg.Width;
}

INT CLcTexture::GetImageHeight()
{
	return m_pImg.Height;
}


INT CLcTexture::GetSurfaceWidth()
{
	return m_SrfW;
}

INT CLcTexture::GetSurfaceHeight()
{
	return m_SrfH;
}


void* CLcTexture::GetTexture()
{
	return m_pTex;
}

void CLcTexture::GetImageRect(void* v)
{
	RECT	rc={0,0, m_pImg.Width, m_pImg.Height};
	memcpy(v, &rc, sizeof(RECT));
}


char* CLcTexture::GetName()
{
	return m_sFile;
}




typedef std::vector<ILcTexture* >	lsPDTX;
typedef lsPDTX::iterator			itPDTX;

lsPDTX	m_vTex;			// Texture List


INT LcDev_TextureInit(void* pDev)
{
	CLcTexture::m_pDevice = (LPDIRECT3DDEVICE9)pDev;
	return 0;
}

void LcDev_TextureDestroy()
{
	INT iSize = m_vTex.size();

	for(INT i=0; i<iSize; ++i)
	{
		SAFE_DELETE( m_vTex[i]	);
	}

	m_vTex.clear();
}


ILcTexture* LcDev_TextureFind(INT _nID)
{
	INT iSize = m_vTex.size();
	INT	nIdx=-1;

	for(INT i=0; i<iSize; ++i)
	{
		if(m_vTex[i]->GetID() == _nID)
		{
			nIdx = i;
			break;
		}
	}

	if(nIdx<0 || nIdx>=iSize)
	{
		return NULL;
	}

	return m_vTex[nIdx];

}



ILcTexture* LcDev_TextureFind(char* sFile)
{
	INT iSize = m_vTex.size();
	INT	nIdx=-1;

	for(INT i=0; i<iSize; ++i)
	{
		ILcTexture* _pTex = m_vTex[i];
		CLcTexture* pTex = (CLcTexture*)_pTex;

		if(0 == _stricmp(pTex->GetName(), sFile))
		{
			nIdx = i;
			break;
		}
	}

	if(nIdx<0 || nIdx>=iSize)
	{
		return NULL;
	}

	return m_vTex[nIdx];

}




INT LcDev_TextureCreate(char* sCmd
					, ILcTexture** pData
					, void* p1
					, void* p2
					, void* p3
					, void* p4
					)
{
	*pData = NULL;

	// Texture를 파일 이름으로 찾는다.
	CLcTexture*	pObj = (CLcTexture*)LcDev_TextureFind((char*)p1);

	if(pObj)
	{
		*pData = pObj;
		return 0;
	}

	pObj = new CLcTexture;

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









INT	LcsLib_TextureLoad(char* sFileName, DWORD dc)
{
	LcsLib::ILcTexture*	p = NULL;

	if(FAILED(LcsLib::LcDev_TextureCreate( "File", &p, sFileName, &dc)))
		return -1;

	LcsLib::m_vTex.push_back(p);

	// ID를 돌려 준다.
	return p->GetID();
}


INT LcsLib_TextureRelease(INT _nID)
{
	INT iSize = LcsLib::m_vTex.size();
	INT	nIdx=-1;

	for(INT i=0; i<iSize; ++i)
	{
		if(LcsLib::m_vTex[i]->GetID() == _nID)
		{
			nIdx = i;
			break;
		}
	}

	if(nIdx<0 || nIdx>=iSize)
		return -1;


	LcsLib::lsPDTX::iterator	itTx;

	itTx = LcsLib::m_vTex.begin() + nIdx;
	SAFE_DELETE(	LcsLib::m_vTex[nIdx]	);
	LcsLib::m_vTex.erase(itTx);

	iSize = LcsLib::m_vTex.size();

	return iSize;
}

INT LcsLib_TextureWidth(INT _nID)
{
	INT iSize = LcsLib::m_vTex.size();
	INT	nIdx=-1;

	for(INT i=0; i<iSize; ++i)
	{
		if(LcsLib::m_vTex[i]->GetID() == _nID)
		{
			nIdx = i;
			break;
		}
	}

	if(nIdx<0 || nIdx>=iSize)
		return -1;

	return (INT)LcsLib::m_vTex[nIdx]->GetImageWidth();
}


INT LcsLib_TextureHeight(INT _nID)
{
	INT iSize = LcsLib::m_vTex.size();
	INT	nIdx=-1;

	for(INT i=0; i<iSize; ++i)
	{
		if(LcsLib::m_vTex[i]->GetID() == _nID)
		{
			nIdx = i;
			break;
		}
	}

	if(nIdx<0 || nIdx>=iSize)
		return -1;

	return (INT)LcsLib::m_vTex[nIdx]->GetImageHeight();
}




