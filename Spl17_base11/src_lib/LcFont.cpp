
#pragma warning(disable: 4996)

#include <vector>

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>

#include "ILcFont.h"


#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }



namespace LcsLib
{


class CLcFont : public ILcFont
{
protected:
	INT					m_nID;
	D3DXFONT_DESC		m_Dsc;
	ID3DXFont*			m_pFnt;

public:
	CLcFont();
	virtual	~CLcFont();

	virtual	INT		Create(void* p1=NULL,void* p2=NULL,void* p3=NULL,void* p4=NULL);
	virtual	void	Destroy();
	virtual	INT		GetID();

	virtual	void*	GetFont();

	static INT					m_nIDFnt;		// Font ID
	static LPDIRECT3DDEVICE9	m_pDevice;		// Window Handle
};




INT					CLcFont::m_nIDFnt	= 0;		// Font ID
LPDIRECT3DDEVICE9	CLcFont::m_pDevice	= NULL;		// Direct3D Device


CLcFont::CLcFont()
{
	m_nID	= -1;
	m_pFnt	= NULL;
	memset(&m_Dsc, 0, sizeof m_Dsc);
}

CLcFont::~CLcFont()
{
	Destroy();
}

void CLcFont::Destroy()
{
	SAFE_RELEASE(	m_pFnt	);
	memset(&m_Dsc, 0, sizeof m_Dsc);
}


INT CLcFont::GetID()
{
	return m_nID;
}

void* CLcFont::GetFont()
{
	return m_pFnt;
}


INT CLcFont::Create(void* p1,void* p2,void* p3,void* p4)
{
	ID3DXFont*	pDXFont	= NULL;
	char*		sName	= (char*)p1;
	LONG		iH		= *((LONG*)p2);
	LONG		iItalic	= *((LONG*)p3);

	D3DXFONT_DESC hFont =
	{
		iH, 0
			, FW_BOLD, 1
			, iItalic
			, HANGUL_CHARSET, OUT_DEFAULT_PRECIS
			, ANTIALIASED_QUALITY, FF_DONTCARE, "Arial"
	};

	strcpy(hFont.FaceName, sName);


    if( FAILED(D3DXCreateFontIndirect( CLcFont::m_pDevice, &hFont, &pDXFont ) ) )
        return -1;


	if(NULL ==pDXFont)
		return -1;

	memcpy(&m_Dsc, &hFont, sizeof m_Dsc);
	m_pFnt = pDXFont;

	// 새로운 아이디 부여
	INT _nID = CLcFont::m_nIDFnt;

	++_nID;

	// overflow....
	if(_nID<0)
	{
		printf("Overflow Font List\n");
		SAFE_RELEASE(	m_pFnt	);
		return -1;
	}


	CLcFont::m_nIDFnt = _nID;
	m_nID = _nID;

	return 0;
}


INT LcDev_FontCreate(char* sCmd
					, ILcFont** pData
					, void* p1
					, void* p2
					, void* p3
					, void* p4
					)
{
	*pData = NULL;

	CLcFont* pObj=new CLcFont;

	if(FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return -1;
	}

	*pData = pObj;
	return 0;
}


typedef std::vector<ILcFont* >	lsLcFont;
typedef lsLcFont::iterator		itLcFont;


lsLcFont	m_vFont;			// Font List


INT LcDev_FontInit(void* pDev)
{
	CLcFont::m_pDevice	= (LPDIRECT3DDEVICE9)pDev;

	return 0;
}

void LcDev_FontDestroy()
{
	INT iSize = LcsLib::m_vFont.size();

	for(INT i=0; i<iSize; ++i)
	{
		SAFE_DELETE( m_vFont[i]	);
	}

	m_vFont.clear();
}


ILcFont* LcDev_FontFind(INT _nID)
{
	INT iSize = m_vFont.size();
	INT	nIdx=-1;

	for(INT i=0; i<iSize; ++i)
	{
		if(m_vFont[i]->GetID() == _nID)
		{
			nIdx = i;
			break;
		}
	}

	if(nIdx<0 || nIdx>=iSize)
	{
		return 0;
	}

	return m_vFont[nIdx];

}


};// namespace LcsLib
////////////////////////////////////////////////////////////////////////////////









INT LcsLib_FontCreate(char* sName, LONG iH, LONG iItalic)
{
	LcsLib::ILcFont* pFont=NULL;

	if(FAILED(LcsLib::LcDev_FontCreate(NULL, &pFont, sName, &iH, &iItalic)))
		return -1;

	LcsLib::m_vFont.push_back(pFont);

	return pFont->GetID();
}


INT LcsLib_FontDrawText(INT nIdx
					   , LONG lLeft
					   , LONG lTop
					   , LONG lRight
					   , LONG lBottom
					   , DWORD fontColor
					   , const char *format, ...)
{
	LcsLib::ILcFont* pFont = NULL;
	ID3DXFont*	pDxFnt = NULL;


	pFont = LcsLib::LcDev_FontFind(nIdx);

	if(!pFont)
		return -1;

	pDxFnt = (ID3DXFont*)pFont->GetFont();

	if(!pDxFnt)
		return -1;


	va_list ap;
	char s[1024];

	if (format == NULL)
		return -1;

	va_start(ap, format);
	vsprintf((char *)s, format, ap);
	va_end(ap);

	if (s == NULL)
		return -2;



    RECT rc;
	rc.left		= lLeft;
	rc.top		= lTop;
    rc.right	= lRight+20;
	rc.bottom	= lBottom;

    return pDxFnt->DrawText(NULL, s, -1, &rc, 0, fontColor );
}


INT LcsLib_FontRelease(INT _nID)
{
	INT iSize = LcsLib::m_vFont.size();
	INT	nIdx=-1;

	for(INT i=0; i<iSize; ++i)
	{
		if(LcsLib::m_vFont[i]->GetID() == _nID)
		{
			nIdx = i;
			break;
		}
	}

	if(nIdx<0 || nIdx>=iSize)
		return -1;


	LcsLib::lsLcFont::iterator	itFont;

	itFont = LcsLib::m_vFont.begin() + nIdx;
	SAFE_DELETE( LcsLib::m_vFont[nIdx]		);
	LcsLib::m_vFont.erase(itFont);

	iSize = LcsLib::m_vFont.size();

	return iSize;
}
