#pragma comment(lib, "legacy_stdio_definitions.lib")

//
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.H"


extern int g_nFont1;
extern int g_Level;
extern int g_ToTal_Grade;
extern int g_GameState;
extern int g_KeyInput;
extern int g_nCount;
extern int g_Stage;
extern int g_Next_Stage;
extern tgFOOD FOOD[MAX_Tail];
extern int g_ItemCount;
extern tgScreen ScreenSrc[Screen_MAX];
extern tgLINE LINE[MAX_Tail];
extern UserInput g_Input;
extern int g_Speed;
extern DWORD g_EndTime;
extern DWORD g_BigenTime;

int IntroFrameMove()
{
	if(g_Input.pKeyNew[VK_ADD] && !g_Input.pKeyOld[VK_ADD])
	{
		++g_Level;

		if(g_Level>4)
			g_Level = 1;
	}

	if(g_Input.pKeyNew[VK_SUBTRACT] && !g_Input.pKeyOld[VK_SUBTRACT])
	{
		--g_Level;

		if(g_Level<1)
			g_Level = 4;
	}

	switch( g_Level )
	{
	case 0:
		g_Speed = 200;
		break;
	case 1:
		g_Speed = 200;
		break;
	case 2:
		g_Speed = 100;
		break;
	case 3:
		g_Speed = 50;
		break;
	case 4:
		g_Speed = 0;
		break;
	}


	if(g_Input.pKeyNew[VK_RETURN] && !g_Input.pKeyOld[VK_RETURN])
	{
		g_GameState=GM_PLAY;
		ReSet();
	}

	return 0;
}

int IntroRender()
{
	RECT	rt3 = {0,0,ScreenSrc[3].iImgW, ScreenSrc[3].iImgH};

	//배경 출력
	LcsLib_Draw2D(ScreenSrc[3].nTx, &rt3);

	LcsLib_FontDrawText(g_nFont1, 230, 50, 500, 70, 0xffFFFF44,  "=======================");
	LcsLib_FontDrawText(g_nFont1, 230, 70, 500, 90, 0xffFFFF44,  "====  지 렁 이 게 임  ====");
	LcsLib_FontDrawText(g_nFont1, 230, 90, 500, 110, 0xffFFFF44, "=======================");

	LcsLib_FontDrawText(g_nFont1, 280, 130, 500, 150, 0xffFFFF44, "청강문화산업대학교");
	LcsLib_FontDrawText(g_nFont1, 290, 150, 500, 170, 0xffFFFF44, "게임과 200614013");
	LcsLib_FontDrawText(g_nFont1, 370, 170, 500, 190, 0xffFFFF44, "박세연");

	LcsLib_FontDrawText(g_nFont1, 230, 230, 500, 250, 0xffFFFF44, " *  게  임  설  명  *");
	LcsLib_FontDrawText(g_nFont1, 180, 270, 500, 290, 0xffFFFF44, " 상 하 좌 우 방향키로 움직일수있다");
	LcsLib_FontDrawText(g_nFont1, 180, 290, 500, 310, 0xffFFFF44, " 벽에 부딪히거나 꼬리에 부딪히면 Game Over!");
	LcsLib_FontDrawText(g_nFont1, 180, 310, 600, 330, 0xffFFFF44, " 난이도 선택 : ( + / - )");

	switch(g_Level)
	{
	case 0:
		LcsLib_FontDrawText(g_nFont1, 200, 350, 600, 370, 0xffFFFF44, "  +나 -를 눌러서 선택해봐");
		break;
	case 1:
		LcsLib_FontDrawText(g_nFont1, 180, 370, 600, 390, 0xffFFFF44, "쉬운거 할려고? 세상 너무 쉽게 사는군!!");
		break;
	case 2:
		LcsLib_FontDrawText(g_nFont1, 180, 390, 600, 410, 0xffFFFF44, "너무 무난한거 아니야? 좀더 올려보시지!");
		break;
	case 3:
		LcsLib_FontDrawText(g_nFont1, 180, 410, 600, 430, 0xffFFFF44, "오~! 좀 하겠는데~? 도전 정신 기억하지!");
		break;
	case 4:
		LcsLib_FontDrawText(g_nFont1, 180, 430, 600, 450, 0xffFFFF44, "하드코어인데 이거 1Stage 깨면 내가 밥사주마!");
		break;
	}

	return 0;
}

int PlayFrameMove()
{
	g_BigenTime = timeGetTime();

	if(g_Input.pKeyOld[VK_UP]) // 위로
		g_KeyInput = UP;
	else if(g_Input.pKeyOld[VK_DOWN]) // 아래로
		g_KeyInput = DOWN;
	else if(g_Input.pKeyOld[VK_LEFT]) // 왼쪽으로
		g_KeyInput = LEFT;
	else if(g_Input.pKeyOld[VK_RIGHT]) // 오른쪽으로
		g_KeyInput = RIGHT;

	if( g_EndTime + g_Speed <= g_BigenTime )
	{
		MoveSnake();
		g_EndTime = g_BigenTime;
	}

	if( g_Stage > 4)
	{
		g_Stage = 0;
		Item();
	}
	return 0;
}

int PlayRender()
{
	RECT	rt0 = {0,0,ScreenSrc[0].iImgW, ScreenSrc[0].iImgH};
	RECT	rt1 = {0,0,ScreenSrc[1].iImgW, ScreenSrc[1].iImgH};
	RECT	rt2 = {0,0,ScreenSrc[2].iImgW, ScreenSrc[2].iImgH};
	RECT	rt4 = {0,0,ScreenSrc[4].iImgW, ScreenSrc[4].iImgH};
	RECT	rt5 = {0,0,ScreenSrc[5].iImgW, ScreenSrc[5].iImgH};
	RECT	rt6 = {0,0,ScreenSrc[6].iImgW, ScreenSrc[6].iImgH};
	RECT	rt7 = {0,0,ScreenSrc[7].iImgW, ScreenSrc[7].iImgH};
	RECT	rt9 = {0,0,ScreenSrc[9].iImgW, ScreenSrc[9].iImgH};
	RECT	rt10 = {0,0,ScreenSrc[10].iImgW, ScreenSrc[10].iImgH};

	//배경 출력
	if ( g_Next_Stage > 5 )
	{
		LcsLib_Draw2D(ScreenSrc[9].nTx, &rt9);
	}
	else
		LcsLib_Draw2D(ScreenSrc[2].nTx, &rt2);

	// 옆면 출력
	VEC2	vcPos10(480, 0);
	LcsLib_Draw2D(ScreenSrc[10].nTx, &rt10,&vcPos10);
	LcsLib_FontDrawText(g_nFont1, 530, 170, 600, 190, 0xffFFFFFF, "점수 : %d", g_Next_Stage*100);


	// 벽
	float i=0.f;
	for(i=0.f; i<SCX+20.f; i+=20.f)
	{
		VEC2	vcPos4(i, 0);
		LcsLib_Draw2D(ScreenSrc[4].nTx, &rt4, &vcPos4);
	}

	for(i=0.f; i<SCX+20.f; i+=20.f)
	{
		VEC2	vcPos4(i,SCY-20);
		LcsLib_Draw2D(ScreenSrc[4].nTx, &rt4, &vcPos4);
	}
	for(i=0.f; i<SCY+20.f; i+=20.f)
	{
		VEC2	vcPos4(0, i);
		LcsLib_Draw2D(ScreenSrc[4].nTx, &rt4, &vcPos4);
	}

	for(i=0.f; i<SCY+20.f; i+=20.f)
	{
		VEC2	vcPos4(SCX,i);
		LcsLib_Draw2D(ScreenSrc[4].nTx, &rt4, &vcPos4);
	}

	// 꼬리 그리기
	for(int Tail = 1; Tail <= g_nCount; ++Tail)
	{
		if(LINE[Tail].X == 0, LINE[Tail].Y == 0)
			break;
		VEC2	vcPos1(LINE[Tail].X, LINE[Tail].Y);
		LcsLib_Draw2D(ScreenSrc[1].nTx, &rt1, &vcPos1);
	}

	// 머리 그리기
	VEC2	vcPos0(LINE[0].X, LINE[0].Y);
	LcsLib_Draw2D(ScreenSrc[0].nTx, &rt0, &vcPos0);

	// 먹이 출력
	VEC2	vcPos5((float)FOOD[0].X, (float)FOOD[0].Y);
	LcsLib_Draw2D(ScreenSrc[5].nTx, &rt0, &vcPos5);

	// 아이템 출력
	if( g_ItemCount != 0)
	{
		if(g_ItemCount == 1)
		{
			VEC2	vcPos6((float)FOOD[1].X, (float)FOOD[1].Y);
			LcsLib_Draw2D(ScreenSrc[6].nTx, &rt0, &vcPos6);
		}
		else if (g_ItemCount == 2)
		{
			VEC2	vcPos7((float)FOOD[2].X, (float)FOOD[2].Y);
			LcsLib_Draw2D(ScreenSrc[7].nTx, &rt0, &vcPos7);
		}
	}

	return 0;

}

int MakeTail()
{
	if ( g_nCount == 0 )
		return 0;

	for(int i=g_nCount; i>0; i--)
	{
		LINE[i] = LINE[i-1];
	}
	return 0;
}

void ReSet()
{
	memset(LINE, 0, sizeof LINE);
	memset(FOOD, 0, sizeof FOOD);

	MakeFood();
	g_Stage = 0;
	g_nCount = 0;

	LINE[0].X = 200.f;
	LINE[0].Y = 200.f;
}

int MoveSnake()
{
	MakeTail();

	if( g_KeyInput == DOWN )
		LINE[0].Y += 20;

	else if( g_KeyInput == UP )
		LINE[0].Y -= 20;

	else if( g_KeyInput == LEFT )
		LINE[0].X -= 20;

	else if( g_KeyInput == RIGHT )
		LINE[0].X += 20;


	if( LINE[0].X  >= SCX || LINE[0].Y + 20 >= SCY || LINE[0].X <= 0 || LINE[0].Y <= 0 )
		g_GameState = GM_END;

	if( LINE[0].X == FOOD[0].X && LINE[0].Y == FOOD[0].Y )
	{
		++g_nCount;
		++g_Stage;
		++g_Next_Stage;
		MakeFood();
	}
	if( LINE[0].X == FOOD[1].X && LINE[0].Y == FOOD[1].Y )
	{
		g_ItemCount= 0;
		srand( GetTickCount() );
		g_nCount += rand()%20;
	}
	if( LINE[0].X == FOOD[2].X && LINE[0].Y == FOOD[2].Y )
	{
		g_ItemCount= 0;
		g_nCount = 0;
	}

	for(int i=1; i<g_nCount; i++)
	{
		if( LINE[0].X == LINE[i].X && LINE[0].Y == LINE[i].Y )
			g_GameState = GM_END;
	}

	return 0;
}

int Item()
{
	srand( GetTickCount() );
	int ntem = rand()%1;
	int X = (rand()%22+1)*20;
	int Y = rand()%22+1*20;

	switch(ntem)
	{
	case 0:
		g_ItemCount = 1;
		break;
	default:
		g_ItemCount = 2;
		break;
	}

	MakeItem(g_ItemCount);

	return 0;
}

int MakeFood()
{
	srand( GetTickCount() );

	MakeItem(0);
	return 0;

}

void MakeItem(int Count)
{
	for(int i=0; i<=g_nCount; i++)
	{
		int X = (rand()%22+1)*20;
		int Y = (rand()%22+1)*20;

		if(	LINE[i].X != X && LINE[i].Y != Y )
		{
			FOOD[Count].X = X;
			FOOD[Count].Y = Y;
		}
	}
}

int EndFrameMove()
{
	if(g_Input.pKeyNew[VK_RETURN] && !g_Input.pKeyOld[VK_RETURN])
		g_GameState=GM_START;

	return 0;
}

int EndRender()
{
	RECT	rt8 = {0,0,ScreenSrc[8].iImgW, ScreenSrc[8].iImgH};

	//배경 출력
	LcsLib_Draw2D(ScreenSrc[8].nTx, &rt8);


	LcsLib_FontDrawText(g_nFont1, 230, 50, 500, 70, 0xffFFFF44,  "=======================");
	LcsLib_FontDrawText(g_nFont1, 230, 70, 500, 90, 0xffFFFF44,  "====  지 렁 이 게 임  ====");
	LcsLib_FontDrawText(g_nFont1, 230, 90, 500, 110, 0xffFFFF44, "=======================");

	LcsLib_FontDrawText(g_nFont1, 280, 130, 500, 150, 0xffFFFF44, "청강문화산업대학교");
	LcsLib_FontDrawText(g_nFont1, 290, 150, 500, 170, 0xffFFFF44, "게임과 200614013");
	LcsLib_FontDrawText(g_nFont1, 370, 170, 500, 190, 0xffFFFF44, "박세연");

	LcsLib_FontDrawText(g_nFont1, 200, 230, 500, 250, 0xffFFFF44, " 다음번에는 슈팅 게임을 제작해보자");
	LcsLib_FontDrawText(g_nFont1, 200, 270, 500, 290, 0xffFFFF44, " 재 시작은 Enter 키를 입력");
	LcsLib_FontDrawText(g_nFont1, 200, 290, 500, 310, 0xffFFFF44, " 수고 많으셨삼");

	return 0;
}