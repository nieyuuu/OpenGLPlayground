#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../stb_image/stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

unsigned int TextureFromFile(const char* vPath, const string& vDirectory, bool vGamma = false);

class CModel 
{
public:
    vector<STexture> m_LoadedTextures;
    vector<Mesh> m_Meshes;
    string m_Directory;
    bool m_GammaCorrection;

    CModel(string const& vPath, bool vGamma = false) : m_GammaCorrection(vGamma)
    {
        __loadModel(vPath);
    }

    void Draw(const CShader& vShader)
    {
        for(unsigned int i = 0; i < m_Meshes.size(); i++)
            m_Meshes[i].Draw(vShader);
    }
    
private:
    void __loadModel(string const &vPath)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(vPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
            return;
        }

        m_Directory = vPath.substr(0, vPath.find_last_of('/'));

        __processNode(scene->mRootNode, scene);
    }

    void __processNode(aiNode *vNode, const aiScene *vScene)
    {
        for(unsigned int i = 0; i < vNode->mNumMeshes; i++)
        {
            aiMesh* mesh = vScene->mMeshes[vNode->mMeshes[i]];
            m_Meshes.push_back(__processMesh(mesh, vScene));
        }
        for(unsigned int i = 0; i < vNode->mNumChildren; i++)
        {
            __processNode(vNode->mChildren[i], vScene);
        }

    }

    Mesh __processMesh(aiMesh *vMesh, const aiScene *vScene)
    {
        vector<SVertex> Vertices;
        vector<unsigned int> Indices;
        vector<STexture> Textures;

        for(unsigned int i = 0; i < vMesh->mNumVertices; i++)
        {
            SVertex Vertex;
            glm::vec3 Temp;
            // positions
            Temp.x = vMesh->mVertices[i].x;
            Temp.y = vMesh->mVertices[i].y;
            Temp.z = vMesh->mVertices[i].z;
            Vertex.Position = Temp;
            // normals
            Temp.x = vMesh->mNormals[i].x;
            Temp.y = vMesh->mNormals[i].y;
            Temp.z = vMesh->mNormals[i].z;
            Vertex.Normal = Temp;
            // texture coordinates
            if(vMesh->mTextureCoords[0])
            {
                glm::vec2 TexCoord;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                TexCoord.x = vMesh->mTextureCoords[0][i].x; 
                TexCoord.y = vMesh->mTextureCoords[0][i].y;
                Vertex.TexCoords = TexCoord;
            }
            else
                Vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            // tangent
            Temp.x = vMesh->mTangents[i].x;
            Temp.y = vMesh->mTangents[i].y;
            Temp.z = vMesh->mTangents[i].z;
            Vertex.Tangent = Temp;
            // bitangent
            Temp.x = vMesh->mBitangents[i].x;
            Temp.y = vMesh->mBitangents[i].y;
            Temp.z = vMesh->mBitangents[i].z;
            Vertex.Bitangent = Temp;
            Vertices.push_back(Vertex);
        }
        
        for(unsigned int i = 0; i < vMesh->mNumFaces; i++)
        {
            aiFace Face = vMesh->mFaces[i];
           
            for(unsigned int j = 0; j < Face.mNumIndices; j++)
                Indices.push_back(Face.mIndices[j]);
        }

        // process materials
        aiMaterial* material = vScene->mMaterials[vMesh->mMaterialIndex];

        // 1. diffuse maps
        vector<STexture> diffuseMaps = __loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        Textures.insert(Textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        vector<STexture> specularMaps = __loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        Textures.insert(Textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<STexture> normalMaps = __loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        Textures.insert(Textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<STexture> heightMaps = __loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        Textures.insert(Textures.end(), heightMaps.begin(), heightMaps.end());
        
        return Mesh(Vertices, Indices, Textures);
    }

    vector<STexture> __loadMaterialTextures(aiMaterial *vMaterial, aiTextureType vTextureType, string vTypeName)
    {
        vector<STexture> Textures;
        for(unsigned int i = 0; i < vMaterial->GetTextureCount(vTextureType); i++)
        {
            aiString FileName;
            vMaterial->GetTexture(vTextureType, i, &FileName);
            
            bool skip = false;
            for(unsigned int j = 0; j < m_LoadedTextures.size(); j++)
            {
                if(std::strcmp(m_LoadedTextures[j].FileName.data(), FileName.C_Str()) == 0)
                {
                    Textures.push_back(m_LoadedTextures[j]);
                    skip = true;
                    break;
                }
            }
            if(!skip)
            {
				STexture Texture;
                Texture.ID = TextureFromFile(FileName.C_Str(), this->m_Directory);
                Texture.Type = vTypeName;
                Texture.FileName = FileName.C_Str();
                Textures.push_back(Texture);
                m_LoadedTextures.push_back(Texture);
            }
        }
        return Textures;
    }
};

unsigned int TextureFromFile(const char* vFileName, const string& vDirectory, bool vGamma)
{
    string filename = string(vFileName);
    filename = vDirectory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << vFileName << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
