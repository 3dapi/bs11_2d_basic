
// link the 2d game library
#if defined(_DEBUG)
  #pragma comment(lib, "../../lib/LcsLib_.lib")
#else
  #pragma comment(lib, "../../lib/LcsLib.lib")
#endif

// include the 2d game header file
#include "../../include/LcsLib.h"


#include <stdio.h>


int		nTx;		// �ؽ�ó �ε���

// ���콺 ��ġ �б�
int mouseX = 0;
int mouseY = 0;
int mouseZ = 0;

int Render()
{
	// �̹��� ��ġ�� ���콺 ��ġ�� �����Ѵ�.
	VEC2	vcPos(mouseX, mouseY);

	LcsLib_Draw2D(nTx, NULL, &vcPos);

	return 0;
}


int FrameMove()
{
	// ���콺 ��ġ �б�
	mouseX = LcsLib_GetMouseX();
	mouseY = LcsLib_GetMouseY();
	mouseZ = LcsLib_GetMouseZ();

	// ������ Ÿ��Ʋ ������ ���콺 ��ġ ���
	LcsLib_SetWindowTitle("%d %d %d", mouseX, mouseY, mouseZ);

	return 0;
}


int main()
{
	// ������ ����
	LcsLib_CreateWin(100, 100, 800, 600, "My First Game Window");


	// �ؽ�ó �ε�
	nTx = LcsLib_TextureLoad("Texture/lena.png");

	// ȭ�鿡 ����ϱ� ���ؼ� ��� �Լ��� �����Ѵ�.
	LcsLib_SetRender(Render);

	// ������ ������ ���� �Լ��� �����Ѵ�.
	LcsLib_SetFrameMove(FrameMove);

	// ����
	LcsLib_Run();

	// ������ ����
	LcsLib_DestroyWin();


	return 0;
}