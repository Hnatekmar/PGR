#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H
#include <string>
#include <entityx/Entity.h>
#include <LinearMath/btVector3.h>
#include <assimp/scene.h>
#include <BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>

class Map {
    entityx::Entity m_entity;
    std::unique_ptr<btTriangleMesh> m_mesh;
    void loadTriangles(const std::string& path);

    void processNode(aiNode* node, const aiScene* scene);
    void loadFromJson(const std::string& path);
public:
    Map(const std::string& modelPath, const std::string& collisionObject, const std::string& infoPath, entityx::EntityManager& manager, std::shared_ptr<btDynamicsWorld> world);

};

#endif //PROJECT_MAP_H
