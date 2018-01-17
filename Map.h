#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H
#include <string>
#include <entityx/Entity.h>
#include <assimp/scene.h>
#include <BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <entityx/System.h>

struct LoadInfo {
    bool shouldLoad = false;
    std::string info;
    std::string model;
    std::string collision;
};

class Map: public entityx::System<Map>{
    entityx::Entity m_entity;
    entityx::Entity m_player;
    std::vector<entityx::Entity> m_entities;
    entityx::EntityManager& m_manager;
    std::shared_ptr<btDynamicsWorld> m_world;
    std::unique_ptr<btTriangleMesh> m_mesh;
    void loadTriangles(const std::string& path);

    void processNode(aiNode* node, const aiScene* scene);
    void load(const std::string &info, const std::string &model, const std::string &collision);
    void destroy() {
        for(entityx::Entity entity: m_entities) {
            entity.destroy();
        }
        m_player.destroy();
        m_entity.destroy();
        m_entities.clear();
    }
    std::shared_ptr<LoadInfo> m_loadInfo;
public:
    Map(const std::string& modelPath, const std::string& collisionObject, const std::string& infoPath, entityx::EntityManager& manager, std::shared_ptr<btDynamicsWorld> world);

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;

};

#endif //PROJECT_MAP_H
