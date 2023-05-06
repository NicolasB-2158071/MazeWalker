#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Model.h"
#include "../../Shaders/Shader.h"
#include "../../Renderer/Renderer.h"

class Masks
{
public:
	Masks();

	void setLocations(const std::vector<glm::vec2>& locations);
	void draw(Renderer& renderer);

	void initMasksInput(EventManager* eventManager);

	const static unsigned int NUMBER_OF_MASKS = 8;

private:
	Model m_maskModel;
	Shader m_shader;
	VertexBuffer m_ivbo;
	VertexBuffer m_ivboNormalModel;

	std::vector<glm::vec2> m_locations;
	std::vector<glm::mat4> m_locationsMatrices;
	
	void initMatrices();
	void initObject();
	void initLighting();
	std::vector<glm::mat3> calculateNormalModels(const std::vector<glm::mat4>& locations) const;

	double m_startTimeSeeThrough = 0.0;
	void handleLeftClickPicking();
};