//
// Created by martin on 5.1.18.
//

#ifndef PROJECT_TIMER_H
#define PROJECT_TIMER_H

#include <chrono>

/**
 * Jednoduchá třída pro měření času. Mírně inspirováná třídou QTimer z Qt
 */
class Timer {
    std::chrono::system_clock::time_point m_start;
public:
    Timer();
    void start();
    const std::chrono::duration<double, std::milli> elapsed() const;
};


#endif //PROJECT_TIMER_H
