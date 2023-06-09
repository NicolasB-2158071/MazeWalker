#pragma once


#include "../../Buffers/VertexArray.h"
#include "../../Textures/Texture.h"
#include "../../Shaders/Shader.h"
#include "../../Renderer/Renderer.h"

class Floor
{
public:
	Floor();

	void draw(Renderer& renderer);

	void initObject(float width, float height);

private:
	VertexArray m_vao;
	Texture m_texture;
	Shader m_shader;

	void initLighting() const;
};