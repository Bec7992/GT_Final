#include "player_handler.h"
#include <SceneTree.hpp>

using namespace godot;

void PlayerHandler::_register_methods() {
	register_method("_process", &PlayerHandler::_process);
	register_method("_physics_process", &PlayerHandler::_physics_process);
	register_method("_movement_process", &PlayerHandler::_movement_process);
	register_method("_ready", &PlayerHandler::_ready);
}

PlayerHandler::PlayerHandler() {
}

PlayerHandler::~PlayerHandler() {
}

void PlayerHandler::_ready() {
	position = get_position().snapped(Vector2(tile_size / 2, tile_size / 2));
	set_position(position);
	target_pos = position;

	abil1 = Ability(Around_user, Fire, 0, 3);
}

void PlayerHandler::_init() {

}

void PlayerHandler::_process(float delta) {
	
}

void PlayerHandler::_physics_process(float delta) {
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

			//Object::cast_to<MapHandler>(get_parent())->player_took_turn();
			begin = std::chrono::steady_clock::now();
		}
	}
}

void PlayerHandler::_movement_process() {
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
		//Object::cast_to<MapHandler>(get_parent())->player_took_turn();
	}
	else {
		time_elapsed = 0;
		just_moved = false;
	}
}