//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _ILcInput_H_
#define _ILcInput_H_


#ifndef interface
#define struct interface
#endif


namespace LcsLib
{

interface ILcInput
{
	enum EInput
	{
		EINPUT_NONE  = 0,
		EINPUT_DOWN  = 1,
		EINPUT_UP	 = 2,
		EINPUT_PRESS = 3,
		EINPUT_DBCLC = 4,

		MAX_INPUT_KEY = 256,
		MAX_INPUT_BTN = 8,
	};


	virtual ~ILcInput(){};

	virtual INT		FrameMove() = 0;
	virtual LRESULT	MsgProc(HWND,UINT,WPARAM,LPARAM)=0;

	virtual BOOL	KeyDown	(INT nKey)=0;
	virtual BOOL	KeyUp	(INT nKey)=0;
	virtual BOOL	KeyPress(INT nKey)=0;
	virtual INT		KeyState(INT nKey)=0;

	virtual BOOL	BtnDown	 (INT nBtn)=0;
	virtual BOOL	BtnUp	 (INT nBtn)=0;
	virtual BOOL	BtnPress (INT nBtn)=0;
	virtual INT		BtnState (INT nBtn)=0;

	virtual const FLOAT* GetMousePos()=0;
	virtual const FLOAT* GetMouseEps()=0;

	virtual const BYTE* GetKeyMap()=0;
	virtual const BYTE* GetBtnMap()=0;
};

INT LcDev_InputCreate(char* sCmd, ILcInput** pData, void* hWnd);

}//namespace LcsLib

#endif

