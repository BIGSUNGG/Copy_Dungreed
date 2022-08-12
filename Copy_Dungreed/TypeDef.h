#pragma once

// 매크로 정의
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

#define	WIN_WIDTH_BASIC 320
#define	WIN_HEIGHT_BASIC 180

#define WIN_RATIO WIN_WIDTH / WIN_WIDTH_BASIC

#define CENTER Vector2(WIN_WIDTH / 2, WIN_HEIGHT / 2)

#define PI 3.141592

#define RED			XMFLOAT4(1,0,0,1)
#define GREEN		XMFLOAT4(0,1,0,1)
#define BLUE		XMFLOAT4(0,0,1,1)
#define WHITE		XMFLOAT4(1,1,1,1)
#define BLACK		XMFLOAT4(0,0,0,1)

#define DEVICE Device::GetInstance()->GetDevice()
#define DEVICE_CONTEXT Device::GetInstance()->GetDeviceContext()

#define DELTA_TIME Timer::GetInstance()->GetDeltaTime()
#define RUN_TIME Timer::GetInstance()->GetRunTime()

#define KEY_DOWN(k) InputManager::GetInstance()->Down(k)
#define KEY_UP(k) InputManager::GetInstance()->Up(k)
#define KEY_PRESS(k) InputManager::GetInstance()->Press(k)

#define MOUSE_POS InputManager::GetInstance()->GetMousePos()
#define MOUSE_WORLD_POS Camera::GetInstance()->GetMouseWorldPos()

#define SAMPLER_STATE StateManager::GetInstance()->GetSampler()
#define ALPHA_STATE StateManager::GetInstance()->GetAlpha()
#define ADDITIVE_STATE StateManager::GetInstance()->GetAdditive()

#define ADD_VS(k) ShaderManager::GetInstance()->AddVS(k)
#define ADD_PS(k) ShaderManager::GetInstance()->AddPS(k)

#define LERP(s,e,t) s + (e - s)*t

#define V(hr) assert(SUCCEEDED(hr))

#define OBJ_MANAGER ObjectManager::GetInstance()
#define MAKE_OBJECT(type,level,num) ObjectManager::GetInstance()->GetNewObject(type,level,num)
#define MAKE_TILE(level,num) ObjectManager::GetInstance()->GetTile(level,num)
#define MAKE_BACKGROUND(level,num) ObjectManager::GetInstance()->GetBackGround(level,num)
#define MAKE_EFFECT(level,num) ObjectManager::GetInstance()->GetEffect(level,num)

#define CAMERA Camera::GetInstance()

#define GAME GameManager::GetInstance()
#define GET_OBJECTS GameManager::GetInstance()->GetObjects()

#define BASIC 0

using CallBack = function<void()>;
using CallBackParam = function<void(int)>;