#include "framework.h"
#include "MapManager.h"

MapManager* MapManager::_instance = nullptr;

void MapManager::Update()
{
	GetCurMap()->CheckCleared();

	if (GetCurMap()->GetCleared())
	{
		_mapDoorDelayTime[_curMapIndex.x][_curMapIndex.y] += DELTA_TIME;
		if (_mapDoorDelayTime[_curMapIndex.x][_curMapIndex.y] >= _doorEffectDelay)
		{
			_mapDoorDelayTime[_curMapIndex.x][_curMapIndex.y] -= _doorEffectDelay;
			MakeDoorEffect();
		}
		if(GAME->GetPlayer() != nullptr)
			CheckMapMove();
	}
}

void MapManager::MakeRandomMap(int level, int num)
{	
	_maps.clear();
	_maps[0][0] = Load(level, num);
	
	if (_maps[0][0]->CanGoTop())
		FindTopMap(level, 0, 0 + 1);

	if (_maps[0][0]->CanGoBottom())
		FindBottomMap(level, 0, 0 - 1);

	if (_maps[0][0]->CanGoLeft())
		FindLeftMap(level, 0 - 1, 0);

	if (_maps[0][0]->CanGoRight())
		FindRightMap(level, 0 + 1, 0);

	SetCurMap({ 0,0 });
}

void MapManager::FindTopMap(int level, int x, int y)
{
	if (_maps[x][y] != nullptr)
		return;

	while (true)
	{
		int num = (rand() % (_mapSize[level].size() - 1)) + 1;
		auto map = Load(level, num);

		if (map->CanGoBottom())
		{
			if(map->CanGoTop() && _maps[x][y+1] != nullptr)
				continue;
			if (map->CanGoLeft() && _maps[x - 1][y] != nullptr)
				continue;
			if (map->CanGoRight() && _maps[x + 1][y] != nullptr)
				continue;

			_maps[x][y] = map;

			if (_maps[x][y]->CanGoTop())
				FindTopMap(level, x, y + 1);

			if (_maps[x][y]->CanGoLeft())
				FindLeftMap(level, x - 1, y);

			if (_maps[x][y]->CanGoRight())
				FindRightMap(level, x + 1, y);

			return;
		}
	}
}

void MapManager::FindBottomMap(int level, int x, int y)
{
	if (_maps[x][y] != nullptr)
		return;

	while (true)
	{
		int num = (rand() % (_mapSize[level].size() - 1)) + 1;
		auto map = Load(level, num);

		if (map->CanGoTop())
		{
			if (map->CanGoBottom() && _maps[x][y - 1] != nullptr)
				continue;
			if (map->CanGoLeft() && _maps[x - 1][y] != nullptr)
				continue;
			if (map->CanGoRight() && _maps[x + 1][y] != nullptr)
				continue;

			_maps[x][y] = map;

			if (_maps[x][y]->CanGoBottom())
				FindBottomMap(level, x, y - 1);

			if (_maps[x][y]->CanGoLeft())
				FindLeftMap(level, x - 1, y);

			if (_maps[x][y]->CanGoRight())
				FindRightMap(level, x + 1, y);

			return;
		}
	}
}

void MapManager::FindLeftMap(int level, int x, int y)
{
	if (_maps[x][y] != nullptr)
		return;

	while (true)
	{
		int num = (rand() % (_mapSize[level].size() - 1)) + 1;
		auto map = Load(level, num);

		if (map->CanGoRight())
		{
			if (map->CanGoTop() && _maps[x][y + 1] != nullptr)
				continue;
			if (map->CanGoBottom() && _maps[x][y - 1] != nullptr)
				continue;
			if (map->CanGoLeft() && _maps[x - 1][y] != nullptr)
				continue;

			_maps[x][y] = map;

			if (_maps[x][y]->CanGoTop())
				FindTopMap(level, x, y + 1);

			if (_maps[x][y]->CanGoBottom())
				FindBottomMap(level, x, y - 1);

			if (_maps[x][y]->CanGoLeft())
				FindLeftMap(level, x - 1, y);

			return;
		}
	}
}

void MapManager::FindRightMap(int level, int x, int y)
{
	if (_maps[x][y] != nullptr)
		return;

	while (true)
	{
		int num = (rand() % (_mapSize[level].size() - 1)) + 1;
		auto map = Load(level, num);

		if (map->CanGoLeft())
		{
			if (map->CanGoTop() && _maps[x][y + 1] != nullptr)
				continue;
			if (map->CanGoBottom() && _maps[x][y - 1] != nullptr)
				continue;
			if (map->CanGoRight() && _maps[x + 1][y] != nullptr)
				continue;

			_maps[x][y] = map;

			if (_maps[x][y]->CanGoTop())
				FindTopMap(level, x, y + 1);

			if (_maps[x][y]->CanGoBottom())
				FindBottomMap(level, x, y - 1);

			if (_maps[x][y]->CanGoRight())
				FindRightMap(level, x + 1, y);

			return;
		}
	}
}

shared_ptr<Map> MapManager::Load(int level, int num)
{
	shared_ptr<Map> newMap = make_shared<Map>(level,num);
	wstring wLoadPath = L"Save/Maps/Level_";
	string sLoadPath = _path + "Save\\Maps\\Level_";

	wstring levelPath;
	{
		if (level < 10)
			levelPath += L"0";

		levelPath += to_wstring(level);
	}
	wstring numPath;
	{
		if (num < 10)
			numPath += L"0";

		numPath += to_wstring(num);
	}
	wLoadPath += levelPath + L"_" + numPath;
	sLoadPath += WstrToStr(levelPath) + "_" + WstrToStr(numPath);

	ifstream checkPath1(sLoadPath + ".bin");
	ifstream checkPath2(sLoadPath + "_Basic" + ".bin");

	if (checkPath1 && checkPath2)
	{
		int objectCount;
		{
			BinaryReader basicReader(wLoadPath + L"_Basic" + L".bin");

			UINT size = basicReader.Uint();

			vector<int> basicInfo;
			basicInfo.resize(15);
			void* ptr = basicInfo.data();
			basicReader.Byte(&ptr, size * sizeof(int));

			objectCount = basicInfo[0];
			newMap->GetLeftBottom() = Vector2(basicInfo[1], basicInfo[2]);
			newMap->GetRightTop() = Vector2(basicInfo[3], basicInfo[4]);
			newMap->GetStartPos() = Vector2(basicInfo[5], basicInfo[6]);

			newMap->GetTopDoor() = Vector2(basicInfo[7], basicInfo[8]);
			newMap->GetBottomDoor() = Vector2(basicInfo[9], basicInfo[10]);
			newMap->GetLeftDoor() = Vector2(basicInfo[11], basicInfo[12]);
			newMap->GetRightDoor() = Vector2(basicInfo[13], basicInfo[14]);
		}

		{
			BinaryReader mapReader(wLoadPath + L".bin");

			UINT size = mapReader.Uint();

			vector<int> mapInfo;
			int info = 6;
			int infoCount = objectCount * info;
			mapInfo.resize(infoCount);
			void* ptr = mapInfo.data();
			mapReader.Byte(&ptr, size * sizeof(int));

			for (int i = 0; i < objectCount; i++)
			{
				int cur = i * info;

				shared_ptr<Object> object = MAKE_OBJECT(mapInfo[cur], mapInfo[cur + 1], mapInfo[cur + 2]);

				object->SetSpawnPos(Vector2(mapInfo[cur + 3], mapInfo[cur + 4]));

				if (mapInfo[cur + 5] == 1)
					object->ReverseTexture();

				newMap->AddObject(object, mapInfo[cur]);
			}
		}
	}
	else
		newMap = make_shared<Map>(level, num);

	return newMap;
}

void MapManager::Save(shared_ptr<Map> map)
{
	const int& level = map->GetLevel();
	const int& num = map->GetNum();

	wstring wLoadPath = L"Save/Maps/Level_";
	string sLoadPath = _path + "Save\\Maps\\Level_";

	wstring levelPath;
	{
		if (level < 10)
			levelPath += L"0";

		levelPath += to_wstring(level);
	}
	wstring numPath;
	{
		if (num < 10)
			numPath += L"0";

		numPath += to_wstring(num);
	}
	wLoadPath += levelPath + L"_" + numPath;
	sLoadPath += WstrToStr(levelPath) + "_" + WstrToStr(numPath);

	{
		ifstream checkPath1(sLoadPath + ".bin");
		ifstream checkPath2(sLoadPath + "_Basic" + ".bin");

		if (!checkPath1 || !checkPath2)
		{
			ofstream makeFile1(sLoadPath + ".bin");
			ofstream makeFile2(sLoadPath + "_Basic" + ".bin");
			_mapSize[level].emplace_back(num);
		}
	}

	{
		BinaryWriter basicWriter(wLoadPath + L"_Basic" + L".bin");

		vector<int> basicInfo;

		basicInfo.push_back(map->GetObjectCount());
		basicInfo.push_back(map->GetLeftBottom().x);
		basicInfo.push_back(map->GetLeftBottom().y);
		basicInfo.push_back(map->GetRightTop().x);
		basicInfo.push_back(map->GetRightTop().y);
		basicInfo.push_back(map->GetStartPos().x);
		basicInfo.push_back(map->GetStartPos().y);

		basicInfo.push_back(map->GetTopDoor().x);
		basicInfo.push_back(map->GetTopDoor().y);
		basicInfo.push_back(map->GetBottomDoor().x);
		basicInfo.push_back(map->GetBottomDoor().y);
		basicInfo.push_back(map->GetLeftDoor().x);
		basicInfo.push_back(map->GetLeftDoor().y);
		basicInfo.push_back(map->GetRightDoor().x);
		basicInfo.push_back(map->GetRightDoor().y);

		basicWriter.Uint(basicInfo.size());
		basicWriter.Byte(basicInfo.data(), basicInfo.size() * sizeof(int));
	}

	{
		BinaryWriter mapWriter(wLoadPath + L".bin");

		vector<int> mapInfo;

		for (auto& objects : map->GetObjects())
		{
			for (auto& object : objects)
			{
				mapInfo.push_back((int)object->GetType());
				mapInfo.push_back(object->GetLevel());
				mapInfo.push_back(object->GetNum());
				mapInfo.push_back((int)object->GetObjectTexture()->GetTransform()->GetPos().x);
				mapInfo.push_back((int)object->GetObjectTexture()->GetTransform()->GetPos().y);
				mapInfo.push_back((int)object->GetReversed());
			}
		}

		mapWriter.Uint(mapInfo.size());
		mapWriter.Byte(mapInfo.data(), mapInfo.size() * sizeof(int));
	}
}

void MapManager::SaveAll()
{
	// Save Load방식의 변경점이 있을때 편하게 쓰기 위해
	for (int level = 0; level < _mapSize.size(); level++)
	{
		for (int num = 0; num < _mapSize[level].size(); num++)
		{
			shared_ptr<Map> temp = Load(level, _mapSize[level][num]);
			Save(temp);
		}
	}
}

void MapManager::SetTarget(shared_ptr<Creature> target)
{
	for (auto& monster : _maps[_curMapIndex.x][_curMapIndex.y]->GetObjects()[Object::CREATURE])
	{
		auto creature = dynamic_pointer_cast<Creature>(monster);
		if (creature != nullptr && creature->GetCreatureType() == Creature::ENEMY)
		{
			auto enemy = dynamic_pointer_cast<Monster>(creature);
			enemy->SetTarget(target);
		}
	}

	GetCurMap()->CheckCleared();
	if (GetCurMap()->GetCleared() == false)
	{
		if (GetCurMap()->CanGoLeft())
		{
			auto door = make_shared<LockDoorLeft>();
			door->SetSpawnPos(GetCurMap()->GetLeftDoor());
			GAME->AddObject(door, Object::TILE);
		}
		if (GetCurMap()->CanGoRight())
		{
			auto door = make_shared<LockDoorRight>();
			door->SetSpawnPos(GetCurMap()->GetRightDoor());
			GAME->AddObject(door, Object::TILE);
		}
		if (GetCurMap()->CanGoTop())
		{
			auto door = make_shared<LockDoorTop>();
			door->SetSpawnPos(GetCurMap()->GetRightDoor());
			GAME->AddObject(door, Object::TILE);
		}
		if (GetCurMap()->CanGoBottom())
		{
			auto door = make_shared<LockDoorBottom>();
			door->SetSpawnPos(GetCurMap()->GetRightDoor());
			GAME->AddObject(door, Object::TILE);
		}
	}
}

void MapManager::SetCurMap(shared_ptr<Map> map)
{
	_maps[_curMapIndex.x][_curMapIndex.y] = map;
	SetCurMap(_curMapIndex);

	return;
}

void MapManager::SetCurMap(const Vector2& index)
{
	int moveX = index.x - _curMapIndex.x;
	int moveY = index.y - _curMapIndex.y;
	_curMapIndex = index;
	GAME->SetMap(_maps[_curMapIndex.x][_curMapIndex.y]);
	if (GAME->GetPlayer() != nullptr)
	{
		GAME->AddPlayer(GAME->GetPlayer());
		if (moveX > 0)
		{
			GAME->GetPlayer()->GetObjectTexture()->SetLeft(GetCurMap()->GetLeftDoor().x + _doorVerticalHalfSize.x + 48);
			GAME->GetPlayer()->GetObjectTexture()->SetBottom(GetCurMap()->GetLeftDoor().y - _doorVerticalHalfSize.y);
		}
		else if (moveX < 0)
		{
			GAME->GetPlayer()->GetObjectTexture()->SetRight(GetCurMap()->GetRightDoor().x - _doorVerticalHalfSize.x - 48);
			GAME->GetPlayer()->GetObjectTexture()->SetBottom(GetCurMap()->GetRightDoor().y - _doorVerticalHalfSize.y);
		}
		else if (moveY > 0)
		{
			GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos().x = GetCurMap()->GetBottomDoor().x;
			GAME->GetPlayer()->GetObjectTexture()->SetBottom(GetCurMap()->GetBottomDoor().y + _doorVerticalHalfSize.y + 48);
		}
		else if (moveY < 0)
		{
			GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos().x = GetCurMap()->GetBottomDoor().x;
			GAME->GetPlayer()->GetObjectTexture()->SetTop(GetCurMap()->GetTopDoor().y - _doorVerticalHalfSize.y + 48);
		}
		else
		{
			GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos().x = GetCurMap()->GetStartPos().x;
			GAME->GetPlayer()->GetObjectTexture()->SetBottom(GetCurMap()->GetStartPos().y);
		}
		GAME->GetPlayer()->SetSpawnPos(GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos());
	}

	UI_MANAGER->Refresh();
	CAMERA->Update();

	string bgm;

	switch (_maps[_curMapIndex.x][_curMapIndex.y]->GetLevel())
	{
	case 0:
		bgm = "0.Town";
		break;
	case 1:
		bgm = "1.JailField";
		break;
	default:
		break;
	}

	if (SOUND->IsPlaySound(bgm) == false)
	{
		SOUND->StopAll();
		SOUND->Play(bgm);
	}

	_mapDoorDelayTime[index.x][index.y] = 0.0f;

	return;
}

void MapManager::CheckMapMove()
{
	shared_ptr<Collider> doorCollider;
	if (GetCurMap()->CanGoLeft())
	{
		doorCollider = make_shared<RectCollider>(_doorVerticalHalfSize);
		doorCollider->GetPos() = GetCurMap()->GetLeftDoor();
		doorCollider->Update();
		if (doorCollider->IsCollision(GAME->GetPlayer()->GetCollider()))
		{
			SetCurMap({ _curMapIndex.x - 1, _curMapIndex.y });
		}
	}

	if (GetCurMap()->CanGoRight())
	{
		doorCollider = make_shared<RectCollider>(_doorVerticalHalfSize);
		doorCollider->GetPos() = GetCurMap()->GetRightDoor();
		doorCollider->Update();
		if (doorCollider->IsCollision(GAME->GetPlayer()->GetCollider()))
		{
			SetCurMap({ _curMapIndex.x + 1, _curMapIndex.y });
		}
	}

	if (GetCurMap()->CanGoTop())
	{
		doorCollider = make_shared<RectCollider>(_doorHorizonlHalfSize);
		doorCollider->GetPos() = GetCurMap()->GetTopDoor();
		doorCollider->Update();
		if (doorCollider->IsCollision(GAME->GetPlayer()->GetCollider()))
		{
			SetCurMap({ _curMapIndex.x, _curMapIndex.y + 1 });
		}
	}

	if (GetCurMap()->CanGoBottom())
	{
		doorCollider = make_shared<RectCollider>(_doorHorizonlHalfSize);
		doorCollider->GetPos() = GetCurMap()->GetBottomDoor();
		doorCollider->Update();
		if (doorCollider->IsCollision(GAME->GetPlayer()->GetCollider()))
		{
			SetCurMap({ _curMapIndex.x, _curMapIndex.y - 1 });
		}
	}
}

void MapManager::MakeDoorEffect()
{
	for (int i = 0; i < 3; i++)
	{
		if (GetCurMap()->CanGoLeft())
		{
			auto trail = make_shared<Effect_Trail>();
			auto quad = make_shared<Quad>(L"Resource/Effect/LockDoor/DoorEffect.png");
			trail->SetTexture(quad);
			trail->GetPos().x = MathUtility::RandomFloat(GetCurMap()->GetLeftDoor().x - _doorVerticalHalfSize.x, GetCurMap()->GetLeftDoor().x + _doorVerticalHalfSize.x);
			trail->GetPos().y = MathUtility::RandomFloat(GetCurMap()->GetLeftDoor().y - (_doorVerticalHalfSize.y * 0.7), GetCurMap()->GetLeftDoor().y + (_doorVerticalHalfSize.y * 0.7));
			trail->SetAlpha(MathUtility::RandomFloat(0.3f, 0.7f));
			trail->GetObjectTexture()->GetTransform()->GetScale() *= MathUtility::RandomFloat(0.5f, 1.0f);
			trail->SetFadeRatio(0.7f);
			trail->SetDirection({ 1,0 });
			trail->SetSpeed(100.0f);
			GAME->AddEffect(trail);
		}
		if (GetCurMap()->CanGoRight())
		{
			auto trail = make_shared<Effect_Trail>();
			auto quad = make_shared<Quad>(L"Resource/Effect/LockDoor/DoorEffect.png");
			trail->SetTexture(quad);
			trail->GetPos().x = MathUtility::RandomFloat(GetCurMap()->GetRightDoor().x - _doorVerticalHalfSize.x, GetCurMap()->GetRightDoor().x + _doorVerticalHalfSize.x);
			trail->GetPos().y = MathUtility::RandomFloat(GetCurMap()->GetRightDoor().y - (_doorVerticalHalfSize.y * 0.7), GetCurMap()->GetRightDoor().y + (_doorVerticalHalfSize.y * 0.7));
			trail->SetAlpha(MathUtility::RandomFloat(0.3f, 0.7f));
			trail->GetObjectTexture()->GetTransform()->GetScale() *= MathUtility::RandomFloat(0.5f, 1.0f);
			trail->SetFadeRatio(0.7f);
			trail->SetDirection({ -1,0 });
			trail->SetSpeed(100.0f);
			GAME->AddEffect(trail);
		}
		if (GetCurMap()->CanGoTop())
		{
			auto trail = make_shared<Effect_Trail>();
			auto quad = make_shared<Quad>(L"Resource/Effect/LockDoor/DoorEffect.png");
			trail->SetTexture(quad);
			trail->GetPos().x = MathUtility::RandomFloat(GetCurMap()->GetTopDoor().x - _doorVerticalHalfSize.x, GetCurMap()->GetTopDoor().x + _doorVerticalHalfSize.x);
			trail->GetPos().y = MathUtility::RandomFloat(GetCurMap()->GetTopDoor().y - (_doorVerticalHalfSize.y * 0.7), GetCurMap()->GetTopDoor().y + (_doorVerticalHalfSize.y * 0.7));
			trail->SetAlpha(MathUtility::RandomFloat(0.3f, 0.7f));
			trail->GetObjectTexture()->GetTransform()->GetScale() *= MathUtility::RandomFloat(0.5f, 1.0f);
			trail->SetFadeRatio(0.7f);
			trail->SetDirection({ 0,-1 });
			trail->SetSpeed(100.0f);
			GAME->AddEffect(trail);
		}
		if (GetCurMap()->CanGoBottom())
		{
			auto trail = make_shared<Effect_Trail>();
			auto quad = make_shared<Quad>(L"Resource/Effect/LockDoor/DoorEffect.png");
			trail->SetTexture(quad);
			trail->GetPos().x = MathUtility::RandomFloat(GetCurMap()->GetBottomDoor().x - _doorVerticalHalfSize.x, GetCurMap()->GetBottomDoor().x + _doorVerticalHalfSize.x);
			trail->GetPos().y = MathUtility::RandomFloat(GetCurMap()->GetBottomDoor().y - (_doorVerticalHalfSize.y * 0.7), GetCurMap()->GetBottomDoor().y + (_doorVerticalHalfSize.y * 0.7));
			trail->SetAlpha(MathUtility::RandomFloat(0.3f, 0.7f));
			trail->GetObjectTexture()->GetTransform()->GetScale() *= MathUtility::RandomFloat(0.5f, 1.0f);
			trail->SetFadeRatio(0.7f);
			trail->SetDirection({ 0,1 });
			trail->SetSpeed(100.0f);
			GAME->AddEffect(trail);
		}
	}
}

MapManager::MapManager()
{
	SOUND->Add("0.Town", "Resource/Sound/Bgm/0.Town.wav", true);
	SOUND->Add("1.JailField", "Resource/Sound/Bgm/1.JailField.wav", true);
	_mapSize.resize(9);

	// 현재 프로젝트 경로 구하기
	char path[1000];
	_getcwd(path, 1000);
	
	_path = CharToStr(path, 1000);
	_path += "\\";

	// 맵 갯수 구하기
	for (int level = 0; level < 9; level++)
	{
		for (int num = 0; num < 30; num++)
		{
			string sLoadPath = _path + "Save\\Maps\\Level_";

			wstring levelPath;
			{
				if (level < 10)
					levelPath += L"0";

				levelPath += to_wstring(level);
			}
			wstring numPath;
			{
				if (num < 10)
					numPath += L"0";

				numPath += to_wstring(num);
			}
			sLoadPath += WstrToStr(levelPath) + "_" + WstrToStr(numPath);

			ifstream checkPath1(sLoadPath + ".bin");
			ifstream checkPath2(sLoadPath + "_Basic" + ".bin");

			if (checkPath1 && checkPath2)
			{
				_mapSize[level].push_back(num);
			}
		}
	}
}

MapManager::~MapManager()
{
}
