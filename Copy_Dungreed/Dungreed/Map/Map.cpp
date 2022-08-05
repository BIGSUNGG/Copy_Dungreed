#include "framework.h"
#include "Map.h"

Map::Map(Level level,int num,char direction)
{
	_level = level;
	_num = num;

	_objects.resize(5);
	
	Save();
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
	int temp = 0;
	for (auto& objects : _objects)
	{
		for (auto& object : objects)
		{
			temp++;
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
	//BinaryWriter writer(L"Save/Map_Info/Level_00_0.txt");
	//vector<int> Info;
	//Info.push_back(_objectCount);
	//for (auto& objects : _objects)
	//{
	//	for (auto& object : objects)
	//	{
	//		Info.push_back((int)object->GetType());
	//		Info.push_back((int)object->GetLevel());
	//		Info.push_back(object->GetNum());
	//		Info.push_back(object->GetTexture()->GetTransform()->GetPos().x);
	//		Info.push_back(object->GetTexture()->GetTransform()->GetPos().y);
	//	}
	//}

	BinaryWriter writer(L"Save/Map_Info/Level_00_0.txt");

	vector<int> posDataes;

	posDataes.push_back(_objectCount);

	writer.Uint(posDataes.size());
	writer.Byte(posDataes.data(), posDataes.size() * sizeof(int));
}

void Map::Load()
{
	BinaryReader reader(L"Save/Map_Info/Level_00_0.txt");

	UINT size = reader.Uint();

	vector<int> posDataes;
	posDataes.resize(1);
	void* ptr = posDataes.data();
	reader.Byte(&ptr, size * sizeof(int));

	_objectCount = posDataes[0];

}

void Map::Reset()
{
	_objects.clear();
}
