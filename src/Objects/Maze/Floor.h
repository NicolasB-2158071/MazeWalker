#pragma once


#include "../../Buffers/VertexArray.h"
#include "../../Textures/Texture.h"
#include "../../Shaders/Shader.h"
#include "../../Renderer/Renderer.h"

class Floor
{
public:
	Floor(const glm::mat4& projection);

	void draw(Renderer& renderer);

	void initObject(float width, float height);

private:
	VertexArray m_vao;
	Texture m_texture;
	Shader m_shader;

	/*glm::vec2 m_floorSize;*/
};