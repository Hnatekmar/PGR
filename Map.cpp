//
// Created by martin on 30.11.17.
//
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include "Map.h"
#include "Engine/Primitives/Model.h"
#include "Engine/GraphicsComponent.h"
#include "RigidBodyComponent.h"
#include "WeaponInfo.h"
#include "Health.h"
#include "Billboard.h"
#include <fstream>
#include "json.hpp"
#include "EntityCreator.h"
#include "Engine/LightComponent.h"
#include "ProximityComponent.h"

using namespace std::chrono_literals;
Map::Map(const std::string &modelPath, const std::string &collisionObject, const std::string& infoPath, entityx::EntityManager &manager, std::shared_ptr<btDynamicsWorld> world): m_manager(manager) {
    m_world = world;
    m_loadInfo = std::make_shared<LoadInfo>();
    m_loadInfo->info = infoPath;
    m_loadInfo->model = modelPath;
    m_loadInfo->collision = collisionObject;
    load(infoPath, modelPath, collisionObject);
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

void Map::load(const std::string &info, const std::string &model, const std::string &collision) {

    std::ifstream inFile;
    inFile.open(info);
    std::stringstream content;
    content << inFile.rdbuf();

    m_entity = m_manager.create();
    std::shared_ptr<IDrawable> mapModel = std::make_shared<Model>(model);
    m_entity.assign<GraphicsComponent>(glm::vec3(),
                                       0.0,
                                       glm::vec3(0.0, 1.0, 0.0),
                                       mapModel);
    m_mesh = std::make_unique<btTriangleMesh>();
    loadTriangles(collision);
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
        if(entityData.at("type").get<std::string>() == "Finish") {
            auto entity = m_manager.create();
            m_entities.push_back(entity);
            auto x = entityData.at("x").get<float>();
            auto y = entityData.at("y").get<float>();
            auto z = entityData.at("z").get<float>();
            auto model = entityData.at("model").get<std::string>();
            auto collision = entityData.at("collision").get<std::string>();
            auto info = entityData.at("info").get<std::string>();
            auto infoCopy = m_loadInfo;
            entity.assign<ProximityComponent<std::function<void(entityx::Entity, entityx::Entity)>>>(
                    glm::vec3(x, y, z),
                    1,
                    [model, collision, info, infoCopy](entityx::Entity pickupEntity, entityx::Entity player) {
                        infoCopy->info = info;
                        infoCopy->collision = collision;
                        infoCopy->model = model;
                        infoCopy->shouldLoad = true;
                    }
            );
        }
        else if(entityData.at("type").get<std::string>() == "Player") {
            m_player = CREATE_ENTITY(m_manager, m_world, entityData);
        }else {
            m_entities.push_back(CREATE_ENTITY(m_manager, m_world, entityData));
        }
    }
    auto lights = jsonData["lights"].get<std::list<nlohmann::json>>();
    for(auto& light: lights) {
        auto entity = m_manager.create();
        glm::vec3 lightPosition(light["x"].get<float>(),
                                light["y"].get<float>(),
                                light["z"].get<float>());
        entity.assign<LightComponent>(
                lightPosition
        );
        m_entities.push_back(entity);
    }
}

void Map::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    if(m_loadInfo->shouldLoad) {
        destroy();
        load(m_loadInfo->info, m_loadInfo->model, m_loadInfo->collision);
        m_loadInfo->shouldLoad = false;
    }
    if(m_player.component<Health>()->healthPoints <= 0) {
        destroy();
        load(m_loadInfo->info, m_loadInfo->model, m_loadInfo->collision);
    }
}
