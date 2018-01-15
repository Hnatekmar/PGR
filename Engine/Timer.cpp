//
// Created by martin on 5.1.18.
//

#include "Timer.h"
#include <ratio>
#include <chrono>

Timer::Timer(): m_start(std::chrono::system_clock::now()) {
}

void Timer::start() {
    m_start = std::chrono::system_clock::now();
}

const std::chrono::duration<double, std::milli> Timer::elapsed() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_start);
}
