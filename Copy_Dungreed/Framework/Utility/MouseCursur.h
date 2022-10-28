#pragma once

class Quad;

class MouseCursur
{
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new MouseCursur();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static MouseCursur* GetInstance()
	{
		if (_instance != nullptr)
		{
			return _instance;
		}

		return nullptr;
	}

	void Update();
	void Render();

	void SetCursurImage(wstring image);

	void CursurOn();
	void CursurOff();

private:
	MouseCursur();
	~MouseCursur();

	static MouseCursur* _instance;

	shared_ptr<Quad> _mouseCursur;
	bool _showMouseCursur = true;
};

