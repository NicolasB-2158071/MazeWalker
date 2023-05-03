#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<aTexture>& textures) : m_vao{ true },
m_vbo{ &vertices[0], sizeof(Vertex) * vertices.size() }, m_ibo{ &indices[0], sizeof(unsigned int) * indices.size() }, m_textures{ textures }, m_indicesSize{ indices.size() }
{
    setupMesh();
}

void Mesh::draw(const Shader& shader)
{
    // Textures
    unsigned int diffuseNr{ 1 };
    unsigned int specularNr{ 1 };
    unsigned int normalNr{ 1 };
    unsigned int heightNr{ 1 };
    for (unsigned int i = 0; i < m_textures.size(); ++i)
    {
        std::string number;
        std::string name = m_textures[i].name;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        // Set the sampler to the current slot (ook nog met material!!)
        shader.setInt((name + number).c_str(), i); // material: naam conventie
        m_textures[i].texture.activeAndBind(GL_TEXTURE0 + i);
    }

    m_vao.bind();
    glDrawElements(GL_TRIANGLES, m_indicesSize, GL_UNSIGNED_INT, 0);
}

void Mesh::setupMesh()
{
    VertexBufferLayout vbl{};
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(2, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);

    vbl.addAttribute(4, GL_INT, sizeof(Vertex));
    vbl.addAttribute(4, GL_FLOAT, GL_FALSE);

    m_vao.connectVertexBuffer(m_vbo, vbl);
    m_ibo.bind();
    m_vao.unbind();
}