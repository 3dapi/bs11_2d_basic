//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _ILcModel_H_
#define _ILcModel_H_


#ifndef interface
#define interface	struct
#endif

namespace LcsLib
{

interface ILcModel
{
	virtual ~ILcModel(){};

	virtual void	Render() =0;

	virtual	INT		GetID()=0;
	virtual const char*	GetName() = 0;

	virtual	void	SetPos(const FLOAT* =NULL) =0;
	virtual	void	SetColor(const DWORD=0xFFFFFFFF) =0;
	virtual	void	SetRect(void* rc=NULL) =0;

	virtual	INT		FindAniIndex(INT* pOut/*Out*/, DWORD TimeCur, DWORD TimeBegin) =0;
	virtual	INT		FindImageRect(void* pRECT/*Out*/, INT nIndex) =0;
};

INT	LcDev_ModelCreate(char* sCmd
					  , ILcModel** pData
					  , void* p1=NULL	//char* : Model Name
					  , void* p2=NULL
					  , void* p3=NULL
					  , void* p4=NULL
					);

INT			LcDev_ModelInit(void* pSprite);	// ID3DXSprite Pointer
ILcModel*	LcDev_ModelFind(INT nID);
void		LcDev_ModelDestroy();

}//namespace LcsLib

#endif

