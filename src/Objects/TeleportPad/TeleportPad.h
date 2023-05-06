#pragma once

#include "../Model.h"
#include "../../Shaders/Shader.h"
#include "../../Renderer/Renderer.h"

#include <SFML/Audio.hpp>

class TeleportPad
{
public:

	TeleportPad(Camera& camera);

	void draw(Renderer& renderer);
	void update(bool eKeyPressed);

private:
	Model m_teleportPadModel;
	Shader m_shader;

	bool m_isVisible;
	
	Camera& m_camera;

	sf::Sound m_teleportSound;
	sf::SoundBuffer m_placingSound;
	sf::SoundBuffer m_teleportingSound;

	void initAudio();
	void initObject();
	glm::mat4 setPosition(const glm::vec3& position);
};