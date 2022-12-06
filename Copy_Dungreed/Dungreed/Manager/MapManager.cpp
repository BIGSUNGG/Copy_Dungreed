#include "framework.h"
#include "MapManager.h"

MapManager* MapManager::_instance = nullptr;

void MapManager::Update()
{
}

void MapManager::MakeRandomMap(int level, int num)
{	
	_maps.clear();
	_mapCount = 0;
	_curMapIndex = { 0,0 };

	pair<shared_ptr<Map>, bool> pair = { nullptr,false };

	// Maps 초기화
	for (int x = -_mapSize.x; x <= _mapSize.x; x++)
	{
		for (int y = -_mapSize.y; y <= _mapSize.y; y++)
		{
			_maps[x][y] = pair;
		}
	}

	// 기본 맵 추가
	shared_ptr<Map> map = Load(level, num);
	AddMap(map, Vector2(0, 0));

	int tempMapCount = 0;
	if (map->CanGoTop())
	{
		_maps[1][0].second = true;
		tempMapCount++;
	}
	if (map->CanGoBottom())
	{
		_maps[0][-1].second = true;
		tempMapCount++;
	}
	if (map->CanGoLeft())
	{
		_maps[-1][0].second = true;
		tempMapCount++;
	}
	if (map->CanGoRight())
	{
		_maps[0][1].second = true;
		tempMapCount++;
	}

	// 이동가능한 맵 추가
	while (tempMapCount <= _mapCountMax)
	{
		Vector2 index = { MathUtility::RandomInt(-_mapSize.x,_mapSize.x),MathUtility::RandomInt(-_mapSize.y,_mapSize.y) };
		if (_maps[index.x][index.y].second == true)
			continue;

		if (_maps[index.x + 1][index.y].second == true || _maps[index.x - 1][index.y].second == true ||
			_maps[index.x][index.y + 1].second == true || _maps[index.x][index.y - 1].second == true)
		{
			_maps[index.x][index.y].second = true;
			tempMapCount++;
		}
	}

	// 이동가능한 맵에 적절한 맵 삽입
	for (int x = -_mapSize.x; x <= _mapSize.x; x++)
	{
		for (int y = -_mapSize.y; y <= _mapSize.y; y++)
		{
			if(_maps[x][y].second == false)
				continue;

			if(_maps[x][y].first != nullptr)
				continue;

			auto rightMap = _maps[x + 1][y];
			auto leftMap = _maps[x - 1][y];
			auto topMap = _maps[x][y + 1];
			auto bottomMap = _maps[x][y - 1];

			bool goRight	= false;
			bool goLeft		= false;
			bool goTop		= false;
			bool goBottom	= false;

			if (rightMap.second)
			{
				if (rightMap.first != nullptr && rightMap.first->CanGoLeft())
					goRight = true;
				else if (rightMap.first == nullptr)
					goRight = true;
			}

			if (leftMap.second)
			{
				if (leftMap.first != nullptr && leftMap.first->CanGoRight())
					goLeft = true;
				else if (leftMap.first == nullptr)
					goLeft = true;
			}

			if (topMap.second)
			{
				if (topMap.first != nullptr && topMap.first->CanGoBottom())
					goTop = true;
				else if (topMap.first == nullptr)
					goTop = true;
			}

			if (bottomMap.second)
			{
				if (bottomMap.first != nullptr && bottomMap.first->CanGoTop())
					goBottom = true;
				else if (bottomMap.first == nullptr)
					goBottom = true;
			}

			int mapNum;
			MapBasic info;
			// 적당한 맵 찾기
			while (true)
			{

				mapNum = (rand() % (_mapList[level].size() - 1)) + 1;
				info = LoadBasicInfo(level, mapNum);

				if (info.CanGoLeft()	!= goLeft)
					continue;
				if (info.CanGoRight()	!= goRight)
					continue;
				if (info.CanGoTop()		!= goTop)
					continue;
				if (info.CanGoBottom()	!= goBottom)
					continue;

				auto map = Load(level, mapNum);
				AddMap(map, { x,y });
				break;
			}
		}
	}
	SetCurMap({ 0,0 });
}

shared_ptr<Map> MapManager::Load(int level, int num)
{
	shared_ptr<Map> newMap = make_shared<Map>(level,num);
	wstring wLoadPath = L"Save/Maps/Level_";
	string sLoadPath = GetCurPath() + "Save\\Maps\\Level_";

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

			vector<float> mapInfo;
			int info = 6;
			int infoCount = objectCount * info;
			mapInfo.resize(infoCount);
			void* ptr = mapInfo.data();
			mapReader.Byte(&ptr, size * sizeof(float));

			for (int i = 0; i < objectCount; i++)
			{
				int cur = i * info;

				shared_ptr<Object> object = MAKE_OBJECT(mapInfo[cur], mapInfo[cur + 1], mapInfo[cur + 2]);

				object->SetSpawnPos(Vector2(mapInfo[cur + 3], mapInfo[cur + 4]));

				if (mapInfo[cur + 5] == 1)
					object->ReverseTexture();

				object->GetObjectTexture()->Update();
				object->GetCollider()->Update();
				newMap->AddObject(object, mapInfo[cur]);
			}
		}
	}
	else
		newMap = make_shared<Map>(level, num);

	return newMap;
}

MapBasic MapManager::LoadBasicInfo(int level, int num)
{
	MapBasic info;
	wstring wLoadPath = L"Save/Maps/Level_";
	string sLoadPath = GetCurPath() + "Save\\Maps\\Level_";

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

	int objectCount;
	{
		BinaryReader basicReader(wLoadPath + L"_Basic" + L".bin");

		UINT size = basicReader.Uint();

		vector<int> basicInfo;
		basicInfo.resize(15);
		void* ptr = basicInfo.data();
		basicReader.Byte(&ptr, size * sizeof(int));

		objectCount = basicInfo[0];

		info._leftBottom	=  Vector2(basicInfo[1], basicInfo[2]);
		info._rightDoor		= Vector2(basicInfo[3], basicInfo[4]);
		info._startPos		= Vector2(basicInfo[5], basicInfo[6]);

		info._topDoor		= Vector2(basicInfo[7], basicInfo[8]);
		info._bottomDoor	= Vector2(basicInfo[9], basicInfo[10]);
		info._leftDoor		= Vector2(basicInfo[11], basicInfo[12]);
		info._rightDoor		= Vector2(basicInfo[13], basicInfo[14]);
	}

	return info;
}

void MapManager::Save(shared_ptr<Map> map)
{
	const int& level = map->GetLevel();
	const int& num = map->GetNum();

	wstring wLoadPath = L"Save/Maps/Level_";
	string sLoadPath = GetCurPath() + "Save\\Maps\\Level_";

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
			_mapList[level].emplace_back(num);
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

		vector<float> mapInfo;

		for (auto& objects : map->GetObjects())
		{
			for (auto& object : objects)
			{
				mapInfo.push_back((float)object->GetType());
				mapInfo.push_back((float)object->GetLevel());
				mapInfo.push_back((float)object->GetNum());
				mapInfo.push_back((float)object->GetObjectTexture()->GetTransform()->GetPos().x);
				mapInfo.push_back((float)object->GetObjectTexture()->GetTransform()->GetPos().y);
				mapInfo.push_back((float)object->IsReversed());
			}
		}

		mapWriter.Uint(mapInfo.size());
		mapWriter.Byte(mapInfo.data(), mapInfo.size() * sizeof(float));
	}
}

void MapManager::SaveAll()
{
	// Save Load방식의 변경점이 있을때 편하게 쓰기 위해
	for (int level = 0; level < _mapList.size(); level++)
	{
		for (int num = 0; num < _mapList[level].size(); num++)
		{
			shared_ptr<Map> temp = Load(level, _mapList[level][num]);
			Save(temp);
		}
	}
}

void MapManager::SetTarget(shared_ptr<Creature> target)
{
	for (auto& monster : _maps[_curMapIndex.x][_curMapIndex.y].first->GetObjects()[Object::CREATURE])
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
	_maps[_curMapIndex.x][_curMapIndex.y].first = map;
	SetCurMap(_curMapIndex);

	return;
}

void MapManager::SetCurMap(const Vector2& index)
{
	int moveX = index.x - _curMapIndex.x;
	int moveY = index.y - _curMapIndex.y;
	_curMapIndex = index;
	GAME->SetCurMap(_maps[_curMapIndex.x][_curMapIndex.y].first);
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
			GAME->GetPlayer()->GetObjectTexture()->SetBottom(GetCurMap()->GetBottomDoor().y + _doorVerticalHalfSize.y + 96);
		}
		else if (moveY < 0)
		{
			GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos().x = GetCurMap()->GetTopDoor().x;
			GAME->GetPlayer()->GetObjectTexture()->SetTop(GetCurMap()->GetTopDoor().y - _doorVerticalHalfSize.y + 96);
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
	string ambience;

	switch (_maps[_curMapIndex.x][_curMapIndex.y].first->GetLevel())
	{
	case 0:
		bgm = "0.Town";
		ambience = "ambience_town";
		UI_MANAGER->SetPostProssesing({ 0,0,0,0 });
		break;
	case 1:
		UI_MANAGER->SetPostProssesing({ 0,0,0,0.3f });
		bgm = "1.JailField";
		ambience = "ambience_prison";
		break;
	default:
		break;
	}

	if (SOUND->IsPlaySound(bgm) == false)
	{
		SOUND->StopAll();
		SOUND->Play(bgm);
		SOUND->Play(ambience);
	}

	return;
}

void MapManager::AddMap(shared_ptr<Map> map, Vector2 where)
{
	if (_maps[where.x][where.y].first != nullptr)
		return;

	_mapCount++;
	_maps[where.x][where.y].first = map;
	_maps[where.x][where.y].second = true;

	map->CheckCleared();

	if (map->CanGoLeft())
	{
		auto door = make_shared<LockDoorLeft>();
		door->SetSpawnPos(map->GetLeftDoor());

		map->AddObject(door, Object::TILE);
	}
	if (map->CanGoRight())
	{
		auto door = make_shared<LockDoorRight>();
		door->SetSpawnPos(map->GetRightDoor());

		map->AddObject(door, Object::TILE);
	}
	if (map->CanGoTop())
	{
		auto door = make_shared<LockDoorTop>();
		door->SetSpawnPos(map->GetTopDoor());

		map->AddObject(door, Object::TILE);
	}
	if (map->CanGoBottom())
	{
		auto door = make_shared<LockDoorBottom>();
		door->SetSpawnPos(map->GetBottomDoor());

		map->AddObject(door, Object::TILE);
	}
}

MapManager::MapManager()
{
	SOUND->Add("0.Town", "Resource/Sound/Bgm/0.Town.wav",true, true);
	SOUND->Add("ambience_town", "Resource/Sound/Bgm/ambience_town.wav",true, false);
	SOUND->Add("1.JailField", "Resource/Sound/Bgm/1.JailField.wav", true,true);
	SOUND->Add("ambience_prison", "Resource/Sound/Bgm/ambience_prison.wav",true, false);

	// 맵 갯수 구하기
	for (int level = 0; level < 9; level++)
	{
		for (int num = 0; num < 30; num++)
		{
			string sLoadPath = GetCurPath() + "Save\\Maps\\Level_";

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

			bool checkPath1 = CheckFileExist(sLoadPath + ".bin");
			bool checkPath2 = CheckFileExist(sLoadPath + "_Basic" + ".bin");

			if (checkPath1 && checkPath2)
			{
				_mapList[level].push_back(num);
			}
		}
	}
}

MapManager::~MapManager()
{
}
