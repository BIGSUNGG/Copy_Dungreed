#include "framework.h"
#include "Audio.h"

Audio * Audio::_instance = nullptr;

using namespace FMOD;

Audio::Audio()
{
	System_Create(&_soundSystem);
	_soundSystem->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);
}

Audio::~Audio()
{
	for (auto& soundPair : _soundMap)
		delete soundPair.second;

	_soundSystem->release();
}

void Audio::Update()
{
	_soundSystem->update();
}

void Audio::Add(string key, string file, bool bgm)
{
	if (_soundMap.count(key) > 0)
		return;

	SoundInfo* info = new SoundInfo();

	if (bgm)
	{
		_soundSystem->createStream(file.c_str(), FMOD_LOOP_NORMAL, nullptr, IN & info->_sound);
		_type[key] = true;
	}
	else
	{
		_soundSystem->createSound(file.c_str(), FMOD_DEFAULT, nullptr, IN & info->_sound);
		_type[key] = false;
	}

	assert(info->_sound != nullptr);

	_soundMap[key] = info;
}

void Audio::Play(string key)
{
	if (_soundMap.count(key) == 0)
	{
		if (key == "")
			return;

		assert(false);
	}

	_soundSystem->playSound(_soundMap[key]->_sound, nullptr, false, &_soundMap[key]->_channel);

	float soundvolume;

	if (_type[key] == true)
		soundvolume = _audioVolume * _bgmVolume;
	else
		soundvolume = _audioVolume * _sfxVolume;

	_soundMap[key]->_channel->setVolume(soundvolume);
}

void Audio::Stop(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundMap[key]->_channel->stop();
}

void Audio::StopAll()
{
	for (auto& sound : _soundMap)
		sound.second->_channel->stop();
}

void Audio::Pause(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundMap[key]->_channel->setPaused(true);
}

void Audio::PauseAll()
{
	for (auto& sound : _soundMap)
		sound.second->_channel->setPaused(true);
}

void Audio::Resume(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundMap[key]->_channel->setPaused(false);
}

void Audio::ResumeAll()
{
	for (auto& sound : _soundMap)
		sound.second->_channel->setPaused(false);
}

void Audio::SetVolume(string key, float volume)
{
	if (_soundMap.count(key) == 0)
		return;

	if (_soundMap[key]->_channel == nullptr)
		return;

	if (volume <= 0)
		volume = 0;

	if (volume >= 2.0f)
		volume = 2.0f;

	_soundMap[key]->_channel->setVolume(volume);
}

void Audio::SetVolumeAll()
{
	for (auto& sound : _soundMap)
	{
		if (sound.second->_channel == nullptr)
			continue;

		float soundvolume;

		if(_type[sound.first] == true)
			soundvolume = _audioVolume * _bgmVolume;
		else
			soundvolume = _audioVolume * _sfxVolume;

		sound.second->_channel->setVolume(soundvolume);
	}
}

bool Audio::IsPlaySound(string key)
{
	if (_soundMap.count(key) == 0)
		return false;

	bool isPlay = false;
	_soundMap[key]->_channel->isPlaying(IN & isPlay);

	return isPlay;
}

void Audio::ImGuiRender()
{
	ImGui::SliderFloat("Audio Volume", &_audioVolume, 0.0f, 2.0f, "%0.1f");
	ImGui::SliderFloat("BGM Volume", &_bgmVolume, 0.0f, 1.0f, "%0.1f");
	ImGui::SliderFloat("SFX Volume", &_sfxVolume, 0.0f, 1.0f, "%0.1f");

	if (ImGui::Button("Apply"))
		SOUND->SetVolumeAll();
}
