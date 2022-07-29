#pragma once
class TextureManager
{
public:
	static void Create() {
		if (_instance == nullptr)
			_instance = new TextureManager;
	}

	static void Delete() {
		if (_instance != nullptr)
			delete _instance;
	}

	static TextureManager* GetInstance() {
		if (_instance != nullptr)
			return _instance;
	}

	shared_ptr<Quad> GetTileTexture(int level, int type, int num);
	shared_ptr<Quad> GetBackGroundTexture(int level,int num = 0);

private:
	TextureManager();
	~TextureManager();
	static TextureManager* _instance;
};
