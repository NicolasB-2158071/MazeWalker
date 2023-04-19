#include "Walls.h"

#include "../../Buffers/VertexBuffer.h"
#include "../../Buffers/VertexBufferLayout.h"
#include "../../Buffers/IndexBuffer.h"


Walls::Walls() : m_texture{ "res/sandStone.jpg", GL_RGB }, m_shader{ "src/Shaders/WallsVShader.vs", "src/Shaders/WallsFShader.fs" }
{
    m_shader.use();
    m_shader.setInt("textureOne", 0);
    m_shader.bindUniformBlock("TransformationBlock", Renderer::TRANSFORMATION_BLOCK);
}

void Walls::draw(Renderer& renderer)
{
    renderer.drawWalls(m_vao, m_shader, m_texture, m_amount);
}

void Walls::initObject(int amount, glm::mat4* locations)
{
    m_amount = amount;

    // Origin (0, 0, 0)
    float vertices[] = {
        // Top (LFT - LBT - RFT - RBT): pos, tex, normals (0 - 3)
         0.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

         // Bottom (LFB - LBB - RFB - RBB): pos, tex, normals (4 - 7)
         0.0f,  0.0f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         0.0f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
         1.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,

         // Front (LFB - LFT - RFB - RFT): pos, tex, normals (8 - 11)
         0.0f,  0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

         // Behind (LBB - LBT - RBB - RBT): pos, tex, normals (12 - 15)
         0.0f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
         0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
         1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
         1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,

         // Left (LFB - LBB - LFT - LBT): pos, tex, normals (16 - 19)
         0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         0.0f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         0.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
         0.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

         // Right (RFB - RBB - RFT - RBT): pos, tex, normals (20 - 23)
         1.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    };

    unsigned int indices[] = {
        12, 13, 14, 14, 15, 13, // Behind
        8, 9, 10, 10, 11, 9, // Front
        16, 17, 18, 18, 19, 17, // Left
        20, 21, 22, 22, 23, 21, // Right
        4, 5, 6, 6, 7, 5, // Bottom
        0, 1, 2, 2, 3, 1 // Top
    };

    VertexBuffer vbo{ vertices, sizeof(vertices) };
    VertexBufferLayout vbl{};
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(2, GL_FLOAT, GL_FALSE);
    vbl.addAttribute(3, GL_FLOAT, GL_FALSE);

    m_vao.connectVertexBuffer(vbo, vbl);
    IndexBuffer ebo{ indices, sizeof(indices) }; // is nog gebind
    VertexBuffer ivbo{ locations, sizeof(glm::mat4) * m_amount };
  
    m_vao.connectInstanceBuffer(ivbo, BufferAttribute{4, GL_FLOAT, GL_FALSE}, 3, 6, sizeof(glm::vec4));
    m_vao.unbind();
}


// LBB (0) - LBT (1) - RBB (2) - RBT (3)
// LFB (4) - LFT (5) - RFB (6) - RFT (7)
//float vertices[] = {
//    // Pos              // Texture
//   -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
//   -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
//    1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
//    1.0f,  1.0f, -1.0f, 1.0f, 1.0f,

//   -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
//   -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
//    1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
//    1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
//};


//unsigned int indices[] = {
//    0, 1, 2, 1, 3, 2, // Behind (LBB - LBT - RBB - LBT - RBT - RBB)
//    4, 5, 6, 5, 7, 6, // Front (LFB - LFT - RFB - LFT - RFT - RFB)
//    4, 0, 5, 1, 5, 0, // Left (LFB - LBB - LFT - LBT - LFT - LBB)
//    6, 2, 7, 3, 7, 2, // Right (RFB - RBB - RFT - RBT - RFT - RBB)
//    4, 6, 0, 0, 6, 2, // Bottom (LFB - RFB - LBB - LBB - RFB - RBB)
//    5, 7, 1, 1, 7, 3 // Top (LFT - RFT - LBT - LBT - RFT - RBT)
//};