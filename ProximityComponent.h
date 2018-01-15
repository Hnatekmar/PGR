//
// Created by martin on 15.1.18.
//

#ifndef PROJECT_PROXIMITYCOMPONENT_H
#define PROJECT_PROXIMITYCOMPONENT_H


#include <glm/vec3.hpp>
/**
 * Jednoduchý komponent, který zavolá funkci s entitou, která je poblíž. Lze to použít pro různé pickupy (lékarnička, zbraně, náboje...)
 * @tparam Fn
 */
template<typename Fn>
struct ProximityComponent {
    glm::vec3 position;
    double distance;
    Fn function;
    ProximityComponent(const glm::vec3 &position, double distance, Fn function) : position(position),
                                                                                  distance(distance),
                                                                                  function(function) {}
};


#endif //PROJECT_PROXIMITYCOMPONENT_H
