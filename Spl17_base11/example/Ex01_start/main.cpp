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

int main()
{
	printf("Starting ...\n\n");

	// ������ ����
	LcsLib_CreateWin(100, 100, 800, 600, "My First Game Window");

	// ����
	LcsLib_Run();

	// ������ ����
	LcsLib_DestroyWin();

	return 0;
}