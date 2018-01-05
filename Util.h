//
// Created by martin on 5.1.18.
//

#ifndef PROJECT_UTIL_H
#define PROJECT_UTIL_H
/*
 * Převede jeden vektor na druhý (například btVector3 na glm::vec3)
 */
template<typename To, typename From>
To convert(const From& vector) {
    return {vector.x, vector.y, vector.z};
}

#endif //PROJECT_UTIL_H
