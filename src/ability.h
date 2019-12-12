#ifndef ABILITY_H
#define ABILITY_H
#include <Node.hpp>

enum Target {On_user, On_target, Around_user, Around_target, Line};
enum Element {None, Fire, Water, Earth};

namespace godot {

    class Ability { 

    public:
    	String name;
        String particle_name;
        Target target;
        Element element;
        int damage;
        int range;
        int radius;
        int cooldown;
        int cooldown_left = 3;

        Ability();
        Ability(String name, String particle_name, Target target, Element element, int damage, int range, int radius, int cooldown);
    };
}

#endif