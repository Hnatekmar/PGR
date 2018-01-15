//
// Created by martin on 15.1.18.
//

#ifndef PROJECT_ANIMATEDTEXTURE_H
#define PROJECT_ANIMATEDTEXTURE_H

#include <string>
#include <vector>
#include "Primitives/Texture.h"
#include "Timer.h"
#include <chrono>
#include "IDrawable.h"

class AnimatedTexture {
    std::size_t m_frame; // Aktualní snímek
    std::size_t m_frameCount;
    Timer m_delay;
    const std::chrono::duration<double, std::milli> m_frameDuration;
    std::vector<Texture> m_frames;
    bool m_started;
public:
    explicit AnimatedTexture(const std::vector<std::string> path, const std::chrono::duration<double, std::milli> frameDuration);
    void start();
    void stop();
    void bind(GLuint programID);
};


#endif //PROJECT_ANIMATEDTEXTURE_H
