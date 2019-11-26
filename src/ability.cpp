#include "ability.h"

using namespace godot;

Ability::Ability() {

}

Ability::Ability(Target target, Element element, int range, int radius) : 
	target(target), element(element), range(range), radius(radius) {

}