#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN 

#define DELTA_TIME TimerManager::Get()->GetElapsedTime()
#define ELAPSED_TIME TimerManager::Get()->GetElapsedTime()

//#define WIN_WIDTH WinSize.x
//#define WIN_HEIGHT WinSize.y

#define RES_HD 1

#ifndef RES_HD
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#else
#define WIN_WIDTH 960
#define WIN_HEIGHT 540
#endif // !HD

#define WIN_CENTER_X WIN_WIDTH * 0.5f
#define WIN_CENTER_Y WIN_HEIGHT * 0.5f

#define WIN_SIZE Vector2(WIN_WIDTH, WIN_HEIGHT)

#define PI 3.141592f

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define MAGENTA RGB(255, 0, 255)
#define BLACK RGB(0, 0, 0)
#define WHITE RGB(255, 255, 255)

#define KEY_DOWN(k) KeyboardManager::Get()->Down(k)
#define KEY_UP(k) KeyboardManager::Get()->Up(k)
#define KEY_PRESS(k) KeyboardManager::Get()->Press(k)

#define Super	__super

#define LPCWSTR WSTR

#define CREATE_COLLISION CollisionManager::Get()->CreateCollision

// Library
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iterator>
#include <fstream>
#include <functional>

// Enums
#include "Enums/Resolution.h"
#include "Enums/CollisionChannel.h"
#include "Enums/CharacterState.h"
#include "Enums/KeyValue.h"

// Math
#include "Math/Vector2.h"
#include "Math/GameMath.h"

// Structs
#include "Structs/TextureInfo.h"
#include "Structs/SpriteInfo.h"
//#include "Structs/DebugInfo.h"

// Manager
#include "Manager/Singleton.h"
#include "Manager/GameManager.h"
#include "Manager/TimerManager.h"
#include "Manager/KeyboardManager.h"
#include "Manager/CollisionManager.h"
#include "Manager/ObjectManager.h"

#include "Components/Camera.h"

// Utilities
#include "Utilities/Keyboard.h"
#include "Utilities/Texture.h"

// Handle
#include "Structs/TimerHandle.h"

// Objects
#include "Objects/Collision.h"
#include "Objects/Object.h"
#include "Objects/Actors/Actor.h"
#include "Objects/Actors/Characters/Character.h"
#include "Objects/Actors/Characters/Monster/Monster.h"
#include "Objects/Actors/Weapon/EnergyBall.h"

//
#include "Background/Background.h"

#include "Animation/Animation.h"

// Components
//#include "Components/ActorComponent.h"

// Scnene
#include "Scene/Scene.h"

using namespace std;

extern HWND hWnd;
extern HINSTANCE hInst;

extern Vector2 mousePos;
extern Vector2 WinSize;