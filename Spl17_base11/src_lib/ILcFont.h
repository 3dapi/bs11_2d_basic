//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _ILcFont_H_
#define _ILcFont_H_


#ifndef interface
#define interface	struct
#endif

namespace LcsLib
{

interface	ILcFont
{
	virtual	~ILcFont(){};

	virtual	INT		GetID()=0;
	virtual	void*	GetFont()=0;
};


INT LcDev_FontCreate(char* sCmd
					, ILcFont** pData
					, void* p1=NULL		// char*: fong Name
					, void* p2=NULL		// LONG: Height
					, void* p3=NULL		// LONG: Italic?
					, void* p4=NULL
					);

INT			LcDev_FontInit(void* pd3dDevice);
ILcFont*	LcDev_FontFind(INT _nID);
void		LcDev_FontDestroy();

}//namespace LcsLib

#endif

