#pragma once

#include "raylib.h"

#include <vector>
#include <string>
#include <filesystem>
#include "UI.h"
#include <unordered_map>
class Audio
{
	inline static std::unordered_map<std::string, Sound> audioFiles;

	static void LoadAudioFile(std::string path)
	{
		if (!std::filesystem::exists(path))
		{
			UI::ConsolePrint("LoadAudioFile: Could not load file: " + path);
			return;
		}
		audioFiles[path] = LoadSound(path.c_str());
	}
public:
	static void PlayAudio(std::string path, float volume)
	{
		if (!IsAudioDeviceReady())
		{
			InitAudioDevice();
		}
		if (!audioFiles.contains(path))
		{
			LoadAudioFile(path);
		}
		if (audioFiles.contains(path))
		{
			SetSoundVolume(audioFiles[path], volume);
			PlaySound(audioFiles[path]);
		}
	}
};