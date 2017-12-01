//
// Created by martin on 1.12.17.
//

#ifndef PROJECT_PLAYERMOTIONSYSTEM_H
#define PROJECT_PLAYERMOTIONSYSTEM_H


#include <entityx/Event.h>
#include <entityx/System.h>
#include "Engine/SDLEvent.h"

class PlayerMotionSystem: public entityx::System<PlayerMotionSystem>,
                          public entityx::Receiver<PlayerMotionSystem> {
    bool m_forwardPressed;
    bool m_backwardPressed;
    float m_yaw;
    float m_pitch;
public:

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;

private:
    void configure(entityx::EventManager &events) override;

public:
    void receive(const SDLEvent& event);

};


#endif //PROJECT_PLAYERMOTIONSYSTEM_H
