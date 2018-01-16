//
// Created by martin on 27.10.17.
//

#include "EngineException.h"

EngineException::EngineException(GLenum error) {
#ifndef __APPLE__ // gluErrorString je v OS X označen za zastaralý a není podporovaný
    m_error = (char*)(gluErrorString(error));
#else
    m_error = "";
#endif
}


std::string EngineException::error() const {
    return m_error;
}
