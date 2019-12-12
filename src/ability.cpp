#include "ability.h"

using namespace godot;

Ability::Ability() {

}

Ability::Ability(String name, String particle_name, Target target, Element element, int damage, int range, int radius, int cooldown) : 
	name(name), particle_name(particle_name), target(target), element(element), damage(damage), range(range), radius(radius), cooldown(cooldown) {

}