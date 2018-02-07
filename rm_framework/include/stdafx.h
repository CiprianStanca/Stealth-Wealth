// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

//25/02/2014 change - Oliver
//This is redundant; simply include rm_framework.h and this can all be got rid of
//Add it back in if we need to
#include <rm_framework.h>

//// C RunTime Header Files
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>
//#include <stdio.h>
//
//
//#include "DebugLog.h"
//#include "Vector.h"
//#include "IRenderable.h"
//#include "IBehavior.h"
//#include "GameObject.h"
//#include "Input.h"
//#include "Timer.h"
//#include "IMaterial.h"
//#include "ColourMaterial.h"
//#include "Sprite.h"
//#include "Transform.h"
//#include "PlayerBehavior.h"
//
//#define DPrint(txt) CDebugLog::Instance()->Print(txt);
//// TODO: reference additional headers your program requires here
