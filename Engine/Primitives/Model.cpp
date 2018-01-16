//
// Created by martin on 18.11.17.
//

#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

Model::Model(std::string path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ImproveCacheLocality);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::string message = "Couldn't load model";
        message += import.GetErrorString();
        throw std::runtime_error(message);
    }
    processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode* node, const aiScene* scene) {
    for(unsigned i = 0; i < node->mNumMeshes; i++) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(createMesh(mesh, scene));
    }
    for(unsigned i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

#define ASSIMP_VEC_TO_GLM(attributeName, vecPosition)  \
    attributeName.x = vecPosition.x; \
    attributeName.y = vecPosition.y; \
    attributeName.z = vecPosition.z;

Mesh Model::createMesh(aiMesh* mesh, const aiScene* scene) {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        ASSIMP_VEC_TO_GLM(vertex.position, mesh->mVertices[i])
        ASSIMP_VEC_TO_GLM(vertex.normal, mesh->mNormals[i])
        if(mesh->mTextureCoords[0]) {
            vertex.uv.x = mesh->mTextureCoords[0][i].x;
            vertex.uv.y = mesh->mTextureCoords[0][i].y;
        } else {
            vertex.uv = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    for(unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        assert(face.mNumIndices == 3);
        for(unsigned int j = 0; j < face.mNumIndices; ++j) indices.push_back(face.mIndices[j]);
    }
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        for(unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); ++i) {
            aiString path;
            material->GetTexture(aiTextureType_DIFFUSE, i, &path);
            textures.emplace_back(
                    TextureType::diffuse,
                    std::string(path.C_Str())
            );
        }
        for(unsigned int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); ++i) {
            aiString path;
            material->GetTexture(aiTextureType_SPECULAR, i, &path);
            textures.emplace_back(
                    TextureType::specular,
                    std::string(path.C_Str())
            );
        }
    }
    Mesh result(vertices, indices, textures);
    return result;
}

void Model::draw(const glm::mat4 &transform, GLuint shader) {
    for(auto& mesh: m_meshes) {
        mesh.draw(transform, shader);
    }
}
