//
// Created by martin on 15.1.18.
//

#include "ProximitySystem.h"
#include "ProximityComponent.h"
#include "Engine/Camera.h"

#define Fn std::function<void(entityx::Entity, entityx::Entity)>

void ProximitySystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
    entities.each<ProximityComponent<Fn>>([&](entityx::Entity sensor, ProximityComponent<Fn>& component){
        entities.each<CameraComponent>([&](entityx::Entity entity, CameraComponent& camera) {
            float distance = glm::distance(component.position, camera.getPosition());
            if(distance < component.distance) {
                component.function(sensor, entity);
            }
        });
    });
}
