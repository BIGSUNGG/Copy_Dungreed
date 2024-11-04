// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <direct.h>
#include <fstream>
#include <cstring> 
#include <tchar.h>
#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <time.h>
#include <queue>
#include <io.h>
#include <map>
#include <set>

#include <wrl/client.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")


// DirectXTeX
#include "../DirectXTex/DirectXTex.h"

// ImGui
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"

// DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>

//FMOD
#include "Library/FMOD/inc/fmod.hpp"
#pragma comment(lib,"Library/FMOD/fmod_vc.lib")

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace DirectX;
using namespace std;

// Device
#include "Framework/Device/Device.h"

// TypeDef
#include "TypeDef.h"

// Math
#include "Framework/Math/Vector2.h" 
#include "Framework/Math/Transform.h"

// Render
#include "Framework/Render/VertexLayOuts.h"
#include "Framework/Render/ConstantBuffer.h"
#include "Framework/Render/GlobalBuffer.h"
#include "Framework/Render/IndexBuffer.h"
#include "Framework/Render/Shader.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"
#include "Framework/Render/ShaderManager.h"
#include "Framework/Render/VertexBuffer.h"
#include "Framework/Render/SRV.h"
#include "Framework/Render/Texture.h"
#include "Framework/Render/RenderTarget.h"

// Camera
#include "Framework/Camera/Camera.h"

// State
#include "Framework/State/SamplerState.h"
#include "Framework/State/BlendState.h"
#include "Framework/State/StateManager.h"

// Utillity
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/InputManager.h"
#include "Framework/Utility/Utillity.h"
#include "Framework/Utility/MathUtility.h"
#include "Framework/Utility/BinaryWriter.h"
#include "Framework/Utility/BinaryReader.h"
#include "Framework/Utility/DirectWrite.h"
#include "Framework/Utility/tinyxml2.h"
#include "Framework/Utility/Audio.h"
#include "Framework/Utility/MouseCursur.h"
#include "Framework/Utility/Graphic.h"

//Collider
#include "Framework/Collider/Collider.h"
#include "Framework/Collider/CircleCollider.h"
#include "Framework/Collider/RectCollider.h"

// Animation
#include "Framework/Animation/Animation.h"

// Object
#include "Object/Quad.h"
#include "Object/InstanceQuad.h"

// Struct
#include "Dungreed/Instance/Status/Creature_Status.h"
#include "Dungreed/Instance/Dash/Dash_Info.h"
#include "Dungreed/Instance/Map/MapBasic.h"
#include "Dungreed/Instance/Inventory/Inventory.h"
#include "Dungreed/Instance/ComponentCollector/ComponentCollector.h"

// ObjComponent
#include "Dungreed/ObjectComponent/ObjectComponent.h"
#include "Dungreed/ObjectComponent/MovementComponent/MovementComponent.h"
#include "Dungreed/ObjectComponent/MovementComponent/DashMovementComponent/DashMovementComponent.h"

// Object
#include "Dungreed/Object/Object.h"
#include "Dungreed/Object/BackGround/BackGround.h"
#include "Dungreed/Object/Wall/Wall.h"
#include "Dungreed/Object/Tile/Tile.h"
#include "Dungreed/Object/Tile/LockDoor/LockDoor.h"
#include "Dungreed/Object/Tile/LockDoor/Left/LockDoorLeft.h"
#include "Dungreed/Object/Tile/LockDoor/Right/LockDoorRight.h"
#include "Dungreed/Object/Tile/LockDoor/Top/LockDoorTop.h"
#include "Dungreed/Object/Tile/LockDoor/Bottom/LockDoorBottom.h"
#include "Dungreed/Object/Effect/Effect.h"
#include "Dungreed/Object/Effect/Trail/Effect_Trail.h"
#include "Dungreed/Object/Effect/Number/Effect_Number.h"

// ECT
#include "Dungreed/Object/Etc/Etc.h"
#include "Dungreed/Object/Etc/Bullet/Bullet.h"
#include "Dungreed/Object/Etc/DropItem/DropItem.h"
#include "Dungreed/Object/Etc/DropGold/DropGold.h"
#include "Dungreed/Object/Etc/Chest/Chest.h"

// Item
#include "Dungreed/Object/Etc/Item/Item.h"
#include "Dungreed/Object/Etc/Item/Weapon/Weapon.h"
#include "Dungreed/Object/Etc/Item/Weapon/Melee/Melee.h"
#include "Dungreed/Object/Etc/Item/Weapon/Melee/FireDragonKiller/Melee_FireDragonKiller.h"
#include "Dungreed/Object/Etc/Item/Weapon/Gun/Gun.h"
#include "Dungreed/Object/Etc/Item/Accessory/Accessory.h"
#include "Dungreed/Object/Etc/Item/SubWeapon/SubWeapon.h"

// Creature
#include "Dungreed/Object/Creature/Creature.h"
#include "Dungreed/Object/Creature/Player/Player.h"
#include "Dungreed/Object/Creature/Monster/Monster.h"
#include "Dungreed/Object/Creature/Monster/GraySkel/GraySkel.h"
#include "Dungreed/Object/Creature/Monster/Ghost/Ghost.h"

// UI
#include "Dungreed/UI/UI.h"

#include "Dungreed/UI/Component/UI_Component.h"
#include "Dungreed/UI/Component/Button/UI_Button.h"
#include "Dungreed/UI/Component/Slider/UI_Slider.h"
#include "Dungreed/UI/Component/Text/UI_Text.h"

#include "Dungreed/UI/HpBar/UI_PlayerHpBar.h"
#include "Dungreed/UI/HpBar/UI_EnemyHpBar.h"
#include "Dungreed/UI/WeaponSlot/UI_WeaponSlot.h"
#include "Dungreed/UI/Info/UI_Info.h"
#include "Dungreed/UI/MiniMap/UI_MiniMap.h"
#include "Dungreed/UI/Inventory/UI_Inventory.h"
#include "Dungreed/UI/Map/UI_Map.h"
#include "Dungreed/UI/Option/UI_Option.h"
#include "Dungreed/UI/Setting/UI_Setting.h"

// Map
#include "Dungreed/Map/Map.h"

// Manager
#include "Dungreed/Manager/ObjectManager.h"
#include "Dungreed/Manager/GameManager.h"
#include "Dungreed/Manager/MapManager.h"
#include "Dungreed/Manager/InventoryManager.h"
#include "Dungreed/Manager/UIManager.h"

// GameMode
#include "Dungreed/GameMode/GameMode.h"
#include "Dungreed/GameMode/Dungreed.h"
#include "Dungreed/GameMode/MapTest.h"
#include "Dungreed/GameMode/MapEditor.h"

// Program
#include "Program/Program.h"