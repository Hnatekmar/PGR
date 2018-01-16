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
    m_finished = true;
}

void AnimatedTexture::start() {
    m_frame = 0;
    m_started = true;
    m_finished = false;
    m_delay.start();
}

void AnimatedTexture::bind(GLuint programID) {
    if(m_started && m_delay.elapsed() >= m_frameDuration) {
        m_delay.start();
        if(m_frame < m_frameCount) {
            m_frame += 1;
        } else {
            stop();
        }
    }
    if(m_frame < m_frameCount) {
        m_frames.at(m_frame).bind(programID);
    } else {
        m_frames.at(m_frameCount - 1).bind(programID);
    }
}

