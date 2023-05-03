#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../stb_image.h"

#include "Mesh.h"
#include "../Textures/Texture.h"
#include "../Shaders/Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

// CODE IS COMPLETLY COPIED FROM LEARNOPENGL AND ADAPTED TO THE CURRENT CODEBASE
class Model
{
public:

    Model(const std::string& path, bool gamma = false);
    void draw(Shader& shader);

private:
    std::vector<Mesh::aTexture> m_texturesLoaded;
    std::vector<Mesh> m_meshes;
    std::string m_directory;
    bool m_gammaCorrection;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Mesh::aTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
};