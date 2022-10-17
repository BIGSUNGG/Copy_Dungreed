#include "framework.h"
#include "MapManager.h"

MapManager* MapManager::_instance = nullptr;

void MapManager::Update()
{
	GetCurMap()->CheckCleared();
}

void MapManager::MakeRandomMap(int level, int num)
{	
	_maps.clear();

	shared_ptr<Map> map = Load(level, num);
	AddMap(map, Vector2(0, 0));
	
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

			AddMap(map, Vector2(x, y));

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

			AddMap(map, Vector2(x, y));

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

			AddMap(map, Vector2(x, y));

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

			AddMap(map, Vector2(x, y));

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

	return;
}

void MapManager::AddMap(shared_ptr<Map> map, Vector2 where)
{
	if (_maps[where.x][where.y] != nullptr)
		return;

	_maps[where.x][where.y] = map;

	map->CheckCleared();

	if (map->CanGoLeft())
	{
		auto door = make_shared<LockDoorLeft>();
		door->SetSpawnPos(map->GetLeftDoor());
		if (map->GetCleared() == true)
			door->Open();
		map->AddObject(door, Object::TILE);
	}
	if (map->CanGoRight())
	{
		auto door = make_shared<LockDoorRight>();
		door->SetSpawnPos(map->GetRightDoor());
		if (map->GetCleared() == true)
			door->Open();
		map->AddObject(door, Object::TILE);
	}
	if (map->CanGoTop())
	{
		auto door = make_shared<LockDoorTop>();
		door->SetSpawnPos(map->GetRightDoor());
		if (map->GetCleared() == true)
			door->Open();
		map->AddObject(door, Object::TILE);
	}
	if (map->CanGoBottom())
	{
		auto door = make_shared<LockDoorBottom>();
		door->SetSpawnPos(map->GetRightDoor());
		if (map->GetCleared() == true)
			door->Open();
		map->AddObject(door, Object::TILE);
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
