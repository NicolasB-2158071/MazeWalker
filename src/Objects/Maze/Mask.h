#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Model.h"
#include "../../Shaders/Shader.h"

class Mask
{
public:
	Mask();

private:
	Model m_maskModel;
	Shader m_shader;
	VertexBuffer m_ivbo;

	std::vector<glm::vec2> m_locations;
	std::vector<glm::mat4> m_locationsMatrices;
	void initMatrices();

	void initObject();
};