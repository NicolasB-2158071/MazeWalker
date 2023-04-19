#pragma once

#include "../../Buffers/VertexArray.h"
#include "../../Textures/Texture.h"
#include "../../Shaders/Shader.h"
#include "../../Renderer/Renderer.h"

class LightObject
{
public:

	LightObject();

	void draw(Renderer& renderer);

	void initObject();

private:
	VertexArray m_vao;
	Shader m_shader;
};