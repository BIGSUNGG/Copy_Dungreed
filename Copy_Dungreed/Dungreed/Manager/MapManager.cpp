#include "framework.h"
#include "MapManager.h"

MapManager* MapManager::_instance = nullptr;

void MapManager::Update()
{
}

void MapManager::MakeRandomMap(int level, int num)
{	
	_maps[0][0] = Load(level, level);
	bool leftDoor = (_maps[0][0]->GetLeftDoor() != Vector2(INT_MAX, INT_MAX));
	bool rightDoor = (_maps[0][0]->GetRightDoor() != Vector2(INT_MAX, INT_MAX));
	bool topDoor = (_maps[0][0]->GetTopDoor() != Vector2(INT_MAX, INT_MAX));
	bool bottomDoor = (_maps[0][0]->GetBottomDoor() != Vector2(INT_MAX, INT_MAX));

	SetCurMap({ 0,0 });
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
				mapInfo.push_back((int)object->GetTexture()->GetTransform()->GetPos().x);
				mapInfo.push_back((int)object->GetTexture()->GetTransform()->GetPos().y);
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
	for (auto& monster : _maps[_curMapIndex.first][_curMapIndex.second]->GetObjects()[Object::CREATURE])
	{
		auto creature = dynamic_pointer_cast<Creature>(monster);
		if (creature->GetCreatureType() == Creature::ENEMY)
		{
			auto enemy = dynamic_pointer_cast<Monster>(creature);
			enemy->SetTarget(target);
		}
	}
}

void MapManager::SetCurMap(shared_ptr<Map> map)
{
	_maps[_curMapIndex.first][_curMapIndex.second] = map;
	GAME->SetMap(_maps[_curMapIndex.first][_curMapIndex.second]);
	GAME->GetObjectUpdate() = false;
	GAME->Update();
	GAME->GetObjectUpdate() = true;

	return;
}

void MapManager::SetCurMap(const pair<int,int>& index)
{
	_curMapIndex = index;
	GAME->SetMap(_maps[_curMapIndex.first][_curMapIndex.second]);
	GAME->GetObjectUpdate() = false;
	GAME->Update();
	GAME->GetObjectUpdate() = true;

	return;
}

MapManager::MapManager()
{
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
