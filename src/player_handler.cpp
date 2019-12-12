#include "player_handler.h"
#include <SceneTree.hpp>

using namespace godot;

void PlayerHandler::_register_methods() {
	register_method("_process", &PlayerHandler::_process);
	register_method("_physics_process", &PlayerHandler::_physics_process);
	register_method("_movement_process", &PlayerHandler::_movement_process);
	register_method("_ready", &PlayerHandler::_ready);
	register_method("_stairs_entered", &PlayerHandler::_stairs_entered);
	register_method("_particle_timeout", &PlayerHandler::_particle_timeout);
	register_method("_fire_pressed", &PlayerHandler::_fire_pressed);
	register_method("_ice_pressed", &PlayerHandler::_ice_pressed);
	register_method("_earth_pressed", &PlayerHandler::_earth_pressed);
}

PlayerHandler::PlayerHandler() {
}

PlayerHandler::~PlayerHandler() {
}

void PlayerHandler::_ready() {
	position = get_position().snapped(Vector2(tile_size / 2, tile_size / 2));
	set_position(position);
	target_pos = position;

	abil1 = Ability("Fire Ball", "FireBall", Around_user, Fire, 20, 7, 3, 3);
	abil2 = Ability("Ice Ball", "IceBall", Around_user, Ice, 20, 7, 3, 3);
	abil3 = Ability("Earth Ball", "EarthBall", Around_user, Earth, 20, 7, 3, 3);

	Node* stairs = get_parent()->get_node("Stairs");
	if (stairs) {
		stairs->connect("area_entered", this, "_stairs_entered");
	}

	Node* timer = get_node("Timer");
	if (timer) {
		timer->connect("timeout", this, "_particle_timeout");
	}

	Node* fire_button = get_node("/root/Node/CanvasLayer/MainMenu/SpellBar/FireBall");
	if (fire_button) {
		fire_button->connect("pressed", this, "_fire_pressed");
	}

	Node* ice_button = get_node("/root/Node/CanvasLayer/MainMenu/SpellBar/IceBall");
	if (ice_button) {
		ice_button->connect("pressed", this, "_ice_pressed");
	}

	Node* earth_button = get_node("/root/Node/CanvasLayer/MainMenu/SpellBar/EarthBall");
	if (earth_button) {
		earth_button->connect("pressed", this, "_earth_pressed");
	}

	//Object::cast_to<HealthBar>(get_node("HealthBar"))->on_health_update(health);
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
		else if (i->is_action_just_pressed("ability1")) {
			Godot::print("ability1 pressed");
			ability_index = 1;
			ability_targeting = true;
		}
		else if (i->is_action_just_pressed("ability2")) {
			Godot::print("ability2 pressed");
			ability_index = 2;
			ability_targeting = true;
		}
		else if (i->is_action_just_pressed("ability3")) {
			Godot::print("ability3 pressed");
			ability_index = 3;
			ability_targeting = true;
		}

		position += motion * tile_size;//speed * delta;

		if (motion != Vector2() && Object::cast_to<TileMap>(get_parent())->get_cell(position.x / tile_size, position.y / tile_size) != -1) {
			//translate(motion * speed * delta);
			set_position(position);
			just_moved = true;

			enemy_turns();
			begin = std::chrono::steady_clock::now();
		}
		else if (ability_targeting) {
			if(i->is_action_just_pressed("click")) {
				Godot::print("ability_targeting click");
				Vector3 enemy_index = Object::cast_to<MapHandler>(get_parent())->get_enemy_index_at_location(get_global_mouse_position());
				//Godot::print("enemy_index = " + enemy_index);
				if (enemy_index.z > -1) {
					Vector2 player_pos = get_global_position();
					player_pos.x = floor(player_pos.x / 16);
					player_pos.y = floor(player_pos.y / 16);

					int abs_distance = abs(enemy_index.x - player_pos.x) + abs(enemy_index.y - player_pos.y);
					if (abs_distance <= abil1.range) {
						if (ability_index == 1)
							enemies[enemy_index.z]->recieve_ability(abil1);
						else if (ability_index == 2)
							enemies[enemy_index.z]->recieve_ability(abil2);
						else if (ability_index == 3)
							enemies[enemy_index.z]->recieve_ability(abil3);

						enemy_turns();

						ability_index = 0;
						ability_targeting = false;
					}
				}

				//ability_index = 0;
				//ability_targeting = false;
			}
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
		enemy_turns();
	}
	else {
		time_elapsed = 0;
		just_moved = false;
	}
}

void PlayerHandler::enemy_turns() {
	change_health(-1);
	if (enemies.size() == 0)
		enemies = Object::cast_to<MapHandler>(get_parent())->get_enemies();

	for (int i = 0; i < enemies.size(); ++i) {
		enemies[i]->_update_movement();
	}
}

void PlayerHandler::_stairs_entered(Area2D* area) {
	String name = area->get_parent()->get_name();

	if (name == "Player") {
		enemies.clear();
	}
}

void PlayerHandler::change_health(int change) {
	if (health - change > 100) {
		health = 100;
	}
	else {
		health -= change;
	}

	Object::cast_to<HealthBar>(get_node("HealthBar"))->on_health_update(health);
}

void PlayerHandler::recieve_ability(Ability enemy_ability) {
	Object::cast_to<Particles2D>(get_node(enemy_ability.particle_name + "/" + enemy_ability.particle_name))->set_emitting(true);
	Object::cast_to<Timer>(get_node("Timer"))->start(1);
	change_health(enemy_ability.damage);
}

void PlayerHandler::death() {
	Godot::print("player death");
	//Object::cast_to<Control>(get_node("Camera2D/GameOver"))->show();
	get_tree()->set_pause(true);
}

void PlayerHandler::enemy_death(int index) {
	enemies.erase(enemies.begin()+index);
}

void PlayerHandler::_particle_timeout() {
	Object::cast_to<Particles2D>(get_node("FireBall/FireBall"))->set_emitting(false);
	Object::cast_to<Particles2D>(get_node("IceBall/IceBall"))->set_emitting(false);
	Object::cast_to<Particles2D>(get_node("EarthBall/EarthBall"))->set_emitting(false);

	if (health <= 0) {
		Godot::print("player health <= 0");
		death();
	}
}

void PlayerHandler::_fire_pressed() {
	Godot::print("_fire_pressed()");
	ability_index = 1;
	ability_targeting = true;
}

void PlayerHandler::_ice_pressed() {
	Godot::print("_ice_pressed()");
	ability_index = 2;
	ability_targeting = true;
}

void PlayerHandler::_earth_pressed() {
	Godot::print("_earth_pressed()");
	ability_index = 3;
	ability_targeting = true;
}