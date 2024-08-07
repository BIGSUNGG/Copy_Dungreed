#include "framework.h"
#include "MapManager.h"
#include "Dungreed/Object/Object.h"

MapManager* MapManager::_instance = nullptr;

void MapManager::Update()
{
}

void MapManager::MakeRandomMap(int level, int num)
{
	// 미로 초기화	
	_maps.clear();
	_mapCount = 0;
	_curMapPos = { 0,0 };

	for (int x = -_mapHalfSize.x; x <= _mapHalfSize.x; x++)
	{
		for (int y = -_mapHalfSize.y; y <= _mapHalfSize.y; y++)
		{
			_maps[x][y] = nullptr;
		}
	}

	vector<MapBasic> curLevelMapList;
	curLevelMapList.reserve(_mapList[level].size() - 1);
	for (int i = 1; i < _mapList[level].size(); i++)
	{
		int num = _mapList[level][i];
		MapBasic info = LoadBasicInfo(level, num);
		curLevelMapList.push_back(info);
	}

	// 기본 맵 추가
	shared_ptr<Map> curMap = LoadMap(level, num);
	const Vector2 startPos = { 0, 0 };
	Vector2 curPos = startPos;
	AddMap(curMap, curPos);
	queue<Vector2> visitQueue;

	while (true)
	{
		// 최근 추가된 맵에서 갈 수 있는 위치 추가
		if (curMap)
		{
			if (curMap->CanGoTop())
				visitQueue.push(curPos + Vector2(0, 1));
			if (curMap->CanGoBottom())
				visitQueue.push(curPos + Vector2(0, -1));
			if (curMap->CanGoLeft())
				visitQueue.push(curPos + Vector2(-1, 0));
			if (curMap->CanGoRight())
				visitQueue.push(curPos + Vector2(1, 0));

			curMap = nullptr;
		}

		if (visitQueue.size() <= 0) // 더 이상 맵을 놓을 수 없다면
			break;

		curPos = visitQueue.front();
		visitQueue.pop();
		if (_maps[curPos.x][curPos.y] != nullptr) // 현재 있는 위치에 맵이 이미 있다면
			continue;

		// 맵을 충분히 추가했다면
		if (_mapCount >= _mapCountMin) 
		{
			// 공백에 연결되어있는 맵 찾기
			queue<Vector2> visitQueue;
			unordered_map<int, unordered_map<int, bool>> visited;
			Vector2 curPos = startPos;
			shared_ptr<Map> curMap = _maps[startPos.x][startPos.y];

			while (true)
			{
				// 최근 추가된 맵에서 갈 수 있는 위치 추가
				if (curMap)
				{
					if (curMap->CanGoTop())
						visitQueue.push(curPos + Vector2(0, 1));
					if (curMap->CanGoBottom())
						visitQueue.push(curPos + Vector2(0, -1));
					if (curMap->CanGoLeft())
						visitQueue.push(curPos + Vector2(-1, 0));
					if (curMap->CanGoRight())
						visitQueue.push(curPos + Vector2(1, 0));

					curMap = nullptr;
				}

				if(visitQueue.size() <= 0) // 더 이상 확인할 맵이 없다면
					break;

				curPos = visitQueue.front();
				visitQueue.pop();

				if(visited[curPos.x][curPos.y] == true) // 이미 확인한 위치라면
					continue;

				visited[curPos.x][curPos.y] = true;

				curMap = _maps[curPos.x][curPos.y];
				if (curMap == nullptr) // 현재 있는 위치에 맵이 없다면
				{
					// 연결되야하는 방향 구하기
					bool shouldCanGoTop = _maps[curPos.x][curPos.y + 1] ? _maps[curPos.x][curPos.y + 1]->CanGoBottom() : false;
					bool shouldCanGoBottom = _maps[curPos.x][curPos.y - 1] ? _maps[curPos.x][curPos.y - 1]->CanGoTop() : false;
					bool shouldCanGoLeft = _maps[curPos.x - 1][curPos.y] ? _maps[curPos.x - 1][curPos.y]->CanGoRight() : false;
					bool shouldCanGoRight = _maps[curPos.x + 1][curPos.y] ? _maps[curPos.x + 1][curPos.y]->CanGoLeft() : false;

					// 적절한 맵 구하기
					MapBasic* info = nullptr;
					while (true)
					{
						// 랜덤한 맵 구하기
						info = &curLevelMapList[MathUtility::RandomInt(0, curLevelMapList.size() - 1)];

						// 맵이 필요한 조건에 맞는지
						if (shouldCanGoTop != info->CanGoTop())
							continue;
						if (shouldCanGoBottom != info->CanGoBottom())
							continue;
						if (shouldCanGoLeft != info->CanGoLeft())
							continue;
						if (shouldCanGoRight != info->CanGoRight())
							continue;

						curMap = LoadMap(info->_level, info->_num);
						AddMap(curMap, curPos);
						break;
					}
				}
			}
			break;
		}

		// 해당 방향으로 무조건 연결되어야하는지 확인
		bool shouldCanGoTop = _maps[curPos.x][curPos.y + 1] ? _maps[curPos.x][curPos.y + 1]->CanGoBottom() : false;
		bool shouldCanGoBottom = _maps[curPos.x][curPos.y - 1] ? _maps[curPos.x][curPos.y - 1]->CanGoTop() : false;
		bool shouldCanGoLeft = _maps[curPos.x - 1][curPos.y] ? _maps[curPos.x - 1][curPos.y]->CanGoRight() : false;
		bool shouldCanGoRight = _maps[curPos.x + 1][curPos.y] ? _maps[curPos.x + 1][curPos.y]->CanGoLeft() : false;

		// 적절한 맵 구하기
		MapBasic* info = nullptr;
		while (true)
		{
			// 랜덤한 맵 구하기
			info = &curLevelMapList[MathUtility::RandomInt(0, curLevelMapList.size() - 1)];

			// 맵이 필요한 조건에 맞는지
			if (shouldCanGoTop && info->CanGoTop() == false)
				continue;
			if (shouldCanGoBottom && info->CanGoBottom() == false)
				continue;
			if (shouldCanGoLeft && info->CanGoLeft() == false)
				continue;
			if (shouldCanGoRight && info->CanGoRight() == false)
				continue;

			// 맵에서 이동할 수 있는 위치가 맵의 크기를 넘는다면
			if (info->CanGoTop() && curPos.y >= _mapHalfSize.y)
				continue;
			if (info->CanGoBottom() && curPos.y <= -_mapHalfSize.y)
				continue;
			if (info->CanGoRight() && curPos.x >= _mapHalfSize.x)
				continue;
			if (info->CanGoLeft() && curPos.x <= -_mapHalfSize.x)
				continue;

			// 맵에서 이동할 수 있는 맵이 있고 그 맵과 이어지지않다면
			shared_ptr<Map> topMap    = _maps[curPos.x][curPos.y + 1];
			shared_ptr<Map> bottomMap = _maps[curPos.x][curPos.y - 1];
			shared_ptr<Map> rightMap  = _maps[curPos.x + 1][curPos.y];
			shared_ptr<Map> leftMap   = _maps[curPos.x - 1][curPos.y];

			if(info->CanGoTop() && topMap && topMap->CanGoBottom() == false)
				continue;
			if (info->CanGoBottom() && bottomMap && bottomMap->CanGoTop() == false)
				continue;
			if (info->CanGoRight() && rightMap && rightMap->CanGoLeft() == false)
				continue;
			if (info->CanGoLeft() && leftMap && leftMap->CanGoRight() == false)
				continue;

			curMap = LoadMap(info->_level, info->_num);
			AddMap(curMap, curPos);
			break;
		}
	}

	SetCurMap(startPos);
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

shared_ptr<Map> MapManager::LoadMap(int level, int num)
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
	result._level = level;
	result._num = num;

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
			shared_ptr<Map> temp = LoadMap(level, _mapList[level][num]);
			Save(temp);
		}
	}
}

void MapManager::SetTarget(shared_ptr<Creature> target)
{
	// 모든 몬스터에게 타켓 설정
	for (auto& creature : _maps[_curMapPos.x][_curMapPos.y]->GetObjects()[Object::CREATURE])
	{
		auto monster = dynamic_pointer_cast<Monster>(creature);
		if(monster)
			monster->SetTarget(target);
	}

	GetCurMap()->CheckClear();
}

void MapManager::SetCurMap(shared_ptr<Map> map)
{
	_maps[_curMapPos.x][_curMapPos.y] = map;
	SetCurMap(_curMapPos);

	return;
}

void MapManager::SetCurMap(const Vector2& index)
{
	// 미로에서 이동한 방향
	int moveX = index.x - _curMapPos.x;
	int moveY = index.y - _curMapPos.y;
	_curMapPos = index;

	GAME->SetCurMap(_maps[_curMapPos.x][_curMapPos.y]);
	if (GAME->GetPlayer() != nullptr)
	{
		GAME->SetPlayer(GAME->GetPlayer());
		GAME->GetPlayer()->GetObjectTexture()->Update();
		GAME->GetPlayer()->GetCollider()->Update();

		// 플레이어 위치 설정
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
		GAME->GetPlayer()->StopMove();
		GAME->GetPlayer()->GetObjectTexture()->Update();
		GAME->GetPlayer()->GetCollider()->Update();
	}

	UI_MANAGER->Refresh();
	CAMERA->Update();

	// BGM 실행
	string bgm;
	string ambience;

	switch (_maps[_curMapPos.x][_curMapPos.y]->GetLevel())
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

void MapManager::AddMap(shared_ptr<Map> map, Vector2 pos)
{
	if (_maps[pos.x][pos.y] != nullptr)
		return;

	_mapCount++;
	_maps[pos.x][pos.y] = map;

	map->CheckClear();

	// 문 오브젝트 추가
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

	// 폴더에 있는 맵 리스트 구하기
	for (int level = 0; level < 9; level++)
	{
		for (int num = 0; num < 30; num++)
		{
			// 맵이 있다면 맵 리스트에 추가
			if (IsMapFileExist(level, num))
				_mapList[level].push_back(num);

		}
	}
}

MapManager::~MapManager()
{
}
