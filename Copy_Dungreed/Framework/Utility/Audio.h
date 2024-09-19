#pragma once

class Audio
{
private:
	struct SoundInfo
	{
		FMOD::Sound* _sound = nullptr;
		FMOD::Channel* _channel = nullptr;

		SoundInfo() {}
		~SoundInfo()
		{
			_sound->release();
		}
	};

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Audio();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Audio* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();

	void Save();
	void Load();

	void Add(string key, string file, bool loop = false, bool bgm = false);
	void Play(string key);

	void Stop(string key);
	void StopAll();

	void Pause(string key);
	void PauseAll();

	void Resume(string key);
	void ResumeAll();

	void SetVolume(string key, float volume);
	void SetVolumeAll();

	bool IsPlaySound(string key);

	void ImGuiRender();

	const float& GetAudioVolume() { return _audioVolume; }
	const float& GetBGMVolume() { return _bgmVolume; }
	const float& GetSFXVolume() { return _sfxVolume; }

	void SetAudioVolume(const float& volume) { _audioVolume = volume; }
	void SetBGMVolume(const float& volume) { _bgmVolume = volume; }
	void SetSFXVolume(const float& volume) { _sfxVolume = volume; }

private:
	Audio();
	~Audio();

	static Audio* _instance;

	FMOD::System* _soundSystem = nullptr;

	unordered_map<string, SoundInfo*> _soundMap;
	map<string, bool> _type;
	const int MAX_CHANNEL = 45;

	float _audioVolume = 0.5f;
	float _bgmVolume = 1.0f;
	float _sfxVolume = 1.0f;

	float _tempAudioVolume = 0.5f;
	float _tempBgmVolume = 1.0f;
	float _tempSfxVolume = 1.0f;
};
