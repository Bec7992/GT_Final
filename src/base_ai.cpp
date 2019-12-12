
#include "base_ai.h"
#include "map_handler.h"
#include "player_handler.h"
#include <queue>
#include <vector>

using namespace godot;

void WanderState::start(Node2D* parent) {
	//path = Object::cast_to<MapHandler>(parent->get_node("/root/Node/TileMap"))->get_path_random();
	Godot::print("WanderState: start");
}

void WanderState::execute(Node2D* parent) {
	Vector2 world_position = parent->get_position();
	Vector2 map_position = world_position / 16;
	map_position.x = floor(map_position.x);
    map_position.y = floor(map_position.y);
    if (path.size() <= path_index) {
    	while (path.size() <= path_index) {
    		//Godot::print("wander path.size() = " + String::num_int64(path.size()));
    		path = Object::cast_to<MapHandler>(parent->get_node("/root/Node/TileMap"))->get_path_random(Vector2(map_position.x, map_position.y));
    		path_index = 0;
    	}
    	//path_index = 1;
    }
    Godot::print("path index = " + String::num_int64(path_index));

	Vector2 direction = Vector2(path[path_index].x, path[path_index].y) - (map_position);
	Vector2 new_position = world_position + (direction * tile_size);
	parent->set_position(new_position);

	//TODO: put an if here so if new get_position == world_position, don't increment path_index.
	// If gets stuck on player.
	++path_index;
}


void WanderState::end(Node2D* parent) {
    //Godot::print("end wander");
}

void AttackState::start(Node2D* parent) {

}

void AttackState::execute(Node2D* parent) {
	Vector2 world_position = parent->get_position();
	Vector2 map_position = world_position / 16;
	map_position.x = floor(map_position.x);
    map_position.y = floor(map_position.y);

    Vector2 player_cell = Object::cast_to<MapHandler>(parent->get_node("/root/Node/TileMap"))->get_player_cell();
    int abs_distance = abs(map_position.x - player_cell.x) + abs(map_position.y - player_cell.y);

    if (Object::cast_to<BaseAI>(parent)->abil1.cooldown_left == 0 && abs_distance <= Object::cast_to<BaseAI>(parent)->abil1.range) {
    	Object::cast_to<PlayerHandler>(parent->get_node("/root/Node/TileMap/Player"))->recieve_ability(Object::cast_to<BaseAI>(parent)->abil1);
    	Object::cast_to<BaseAI>(parent)->abil1.cooldown_left = Object::cast_to<BaseAI>(parent)->abil1.cooldown;
    }
    else {
	    path = Object::cast_to<MapHandler>(parent->get_node("/root/Node/TileMap"))->get_path_to_player(Vector2(map_position.x, map_position.y));
	    while (path.size() == 0) {
	    	//Godot::print("path size = " + String::num_int64(path.size()));
	    	path = Object::cast_to<MapHandler>(parent->get_node("/root/Node/TileMap"))->get_path_to_player(Vector2(map_position.x, map_position.y));
	    }
	    Godot::print("path size = " + String::num_int64(path.size()));
	    Vector2 direction = Vector2(path[1].x, path[1].y) - (map_position);
		Vector2 new_position = world_position + (direction * tile_size);
		parent->set_position(new_position);
	}

}

void AttackState::end(Node2D* parent) {

}

void RunAwayState::start(Node2D* parent) {

}

void RunAwayState::execute(Node2D* parent) {
    
}

void RunAwayState::end(Node2D* parent) {

}

void BaseAI::_register_methods() {
	register_method("_ready", &BaseAI::_ready);
	register_method("_process", &BaseAI::_process);
	register_method("_physics_process", &BaseAI::_physics_process);
	register_method("_area_entered", &BaseAI::_area_entered);
	register_method("_area_exited", &BaseAI::_area_exited);
	register_method("_particle_timeout", &BaseAI::_particle_timeout);
}

BaseAI::BaseAI() {

}

BaseAI::~BaseAI() {

}

void BaseAI::_init() {

}

void BaseAI::_ready() {
	brain.set_state(this, &wanderState);

	abil1 = Ability("Fire Ball", "FireBall", Around_user, Fire, 5, 3, 2, 3);

	Node* area = get_node("EnemyArea");
	if (area) {
		area->connect("area_entered", this, "_area_entered");
		area->connect("area_exited", this, "_area_exited");
	}

	Node* timer = get_node("Timer");
	if (timer) {
		timer->connect("timeout", this, "_particle_timeout");
	}
}

void BaseAI::_process(float delta) {
    //brain.update(this, delta);
}

void BaseAI::_physics_process(float delta) {
    
}

void BaseAI::_update_movement() {
	brain.update(this);

	//Godot::print("enemy cooldown_left = " + String::num_int64(abil1.cooldown_left));
	if (abil1.cooldown_left != 0) {
		--abil1.cooldown_left;
	}
	//Godot::print("_update_movement");
}

void BaseAI::change_health(int change) {
	if (health - change > 100) {
		health = 100;
	}
	else {
		health -= change;
	}
	Object::cast_to<HealthBar>(get_node("HealthBar"))->on_health_update(health);
}

void BaseAI::death() {
	Godot::print("enemy death");
	Object::cast_to<MapHandler>(get_parent()->get_node("/root/Node/TileMap"))->enemy_death(get_global_position());
}

void BaseAI::recieve_ability(Ability ability) {
	//Godot::print("recieve_ability");
	//Godot::print("damage = " + String::num_int64(ability.damage));
	Godot::print("about to set emitting true");
	Object::cast_to<Particles2D>(get_node(ability.particle_name + "/" + ability.particle_name))->set_emitting(true);
	Godot::print("set emitting true");
	Object::cast_to<Timer>(get_node("Timer"))->start(1);
	change_health(ability.damage);
}

void BaseAI::_area_entered(Area2D* area) {
	if (area->get_name() == "PlayerArea") {
		Object::cast_to<Node2D>(get_node("EnemyArea"))->set_scale(Vector2(12, 12));
		brain.set_state(this, &attackState);
	}
}

void BaseAI::_area_exited(Area2D* area) {
	if (area->get_name() == "PlayerArea") {
		Object::cast_to<Node2D>(get_node("EnemyArea"))->set_scale(Vector2(8, 8));
		brain.set_state(this, &wanderState);
	}
}

void BaseAI::_particle_timeout() {
	Godot::print("enemy::_particle_timeout");
	Object::cast_to<Particles2D>(get_node("FireBall/FireBall"))->set_emitting(false);
	if (health <= 0) {
		death();
	}
}