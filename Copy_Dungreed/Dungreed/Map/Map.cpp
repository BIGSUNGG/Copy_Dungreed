#include "framework.h"
#include "Map.h"

Map::Map(Level level,int num,char direction)
{
	_level = level;
	_num = num;

	Reset();
}

void Map::AddObject(shared_ptr<Object> addObject, int type,bool toFront)
{
	addObject->GetTexture()->Update();
	shared_ptr<Quad> addQuad = addObject->GetTexture();

	Vector2& pos = addObject->GetTexture()->GetTransform()->GetPos();

	for (auto& objects : _objects[type])
	{
		if (addObject->GetTexture()->GetTransform()->GetPos() ==
			objects->GetTexture()->GetTransform()->GetPos())
		{
			return;
		}
	}

	_objectCount++;
	
	if (toFront)
		_objects[type].emplace(_objects[type].begin(), addObject);
	else
		_objects[type].emplace_back(addObject);
}

void Map::DeleteObject(Vector2 pos, int type, bool toFront)
{
	if (toFront)
	{
		for (auto objects = _objects[type].begin(); objects != _objects[type].end(); objects++)
		{
			shared_ptr<Quad> object = objects->get()->GetTexture();
			if (pos.x > object->Left() && pos.x < object->Right() &&
				pos.y < object->Top() && pos.y > object->Bottom())
			{
				_objects[type].erase(objects);
				_objectCount--;
				break;
			}
		}
	}
	else
	{
		for (int i = _objects[type].size() - 1; i > 0; i--)
		{
			shared_ptr<Quad> object = _objects[type][i]->GetTexture();
			if (pos.x > object->Left() && pos.x < object->Right() &&
				pos.y < object->Top() && pos.y > object->Bottom())
			{
				auto iter = _objects[type].begin() + i;
				_objects[type].erase(iter);
				_objectCount--;
				break;
			}
		}
	}
}

void Map::Save()
{
	{
		BinaryWriter basicWriter(L"Save/Map_Info/Level_00_0_basic.txt");

		vector<int> basicInfo;

		basicInfo.push_back(_objectCount);
		basicInfo.push_back(_leftBottom.x);
		basicInfo.push_back(_leftBottom.y);
		basicInfo.push_back(_rightTop.x);
		basicInfo.push_back(_rightTop.y);
		basicInfo.push_back(_startPos.x);
		basicInfo.push_back(_startPos.y);

		basicWriter.Uint(basicInfo.size());
		basicWriter.Byte(basicInfo.data(), basicInfo.size() * sizeof(int));
	}

	{
		BinaryWriter mapWriter(L"Save/Map_Info/Level_00_0.txt");

		vector<int> mapInfo;


		for (auto& objects : _objects)
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

void Map::Load()
{
	Reset();

	int objectCount;
	{
		BinaryReader basicReader(L"Save/Map_Info/Level_00_0_basic.txt");

		UINT size = basicReader.Uint();

		vector<int> basicInfo;
		basicInfo.resize(7);
		void* ptr = basicInfo.data();
		basicReader.Byte(&ptr, size * sizeof(int));

		objectCount = basicInfo[0];
		_leftBottom = Vector2(basicInfo[1], basicInfo[2]);
		_rightTop = Vector2(basicInfo[3], basicInfo[4]);
		_startPos = Vector2(basicInfo[5], basicInfo[6]);
	}

	{
		BinaryReader mapReader(L"Save/Map_Info/Level_00_0.txt");

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

			AddObject(object, mapInfo[cur]);
		}
	}
}

void Map::Reset()
{
	_objects.clear();
	_objects.resize(6);
	for (auto& object : _objects)
		object.reserve(100);
	_objectCount = 0;
}
