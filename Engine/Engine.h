#ifndef PROJECT_ENGINE_H
#define PROJECT_ENGINE_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <entityx/entityx.h>

/*!
 * \brief Třída starající se o běh enginu.
 */
class Engine {

    SDL_Window* m_window;
    SDL_GLContext m_context;
    entityx::EntityX m_entityManager;
public:
    explicit Engine(const char* name);
    ~Engine();
    void update();
    entityx::EntityX& getEntityManager();
};


#endif //PROJECT_ENGINE_H
