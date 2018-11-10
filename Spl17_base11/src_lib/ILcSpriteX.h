// Interface for the ILcSpriteX class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _ILcSpriteX_H_
#define _ILcSpriteX_H_


#ifndef interface
#define interface	struct
#endif

namespace LcsLib
{

interface ILcSpriteX
{
	virtual ~ILcSpriteX(){};

	virtual	INT		Begin(DWORD=0)=0;
	virtual	INT		End(DWORD=0)=0;

	virtual	INT		OnResetDevice()=0;
	virtual	INT		OnLostDevice()=0;

	virtual	INT		Draw( void* pTex				// Texture
						, RECT* pRct				// Draw Region
						, void* pScl=NULL			// Scaling
						, void* pTrn=NULL			// Position
						, DWORD dColor=0xFFFFFFFF	// color
						, INT   bMono=0				// Monotone
						)=0;

	virtual	INT		DrawEx( void* pTex				// Texture
						, RECT* pRct				// Draw Region
						, void* pScl				// Scaling
						, void* pTrn				// Position
						, void* pRot				// Rotation Center
						, FLOAT	fAngle				// Rotation Angle(Radian)
						, DWORD dColor=0xFFFFFFFF	// color
						, INT   bMono=0				// Monotone
						)=0;

	virtual	void	AlphaOption(INT opt=0)=0;
};



INT	LcDev_SpriteCreate(char* sCmd
					, ILcSpriteX** pData
					, void* p1=NULL
					, void* p2=NULL
					, void* p3=NULL
					, void* p4=NULL
					);


}//namespace LcsLib

#endif

