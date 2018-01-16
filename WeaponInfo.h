//
// Created by martin on 9.12.17.
//

#ifndef PROJECT_WEAPONINFO_H
#define PROJECT_WEAPONINFO_H

#include <entityx/Entity.h>
#include <memory>
#include <SDL2/SDL_types.h>
#include <chrono>
#include "Engine/Timer.h"

class btDynamicsWorld;
struct WeaponInfo {
    unsigned damage;
    unsigned clipSize;
    const std::chrono::duration<double, std::milli> weaponCooldown;
    Timer sinceLastShot;
    unsigned ammo;
    bool shooting = true;
    std::shared_ptr<btDynamicsWorld> world;

    explicit WeaponInfo(const unsigned int damage,
               const unsigned int clipSize,
               std::chrono::duration<double, std::milli> cooldown,
               unsigned int ammo,
               std::shared_ptr<btDynamicsWorld> world) : damage(damage),
                                                               clipSize(clipSize),
                                                               weaponCooldown(cooldown),
                                                               sinceLastShot(),
                                                               ammo(ammo),
                                                               world(world) {}

    bool fire() {
        if (shooting && sinceLastShot.elapsed() >= weaponCooldown && ammo > 0) {
            ammo -= 1;
            shooting = false;
            sinceLastShot.start();
            return true;
        }
        return false;
    }
};

#endif //PROJECT_WEAPONINFO_H
