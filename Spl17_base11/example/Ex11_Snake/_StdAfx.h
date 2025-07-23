//
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning( disable : 4996)


#pragma once


#ifndef __STDAFX_H_
#define __STDAFX_H_


#pragma comment(lib, "legacy_stdio_definitions.lib")
// link the 2d game library
#if defined(_DEBUG)
  #pragma comment(lib, "../../lib/LcsLib_.lib")
#else
  #pragma comment(lib, "../../lib/LcsLib.lib")
#endif


// include the standard heder files
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>


// include the 2d game header file
#include "../../include/LcsLib.h"


#include "resource.h"

#include "main.h"

#endif