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
        entities.each<CameraComponent>([&](entityx::Entity entity, CameraComponent& cameraComponent) {
                                                           entities.each<GraphicsComponent>([&](entityx::Entity entity, GraphicsComponent &component) {
                                                               glm::mat4 model = glm::translate(glm::mat4(), component.position);
                                                               model = glm::rotate(model, component.angle, component.angleVec);
                                                               component.drawable->draw(cameraComponent.getPVMatrix() * model, shaderProgram);
                                                           });
                                                       });
        SDL_WarpMouseInWindow(m_window, 1024 / 2, 800 / 2);
        SDL_GL_SwapWindow(m_window);
        HANDLE_GL_ERRORS()
    }
}

Engine::~Engine() {
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


