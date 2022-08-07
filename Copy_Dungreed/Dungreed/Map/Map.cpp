#include "framework.h"
#include "Map.h"

Map::Map(Level level,int num,char direction)
{
	_level = level;
	_num = num;

	_objects.resize(5);

	//Load();

	_objects[Object::Object_Type::CREATURE].push_back(GET_OBJECT(3, -1, 0));
	_objects[Object::Object_Type::CREATURE].back()->GetTexture()->GetTransform()->GetPos() = CENTER;
}

void Map::AddObject(shared_ptr<Object> addObject, Object::Object_Type type)
{
	addObject->GetTexture()->Update();
	shared_ptr<Quad> addQuad = addObject->GetTexture();

	for (auto& objects : _objects[type])
	{
		if (objects->GetTexture()->GetTransform()->GetPos() == 
			addObject->GetTexture()->GetTransform()->GetPos())
		{
			return;
		}
	}

	_objectCount++;
	_objects[type].push_back(make_shared<Object>());
	_objects[type].back() = addObject;
}

void Map::DeleteObject(Vector2 pos, Object::Object_Type type)
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

void Map::Update()
{
	for (auto& objects : _objects)
	{
		for (auto& object : objects)
		{
			object->Update();
		}
	}
}

void Map::PreRender()
{
}

void Map::Render()
{
	for (auto& objects : _objects)
	{
		for (auto& object : objects)
		{
			object->Render();
		}
	}

}

void Map::PostRender()
{
	for (auto& objects : _objects)
	{
		for (auto& object : objects)
		{
			object->PostRender();
		}
	}
}

void Map::ImguiRender()
{
}

void Map::Save()
{
	{
		BinaryWriter basicWriter(L"Save/Map_Info/Level_00_0_basic.txt");

		vector<int> basicInfo;

		basicInfo.push_back(_objectCount);

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
				mapInfo.push_back((int)object->GetLevel());
				mapInfo.push_back(object->GetNum());
				mapInfo.push_back(object->GetTexture()->GetTransform()->GetPos().x);
				mapInfo.push_back(object->GetTexture()->GetTransform()->GetPos().y);
			}
		}

		mapWriter.Uint(mapInfo.size());
		mapWriter.Byte(mapInfo.data(), mapInfo.size() * sizeof(int));
	}
}

void Map::Load()
{
	Reset();
	{
		BinaryReader basicReader(L"Save/Map_Info/Level_00_0_basic.txt");

		UINT size = basicReader.Uint();

		vector<int> basicInfo;
		basicInfo.resize(1);
		void* ptr = basicInfo.data();
		basicReader.Byte(&ptr, size * sizeof(int));

		_objectCount = basicInfo[0];
	}

	{
		BinaryReader mapReader(L"Save/Map_Info/Level_00_0.txt");

		UINT size = mapReader.Uint();

		vector<int> mapInfo;
		int infoCount = _objectCount * 5;
		mapInfo.resize(infoCount);
		void* ptr = mapInfo.data();
		mapReader.Byte(&ptr, size * sizeof(int));

		for (int i = 0; i < _objectCount; i++)
		{
			int cur = i * 5;

			shared_ptr<Object> object = GET_OBJECT(mapInfo[cur], mapInfo[cur + 1], mapInfo[cur + 2]);

			object->GetTexture()->GetTransform()->GetPos() = Vector2(mapInfo[cur + 3], mapInfo[cur + 4]);
			_objects[mapInfo[cur]].emplace_back(object);
		}
	}
}

void Map::Reset()
{
	_objects.clear(); 
}
