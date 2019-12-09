#include "testing.h"

using namespace godot;

void Testing::_register_methods() {
	register_method("_process", &Testing::_process);
	register_method("_physics_process", &Testing::_physics_process);
	register_method("_movement_process", &Testing::_movement_process);
	register_method("_ready", &Testing::_ready);
}

Testing::Testing() {
}

Testing::~Testing() {
}

void Testing::_ready() {
	position = get_position().snapped(Vector2(tile_size / 2, tile_size / 2));
	set_position(position);
	target_pos = position;

	abil1 = Ability(Around_user, Fire, 0, 3);
}

void Testing::_init() {

}

void Testing::_process(float delta) {
	
}

void Testing::_physics_process(float delta) {
	//begin = std::chrono::steady_clock::now();
	if (just_moved) {
		//Godot::print("counting up");
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		time_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	}
	
	//Godot::print("time_elapsed: " + String::num(time_elapsed));
	if (time_elapsed >= 300000) {
		//Godot::print("time_elapsed >= 500000");
		_movement_process();
		begin = std::chrono::steady_clock::now();
	}
	else {
		Input* i = Input::get_singleton();
		Vector2 motion = Vector2(0, 0);
		position = get_position();

		if (i->is_action_just_pressed("ui_up")) {
			motion.y--;
		}
		else if (i->is_action_just_pressed("ui_down")) {
			motion.y++;
		}
		else if (i->is_action_just_pressed("ui_left")) {
			motion.x--;
		}
		else if (i->is_action_just_pressed("ui_right")) {
			motion.x++;
		}

		position += motion * tile_size;//speed * delta;

		if (motion != Vector2() && Object::cast_to<TileMap>(get_parent())->get_cell(position.x / tile_size, position.y / tile_size) != -1) {
			//translate(motion * speed * delta);
			set_position(position);
			just_moved = true;
			begin = std::chrono::steady_clock::now();
		}
	}
}

void Testing::_movement_process() {
	//Godot::print("_movement_process");

	Input* i = Input::get_singleton();
	Vector2 motion = Vector2(0, 0);
	position = get_position();

	if (i->is_action_pressed("ui_up")) {
		motion.y--;
	}
	else if (i->is_action_pressed("ui_down")) {
		motion.y++;
	}
	else if (i->is_action_pressed("ui_left")) {
		motion.x--;
	}
	else if (i->is_action_pressed("ui_right")) {
		motion.x++;
	}

	position += motion * tile_size;//speed * delta;

	if (motion != Vector2() && Object::cast_to<TileMap>(get_parent())->get_cell(position.x / tile_size, position.y / tile_size) != -1) {
		//translate(motion * speed * delta);
		set_position(position);
	}
	else {
		time_elapsed = 0;
		just_moved = false;
	}
}