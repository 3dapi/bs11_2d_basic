
#include <LcsLib.h>
#include <stdio.h>

#include "GameHeader.h"


int		ImgArrayInit();					// Image Array Init
void	ImgArrayDestroy();				// Image Array Delete
void	ImgArrayShuffle();				// Image Array Shuffle

// Lena
int		nTx1;
int		iImgW1;
int		iImgH1;

int		nFont1;

int		mouseX;
int		mouseY;
int		mouseZ;

BYTE	m_pKeyOld[256];		// Old Key
BYTE	m_pKeyCur[256];		// Current Key

int		nSound[2];


#define TX_NUM			1

int		m_pTx[TX_NUM];		// 배경 텍스춰

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



DWORD	m_dScreenW		= 640;				// Screen Width
DWORD	m_dScreenH		= 480;				// Screen Height

int					m_nCntRow=3;		// Number of Row
int					m_nCntCol=4;		// Number of column
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
bool				m_bSuccess=false;


DWORD GameGetScreenWidth()
{
	return m_dScreenW;
}

DWORD GameGetScreenHeight()
{
	return m_dScreenH;
}

int GameInit()
{
	m_pTx[0]	= LcsLib_TextureLoad("Texture/img1.bmp", 0xFF000000);
	iImgW1	= LcsLib_TextureWidth(nTx1);
	iImgH1	= LcsLib_TextureHeight(nTx1);

	memset(m_pKeyOld, 0, sizeof(m_pKeyOld));
	memset(m_pKeyCur, 0, sizeof(m_pKeyCur));


	ImgArrayInit();


	nFont1 = LcsLib_FontCreate("Arial", 50, 0);

	//배경 음악
	nSound[0] = LcsLib_SoundLoad("sound/trample.wav");

	//Key board Event
	nSound[1] = LcsLib_SoundLoad("sound/move3.wav");

//	LcsLib_SoundPlay(nSound[0]);
	return 0;
}


int GameDestroy()
{
	ImgArrayDestroy();
	return 0;
}


int	GamePlay()
{
//	if(false== m_bSuccess && !LcsLib_SoundIsPlaying(nSound[0]))
//	{
//		LcsLib_SoundReset(nSound[0]);
//		LcsLib_SoundPlay(nSound[0]);
//	}

	mouseX = LcsLib_GetMouseX();
	mouseY = LcsLib_GetMouseY();
	mouseZ = LcsLib_GetMouseZ();

	memcpy(m_pKeyOld, m_pKeyCur, sizeof(m_pKeyCur));
	memcpy(m_pKeyCur, LcsLib_GetKeyboard(), sizeof(m_pKeyCur));


	int	i,j;
	int	nCntSuccess=0;

	if(0 == m_pKeyOld[VK_HOME] && m_pKeyCur[VK_HOME] )
	{
		ImgArrayDestroy();
		return 0;
	}


	// 우측 이동...
	if(0 == m_pKeyOld[VK_RIGHT] && m_pKeyCur[VK_RIGHT] )
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

		LcsLib_SoundStop(nSound[1]);
		LcsLib_SoundReset(nSound[1]);
		LcsLib_SoundPlay(nSound[1]);
	}

	// 좌측 이동...
	if(0 == m_pKeyOld[VK_LEFT] && m_pKeyCur[VK_LEFT] )
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

		LcsLib_SoundStop(nSound[1]);
		LcsLib_SoundReset(nSound[1]);
		LcsLib_SoundPlay(nSound[1]);
	}

	// 하측 이동...
	if(0 == m_pKeyOld[VK_DOWN] && m_pKeyCur[VK_DOWN] )
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

		LcsLib_SoundStop(nSound[1]);
		LcsLib_SoundReset(nSound[1]);
		LcsLib_SoundPlay(nSound[1]);
	}

	// 상측 이동...
	if(0 == m_pKeyOld[VK_UP] && m_pKeyCur[VK_UP] )
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

		LcsLib_SoundStop(nSound[1]);
		LcsLib_SoundReset(nSound[1]);
		LcsLib_SoundPlay(nSound[1]);
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
		m_bSuccess	= true;


		LcsLib_SoundStop(nSound[0]);
	}

	return 0;
}

int GameRender()
{
	int i;
	int j;

	if(false == m_bSuccess)
	{
		for(i=0; i< m_nCntRow; ++i)
		{
			for(j=0; j< m_nCntCol; ++j)
			{
				if( m_pMapImg[i][j].nIdx != m_iNumMap )
				{
					RECT	rt1 = {0,0,iImgW1, iImgH1};

					LcsLib_Draw2D(m_pTx[m_nImg]
								, &m_pMapBit[ m_pMapImg[i][j].nIdx ].rc
								, &D3DXVECTOR2(m_pMapImg[i][j].x, m_pMapImg[i][j].y)
						) ;
				}
			}
		}
	}

	else
	{
		RECT rc={0,0, m_dScreenW, m_dScreenH};
		LcsLib_Draw2D(m_pTx[m_nImg], &rc);

		int c= LcsLib_FontDrawText(nFont1, 200, 300, 500, 340, 0xffFFBB77, "추카추가 !!!");
	}



	return 0;
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

	m_bSuccess	= false;
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





int g_GamePhase = GAME_INIT;



int GameFrameMove()
{
	switch(g_GamePhase)
	{
		case GAME_INIT:
			GameInit();
			break;

		case GAME_PLAY:
			GamePlay();
			break;

		case GAME_END:
			GameEnd();
			break;
	}
}

