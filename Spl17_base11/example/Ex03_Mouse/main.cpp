
// link the 2d game library
#if defined(_DEBUG)
  #pragma comment(lib, "../../lib/LcsLib_.lib")
#else
  #pragma comment(lib, "../../lib/LcsLib.lib")
#endif

// include the 2d game header file
#include "../../include/LcsLib.h"


#include <stdio.h>


int		nTx;		// 텍스처 인덱스

// 마우스 위치 읽기
int mouseX = 0;
int mouseY = 0;
int mouseZ = 0;

int Render()
{
	// 이미지 위치를 마우스 위치로 설정한다.
	VEC2	vcPos(mouseX, mouseY);

	LcsLib_Draw2D(nTx, NULL, &vcPos);

	return 0;
}


int FrameMove()
{
	// 마우스 위치 읽기
	mouseX = LcsLib_GetMouseX();
	mouseY = LcsLib_GetMouseY();
	mouseZ = LcsLib_GetMouseZ();

	// 윈도우 타이틀 영역에 마우스 위치 출력
	LcsLib_SetWindowTitle("%d %d %d", mouseX, mouseY, mouseZ);

	return 0;
}


int main()
{
	// 윈도우 생성
	LcsLib_CreateWin(100, 100, 800, 600, "My First Game Window");


	// 텍스처 로드
	nTx = LcsLib_TextureLoad("Texture/lena.png");

	// 화면에 출력하기 위해서 출력 함수를 연결한다.
	LcsLib_SetRender(Render);

	// 데이터 갱신을 위한 함수를 연결한다.
	LcsLib_SetFrameMove(FrameMove);

	// 실행
	LcsLib_Run();

	// 윈도우 해제
	LcsLib_DestroyWin();


	return 0;
}