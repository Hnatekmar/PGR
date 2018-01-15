//
// Created by martin on 15.1.18.
//

#include "AnimatedTexture.h"
#include <algorithm>

AnimatedTexture::AnimatedTexture(const std::vector<std::string> path,
                                 const std::chrono::duration<double, std::milli> frameDuration):
        m_frame(0),
        m_delay(),
        m_frameCount(path.size()),
        m_frameDuration(frameDuration),
        m_started(true) {
    std::for_each(path.cbegin(), path.cend(), [&](const std::string& path) {
        m_frames.emplace_back(TextureType::diffuse, path);
    });
}

void AnimatedTexture::stop() {
    m_frame = 0;
    m_started = false;
}

void AnimatedTexture::start() {
    m_frame = 0;
    m_started = true;
    m_delay.start();
}

void AnimatedTexture::bind(GLuint programID) {
    if(m_started && m_delay.elapsed() >= m_frameDuration) {
        if(m_frame + 1 < m_frameCount) {
            m_frame += 1;
            m_delay.start();
        } else {
            start();
        }
    }
    m_frames.at(m_frame).bind(programID);
}

