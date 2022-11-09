#pragma once
class Graphic
{
public:
	static void Create() {
		if (_instance == nullptr)
			_instance = new Graphic;
	}

	static void Delete() {
		if (_instance != nullptr)
			delete _instance;
	}

	static Graphic* GetInstance() {
		if (_instance != nullptr)
			return _instance;
	}

	void Save();
	void Load();

	void ImGuiRender();

	const int& GetWinMode() { return _winMode; }
	const int& GetFpsLimit() { return _fpsLimit; }

	void SetWinMode(const int& mode);
	void SetFpsLimit(const int& mode);

private:
	Graphic();
	~Graphic();
	static Graphic* _instance;

	int _winMode = 1;
	int _fpsLimit = 0;

	bool _restart = false;
};

