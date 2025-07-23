

#pragma once


DWORD GameGetScreenWidth();
DWORD GameGetScreenHeight();
int   GameRender();
int   GameFrameMove();
int   GameInit();
int   GameDestroy();

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


#pragma comment(lib, "legacy_stdio_definitions.lib")
// link the 2d game library
#if defined(_DEBUG)
  #pragma comment(lib, "../../lib/LcsLib_.lib")
#else
  #pragma comment(lib, "../../lib/LcsLib.lib")
#endif


enum
{
	GAME_INIT = 0,
	GAME_PLAY = 1,
	//GAME_END  = 2,
};
