# 샘플 소개
- DirectX 9 를 사용한 간단한 게임 라이브러리 작성
- 문서
    - [bs11_2d_basic.doc](https://github.com/3dapi/bs11_2d_basic/raw/master/bs11_2d_basic.doc)

# DirectX 9 sdk
- 설치 - [DirectX 9 sdk](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
- 설치 확인
  - ※ 프로젝트가 DXSDK_DIR를 사용해서 DirectX9의 헤더 파일와 lib 파일 경로를 설정합니다. DXSDK_DIR는 반드시 필요합니다.
      - 수동으로 DirectX 9 의 헤더와 Lib파일을 복사해서 PC에 복사해 왔다면, 환경변수에서 DXSDK_DIR를 지정하고 경로를 지정하십시오.
      - <img src="https://github.com/user-attachments/assets/9425d1b2-b29d-49fe-9b3c-4f60b63e85bc" width="600">

  - ex)DXSDK_DIR 확인(dos terminal)
    - C:\Users\user>echo %DXSDK_DIR%
    - => C:\dx2010june\


# Simple library 라이브러리 만들기

- windows API
  - Sp01_api
- direct3d9 device
  - Sp02_device
- d3dx9 sprite
  - Sp02_sprite
- texture and matrix
  - Sp03_texture
  - Sp03_texture_ani sprite
  - Sp03_Texture_matrix
  - Sp03_texture_numerous
- 샘플 게임
  - Sp05_puzzle
  - Sp05_puzzle_complete

# Simple library 활용
- 라이브러리 초기화
  - Ex01_start
- 텍스처 띄우기
  - Ex02_Texture
- 마우스 제어
  - Ex03_Mouse
- 키보드 제어
  - Ex04_Keyboard
- 스프라이트 애니메이션
  - Ex05_Animation
  - <img src="https://github.com/user-attachments/assets/12c0a4a2-1f17-4925-8e26-bf17e3792524" width="400">

- 한글 문자열 출력
  - Ex06_StringOut
  - <img src="https://github.com/user-attachments/assets/4bf604e9-94ed-4ee6-94ae-35b0a78defee" width="400">

- 사운드
  - Ex08_Sound
- 라이브러리를 활요한 게임
  - 스네이크 게임
    - Ex11_Snake
    - <img src="https://github.com/user-attachments/assets/f773510c-5cc5-492d-95c2-f7bd5ae77f60" width="400">

  - 그림 맞추기게임
    - Ex12_ZigZagGame
    - <img src="https://github.com/user-attachments/assets/1243d45e-f785-48c3-981e-e63bafbcfbb9" width="400">





# ◈2D Game Programming◈


  
2D 게임프로그램은 RPG 게임과 같은 거대한 기획과 그래픽 자료가 필요한 장르를 제외한다면
  
게임 개발자가 프로그램, 기획, 그래픽의 도움 없이 혼자서 게임을 만들 수 있는 장르입니다.
  
또한 2D 게임을 완성해 보면서 점차 3D 게임 프로그래밍에서 사용할 기법들을 조금씩 터득해
  
나가는 과정이 2D 게임 프로그래밍의 재미 있는 부분이자 목적입니다.
  

  
따라서 대부분 게임 교육기관에서는 2D 게임의 과정이 필수입니다. 특히 프로그래머 에게 2D
  
게임 제작을 많이 할수록 게임 개발의 다양한 기술을 축적할 수 있는 좋은 기회입니다. 화면에
  
연출되는 2D와 3D의 속도를 보면 2D는 보통 반 나절 정도면 원하는 모양을 화면에 표현하지만
  
초보자의 경우 3D는 몇 주가 지나도 해결을 못하는 경우가 많습니다.
  

  
대부분 명령어의 순서가 올바르지 못한 경우와 데이터의 초기화가 대부분인데 3D의 경우 그래픽
  
파이프라인의 이해와 수학적인 알고리듬을 이해하고 프로그램을 작성해야 하는데 이 부분이
  
쉽지가 않습니다. 따라서 초보자의 경우 완성도 높은 2D 게임제작은 경험 축적뿐만 아니라
  
복잡하고 다양한 게임 개발의 기초라 할 수 있습니다.
  

  
Microsoft Windows 운영체제를 배경으로 한 2D 게임을 만드는 방법은 윈도우의
  
GDI(Graphics Device Interface)를 이용하는 방법과 Direct3D, OpenGL, 플래시(Adobe Flash) 등의
  
그래픽 라이브러리를 이용하는 방법 두 가지가 있습니다.
  

  
GDI를 이용하면 별도의 그래픽 라이브러리를 사용하지 않아도 되므로 제작하기가 쉽고,
  
마이크로소프트 윈도우 운영체제가 동작하는 모든 기기에서 작동이 되므로 이식이 높은 편입니다.
  
하지만 GDI 자체 한계로 인해 화면 재생에 대한 한계가 있고 3D의 경우 소프트웨어로 모든 것을
  
연산해야 하는 어려움이 있습니다.
  

  
반대로 그래픽 라이브러리를 이용하는 경우 그래픽 카드에 대한 장치 의존도가 높고,
  
라이브러리의 SDK(Software Development Kit)에 대한 이해를 위해 시간과 노력이 필요하지만
  
고속의 화면 재생 률(Refresh Rate)과 하드웨어 가속의 지원에 힘입어 2D(2 Dimensional: 이차원)
  
뿐만 아니라 3D (Three-Dimensional: 삼차원)에서 탁월한 성능을 보여 현재는 대부분 그래픽
  
라이브러리를 이용해서 게임을 만듭니다.
  

  
그래픽 라이브러리도 많이 있지만 2D 게임에서 가장 많이 사용되는 라이브러리는 DirectX와
  
OpenGL입니다. 특히 DirectX는 우리나라 업계에서 거의 90%이상 사용한다고 볼 수 있습니다.
  
DirectX도 여러 버전이 있는데 과거에는 DirectX 7.0 Draw를 가장 많이 사용했지만 현재에는
  
유지보수 차원에서만 사용하고 있습니다.
  

  
현재 새로운 2D 게임을 만든다면 대부분 DirectX 9.0을 사용하고 있습니다. 버전 8.0부터
  
DirectX는 장면 연출에 대한 렌더링(Rendering) 아키텍처(Architecture)를 3D 기반으로
  
만들었습니다. 따라서 2D 그래픽도 3D 기반으로 동작하도록 되어 있어 있습니다.
  

  
DirectX 7.0 에서 2D를 위한 Draw는 8.0부터 ID3DXSprite(스프라이트) 객체가 이를 대신합니다.
  
DirectX 9.0은 2002년, 2003년, 2004년, 버전마다 스프라이트 객체의 사용법이 조금씩 다르므로
  
사용에 대해서 주의해야 하는데 버전마다 사용방법을 맞추기가 번거로워 대부분 2D 렌더링을 3D를
  
기반으로 만들어서 사용하는 경우가 많습니다.
  

  
이 장에서는 윈도우 API 프로그램을 바탕으로 게임을 만들어 가면서 DirectX의 스프라이트 객체
  
사용 방법을 익히는 과정으로 하겠습니다.
  

  

  

  

  

  

## 1. 윈도우 프로그램


  
2D(2-Demensional)게임 이건 3D 게임이건 윈도우에서는 윈도우 프로그래밍을 기본으로 합니다.
  
왜일까요? 대답은 간단합니다. 프로그램이 윈도우 운영체제 위에서 동작 하기 때문입니다.
  
그런데 일반적인 윈도우 프로그램은 화면 출력을 위해 윈도우 운영체제가 제공하는 GDI를
  
사용하는데 게임에서는 2D나 3D를 표현하기 위해서 윈도우의 GDI를 반드시 이용하지는 않고
  
GDI보다 화면에 보다 많은 그래픽 자료들을 표현할 수 있도록 하드웨어 가속을 받는 그래픽
  
라이브러리를 이용합니다. 대표적인 그래픽 라이브러리가 DirectX와 OpenGL입니다. 이 두
  
라이브러리를 사용하려면, 즉 컴퓨터의 메모리에 적재하기 위해서 꼭 윈도우 핸들이 필요합니다.
  
그래서 윈도우 프로그래밍이 기본이 되는 것입니다.
  
윈도우 프로그램은 기억해야 될 함수와 개념들이 많이 있지만 윈도우 프로그램은 메시지
  
기반이라는 것과 GetMessage()와 PeekMessage() 함수의 차이점 정도만 꼭 기억하라고 이야기
  
하겠습니다.
  

  
마이크로소프트가 만든 윈도우 운영체제는 멀티 프로세싱, 멀티 테스킹의 처리를 메시지를
  
통해서 관리하는지라 윈도우 관련 프로그램 또한 이에 맞추어서 만들어야 합니다. 윈도우
  
운영체제는 해당 윈도우의 이동, 크기 변환, 키보드 누름, 마우스의 클릭 등등 입력과 환경의
  
변화를 메시지라는 것을 통해서 인식을 하고 이를 해당 프로그램에 되돌려 주는데, 해당
  
프로그램은 윈도우가 보낸 메시지를 받아서 이를 처리하는 방식으로 작성이 됩니다.
  

  
이렇게 운영체제가 메시지 기반으로 작동을 하는 이유는 컴퓨터 자원의 효율을 높이기
  
위해서 입니다. 예를 들면 빨래를 하기 위해 세탁기를 돌린다고 할 때 빨래 다 될 때까지
  
세탁기 앞에서 가만히 있는 것이 아니라 세탁기 작동시키고 밥을 한다든가 청소를 한다든가
  
하는 것입니다. 아니면 소파에 앉아서 편안하게 쉬고 있다가 빨래가 다 끝나면 세탁기에서
  
종료 신호가 울리면 그 때 세탁기를 가서 빨래를 거두기만 하면 되는 데 바로 빨래가
  
다 되었다는 신호는 윈도우 운영체제에서는 메시지에 해당이 됩니다. 이러한 것을 컴퓨터에서는
  
작업-스케줄링(Job-Scheduling)이라고 하는데 좀 더 자세한 내용은 운영체제 관련 책들을
  
참고 하기 바랍니다.
  

  
윈도우의 GetMessage() 함수는 해당 프로그램이 운영체제에서 보낸 메시지를 받을 때까지
  
기다립니다. 콘솔 모드의 프로그램에서 scanf() 함수나 fgets(, stdin) 함수와 비슷하다고
  
볼 수 있습니다. 그런데 게임 프로그램에서는 프로그램의 안정성을 위해 윈도우 메시지를
  
즉시 처리하고, 또한 CPU도 독점하는 일거 양득의 전략을 취하는 것이 보통입니다. 이것이
  
가능하게 하려면 GetMessage() 함수를 사용하지 않고, PeekMessage() 함수를 이용합니다.
  

  
PeekMessage() 함수는 운영체제가 보낸 메시지가 있는지 기다리지 않고 바로 확인이 가능한데
  
윈도우 운영체제를 바탕으로 둔 게임프로그램은 대부분 이 함수로 메시지를 확인합니다.
  

  
윈도우 프로그램에 대해서 언급하지 않은 중요한 부분들이 많이 남아 있지만 지금 당장
  
2D 게임을 만드는 과정에서는 필요가 없습니다. 왜냐고요? 나중에 게임을 만들어 보면
  
저절로 알게 된답니다. 이 부분은 독자 여러분이 찾아 공부해 보기 바랍니다.
  

  
윈도우 운영체제하에서 게임프로그램은 MFC를 배경으로 작성되는 경우도 몇몇 있지만
  
거의 API 기반에서 작성이 됩니다. 그리고 윈도우 프로그래밍의 코드 흐름을 살펴본다면
  
윈도우 기반의 프로그램 코드는 다음과 같은 순서로 진행됩니다.
  


```

	main() → 프로그램 핸들 얻기 → 윈도우 클래스 등록 → 윈도우 생성
	 → Run → 윈도우 소멸 → 윈도우 클래스 해제

```

  
프로그램의 구체적인 코드는 다음과 같습니다. 이 코드는 아마도 세상에서 가장 짧은
  
윈도우 생성 코드 중에 하나일 것입니다.
  


```

	#pragma comment(linker, "/subsystem:console")
	//#pragma comment(linker, "/subsystem:windows")

	#include < windows.h>

	LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if( WM\_DESTROY == msg )
		{
			::PostQuitMessage( 0 );
			return 0;
		}

		return ::DefWindowProc( hWnd, msg, wParam, lParam );
	}

	//INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
	int main()
	{
		HINSTANCE hInst = (HINSTANCE)::GetModuleHandle(NULL);

		WNDCLASS wc =					// Register the window class
		{
			CS\_CLASSDC
			, WndProc
			, 0L
			, 0L
			, hInst
			, NULL
			, LoadCursor(NULL,IDC\_ARROW)
			, (HBRUSH)GetStockObject(LTGRAY\_BRUSH)
			, NULL
			, "D3D Tutorial"
		};

		::RegisterClass( &wc );


		HWND	hWnd = CreateWindow( "D3D Tutorial"
			, "D3D Tutorial"
			, WS\_OVERLAPPEDWINDOW| WS\_VISIBLE
			, 20
			, 10
			, 800
			, 600
			, NULL
			, NULL
			, hInst
			, NULL );


		::ShowWindow( hWnd, SW\_SHOW );
		::UpdateWindow( hWnd );
		::ShowCursor(TRUE);

		MSG msg;
		memset( &msg, 0, sizeof(msg) );

		while( msg.message!=WM\_QUIT )
		{
			if( PeekMessage( &msg, NULL, 0U, 0U, PM\_REMOVE ) )
			{
				::TranslateMessage( &msg );
				::DispatchMessage( &msg );
			}
		}

	::UnregisterClass( "D3D Tutorial", hInst);

		return 0;
	}

```

  
중요한 함수들로 다시 쓴다면
  


```

	main() → GetModuleHandle() → RegisterClass() → CreateWindow()
	→ PeekMessage() or GetMessage() → TranslateMessage() → DispatchMessage()
	→ WindowProcedure() → DestroyWindow() → UnRegisterClass()

```

  
으로 이루어 집니다.
  

  
중요한 부분을 설명한다면 다음과 같습니다.
  

  

  
< 1-1 프로그램 핸들 얻기>
  
콘솔(도스 창이라고 생각하면 됩니다.)기반 프로그램이라면 GetModuleHandle()이라는
  
함수가 필요하지만 윈도우 프로그램이라면 WinMain(HINSTANCE hInst)에서
  
GetModuleHandle() 함수를 사용하지 않고, hInst 인수를 이용하면 됩니다.
  
(GetModuleHandle() 함수로 HINSTANCE 값을 구해보면 hInst와 동일합니다.)
  
그리고 WinMain을 사용하면 콘솔 창이 만들어지지 않습니다.
  

  

  
< 1-2 윈도우 클래스 등록>
  
WNDCLASS 구조체의 인스턴스를 생성하고 이 인스턴스에 데이터를 채워서 RegisterClass()
  
함수에 전달을 하면 윈도우 클래스가 등록이 됩니다. WNDCLASS 인스턴스의 내용에서 꼭
  
기억해야 할 것이 있는데 className 과 다음에 윈도우를 생성하는 CreateWindow 함수에서
  
className은 반드시 동일해야 합니다. 그렇지 않으면 윈도우가 제대로 생성이 되지 않습니다.
  
아주 중요한 것이 남아 있는데 운영체제가 호출하는 사용자 정의 메시지 처리함수를 이
  
인스턴스의 lpfnWndProc함수 포인터에 연결해야 하는 것도 잊지 말아야 합니다.
  

  

  
< 1-3 윈도우 생성>
  
윈도우 클래스를 운영체제에 등록을 했다면 이제 윈도우를 만들 차례입니다. 윈도우는
  
CreateWindow() 함수로 만듭니다. 간혹 CreateDialog() 함수나 DialogBox() 함수로 만들 수도
  
있지만 이 함수는 이 장에서는 잊으세요. CreateWindow() 함수는 윈도우 만드는 것이 성공한다면
  
NULL 이외의 값을 돌려 줍니다. 이 값은 HWND형에 꼭 저장하시기 바랍니다.
  

  
CreateWindow() 함수는 윈도우만 만들었지 화면에 즉시 보여주지 않습니다. 윈도우를 화면에 보이게
  
하려면 ShowWindow(hWnd, SW\_SHOW) 함수를 호출해야 합니다. 여기서 hWnd는 CreateWindow()함수가
  
돌려준 값입니다.
  

  

  
< 1-4 함수로 분리>
  
위의 예제처럼 main()함수 안에 코드를 전부 구현해도 전혀 상관 없습니다. 그러나 우리가
  
작성하려고 하는 프로그램의 코드 량은 수만에서 수십만 줄 됩니다. 이런 것은 한 함수 안에
  
만든다는 것은 거의 불가능한 일입니다. 가능하더라도 이것을 시도하는 사람은 없습니다. 그러한
  
이유는 코드를 만드는 것뿐만 아니라 논리적인 버그, 코드의 재사용에서 바람직하지 않기
  
때문입니다.
  

  
프로그램을 만드는 여러 가지 암묵적인 원칙 중에 Divide and Conquer! (분할해서 정복하라!)
  
라는 격언을 적용하는데 이것이 하나의 커다란 프로그램을 적절히 작은 완전한 프로그램
  
(이것을 모듈이라고 합니다.)으로 나누어서 제작을 합니다.
  

  
C언어에서는 이것을 함수 단위로 만들 수 있습니다. 함수로 만들기 위해 어떤 기준을 가지고
  
함수로 나눌 것인지 원칙이 있어야 합니다.
  
지금은 윈도우 생성(Create) → 윈도우 가동(Run) → 윈도우 소멸(Cleanup) 세 부분으로 나누어서
  
함수를 만들어 봅시다.
  
또한 윈도우 생성 Create() 함수의 경우 성공과 실패의 두 가지가 있으므로 정수형(int) 반환을
  
하도록 하고 성공은 0, 실패의 경우 -1를 반환하도록 합니다. Run() 함수도 정수형 반환을 넣어서
  
만들도록 합니다. Cleanup() 함수는 윈도우의 해제 부분임으로 굳이 성공과 실패의 반환이
  
필요가 없어서 void로 합니다.
  

  
다음은 위의 코드를 다듬은 예제 입니다.
  

  
[Sp01\_api.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp01_api.7z)
  

  

  

  

  

  

## 2. 디바이스와 스프라이트


  
윈도의 생성과 해제 그리고 메시지 출력을 알고 있다면 이제 DirectX를 배울 차례입니다.
  
DirectX는 게임에 관련한 과학상자 5호 2개쯤으로 생각하면 됩니다. 크게 디스플레이용
  
그래픽, 키보드, 마우스, 조이스틱 등에 대한 인풋, 사운드에 대한 사운드, 미디, 네트워크용
  
다이렉트 플레이 등으로 구성되어 있습니다.
  
jpg, png, tga등과 같은 그림 파일 등을 화면에 출력하기 위해서 Direct3D를 이용할 수
  
있습니다. 하지만 이것을 하려면 좀더 많은 지식이 필요합니다. 이 것은 3D시간에 보도록
  
하고, 여기서는 2D 출력용 인터페이스인 스프라이트 Sprite(요정)를 알아보도록 합니다.
  
앞서 말했듯이 DirectX의 그래픽 라이브러리를 사용하기 위해서 윈도우 핸들이 필요하다고
  
했습니다. 이 그래픽 라이브러리 이름이 Direct3D(Direct Three D)인데 윈도우 핸들을 만들고
  
나서 Dirct3D를 먼저 만들어야 합니다. 생성된 Direct3D 객체와 윈도우 핸들을 이용해서
  
그래픽 카드의 추상화 객체인 Direct3D Device(이하 디바이스)를 만들어야 합니다.
  

  
이 디바이스는 2D, 3D를 망라한 모든 그래픽의 시작이라 할 수 있는데 디바이스를 통해서
  
그림파일을 메모리에 로딩하고, 나중에 배울 3D에 적용되는 폴리곤 또한 디바이스를 통해
  
만들어 집니다. 디바이스는 일종의 그래픽 코어 엔진 Core Engine이라 할 수 있습니다.
  
하지만 디바이스에 관련된 옵션과 함수들은 3D의 내용을 어느 정도 알아야 컨트롤이 제대로
  
되기 때문에 단순히 2D게임을 만드는 초보자에게는 부담이 될 수가 있습니다.
  

  
다행히도 Microsoft는 2D 그래픽 출력을 위해서 디바이스보다 사용하기 편리한
  
Sprite(스프라이트)라는 것을 만들어 내었습니다. 스프라이트 객체를 사용하지 않으면
  
삼각형의 집합인 폴리곤을 통해서 출력을 하거나 이미지 파일을 디바이스의 후면 버퍼에
  
직접 올리는 방법을 이용해야 합니다. 이 스프라이트는 디바이스 객체를 이용해서 만들어
  
집니다.
  

  
DirectX에 관련된 모든 객체들은 마이크로소프트에서 만든 COM(Common Object Modeling)
  
객체를 상속받기 때문에 해제는 딱! 하나의 함수-Release()를 통해서 합니다.
  
Direct3D객체의 소멸은 Direct3D의 인스턴스 포인터→Release(); 인스턴스포인터 = NULL;
  
하면 됩니다.
  

  
생성과 소멸에 대해서 정리하자면 Window Handle → Create Direct3D → Create Device
  
→ Create Sprite → Release Sprite → Release Device → Release Direct3D 로 할 수
  
있습니다.
  

  
이 순서는 반드시 꼭 지켜야 됩니다.
  

  

  

  

  

  

### 2.1 디바이스(IDirect3DDevice9) 객체 만들기


  
디바이스를 생성하기 위해서 IDirect3D9 객체, IDirect3DDevice9 객체가 필요합니다.
  
또한 DirectX의 그래픽 라이브러리인 Direct3D(D3D)를 사용하기 위해서 라이브러리를
  
다음과 같이 링크를 해야 합니다.
  


```

	#pragma comment(lib, "legacy\_stdio\_definitions.lib")
	#pragma comment(lib, "d3d9.lib")

```

  
그리고 이 라이브러리를 사용하기 위해서 다음과 같은 헤더파일이 필요합니다.
  


```

	#include < d3d9.h>

```

  
또한 Direct3D 객체 IDirect3D9와 그래픽 카드 장치(Device)를 추상화한 디바이스 객체인
  
IDirect3DDevice9 객체를 사용하기 위해 다음과 같이 변수를 선언과 동시에 NULL 값으로
  
정의합니다.
  


```

	LPDIRECT3D9		m\_pD3D		= NULL;		// D3D
	LPDIRECT3DDEVICE9	m\_pd3dDevice	= NULL;		// Device

```

  
보통 프로그래머들이 그래픽 카드나, 디바이스는 같은 개념으로 사용되기 때문에 특별한 언급이
  
없는 한 디바이스는 그래픽 카드로 생각하면 됩니다.
  

  
Direct3D 객체는 SDK 버전에 따른 사용 가능 여부를 확인해주고 사용할 수 있다면 NULL이 아닌
  
값을 반환해 줍니다.
  


```

	// D3D생성
	if( NULL == ( m\_pD3D = Direct3DCreate9( D3D\_SDK\_VERSION ) ) )
		return -1;

```

  
다음으로 그래픽 카드의 추상화인 디바이스(장치) 객체를 생성하는데 이 객체를 만들기 위해서
  
반드시 윈도우 핸들이 필요합니다. 따라서 프로그램의 순서는 CreateWindow() 함수가 사용된
  
후에 이 객체를 만들어야 합니다.
  

  
또한 디바이스를 생성하기 위해서 모니터를 제어와 화면의 픽셀 정보를 가지고 있는 디바이스의
  
프레임 버퍼를 설정과 속도를 위한 더블 버퍼링(Double Buffering) 등의 기능을 설정해야 하는데
  
이를 위해 D3DPRESENT\_PARAMETERS 구조체를 이용합니다.
  
이 구조체와 윈도우 핸들을 가지고 다음과 같이 Direct3D 객체의 CreateDevice() 멤버 함수를
  
통해서 디바이스를 생성합니다.
  


```

	m\_hWnd = CreateWindow(…);
	…
	Direct3DCreate9( D3D\_SDK\_VERSION );
	…
	D3DPRESENT\_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.Windowed			= m\_bWindow;
	d3dpp.SwapEffect		= D3DSWAPEFFECT\_DISCARD;
	d3dpp.EnableAutoDepthStencil	= TRUE;
	d3dpp.AutoDepthStencilFormat	= D3DFMT\_D16;

	if( FAILED( m\_pD3D->CreateDevice( D3DADAPTER\_DEFAULT, D3DDEVTYPE\_HAL
					, m\_hWnd
					, D3DCREATE\_MIXED\_VERTEXPROCESSING
					, &d3dpp
					, &m\_pd3dDevice ) ) )
	{
		if( FAILED( m\_pD3D->CreateDevice( D3DADAPTER\_DEFAULT, D3DDEVTYPE\_HAL
						, m\_hWnd
						, D3DCREATE\_SOFTWARE\_VERTEXPROCESSING
						, &d3dpp
						, &m\_pd3dDevice ) ) )
		{
			m\_pD3D->Release();
			return -1;
		}
	}

```

  
위의 코드 중간에 있는 D3DADAPTER\_DEFAULT 변수는 대상이 듀얼 모니터 중 디폴트 모니터를
  
대상으로 한다는 것이고, D3DCREATE\_MIXED\_VERTEXPROCESSING, 와 D3DCREATE\_SOFTWARE\_VER-
  
TEXPROCESSING 값은 3D에서 필요한 버텍스 Vertex 처리에 대한 것입니다. 지금은 그냥
  
‘약속이다’라고 생각하시고 신경 안 써도 됩니다.
  
(나중에 3D프로그램에서는 이 부분도 최적화를 해야 할 부분입니다.)
  

  
눈 여겨 볼 것은 생성에 실패했을 때 DirectX의 COM객체들은 항상 음수(마이너스)값을 리턴
  
합니다. 그래서 FAILED 이라는 매크로-음수일 때 TRUE를 반환-를 쓸 수 있습니다. 앞으로
  
이 매크로는 자주 사용되므로 꼭 기억해 두기 바라며 여러분들의 코드도 실패할 경우 항상
  
음수 값을 리턴 하도록 하는 것이 좋습니다.
  

  
이렇게 디바이스를 만들었다면 이를 시험해봐야 하는데 2D, 3D 모든 게임의 장면 연출은
  
다음 순서를 통해서 장면을 디바이스에 연출 합니다.
  

* 1. 화면을 Clear() 함수로 초기화 한다.
 * 2. 장면을 후면 버퍼(Back Face Buffer)에 그리기 위해 디바이스의 BeginScene() 함수를 호출한다.
 * 3. 장면을 그린다.
 * 4. 장면을 다 그렸다는 것을 EndScene() 함수로 알린다.
 * 5. Present() 함수로 전면 버퍼(Front Face Buffer)와 후면 버퍼를 교체한다.
 * 6. 1부터 5를 반복한다.







  

  
이를 코드로 구현하면 다음과 같습니다.
  


```

	m\_pd3dDevice->Clear( 0
			, NULL
			, D3DCLEAR\_TARGET|D3DCLEAR\_ZBUFFER
			, D3DCOLOR\_XRGB(0,120,160), 1.0f, 0 );

	if( FAILED( m\_pd3dDevice->BeginScene() ) )
		return -1;

	// 렌더링

	m\_pd3dDevice->EndScene();
	m\_pd3dDevice->Present( 0, 0, 0, 0);

```

  
팁)장치 사이의 속도의 차이나 데이터 형식의 차이가 있을 때 중간에 만들어 놓은 임시
  
기억장치를 버퍼라고 합니다. 모니터는 아무리 빨라도 1초에 1000 번 이상을 넘지 못합니다.
  
반면 CPU의 경우 초당 수백만 이상 연산이 가능합니다. 아무리 연산이 많아도 모니터가
  
화면을 재생하는 것보다 월등히 빠릅니다.
  
또한 모니터에 출력을 하는 동안 이 버퍼는 데이터 갱신해서는 안됩니다. 따라서 출력이
  
다 될 때까지 기다린 후 다시 이 버퍼에 다음에 출력할 장면에 대한 픽셀 데이터를 복사해야
  
하는데 이렇게 하면 복사에 대한 시간 때문에 전체가 느려질 수 있습니다. 이것을 방지하기
  
위해 현재 출력되는 버퍼와 동일한 크기와 형태의 버퍼를 하나 더 두어 하나의 버퍼가
  
모니터에 출력되는 동안 다른 하나의 버퍼에 다음에 출력할 데이터를 복사하는 방법을
  
사용합니다. 이렇게 이중 버퍼를 이용해서 출력 속도를 올리는 방법을 더블 버퍼링
  
(Double Buffering)이라 합니다. 위의 Present() 함수는 현재 후면 버퍼에 기록된 픽셀
  
데이터를 전면 버퍼로 교체 지시를 내리는 함수 입니다.
  

  
위의 내용에 대한 좀 더 자세한 코드는 다음 예제를 살펴 보기 바랍니다.
  

  
[Sp02\_device.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp02_device.7z)
  

  

  

  

  

  

### 2.2 스프라이트(ID3DXSprite) 객체 생성


  
3D 폴리곤(Polygon)을 이용해서 2D를 얼마든지 엄밀히 표현할 수 있어서 엄밀히 말한다면
  
스프라이트(ID3DXSprite) 객체는 필요가 없습니다. 하지만 3D로 2D를 표현할 때 여러 해야
  
할 작업들이 많이 있으므로 2D 전용 객체가 필요하며 이것을 DirectX는 스프라이트(ID3DXSprite)
  
라는 객체로 지원을 합니다. 이 스프라이트 객체는 Direct3D 의 확장으로 간혹 PDA와 같이
  
이 스프라이트를 사용할 수 없는 환경이 있을 수 있습니다.
  
이러한 경우 서피스(Surface)를 이용해야 합니다. 여기서는 서피스 이용은 생략하고 스프라이트를
  
사용하는 방법만 살펴보겠습니다.
  

  
이 스프라이트 객체를 사용하기 위해서 다음과 같이 라이브러리를 링크 해야 합니다.
  


```

	#pragma comment(lib, "d3dx9.lib")

```

  
또한 이 라이브러리에 대한 헤더 파일을 다음과 같이 인클루드 해야 합니다.
  


```

	#include < d3dx9.h>

```

  
참고로 d3d 다음 x 는 Extended의 의미로 Direct3D의 기본에 대한 확장을 의미합니다.
  

  
스프라이트 객체는 다음과 같이 정의 합니다.
  


```

	LPD3DXSPRITE	m\_pd3dSprite= NULL;

```

  
다음으로 스프라이트 객체를 생성해야 하는데 스프라이트는 디바이스를 생성한 다음에 만들어야
  
합니다. 스프라이트를 만드는 함수는 D3DXCreateSprite() 함수를 이용해서 다음과 같이 만듭니다.
  


```

	if(FAILED(D3DXCreateSprite(m\_pd3dDevice, &m\_pd3dSprite)))
	{
		m\_pd3dDevice->Release();
		m\_pd3dDevice = NULL;

		m\_pD3D->Release();
		m\_pD3D = NULL;

		return -1;
	}

```

  
이 객체도 COM을 상속 받으므로 Release() 함수를 통해서 해제 합니다. 해제의 순서가 아주
  
중요한데 D3D, 디바이스, 스프라이트 순으로 생성했으므로 해제는 스프라이트, 디바이스,
  
D3D 순으로 해제를 합니다.
  


```

	if(m\_pd3dSprite)
	{
		m\_pd3dSprite->Release();
		m\_pd3dSprite = NULL;
	}

	if(m\_pd3dDevice)
	{
		m\_pd3dDevice->Release();
		m\_pd3dDevice = NULL;
	}

	if(m\_pD3D)
	{
		m\_pD3D->Release();
		m\_pD3D = NULL;
	}

```

  
앞으로도 꼭 명심해야 할 점은 DirectX에 관련된 모든 객체들의 생성과 해제의 순서는
  
꼭 지켜야 합니다. 그렇지 않으면 어떤 그래픽 카드에서는 그냥 아무런 에러 출력 없이
  
컴퓨터가 갑자기 다시 부팅 되어 작성하고 있던 코드들을 잃어 버리는 수가 발생할
  
수 있습니다.
  

  
다음으로 스프라이트를 이용해서 출력을 해야 하는데 반드시 디바이스의 BeginScene() 함수와
  
EndScene() 사이에서 다음과 같이 스프라이트의 Begin()함수와 End()함수 사이에서
  
Draw() 함수를 호출해야 합니다.
  


```

	if( FAILED( m\_pd3dDevice->BeginScene() ) )
		return -1;

	m\_pd3dSprite->Begin(D3DXSPRITE\_ALPHABLEND);

	// 스프라이트 Draw
	//m\_pd3dSprite->Draw(...);

	m\_pd3dSprite->End();

	m\_pd3dDevice->EndScene();

```

  
스프라이트의 Begin() 함수의 옵션과 Draw() 함수의 인수들은 DirectX SDK 버전마다
  
차이가 있는데 이 강좌에서는 2003 summer 버전을 기준으로 설명 하겠습니다.
  

  
스프라이트의 생성과 해제는 다음 코드를 살펴 보기 바랍니다.
  

  
[Sp02\_sprite.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp02_sprite.7z)
  

  

  

  

  

  

## 3. 텍스처


### 3.1 텍스처 생성/해제


  
DirectX는 2D, 3D의 장면 연출에 대한 모든 이미지를 텍스처(ID3DXTexture9)라는
  
객체를 이용합니다. 스프라이트는 이 텍스처 객체를 Draw() 함수의 인수로 받아서
  
화면에 출력합니다.
  
이 객체는 스프라이트와 마찬가지로 디바이스를 통해서 생성됩니다. 만약 텍스처가
  
파일로 되어 있다면 D3DXCreateTextureFromFileEx() 함수를 사용하고, 메모리에 저장된
  
이미지라면 D3DXCreateTextureFromMemory() 함수를 이용하고, 리소스에 있다면
  
D3DXCreateTextureFromResource() 함수를 사용합니다. 그리고 실시간으로 메모리에
  
생성하려면 D3DXCreateTexture() 함수를 사용합니다.
  

  
간혹 D3DXCreateTextureFromFile() 함수를 이용하는 것도 볼 수 있는데 이 함수는
  
D3DXCreateTextureFromFileEx() 함수의 간소화된 사용이라고 볼 수 있습니다. (도움말 참조).
  
그런데 이 D3DXCreateTextureFromFile() 함수는 2D에서는 사용을 안 하는 것이 좋습니다.
  
왜냐하면 2D인 경우 픽셀을 대부분 도트 작업을 통해서 만들고, 또한 텍스처를 확대하거나
  
축소해도 픽셀 사이를 보간 하는 필터링을 안 거치게 하는 것이 보통인데
  
D3DXCreateTextureFromFile() 함수는 생성할 때 필터링 옵션이 디폴트로 설정이 되어 있어서
  
2D 게임 제작에서는 적합하지 않습니다.
  
D3DXCreateTextureFromFileEx() 함수는 많은 수의 인수(argument)들을 사용하고 있는데
  
2D에서는 이중에 몇 가지만 설정하고 나머지는 디폴트 값으로 설정하는 것이 보통입니다.
  
앞으로 3D 게임 제작에서도 텍스처에 관련해서 이 함수를 계속 사용할 것이니 지금부터 잘
  
알아 두는 것이 좋습니다.
  

  
먼저 텍스처를 만들기 위해서 다음과 같이 인스턴스를 NULL로 초기화합니다.
  


```

	//(LPDIRECT3DTEXTURE9는 IDirect3DTexture9 * (포인터) 의 또 다른 표현입니다.)
	LPDIRECT3DTEXTURE9	m\_pTx1		= NULL;

	D3DXCreateTextureFromFileEx() 함수로 텍스처 인스턴스를 생성합니다.

	D3DXIMAGE\_INFO	pImgInf;

	if( FAILED( D3DXCreateTextureFromFileEx(
		m\_pd3dDevice			// 디바이스 포인터
		, "Texture/earth.bmp"		// 텍스처 파일 이름
		, D3DX\_DEFAULT
		, D3DX\_DEFAULT
		, 1				// 밉 레벨(2D에서는 반드시 1)
		, 0
		, D3DFMT\_UNKNOWN
		, D3DPOOL\_MANAGED
		, 0x0000001			// 필터링
		, 0x0000001			// 밉 필터링
		, 0x00FFFFFF			// 컬러 키
		, &pImgInf			// 텍스처 인포메이션
		, NULL
		, &m\_pTx1			// 텍스처 포인터
	{
		MessageBox(m\_hWnd
			, "dx5\_logo.bmp"
			  "file Could not find"
			, "Err"
			, 0);

		m\_pTx1 = NULL;
		return -1;
	}

```

  
D3DXCreateTextureFromFileEx() 함수에서 프로그래머가 실제로 사용하는 인수 값은 간단하게
  
주석으로 설명을 처리한 부분입니다. 밉(MIP) 레벨의 경우 3D게임에서는 D3DX\_DEFAULT 로
  
둡니다. 필터링(Filtering)과 밉 필터는 3D에서 D3DX\_DEFAULT 로 설정합니다. 텍스처
  
인포메이션의 경우 파일에서의 이미지의 가로, 세로, 깊이의 크기를 가지고 있습니다.
  
나중에 애니메이션을 하려면 이 부분을 텍스처 포인터와 함께 같이 저장해 두는 것이 좋습니다.
  

  
이 함수에서 중요한 부분이 컬러 키입니다. 컬러 키는 일종의 투명 키라고 생각하면 됩니다.
  
투명 키는 실제 화면에서 색상이 탈색 되듯이 아무것도 그리지 않는 부분의 색상을 지정하는
  
것입니다. 만약 여러분이 분홍색(0xFFFF00FF)을 컬러 키로 지정했다면 분홍색은 화면에
  
그리지 않게 됩니다. (이 부분은 정밀하게 작업을 해야 하니까 포토샵과 같은 그래픽 툴을
  
이용해서 작업을 한 다음, 올려 보기 바랍니다.)
  

  
앞서 DirectX는 COM을 상속 받는다고 했습니다. 따라서 텍스처 객체 또한 메모리 해제는
  
Release() 함수를 통해서 합니다. 다음과 같이 텍스처 객체를 해제합니다.
  


```

	if(m\_pTx1)
	{
		m\_pTx1->Release();
		m\_pTx1 = NULL;
	}

```

  
이제 그리기만 남아 있습니다. 스프라이트의 Draw()함수를 통해서 다음과 같이 화면에
  
렌더링 합니다.
  


```

	if( FAILED( m\_pd3dDevice->BeginScene() ) )
		return -1;

	m\_pd3dSprite->Begin(D3DXSPRITE\_ALPHABLEND);

	RECT	rt1 = {0,0,600, 400};
		m\_pd3dSprite->Begin(D3DXSPRITE\_ALPHABLEND);

		D3DXVECTOR3	vcCenter(200, 100, 0);
		D3DXVECTOR3	vcPos(   300, 200, 0);

		m\_pd3dSprite->Draw(m\_pTx1, &rt1, &vcCenter, &vcPos, D3DXCOLOR(1,1,1,1));

	//	m\_pd3dSprite->Draw(…);
	//	m\_pd3dSprite->Draw(…);

	m\_pd3dSprite->End();

	m\_pd3dDevice->EndScene();

```

  
스프라이트의 Draw() 함수를 사용하려면 반드시 디바이스의 BeginScene() 이후 EndScene() 함수
  
사이에 스프라이트 객체의 Begin()함수와 End()함수 사이에 Draw() 함수를 호출해야 합니다.
  
만약 여러 번 Draw()를 호출 한다면 BeginScene()… Begin() … Draw(), …, Draw() … End(),
  
..EndScene() 으로 BeginScene()/EndScene()는 한번만 하고 이 사이에서 여러 번
  
Begin()/Draw()/End() 함수를 호출 하면 됩니다. 또한 스프라이트의 Begin()함수의 옵션이
  
동일하다면 Begin()/End() 함수는 한 번만 호출해도 됩니다.
  

  
Draw() 함수를 살펴보면 처음 인수는 텍스처 포인터 입니다. 그 다음 인수는 그리고 싶은
  
텍스처의 영역입니다. 만약 영역이 텍스처의 크기보다 크다면 텍스처의 각 x, y의 마지막
  
색상으로 채워 집니다.
  
세 번째 인수는 중심 위치 인데 자료구조가 D3DXVECTOR3 구조체인 변수의 주소 값을 주는데
  
D3DXVECTOR3 구조체는 float x, float y, float z가 들어 있는 구조체 입니다.
  

  
Draw에 이 구조체 인스턴스의 주소 값 대신 NULL을 줄 수도 있는데 이렇게 하면 중심 위치가
  
자동으로 (0,0,0)이 설정이 됩니다. 만약 중심 위치가 설정되어 있다면 화면에 그림은 이
  
중심 위치를 상대로 이동을 하게 됩니다.
  
결과적으로 최종 위치 = 입력 값 위치 - 중심 위치가 됩니다.
  

  
네 번째 인수는 위치 입니다. 최종 위치는 이 위치 값과 중심 위치를 가지고 구합니다.
  
만약 NULL을 설정하면 (0,0,0)위치 값으로 결정이 됩니다. 위치, 중심 위치의 z 값은 모두
  
0.0F 값으로 설정합니다.
  
마지막 인수는 칼라 값입니다. 이 값은 텍스처 전체에 어떤 색상을 곱할 것인가 하는 것입니다.
  
이 값은 반투명 처리나 특정 색 만 추출 할 때 사용되니 꼭 기억하기 바랍니다.
  
위의 코드 중에서 D3DXCOLOR 구조체가 보이는데 이 구조체는
  
float r, float g, float b, float a로 구성된 구조체 입니다. 보통 색상 값이 0~255 이지만
  
이 구조체에서는 색상 값을 0~1.F 사이의 값으로 설정해야 합니다. 또한 DWORD 형 캐스팅 연산자가
  
재 정의 되어 있어서 DWORD값으로 자동으로 계산을 통한 형 변환을 해줍니다.
  
앞으로 이 구조체를 사용하는 것이 편리할 때가 많고 3D 게임제작에서 쉐이더를 사용한다면
  
이 구조체가 유리합니다.
  

  
다음 예제는 텍스처 하나를 화면에 출력하는 예제입니다.
  

  
[Sp03\_texture.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp03_texture.7z)
  

  

  
게임에서는 수 많은 텍스처를 이용해서 장면을 구성합니다. 다음 예제는 여러 텍스처를 출력하는
  
예제입니다.
  

  

  
![](https://github.com/3dapi/bs11_2d_basic/raw/master/img_src/image0001.png)
  

  

  
[Sp03\_texture\_numerous.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp03_texture_numerous.7z)
  

  

  

  

  

  

  

### 3.2 텍스처 애니메이션


  
텍스처 애니메이션은 영화 필름처럼 이미지를 프레임마다 하나 그린 것을 시간 간격에 따라
  
연속적으로 출력하는 것입니다. 먼저 다음과 같은 그림을 준비해야 합니다.
  

  

  
![](https://github.com/3dapi/bs11_2d_basic/raw/master/img_src/animate.bmp)
  

  

  
(이 그림은 [Sp03\_texture\_ani.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp03_texture_ani.7z) 파일의 Texture 폴더 안에 있습니다.)
  

  
또 준비해야 할 것이 있는데 시간을 얻어오는 함수가 필요합니다. 시간관련 Win API 함수에는
  
GetTickCount() 함수와 timeGetTime() 함수가 있습니다. 만약 timeGetTime() 함수를 사용하기
  
위해서는 winmm.lib 라이브러리 파일과 mmsystem.h 헤더 파일이 필요합니다. 이 둘을 다음과
  
같이 추가합니다.
  


```

	…
	#pragma comment(lib, "winmm.lib")
	…
	#include < windows.h>
	#include < mmsystem.h>
	…

```

  
INT Init() 함수에서 텍스처 생성에서 컬러 키 설정 부분이 애니메이션 용 그림은 컬러 키를
  
0xFF000000 값으로 설정했는데 이것은 완전 불투명 검정색과 동일합니다. 소스를 실행하면
  
검정색 부분이 투명하게 빠져 있음을 알 수 있습니다. 또한 텍스처를 만들 때 이미지 구조체
  
D3DXIMAGE\_INFO에 정보를 저장하는 것을 볼 수 있는 데 앞으로는 텍스처 포인터와 이 구조체의
  
값을 가지는 변수를 함께 저장해서 사용하는 것이 여러모로 편리합니다.
  

  
다음으로 INT FrameMove() 함수에 내용이 구현되어 있음을 볼 수 있는 데 timeGetTime() 함수는
  
1/1000초 값을 반환해 줍니다. 따라서 if( (m\_dTimeEnd - m\_dTimeBegin)>12) 로 되어 있는
  
부분은 12/1000초 (24frame의 절반) 마다 데이터를 설정하겠다는 의미입니다.
  
이미지의 영역을 D3DXVECTOR3 구조체를 이용하고 있는데 이 구조체는 앞서 잠깐 소개했는데
  
+, -, * 등 필요한 오퍼레이터 연산자들이 잘 재정의 되어 있어서 사용하기가 무척 편리하고,
  
스프라이트의 Draw() 함수에서도 이것을 기본으로 사용하고 있으니 꼭 이 구조체를 이용하기
  
바랍니다.
  

  
또한 애니메이션을 그리는 함수에서 색상 값을 D3DXCOLOR(1,1,1,0.4F)로 바꾸어 보면 반투명
  
효과가 적용되고 있음을 알 수 있습니다.
  

  
전체 코드는 다음 예제를 살펴보기 바랍니다.
  

  
[Sp03\_texture\_ani.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp03_texture_ani.7z)
  

  

  

  

  

  

### 3.3 행렬 사용


  
회전과 크기 변환을 위해서 스프라이트에 행렬을 설정을 해야 합니다. 순서는 4X4 행렬을
  
단위 행렬(항등 행렬)로 만들고 스프라이트의 SetTransform() 함수를 호출한 다음, 마지막으로
  
Draw() 함수를 호출합니다. 이 대 Draw() 함수 인수의 중심 위치와 위치 값은 NULL 값으로
  
설정합니다.
  


```

	D3DXMATRIX	mtW;
	D3DXMatrixIdentity(&mtW);
	mtW.\_11 =  .5f;
	mtW.\_22 =  .5f;
	mtW.\_41	=  (rt1.right - rt1.left) * 1.f;
	mtW.\_42	=  (rt1.bottom - rt1.top) * 1.f;
	m\_pd3dSprite->SetTransform(&mtW);
	m\_pd3dSprite->Draw(m\_pTx1, &rt1, NULL, NULL, D3DXCOLOR(1,1,1,1));

	D3DXMatrixIdentity(&mtW);
	m\_pd3dSprite->SetTransform(&mtW);

```

  
주의 해야 할 점은 Draw()를 끝내고 나서 다음 사용에 영향을 주지 않도록 스프라이트의
  
행렬을 단위행렬로 다시 설정해 합니다.
  
또한 텍스처를 생성할 때 다음과 같이 MIP 맵 체인이 하나만 설정 되도록 해야 합니다.
  


```

	D3DXCreateTextureFromFileEx(
			m\_pd3dDevice
			, "Texture/dx5\_logo.bmp"
			, D3DX\_DEFAULT
			, D3DX\_DEFAULT
			, 1		// 밉 맵 체인은 반드시 하나만 생성
			…

```

  
좀 더 자세한 코드는 다음 예제를 참고하기 바랍니다.
  

  

  
![](https://github.com/3dapi/bs11_2d_basic/raw/master/img_src/image0002.png)
  

  

  
[Sp03\_Texture\_matrix.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp03_Texture_matrix.7z)
  

  

  

  

  

  

## 4. 기타


### 4.1 Off screen Plain Surface


  
Off screen Plain Surface를 사용하면 스프라이트와 텍스처 객체를 사용하지 않고 바로 화면에
  
출력을 할 수 있는데 별로 추천할 방법이 못됩니다. 가장 큰 문제는 유연성이 떨어진다는
  
점입니다. 스프라이트 객체는 3D 장면 자체를 연출하는데도 필요한 객체이지만 Off Screen는
  
단순히 파일의 이미지만 출력을 할 뿐입니다.
  

  
사용 방법은 다음과 같습니다. 먼저 이미지에 대한 Off screen을 생성합니다.
  


```

	char sFile[] = "Texture/earth.bmp";
	D3DXGetImageInfoFromFile(sFile, &m\_ImgSrc);

	m\_pd3dDevice->CreateOffscreenPlainSurface(
			  m\_ImgSrc.Width
			, m\_ImgSrc.Height
			, D3DFMT\_A8R8G8B8
			, D3DPOOL\_DEFAULT		//D3DPOOL\_MANAGED는 안됨.
			, &m\_ImgSurface
			, NULL);

	D3DXLoadSurfaceFromFile(m\_ImgSurface,NULL,NULL, sFile,NULL,D3DX\_DEFAULT,0,NULL);

```

  
여기서 생성한 서피스 객체를 가지고 화면에 출력합니다.
  


```

	m\_pd3dDevice->BeginScene();
	…
	RECT rcSrc={0,0,m\_ImgSrc.Width, m\_ImgSrc.Height};
	RECT rcDst={0,0, rcSrc.right, rcSrc.bottom};

	m\_pd3dDevice->StretchRect(m\_ImgSurface,&rcSrc,m\_pd3dBackBuffer,&rcDst,D3DTEXF\_NONE);
	…
	m\_pd3dDevice->EndScene();

```

  
좀 더 자세한 내용은 다음 코드를 살펴보기 바랍니다.
  

  
[Sp04\_etc1\_offscreen.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp04_etc1_offscreen.7z)
  

  

  

  

  

  

### 4.2 Device Context


  
Direct3D 9.0에서는 서피스의 DC(Device Context)를 사용할 수 있습니다. 따라서 서피스에서
  
얻은 DC에 문자열, 이미지 등을 출력할 수 있습니다. DC를 이용하는 것이 게임에서 그리 좋은
  
모습은 아니지만 연습이나 급하게 에러 등을 출력할 때 편리하게 사용할 수 있습니다.
  
DC는 디바이스 생성에서 D3DPRESENT\_PARAMETERS 구조체의 값을 채울 때 다음과 같이 설정해야
  
합니다. 참고로 DC는 모든 서피스 객체에서 얻을 수 있는데 서피스 객체의 포멧이 알파가
  
없는 경우에만 가능합니다.
  


```

	D3DPRESENT\_PARAMETERS d3dpp;
	…
	d3dpp.Flags	= D3DPRESENTFLAG\_LOCKABLE\_BACKBUFFER;

```

  
이 값을 설정하고 나서 디바이스가 만들어진 후에 디바이스의 후면 버퍼의 색상 버퍼 서피스를
  
얻습니다.
  


```

	if(FAILED(m\_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER\_TYPE\_MONO, &m\_pBackBuffer )))
	{
		…
	}

```

  
렌더링 부분의 EndScene() 함수 호출 이후에 다음과 같이 디바이스의 DC를 얻습니다. DC를
  
사용하고 나서 반드시 DC를 얻은 서피스 버퍼 객체의 ReleaseDC() 함수를 호출해서 DC를
  
해제해야 합니다.
  


```

	if(m\_pBackBuffer)
	{
		m\_pBackBuffer->GetDC(&m\_hDC);

		if(m\_hDC)
		{
			// DC 사용
			m\_pBackBuffer->ReleaseDC(m\_hDC);
		}
	}

```

  
다음 예제는 서피스의 DC를 얻어서 이 DC에 이미지와 문자열을 출력하는 예제입니다.
  

  
[Sp04\_etc2\_device\_context.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp04_etc2_device_context.7z)
  

  

  

  

  

  

###  4.3 후면 버퍼 색상 사용


  
앞서 DC를 얻는 방법을 설명하면서 디바이스의 후면 버퍼의 색상 버퍼를 가져오는 방법을 잠깐
  
설명한 적이 있습니다. 색상 버퍼를 얻었다면 다음과 같이 픽셀(Pixel: 색상 값)을 직접 설정
  
할 수 있습니다.
  
픽셀을 얻기 위해서 서피스의 LockRect() 함수를 호출 합니다. 다음으로 D3DLOCKED\_RECT 구조체
  
안에 void* 형의 pBits 값이 픽셀인데 이 것을 적당한 형태로 캐스팅해서 사용합니다.
  


```

	D3DLOCKED\_RECT	rc;
	DWORD*	pPxl;

	m\_pBackBuffer->LockRect(&rc, 0, 0);

	pPxl = (DWORD*) rc.pBits;
	…
	m\_pBackBuffer->UnlockRect();

```

  
다음은 화면 보호기 예제입니다. 이 예제는 후면 버퍼의 색상 버퍼의 픽셀을 직접 설정해서
  
만들었습니다.
  

  
[Sp04\_etc3\_back\_buffer.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp04_etc3_back_buffer.7z)
  

  

  

  

  

  

## 5. 간단한 게임 제작


  
2D 기초 과정의 마지막 단계로 간단한 퍼즐 게임을 만들어 봅시다. 게임의 응용 이므로 자세한
  
내용은 생략하겠습니다.
  

  

  
![](https://github.com/3dapi/bs11_2d_basic/raw/master/img_src/image0003.png)
  

  

  
[Sp05\_puzzle.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp05_puzzle.7z)
  

  

  
게임으로 대부분의 게임은 시작-->플레이-->끝 3단계로 진행 합니다. 이 단계를 "그림 맞추기 퍼즐"
  
게임에 적용해야 하는데 시작 부분에서는 그림과 난이도를 선택할 수 있게 하고, 종료에서는 점수에
  
대한 순위를 보여주며 다시 게임을 진행할 것인지 선택하게 해야 합니다. 이러한 단계를 완성하면
  
다음과 같습니다.
  

  

  
![](https://github.com/3dapi/bs11_2d_basic/raw/master/img_src/image0004.png)
  

  

  
[Sp05\_puzzle\_complete.7z](https://github.com/3dapi/bs11_2d_basic/raw/master/Sp05_puzzle_complete.7z)
  

