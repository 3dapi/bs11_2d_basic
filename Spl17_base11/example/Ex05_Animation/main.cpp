#pragma comment(lib, "legacy_stdio_definitions.lib")


// link the 2d game library
#if defined(_DEBUG)
  #pragma comment(lib, "LcsLib_.lib")
#else
  #pragma comment(lib, "LcsLib.lib")
#endif

// include the 2d game header file
#include <LcsLib.h>


#include <stdio.h>


#include <stdio.h>


// Lena
int		nTx1;
int		iImgW1;
int		iImgH1;

int		g_mouseX = 0;
int		g_mouseY = 0;
int		g_mouseZ = 0;


// Super Mario Animation
int		g_AniTex;			// Texture index
int		g_AniImgW;			// Image width
int		g_AniImgH;			// Image Height
RECT	g_AniRc;			// Rendering RECT
int		g_AniW=50;			// Animation Width
int		g_AniMaxF=18;		// Animation Max Frame
FLOAT	g_AniSpeed=120;		// Animation Speed



int FrameMove()
{
	// Update the input
	g_mouseX = LcsLib_GetMouseX();
	g_mouseY = LcsLib_GetMouseY();
	g_mouseZ = LcsLib_GetMouseZ();
	BYTE* pKey = (BYTE*)LcsLib_GetKeyboard();


	// Get the current time
	DWORD currentTime = LcsLib_TimeGetTime();

	// Update the frame index
	int frameIndex = int(currentTime / g_AniSpeed);
	frameIndex %= g_AniMaxF;

	// setupt the Image RECT
	g_AniRc.left  = (frameIndex +0) * g_AniW;
	g_AniRc.right = (frameIndex +1) * g_AniW;
	g_AniRc.top   = 0;
	g_AniRc.bottom= g_AniImgH;

	return 0;
}



int Render()
{
	RECT	rt1 = {0,0,iImgW1, iImgH1};

	LcsLib_Draw2D(nTx1, &rt1);
	//LcsLib_Draw2D(g_AniTex, &g_AniRc, &VEC2(300, 300), &VEC2(2, 2));
	VEC2	vcMouse = VEC2(g_mouseX, g_mouseY);
	LcsLib_Draw2D(g_AniTex, &g_AniRc, &vcMouse, &VEC2(2, 2));

	return 0;
}

int main()
{
	LcsLib_SetClearColor(0xFF006699);
	LcsLib_SetWindowStyle(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU| WS_VISIBLE);

	LcsLib_CreateWin(100, 100, 800, 600, "McUtil Animation Test", false);
	LcsLib_SetRender(Render);
	LcsLib_SetFrameMove(FrameMove);

	nTx1	= LcsLib_TextureLoad("Texture/lena.png");
	iImgW1	= LcsLib_TextureWidth(nTx1);
	iImgH1	= LcsLib_TextureHeight(nTx1);

	g_AniTex = LcsLib_TextureLoad("Texture/mario.png");
	g_AniImgW= LcsLib_TextureWidth(g_AniTex);
	g_AniImgH= LcsLib_TextureHeight(g_AniTex);



	LcsLib_Run();

	LcsLib_DestroyWin();


	return 0;
}


