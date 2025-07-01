# 샘플 소개
- DirectX 9 를 사용한 간단한 게임 라이브러리 작성
- 문서
    - [bs11_2d_basic.doc](https://github.com/3dapi/bs11_2d_basic/raw/master/bs11_2d_basic.doc)

# DirectX 9 sdk
- 설치 - [DirectX 9 sdk](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
- 설치 확인
  - ※ 프로젝트가 DXSDK_DIR를 사용해서 DirectX9의 헤더 파일와 lib 파일 경로를 설정합니다. DXSDK_DIR는 반드시 필요합니다.
      - 수동으로 DirectX 9 의 헤더와 Lib파일을 복사해서 PC에 복사해 왔다면, 환경변수에서 DXSDK_DIR를 지정하고 경로를 지정하십시오.
      - ![image](https://github.com/user-attachments/assets/9425d1b2-b29d-49fe-9b3c-4f60b63e85bc)

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
- 한글 문자열 출력
  - Ex06_StringOut
- 사운드
  - Ex08_Sound
- 라이브러리를 활요한 게임
  - 스네이크 게임
    - Ex11_Snake
  - 그림 맞추기게임
    - Ex12_ZigZagGame
