
// link the 2d game library
#if defined(_DEBUG)
  #pragma comment(lib, "../../lib/LcsLib_.lib")
#else
  #pragma comment(lib, "../../lib/LcsLib.lib")
#endif

// include the 2d game header file
#include "../../include/LcsLib.h"


#include <stdio.h>


int FrameMove();
int Render();


// Lena
int		nTx1;
int		iImgW1;
int		iImgH1;


int		nFont1;
int		nFont2;
int		nFont3;


int		mouseX;
int		mouseY;
int		mouseZ;

BYTE*	pKey;


int main()
{
	LcsLib_SetClearColor(0xFF006699);
	LcsLib_SetWindowStyle(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU| WS_VISIBLE);

	LcsLib_CreateWin(100, 100, 800, 600, "���ڿ� ���");
	LcsLib_SetRender(Render);
	LcsLib_SetFrameMove(FrameMove);

	LcsLib_SetStateShow(false);// State �����ִ� ���� �����.


	nTx1	= LcsLib_TextureLoad("Texture/lena.png");
	iImgW1	= LcsLib_TextureWidth(nTx1);
	iImgH1	= LcsLib_TextureHeight(nTx1);


	nFont1 = LcsLib_FontCreate("����", 20, 0);
	nFont2 = LcsLib_FontCreate("Arial", 25, 1);
	nFont3 = LcsLib_FontCreate("�ü�", 20, 1);




	LcsLib_Run();


	LcsLib_DestroyWin();


	return 0;
}


int FrameMove()
{
	mouseX = LcsLib_GetMouseX();
	mouseY = LcsLib_GetMouseY();
	mouseZ = LcsLib_GetMouseZ();

	pKey = (BYTE*)LcsLib_GetKeyboard();


	return 0;
}


int Render()
{
	RECT	rt1 = {0,0,iImgW1, iImgH1};

	LcsLib_Draw2D(nTx1, &rt1);


	LcsLib_FontDrawText(nFont2, 10, 10, 500, 40, 0xffffFF00
		, "���콺�� ������ ��ư�� ��������!!!");


	if( LcsLib_GetMouseEvent(1))		// R button
	{
		int c= LcsLib_FontDrawText(nFont3, mouseX, mouseY, mouseX+500, mouseY+ 40
			, 0xffffaaff
			, "Mouse ��ġ: %d %d %d ", mouseX, mouseY, mouseZ);
	}

	return 0;
}