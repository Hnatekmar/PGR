//
// Created by martin on 18.11.17.
//

#ifndef PROJECT_MODEL_H
#define PROJECT_MODEL_H

#include "Mesh.h"
#include "../IDrawable.h"
#include <vector>
#include <assimp/scene.h>
#include <assimp/mesh.h>

class Model: public IDrawable {
    std::vector<Mesh> m_meshes;
    void processNode(aiNode* node, const aiScene* scene);
    Mesh createMesh(aiMesh* mesh, const aiScene* scene);
public:
    Model(std::string path);

    void draw(const glm::mat4 &transform, GLuint shader) override;
};


#endif //PROJECT_MODEL_H
