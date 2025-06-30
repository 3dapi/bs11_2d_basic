#pragma comment(lib, "legacy_stdio_definitions.lib")


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

int		mouseX;
int		mouseY;
int		mouseZ;

BYTE*	pKey;


int		nSound1;
int		nSound2;


int main()
{
	LcsLib_SetClearColor(0xFF006699);
	LcsLib_SetWindowStyle(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU| WS_VISIBLE);

	LcsLib_CreateWin(100, 100, 800, 600, "Sound");
	LcsLib_SetRender(Render);
	LcsLib_SetFrameMove(FrameMove);

	LcsLib_SetStateShow(false);// State 보여주는 것을 감춘다.

	nTx1	= LcsLib_TextureLoad("Texture/lena.png");
	iImgW1	= LcsLib_TextureWidth(nTx1);
	iImgH1	= LcsLib_TextureHeight(nTx1);

	nFont1 = LcsLib_FontCreate("Arial", 30, 0);

	nSound1 = LcsLib_SoundLoad("sound/bounce.wav");
	nSound2 = LcsLib_SoundLoad("sound/move3.wav");




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


	if(pKey[VK_LEFT] && !LcsLib_SoundIsPlaying(nSound1))
	{
		LcsLib_SoundReset(nSound1);
		LcsLib_SoundPlay(nSound1);
	}

	if(pKey[VK_RIGHT] && !LcsLib_SoundIsPlaying(nSound2))
	{
		LcsLib_SoundReset(nSound2);
		LcsLib_SoundPlay(nSound2);
	}


	return 0;
}

int Render()
{
	RECT	rt1 = {0,0,iImgW1, iImgH1};

	LcsLib_Draw2D(nTx1, &rt1);


	int c= LcsLib_FontDrawText(nFont1, 20, 300, 500, 340
			, 0xffFFAA44, "Tri to Press Left or Right Key");



	return 0;
}