#pragma once

#include "../../Buffers/VertexArray.h"
#include "../../Textures/Cubemap.h"
#include "../../Shaders/Shader.h"
#include "../../Renderer/Renderer.h"

// VAO aanmaken, aparte shader (projection matrix), anders renderen

class Skybox
{
public:
	Skybox(const glm::mat4& projection);

	void draw(Renderer& renderer);

	void initObject();

private:
	std::vector<std::string> m_textures{
		"res/Skybox/right.png",
		"res/Skybox/left.png",
		"res/Skybox/top.png",
		"res/Skybox/bottom.png",
		"res/Skybox/front.png",
		"res/Skybox/back.png"
	};

	VertexArray m_vao;
	Cubemap m_cubemap;
	Shader m_shader;
};