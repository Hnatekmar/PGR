#include <iostream>
#include "Engine.h"
#include "Shader.h"
#include "Exceptions/EngineException.h"
#include "Primitives/Model.h"
#include <glm/gtx/transform.hpp>
#include <il.h>
#include "GraphicsComponent.h"
#include "SDLEvent.h"

Engine::Engine(const char* name) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        // ERROR HANDLING
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Couldn't initialize video");
    } else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        //SDL_SetRelativeMouseMode(SDL_TRUE);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    1024, 800, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if(m_window == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Couldn't initialize window");
        }
        m_context = SDL_GL_CreateContext(m_window);
        SDL_GL_SetSwapInterval(1);
        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize glew");
        }
        ilInit();
    }
}

#include "Camera.h"
#include "../GuiComponent.h"
#include "../Health.h"
#include "../GuiBar.h"
#include "../WeaponInfo.h"
#include "LightComponent.h"

void Engine::update() {
    auto shaderProgram = glCreateProgram();
    auto vertex = compileShader(GL_VERTEX_SHADER, "default.vert");
    auto fragment = compileShader(GL_FRAGMENT_SHADER, "default.frag");
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glLinkProgram(shaderProgram);
    HANDLE_GL_ERRORS()
    glUseProgram(shaderProgram);
    GuiBar healthBar{
            "health_gauge.png"
    };
    GuiBar ammoBar{
            "ammo_gauge.png"
    };
    SDL_Event event{};
    bool run = true;
    auto previousFrameTimestamp = SDL_GetTicks();
    glEnable(GL_DEPTH_TEST);
    while(run) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) run = false;
            else {
                events.emit<SDLEvent>(event);
            }
        }
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        auto current = SDL_GetTicks();
        auto delta = current - previousFrameTimestamp;
        previousFrameTimestamp = current;
        systems.update_all(delta / 1000.0);
        entities.each<Health, GuiComponent, WeaponInfo>([&](entityx::Entity entity, Health& health, GuiComponent &component, WeaponInfo& weaponInfo) {
            if(component.gun != nullptr) {
                glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0.0, -0.8, 0));
                component.gun->draw(model, shaderProgram);
            }
            glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(-0.99, -0.9, 0));
            healthBar.draw(model, shaderProgram, health.healthPoints, 100.0f);
            model = glm::translate(glm::mat4(), glm::vec3(0.49, -0.9, 0));
            ammoBar.draw(model, shaderProgram, weaponInfo.ammo % weaponInfo.clipSize, weaponInfo.clipSize);
        });
        std::vector<glm::vec3> lights;
        entities.each<LightComponent>([&lights](entityx::Entity entity, LightComponent& component) {
            lights.push_back(component.position);
        });
        assert(lights.size() <= 8);
        auto lightAttributePosition = glGetUniformLocation(shaderProgram, "numberOfLights");
        assert(lightAttributePosition != -1);
        glUniform1i(lightAttributePosition, static_cast<GLint>(lights.size()));
        std::size_t index = 1;
        for(auto& light: lights) {
            std::string lightIndex = "lights[";
            lightIndex += index + "]";
            glUniform3fv(glGetUniformLocation(shaderProgram, lightIndex.c_str()),
                         1,
                         &light[0]);
            index += 1;
        }
        entities.each<CameraComponent>([&](entityx::Entity entity, CameraComponent& cameraComponent) {
            glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"),
                         1,
                         &cameraComponent.getPosition()[0]);
            entities.each<GraphicsComponent>([&](entityx::Entity entity, GraphicsComponent &component) {
                glm::mat4 model = glm::translate(glm::mat4(), component.position);
                model = glm::rotate(model, component.angle, component.angleVec);
                glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
                component.drawable->draw(cameraComponent.getPVMatrix() * model, shaderProgram);
            });
        });
        SDL_GL_SwapWindow(m_window);
        HANDLE_GL_ERRORS()
    }
}

Engine::~Engine() {
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


