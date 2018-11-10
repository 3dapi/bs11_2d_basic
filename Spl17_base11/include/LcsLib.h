// GaLic Game Library Collection for simple 2d Game.
//
// This library constructed with DirectX SDK summer update 2003
//   and modified on DirectX SDK 2010 jun( it's need to compiling).
//
// Build Env: DirectX SDK 2010 jun, Visual studio 2008
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning(disable: 4096)
#pragma warning(disable: 4099)


#pragma once

#ifndef _LcsLib_H_
#define _LcsLib_H_


#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>


typedef D3DXVECTOR2							VEC2;
typedef D3DXVECTOR3							VEC3;
typedef D3DXCOLOR							DCLR;

typedef	LPDIRECT3D9							PD3D;
typedef LPDIRECT3DDEVICE9					PDEV;
typedef	LPD3DXSPRITE						PDSP;

typedef LPDIRECT3DTEXTURE9					PDTX;
typedef LPDIRECT3DSURFACE9					PDSF;
typedef	D3DXIMAGE_INFO						DIMG;


// Create window and DirectX
INT		LcsLib_CreateWin(INT x,INT y								// Screen position x, y
						 ,INT ScnW,INT ScnH							// Screen Width, height
						 ,char* sName,INT bFull=FALSE				// Class name, Full screen mode
						 );

void	LcsLib_DestroyWin();										// ������� DirectX�Ҹ�
INT		LcsLib_ChangeWindow(INT bFull=TRUE);						// Change Window Mode
INT		LcsLib_Run();												// ���� ����


// Setting the runtime Function pointer
void	LcsLib_SetFrameMove( INT (*)() );							// ���� ������ update �Լ�
void	LcsLib_SetRender( INT (*)() );								// ���� ������ ������ �Լ�
void	LcsLib_SetKeyboard( INT (*)(BYTE*) );						// ���ӿ����� Ű���� �̺�Ʈ�� �������� �Լ��� �������ִ� �Լ�
void	LcsLib_SetMouse( INT (*)(INT x,INT y,INT z,INT _event) );	// ���ӿ����� ���콺 �̺�Ʈ�� �������� �Լ��� �������ִ� �Լ�


// Keyboard and Mouse
const BYTE*	LcsLib_GetKeyboard();									// Ű����(0~255)
INT		LcsLib_GetMouseX();											// ���콺 ��ġ X
INT		LcsLib_GetMouseY();											// ���콺 ��ġ Y
INT		LcsLib_GetMouseZ();											// ���콺 ��ġ Z
INT		LcsLib_GetMouseEvent(INT nMouse);							// ���콺 �̺�Ʈ (0: LButton, 1: RButton, 2: MButton)

void	LcsLib_SetWindowStyle(DWORD dSty);
DWORD	LcsLib_GetWindowStyle();
HWND	LcsLib_GetHwnd();											// ������ �ڵ� ���
INT		LcsLib_GetScnW();											// ȭ���� ũ�⸦ ��������
INT		LcsLib_GetScnH();											// ȭ���� �ʺ� ��������

void	LcsLib_SetStateShow(INT _bShow);							// State �����ֱ�
void	LcsLib_SetCursorShow(INT _bShow);							// Cursor �����ֱ�
void	LcsLib_SetClearColor(DWORD dC);								// ���ȭ�� Ŭ���� ������
DWORD	LcsLib_GetClearColor();										// ���ȭ�� Ŭ���� ���� ��������
void	LcsLib_SetWindowTitle(const char *format, ...);				// ������ Ÿ��Ʋ


// 2D Texture
INT		LcsLib_TextureLoad(char* sFileName, DWORD dc=0x00FFFFFF);	// �̹��� ���� �ε�
INT		LcsLib_TextureRelease(INT _nKey);							// �̹��� ���� ����
INT		LcsLib_TextureWidth(INT _nKey);								// �̹��� ���� �ʺ�
INT		LcsLib_TextureHeight(INT _nKey);							// �̹��� ���� ����

INT		LcsLib_Draw2D(INT _nKey
					, RECT* pSrcRect								// �׸� ����
					, VEC2* pTranslate=NULL							// �̵� ��ġ
					, VEC2* pScaling=NULL							// ũ�� ��ȯ ��
					, VEC2* pRotation=NULL							// ȸ�� �߽� ��ġ
					, FLOAT fAngle=0								// ȸ�� ����: Radian
					, DWORD dC=0xFFFFFFFF							// �̹��� ���� �׸���
					, INT	bMono=FALSE								// Monotone
					);


INT		LcsLib_DrawAlphaOption(INT nAlphaMethod=0);


// for Font
INT		LcsLib_FontCreate(char* sName, LONG iH, LONG iItalic=0);	// ��Ʈ ��ü ����
INT		LcsLib_FontDrawText(INT nIdx								// ���ڿ� ���
					   , LONG left
					   , LONG top
					   , LONG right
					   , LONG bottom
					   , DWORD fontColor
					   , const char *format, ...);


// sound
INT		LcsLib_SoundLoad(char* sFileName);				// ���� �ε�
INT		LcsLib_SoundRelease(INT _nKey);					// ���� ��ü ����
void	LcsLib_SoundPlay(INT _nKey);					// ���� ����
void	LcsLib_SoundStop(INT _nKey);					// ���� ����
void	LcsLib_SoundReset(INT _nKey);					// ���� ����
BOOL	LcsLib_SoundIsPlaying(INT _nKey);				// ���� ������?


// etc
DWORD	LcsLib_TimeGetTime();							// return the time GetTime

#endif

