#ifndef ABILITY_H
#define ABILITY_H
#include <Node.hpp>

enum Target {On_user, On_target, Around_user, Around_target, Line};
enum Element {None, Fire, Water, Earth};

namespace godot {

    class Ability { 

    public:
        Target target;
        Element element;
        int range;
        int radius;

        Ability();
        Ability(Target target, Element element, int range, int radius);
    };
}

#endif