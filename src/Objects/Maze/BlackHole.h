#pragma once

#include "../Model.h"
#include "../../Shaders/Shader.h"
#include "../../Renderer/Renderer.h"

#include <SFML/Audio.hpp>

class BlackHole
{
public:
	BlackHole();

	void draw(Renderer& renderer);
	void initObject(float floorWidth, float floorHeight);

	void initBlackHoleInput(EventManager* eventManager);

private:
	Model m_blackHoleModel;
	Shader m_shader;

	float m_floorWidth;
	float m_floorHeight;

	sf::Music m_backgroundMusic;
	void initAudio();
	void handleLeftClickPicking();
};