#pragma once
#include <string>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <Shader.h>

using namespace std;

struct Vertex 
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct TextureId {
    unsigned int id;
    string type;
    string path;
};

class Mesh 
{
public:
    // mesh data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<TextureId>    textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<TextureId> textures);
    void Draw(Shader& shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

