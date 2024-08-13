#pragma once
#include "Camera.h"

class Engine {
public:
	static Engine& getInstance() {
		static Engine instance;
		return instance;
	}

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	Camera camera{};

private:
	Engine() = default;
	~Engine() = default;
};
