#include "Model.h"

Model::Model() {}

Model::Model(const std::string& path, bool gamma, const VertexBuffer* ivbo) : m_gammaCorrection{ gamma }, m_ivbo{ivbo}
{
    loadModel(path);
}

void Model::draw(const Shader& shader, int instanceCount)
{
    for (unsigned int i = 0; i < m_meshes.size(); i++)
        m_meshes[i].draw(shader, instanceCount);
}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    m_directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // Process meshes of node
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
        m_meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));

    // Process all children of node
    for (unsigned int i = 0; i < node->mNumChildren; ++i)
        processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Mesh::aTexture> textures;

    // Go through vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        // Pos
        Mesh::Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.pos = vector;

        // Normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        // Texture coordinates
        if (mesh->mTextureCoords[0])
        {
            // Assumption only two vertex coordinates
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.tex = vec;

            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
            vertex.tex = glm::vec2{ 0.0f, 0.0f };

        vertices.push_back(vertex);
    }

    // Go through faces to retrieve vertex indices
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // Materials: using naming convention!
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Mesh::aTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Mesh::aTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Mesh::aTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Mesh::aTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh{ vertices, indices, textures, m_ivbo };
}

std::vector<Mesh::aTexture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
    // Finds and creates the textures
    std::vector<Mesh::aTexture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool alreadyLoaded = false;
        for (unsigned int j = 0; j < m_texturesLoaded.size(); j++)
        {
            if (std::strcmp(m_texturesLoaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(m_texturesLoaded[j]);
                alreadyLoaded = true;
                break;
            }
        }
        if (!alreadyLoaded)
        {
            size_t index{ std::string{ str.C_Str()}.find_last_of('\\') }; // For torch also needed for the rest?
            std::string filename = m_directory + '/' + std::string{ str.C_Str() }.substr(index + 1);

            Mesh::aTexture texture{ Texture{filename.c_str(), true}, typeName, filename.c_str() };
            textures.push_back(texture);
            m_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}