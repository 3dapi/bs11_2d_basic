#pragma comment(lib, "legacy_stdio_definitions.lib")


// link the 2d game library
#if defined(_DEBUG)
  #pragma comment(lib, "../../lib/LcsLib_.lib")
#else
  #pragma comment(lib, "../../lib/LcsLib.lib")
#endif

// include the 2d game header file
#include <LcsLib.h>

#include <stdio.h>


int		nTx;					// �̹��� �ε���

VEC2	g_vcVcl(1, 0);			// Object Velocity
VEC2	g_vcPos(400, 200);		// Object Position

FLOAT	g_fSpeed  = 4;			// Object Speed
FLOAT	g_fRadius = 0;			// Radius
FLOAT	g_dRadius = 0.1F;		// Delta Radius
FLOAT	g_dDir    = 1.0F;		// Right or left rotation direction


int Render()
{
	FLOAT fAngle = acosf(g_vcVcl.x);
	if(0 > g_vcVcl.y)
		fAngle *= -1.F;

	FLOAT fCos = cosf(fAngle);
	FLOAT fSin = sinf(fAngle);
	VEC2  vDir = VEC2(-fSin, fCos)  * g_dDir;

	g_vcVcl = g_fRadius * g_vcVcl + vDir;		// setup the the velocity
	D3DXVec2Normalize(&g_vcVcl, &g_vcVcl);		// Normalize the velocity

	g_vcPos += g_vcVcl * g_fSpeed;				// accumulate the position

	g_fRadius += g_dRadius;

	// Draw Object
	LcsLib_DrawAlphaOption(1);
	LcsLib_Draw2D(nTx, NULL, &g_vcPos);
	LcsLib_DrawAlphaOption(0);

	return 0;
}





int main()
{
	printf("�׸� �ø���.......................\n\n");

	//������ �ٲ۴�.
	LcsLib_SetClearColor(0xFF336699);
	LcsLib_CreateWin(100, 100, 800, 600, "My First Game Window");


	// �׸��� ���α׷��� �ε�
	nTx = LcsLib_TextureLoad("Texture/tst.png");


	// ȭ�鿡 ����ϱ� ���ؼ� �Լ��� �����Ѵ�.
	LcsLib_SetRender(Render);


	// ����
	LcsLib_Run();


	// �ؽ�ó ����
	LcsLib_TextureRelease(nTx);

	// ������ ����
	LcsLib_DestroyWin();


	return 0;
}