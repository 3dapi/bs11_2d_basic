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

	// 扩档快 积己
	LcsLib_CreateWin(100, 100, 800, 600, "My First Game Window");

	// 角青
	LcsLib_Run();

	// 扩档快 秦力
	LcsLib_DestroyWin();

	return 0;
}