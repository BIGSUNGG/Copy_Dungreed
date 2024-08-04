#include "framework.h"
#include "MapManager.h"
#include "Dungreed/Object/Object.h"

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

	// Maps �ʱ�ȭ
	for (int x = -_mapSize.x; x <= _mapSize.x; x++)
	{
		for (int y = -_mapSize.y; y <= _mapSize.y; y++)
		{
			_maps[x][y] = pair;
		}
	}

	// �⺻ �� �߰�
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

	// �̵������� �� �߰�
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

	// �̵������� �ʿ� ������ �� ����
	for (int x = -_mapSize.x; x <= _mapSize.x; x++)
	{
		for (int y = -_mapSize.y; y <= _mapSize.y; y++)
		{
			if (_maps[x][y].second == false)
				continue;

			if (_maps[x][y].first != nullptr)
				continue;

			auto rightMap = _maps[x + 1][y];
			auto leftMap = _maps[x - 1][y];
			auto topMap = _maps[x][y + 1];
			auto bottomMap = _maps[x][y - 1];

			bool goRight = false;
			bool goLeft = false;
			bool goTop = false;
			bool goBottom = false;

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
			// ������ �� ã��
			while (true)
			{

				mapNum = (rand() % (_mapList[level].size() - 1)) + 1;
				info = LoadBasicInfo(level, mapNum);

				if (info.CanGoLeft() != goLeft)
					continue;
				if (info.CanGoRight() != goRight)
					continue;
				if (info.CanGoTop() != goTop)
					continue;
				if (info.CanGoBottom() != goBottom)
					continue;

				auto map = Load(level, mapNum);
				AddMap(map, { x,y });
				break;
			}
		}
	}
	SetCurMap({ 0,0 });
}

bool MapManager::IsMapFileExist(int level, int num)
{
	ifstream checkPath1(GetMapBasicInfoFileSPath(level, num));
	ifstream checkPath2(GetMapObjectsFileSPath(level, num));

	if (!checkPath1)
		return false;

	if (!checkPath2)
		return false;

	return true;
}

std::wstring MapManager::GetMapBasicInfoFileWPath(int level, int num)
{
	wstring result = L"Save/Maps/Level_";
	wstring levelStr;
	{
		if (level < 10)
			levelStr += L"0";

		levelStr += to_wstring(level);
	}
	wstring numStr;
	{
		if (num < 10)
			numStr += L"0";

		numStr += to_wstring(num);
	}
	result += levelStr + L"_" + numStr + L"_Basic" + L".bin";
	return result;
}

std::string MapManager::GetMapBasicInfoFileSPath(int level, int num)
{
	string result = GetCurPath() + "Save\\Maps\\Level_";
	string levelPath;
	{
		if (level < 10)
			levelPath += "0";

		levelPath += to_string(level);
	}
	string numPath;
	{
		if (num < 10)
			numPath += "0";

		numPath += to_string(num);
	}
	result += levelPath + "_" + numPath + "_Basic" + ".bin";
	return result;
}

std::wstring MapManager::GetMapObjectsFileWPath(int level, int num)
{
	wstring result = L"Save/Maps/Level_";
	wstring levelStr;
	{
		if (level < 10)
			levelStr += L"0";

		levelStr += to_wstring(level);
	}
	wstring numStr;
	{
		if (num < 10)
			numStr += L"0";

		numStr += to_wstring(num);
	}
	result += levelStr + L"_" + numStr + L".bin";
	return result;
}

std::string MapManager::GetMapObjectsFileSPath(int level, int num)
{
	string result = GetCurPath() + "Save\\Maps\\Level_";
	string levelPath;
	{
		if (level < 10)
			levelPath += "0";

		levelPath += to_string(level);
	}
	string numPath;
	{
		if (num < 10)
			numPath += "0";

		numPath += to_string(num);
	}
	result += levelPath + "_" + numPath + ".bin";
	return result;
}

shared_ptr<Map> MapManager::Load(int level, int num)
{
	shared_ptr<Map> newMap = make_shared<Map>(level, num);

	if (IsMapFileExist(level, num)) // 불러올 파일이 있는지
	{
		// 맵 정보 불러오기
		MapBasic basicInfo = LoadBasicInfo(level, num);
		newMap->GetLeftBottom() = basicInfo._leftBottom;
		newMap->GetRightTop() = basicInfo._rightTop;
		newMap->GetStartPos() = basicInfo._startPos;

		newMap->GetTopDoor() = basicInfo._topDoor;
		newMap->GetBottomDoor() = basicInfo._bottomDoor;
		newMap->GetLeftDoor() = basicInfo._leftDoor;
		newMap->GetRightDoor() = basicInfo._rightDoor;

		// 오브젝트 정보 불러오기
		vector<shared_ptr<Object>> objects = LoadObjects(level, num, basicInfo._objectCount);
		for (shared_ptr<Object> object : objects)
			newMap->AddObject(object, object->GetType());
	}

	return newMap;
}

MapBasic MapManager::LoadBasicInfo(int level, int num)
{
	MapBasic result;

	// Load Basic
	{
		BinaryReader basicReader(GetMapBasicInfoFileWPath(level, num));
		UINT size = basicReader.Uint();

		const int basicInfoSize = 60;
		unsigned char basicInfo[basicInfoSize];
		void* ptr = &basicInfo;
		basicReader.Byte(&ptr, size);

		int offset = 0;

		memcpy(const_cast<int*>(&result._objectCount), basicInfo + offset, sizeof(int));
		offset += sizeof(int);
		memcpy(const_cast<Vector2*>(&result._leftBottom), basicInfo + offset, sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(const_cast<Vector2*>(&result._rightTop), basicInfo + offset, sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(const_cast<Vector2*>(&result._startPos), basicInfo + offset, sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(const_cast<Vector2*>(&result._topDoor), basicInfo + offset, sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(const_cast<Vector2*>(&result._bottomDoor), basicInfo + offset, sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(const_cast<Vector2*>(&result._leftDoor), basicInfo + offset, sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(const_cast<Vector2*>(&result._rightDoor), basicInfo + offset, sizeof(Vector2));
		offset += sizeof(Vector2);
	}

	return result;
}

std::vector<std::shared_ptr<Object>> MapManager::LoadObjects(int level, int num, int objectCount)
{
	vector<shared_ptr<Object>> result;
	result.reserve(objectCount);

	// Load Objects
	{
		BinaryReader mapReader(GetMapObjectsFileWPath(level, num));
		UINT size = mapReader.Uint();

		vector<unsigned char> objectsInfo(size);
		void* ptr = objectsInfo.data();
		mapReader.Byte(&ptr, size);

		int offset = 0;
		for (int i = 0; i < objectCount; i++)
		{
			Object::Object_Type type;
			int level;
			int num;
			Vector2 spawnPos;
			bool isReversed;

			memcpy(&type, objectsInfo.data() + offset, sizeof(Object::Object_Type));
			offset += sizeof(Object::Object_Type);
			memcpy(&level, objectsInfo.data() + offset, sizeof(int));
			offset += sizeof(int);
			memcpy(&num, objectsInfo.data() + offset, sizeof(int));
			offset += sizeof(int);
			memcpy(&spawnPos, objectsInfo.data() + offset, sizeof(Vector2));
			offset += sizeof(Vector2);
			memcpy(&isReversed, objectsInfo.data() + offset, sizeof(bool));
			offset += sizeof(bool);

			shared_ptr<Object> object = MAKE_OBJECT(type, level, num);
			object->SetSpawnPos(spawnPos);

			if (isReversed == true)
				object->ReverseTexture();

			object->GetObjectTexture()->Update();
			object->GetCollider()->Update();

			result.emplace_back(object);
		}
	}

	return result;
}

void MapManager::Save(shared_ptr<Map> map)
{
	const int& level = map->GetLevel();
	const int& num = map->GetNum();

	// 덮어쓸 파일이 없다면
	if (IsMapFileExist(level, num) == false)
	{
		// 파일 생성
		ofstream makeBasicFile(GetMapBasicInfoFileSPath(level, num));
		ofstream makeObjectsFile(GetMapObjectsFileSPath(level, num));
		_mapList[level].emplace_back(num);
	}

	for (auto& objects : map->GetObjects())
	{
		for (auto& object : objects)
		{
			if (object == nullptr)
				map->DeleteObject(object);
		}
	}

	// 맵 기본 정보 저장
	{
		BinaryWriter basicWriter(GetMapBasicInfoFileWPath(level, num));

		const int basicInfoSize = 60;
		unsigned char basicInfo[basicInfoSize];
		int offset = 0;

		memcpy(basicInfo + offset, const_cast<int*>(&map->GetObjectCount()), sizeof(int));
		offset += sizeof(int);
		memcpy(basicInfo + offset, const_cast<Vector2*>(&map->GetLeftBottom()), sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(basicInfo + offset, const_cast<Vector2*>(&map->GetRightTop()), sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(basicInfo + offset, const_cast<Vector2*>(&map->GetStartPos()), sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(basicInfo + offset, const_cast<Vector2*>(&map->GetTopDoor()), sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(basicInfo + offset, const_cast<Vector2*>(&map->GetBottomDoor()), sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(basicInfo + offset, const_cast<Vector2*>(&map->GetLeftDoor()), sizeof(Vector2));
		offset += sizeof(Vector2);
		memcpy(basicInfo + offset, const_cast<Vector2*>(&map->GetRightDoor()), sizeof(Vector2));
		offset += sizeof(Vector2);

		basicWriter.Uint(basicInfoSize);
		basicWriter.Byte(basicInfo, basicInfoSize);
	}

	// 오브젝트 정보 저장
	{
		BinaryWriter mapWriter(GetMapObjectsFileWPath(level, num));

		const int objectsInfoSize = map->GetObjectCount() * 18;
		vector<unsigned char> objectsInfo(objectsInfoSize);
		int offset = 0;

		for (int i = Object::Object_Type::BACKGROUND; i <= Object::Object_Type::CREATURE; i++)
		{
			for (auto& object : map->GetObjects()[i])
			{
				memcpy(objectsInfo.data() + offset, const_cast<Object::Object_Type*>(&object->GetType()), sizeof(Object::Object_Type));
				offset += sizeof(Object::Object_Type);
				memcpy(objectsInfo.data() + offset, const_cast<int*>(&object->GetLevel()), sizeof(int));
				offset += sizeof(int);
				memcpy(objectsInfo.data() + offset, const_cast<int*>(&object->GetNum()), sizeof(int));
				offset += sizeof(int);
				memcpy(objectsInfo.data() + offset, const_cast<Vector2*>(&object->GetObjectTexture()->GetTransform()->GetPos()), sizeof(Vector2));
				offset += sizeof(Vector2);

				bool isReversed = object->IsReversed();
				memcpy(objectsInfo.data() + offset, const_cast<bool*>(&isReversed), sizeof(bool));
				offset += sizeof(bool);
			}
		}

		mapWriter.Uint(objectsInfoSize);
		mapWriter.Byte(objectsInfo.data(), objectsInfoSize);
	}
}

void MapManager::SaveAll()
{
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
		GAME->SetPlayer(GAME->GetPlayer());
		GAME->GetPlayer()->GetObjectTexture()->Update();
		GAME->GetPlayer()->GetCollider()->Update();
		if (moveX > 0)
		{
			GAME->GetPlayer()->GetObjectTexture()->SetLeft(GetCurMap()->GetLeftDoor().x + _doorVerticalHalfSize.x + 30);
			GAME->GetPlayer()->GetObjectTexture()->SetBottom(GetCurMap()->GetLeftDoor().y - _doorVerticalHalfSize.y);
		}
		else if (moveX < 0)
		{
			GAME->GetPlayer()->GetObjectTexture()->SetRight(GetCurMap()->GetRightDoor().x - _doorVerticalHalfSize.x - 30);
			GAME->GetPlayer()->GetObjectTexture()->SetBottom(GetCurMap()->GetRightDoor().y - _doorVerticalHalfSize.y);
		}
		else if (moveY > 0)
		{
			GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos().x = GetCurMap()->GetBottomDoor().x;
			GAME->GetPlayer()->GetObjectTexture()->SetBottom(GetCurMap()->GetBottomDoor().y + _doorVerticalHalfSize.y + 30);
		}
		else if (moveY < 0)
		{
			GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos().x = GetCurMap()->GetTopDoor().x;
			GAME->GetPlayer()->GetObjectTexture()->SetTop(GetCurMap()->GetTopDoor().y - _doorVerticalHalfSize.y - 30);
		}
		else
		{
			GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos().x = GetCurMap()->GetStartPos().x;
			GAME->GetPlayer()->GetObjectTexture()->SetBottom(GetCurMap()->GetStartPos().y);
		}
		GAME->GetPlayer()->SetSpawnPos(GAME->GetPlayer()->GetObjectTexture()->GetTransform()->GetPos());
		//GAME->GetPlayer()->StopMove();
		GAME->GetPlayer()->GetObjectTexture()->Update();
		GAME->GetPlayer()->GetCollider()->Update();
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
	SOUND->Add("0.Town", "Resource/Sound/Bgm/0.Town.wav", true, true);
	SOUND->Add("ambience_town", "Resource/Sound/Bgm/ambience_town.wav", true, false);
	SOUND->Add("1.JailField", "Resource/Sound/Bgm/1.JailField.wav", true, true);
	SOUND->Add("ambience_prison", "Resource/Sound/Bgm/ambience_prison.wav", true, false);

	// �� ���� ���ϱ�
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
