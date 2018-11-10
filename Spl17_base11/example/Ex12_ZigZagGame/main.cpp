
#include <LcsLib.h>
#include <stdio.h>

#include "GameHeader.h"

int main()
{
	srand( NULL );
	LcsLib_SetClearColor(0xFF000000);
	LcsLib_SetWindowStyle(WS_OVERLAPPED | WS_CAPTION| WS_VISIBLE);

	DWORD scnW = GameGetScreenWidth();
	DWORD scnH = GameGetScreenHeight();
	LcsLib_CreateWin(0, 0, scnW, scnH, "Simple zigzag ∞‘¿”", true);
	LcsLib_SetRender(GameRender);
	LcsLib_SetFrameMove(GameFrameMove);


	LcsLib_SetStateShow(false);

	GameInit();

	LcsLib_Run();

	GameDestroy();

	LcsLib_DestroyWin();

	return 0;
}

