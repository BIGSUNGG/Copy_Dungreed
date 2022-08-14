#pragma once
class GraphicManager
{
public:
	static void Create() {
		if (_instance == nullptr)
			_instance = new GraphicManager;
	}

	static void Delete() {
		if (_instance != nullptr)
			delete _instance;
	}

	static GraphicManager* GetInstance() {
		if (_instance != nullptr)
			return _instance;
	}

	void Save();
	void Load();

	void ImguiRender();

private:
	GraphicManager();
	~GraphicManager();
	static GraphicManager* _instance;

	int _winMode = 1;

	bool _applied = false;
};

