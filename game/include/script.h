#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>
#include "audio.h"
#include <utility>
#include <any>

class ScriptFunction
{
public:

	void* Func;

	ScriptFunction() {};

	template<class Return = void, class... Args>
	ScriptFunction(Return(*Function)(Args... args)) {
		Func = Function;
	};

	//Calls function with any number of arguments
	template<class Return = void, class... Args>
	Return Call(const Args&... args)
	{
		typedef Return(*Function)(Args...);
		return reinterpret_cast<Function>(Func)(args...);
	}
};

class Script
{
	inline static std::unordered_map<std::string, ScriptFunction> functions;
public:
	template<class... Args>
	static void CallFunction(std::string name, const Args&... args)
	{
		
		if (functions.find(name) != functions.end())
			functions[name].Call(args...);
	}

	//shim for play audio
	//todo: find a better way to do this?
	static void Scr_PlayAudio(std::vector<std::any> args)
	{
		std::string path = std::any_cast<std::string>(args[0]);
		float vol = std::any_cast<float>(args[1]);

		Audio::PlayAudio(path, vol);

	}

	static void InitScript()
	{
		functions["PlaySound"] = ScriptFunction(Script::Scr_PlayAudio);
		//CallFunction("PlaySound", std::string("test"), (float)1 );
	}
};