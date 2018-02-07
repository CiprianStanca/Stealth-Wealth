#pragma once
#include "game.h"



//setup an enumeration so we can refer to the textures by name rather than by number
static enum TextureNames
		{
			NO_TEXTURE, //0 is never used for texture mapping - OpenGL just won't assign this as a name for a texture binding
			MENU,
			SKYBOX,
			CRATE,
			FENCE,
			ENEMY,
			GRASS
		};


class CSpaceGame :
	public CGame
{
public:
	CSpaceGame(void);
	~CSpaceGame(void);
	void Initialize();
};

