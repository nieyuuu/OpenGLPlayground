#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct SVertex
{
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct STexture
{
    unsigned int ID;
    string Type;
    string FileName;
};

class Mesh {
public:
    vector<SVertex> m_Vertices;
    vector<unsigned int> m_Indices;
    vector<STexture> m_Textures;
    unsigned int m_VAO;

    Mesh(const vector<SVertex>& vVertices, const vector<unsigned int>& vIndices, const vector<STexture>& vTextures)
    {
        m_Vertices = vVertices;
        m_Indices = vIndices;
        m_Textures = vTextures;

        __setupMesh();
    }

    void Draw(const CShader& vShader) 
    {
        unsigned int diffuseNum  = 1;
        unsigned int specularNum = 1;
        unsigned int normalNum   = 1;
        unsigned int heightNum   = 1;
        for(unsigned int i = 0; i < m_Textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            string number;
            string type = m_Textures[i].Type;
            if(type == "texture_diffuse")
				number = std::to_string(diffuseNum++);
			else if(type == "texture_specular")
				number = std::to_string(specularNum++);
            else if(type == "texture_normal")
				number = std::to_string(normalNum++);
             else if(type == "texture_height")
			    number = std::to_string(heightNum++);

			vShader.setTexture2DUniformValue(type + number, m_Textures[i].ID, i);
        }
        
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
    }

private:
    unsigned int m_VBO, m_EBO;

    void __setupMesh()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(SVertex), &m_Vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

        // vertex Positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, TexCoords));
        // vertex tangent
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Tangent));
        // vertex bitangent
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)offsetof(SVertex, Bitangent));

        glBindVertexArray(0);
    }
};
