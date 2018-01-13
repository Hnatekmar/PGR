#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Exceptions/EngineException.h"
#include "PlayerMotionSystem.h"
#include "PhysicsSystem.h"
#include "Map.h"
#include "ShootingSystem.h"
#include "RotationSystem.h"

int main() {
    try {
        Engine engine("FPS");
        engine.systems.add<PlayerMotionSystem>();
        engine.systems.add<PhysicsSystem>();
        engine.systems.add<ShootingSystem>();
        engine.systems.add<RotationSystem>();
        engine.systems.configure();
        Map map("level.obj", "level.obj", engine.entities, engine.systems.system<PhysicsSystem>()->getWorld());
        engine.update();
    } catch (EngineException& ex) {
        std::cerr << ex.error() << std::endl;
    }
    return 0;
}
