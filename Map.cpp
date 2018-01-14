//
// Created by martin on 30.11.17.
//
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include "Map.h"
#include "Engine/Primitives/Model.h"
#include "Engine/GraphicsComponent.h"
#include "RigidBodyComponent.h"
#include "LookingDirection.h"
#include "Engine/Camera.h"
#include "WeaponInfo.h"
#include "Health.h"
#include "Billboard.h"
#include "RotationComponent.h"
#include <fstream>
#include "json.hpp"
#include "EntityCreator.h"

using namespace std::chrono_literals;
Map::Map(const std::string &modelPath, const std::string &collisionObject, const std::string& infoPath, entityx::EntityManager &manager, std::shared_ptr<btDynamicsWorld> world) {
    std::ifstream inFile;
    inFile.open(infoPath);
    std::stringstream content;
    content << inFile.rdbuf();

    m_entity = manager.create();
    std::shared_ptr<IDrawable> mapModel = std::make_shared<Model>(modelPath);
    m_entity.assign<GraphicsComponent>(glm::vec3(),
                                        0.0,
                                        glm::vec3(0.0, 1.0, 0.0),
                                        mapModel);
    m_mesh = std::make_unique<btTriangleMesh>();
    loadTriangles(collisionObject);
    std::shared_ptr<btCollisionShape> shape = std::make_shared<btBvhTriangleMeshShape>(static_cast<btStridingMeshInterface*>(m_mesh.get()), true);
    m_entity.assign<RigidBody>(
            btQuaternion(0.0, 0.0, 0.0, 1.0),
            btVector3(0.0, 0.0, 0.0),
            shape,
            0,
            btVector3(0, 0, 0)
    );

    auto jsonData = nlohmann::json::parse(content.str());
    auto entities = jsonData["entities"].get<std::list<nlohmann::json>>();
    for(auto& entityData: entities) {
        CREATE_ENTITY(manager, world, entityData);
    }
}

void Map::loadTriangles(const std::string &path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ImproveCacheLocality);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::string message = "Couldn't load model";
        message += import.GetErrorString();
        throw std::runtime_error(message);
    }
    processNode(scene->mRootNode, scene);
}

void Map::processNode(aiNode *node, const aiScene *scene) {
    for(unsigned i = 0; i < node->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        for(unsigned int k = 0; k < mesh->mNumFaces; ++k) {
            const aiFace& face = mesh->mFaces[k];
            if(face.mNumIndices != 3) continue;
            btVector3 triangle[3];
            for(unsigned int j = 0; j < face.mNumIndices; ++j) {
                auto vertex = mesh->mVertices[face.mIndices[j]];
                triangle[j] = btVector3(vertex.x, vertex.y, vertex.z);
            }
            m_mesh->addTriangle(triangle[0], triangle[1], triangle[2]);
        }
    }
    for(unsigned i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

void Map::loadFromJson(const std::string &path) {

}
