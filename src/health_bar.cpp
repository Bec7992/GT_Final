#include "health_bar.h"

using namespace godot;

void HealthBar::_register_methods() {
	register_method("_ready", &HealthBar::_ready);
	register_method("on_health_update", &HealthBar::on_health_update);
}

HealthBar::HealthBar() {
}

HealthBar::~HealthBar() {
}

void HealthBar::_ready() {
}

void HealthBar::_init() {

}

void HealthBar::on_health_update(int health) {
	//Godot::print("on_health_update");
	//Godot::print("health = " + String::num_int64(health));
	Object::cast_to<TextureProgress>(get_node("HealthBar"))->set_value(health);
}