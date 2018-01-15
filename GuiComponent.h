//
// Created by martin on 15.1.18.
//

#ifndef PROJECT_GUICOMPONENT_H
#define PROJECT_GUICOMPONENT_H

#include <memory>
#include "Billboard.h"

struct GuiComponent {
    std::shared_ptr<Billboard> gun = nullptr;
};

#endif //PROJECT_GUICOMPONENT_H
