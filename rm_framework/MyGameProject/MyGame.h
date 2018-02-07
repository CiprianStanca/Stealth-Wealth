#pragma once


//setup an enumeration so we can refer to the textures by name rather than by number
static enum TextureNames
{
	NO_TEXTURE, //0 is never used for texture mapping - OpenGL just won't assign this as a name for a texture binding
	MENU,
	PLAYBUTTON,
	PLAYBUTTONHI,
	PLAYBUTTONCLICK,
	SETTINGSBUTTON,
	SETTINGSBUTTONHI,
	SETTINGSBUTTONCLICK,
	SCOREBUTTON,
	SCOREBUTTONHI,
	SCOREBUTTONCLICK,
	EXITWINDOW,
	SKYBOX,
	CRATE,
	FENCE,
	ENEMY,
	HUT,
	GRASS,
	EXPLOSION,
	GUI,
	GUN,
	OUTWALL,
	FLOOR,
	TREE,
	DIAMOND,
	ARTIFACT,
	ZERO,
	ONE,
	TWO,
	BENCH,
	POLE,
	BIN,
	METAL,
	LADDER,
	EGYPT,
	SCARAB,
	INSTRUCTIONS,
	GAMEWON,
	GAMELOST,


};

//TODO1: add an enumeration to store different game states

class CGameObject;


class MyGame :
	public CGame
{
public:
	MyGame(void);
	~MyGame(void);
	void Initialize();
	void LoadTextures();
	void LoadMenu();
	void LoadInstructions();
	void LoadWon();
	void LoadLost();
	void LoadWorld();
	void LoadWorld2();

	void DoFrame();


private:

	CGameObject * pMenu;
	CGameObject * pPlayButton;
	CGameObject * pOptionsButton;
	CGameObject * pScoreButton;
	CGameObject * pInstructions;
	CGameObject * pWon;
	CGameObject * pLost;

	bool m_bWorldLoaded = false;
};

