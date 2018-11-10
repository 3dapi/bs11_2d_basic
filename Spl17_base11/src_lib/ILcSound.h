//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _ILcSound_H_
#define _ILcSound_H_


#ifndef interface
#define interface	struct
#endif

namespace LcsLib
{

interface	ILcSound
{
	virtual	~ILcSound(){};

	virtual	INT		GetID()=0;

	virtual	INT		Play()=0;
	virtual	INT		Stop()=0;
	virtual	INT		Reset()=0;
	virtual INT		GetState()=0;
};


INT	LcDev_SoundCreate(char* sCmd
					, ILcSound** pData
					, void* p1=NULL		// char* : Sound File Name
					, void* p2=NULL
					, void* p3=NULL
					, void* p4=NULL
					);

INT			LcDev_SoundInit(void* hWnd);
ILcSound*	LcDev_SoundFind(INT nID);
void		LcDev_SoundDestroy();

}//namespace LcsLib

#endif

