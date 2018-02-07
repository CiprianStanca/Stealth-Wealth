#pragma once

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
//#include <gl\gl.h>
#include <gl\glu.h>
#include <fstream>

#include "Game.h"
#include "DebugLog.h"
#include "Vector.h"

#include "IRenderable.h"
#include "SkyBoxRenderable.h"
#include "Sprite.h"
#include "C3DShape.h"
#include "MeshRenderable.h"
#include "TerrainRenderable.h"
#include "GUITextureRenderable.h"
#include "RayRenderable.h"
#include "ExitMenu.h"

#include "IBehavior.h"
#include "GameObject.h"
#include "Input.h"
#include "Timer.h"

#include "IMaterial.h"
#include "LitMaterial.h"
#include "ColourMaterial.h"
#include "SkyBoxMaterial.h"

#include "Camera.h"
#include "Transform.h"

#include "MovingForwardBehavior.h"
#include "PlayerBehavior.h"
#include "AgentBehavior.h"
#include "MissileBehavior.h"
#include "FPSCameraBehavior.h"
#include "FaceCameraBehavior.h"
#include "SpinBehavior.h"
#include "SpriteSheetAnimationBehavior.h"
#include "ConstantVelocityBehavior.h"
#include "UpdateBoundingSphereBehavior.h"
#include "MissileCheckCollisionBehavior.h"
#include "MissileCheckPlayerCollisionBehavior.h"
#include "RayBehavior.h"
#include "TimedDeletionBehavior.h"
#include "MovingForwardBehavior.h"
#include "TurnAfterTimeBehavior.h"
//#include "JumpBehavior.h"
#include "FallUnderGravityBehavior.h"
#include "GUIButtonBehavior.h"
#include "GUIPlayButtonBehavior.h"
#include "GUIExitButtonBehavior.h"
#include "GUIInstructionButtonBehavior.h"

#include "ICollisionResponder.h"
#include "DestroyedByMissileCollisionResponder.h"

#include "IMouseListener.h"
#include "MouseManager.h"
#include "TagManager.h"
#include "CollisionManager.h"

#include "ICollider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "CubeCollider.h"
#include "LadderCollider.h"
#include "CollideDeleteBehavior.h"
#include "PlayerSpotted.h"

#include "Graphics.h"
#include "TextureLoader.h"

#include "TransparentRenderingManager.h"

#include <assert.h>
#include <map>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

#include <typeinfo>

#define DPrint(txt) CDebugLog::Instance()->Print(txt);
#define DEG2RAD(x) 3.142*x/180

#pragma comment (lib, "rm_framework.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "FreeImage.lib")
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
