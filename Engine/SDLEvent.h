//
// Created by martin on 29.11.17.
//

#ifndef PROJECT_KEYBOARDEVENT_H
#define PROJECT_KEYBOARDEVENT_H

#include <SDL2/SDL_events.h>

struct SDLEvent {
    SDL_Event event;
    SDLEvent(SDL_Event ev): event(ev) {

    }
};

#endif //PROJECT_KEYBOARDEVENT_H
