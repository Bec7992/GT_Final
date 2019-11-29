
#include "base_ai.h"
#include <queue>
#include <vector>

using namespace godot;

void WanderState::start(Node* parent) {
}

void WanderState::execute(Node* parent) {
    
}


void WanderState::end(Node* parent) {
    //Godot::print("end wander");
}

void AttackState::start(Node* parent) {

}

void AttackState::execute(Node* parent) {
    
}

void AttackState::end(Node* parent) {

}

void RunAwayState::start(Node* parent) {

}

void RunAwayState::execute(Node* parent) {
    
}

void RunAwayState::end(Node* parent) {

}

void BaseAI::_register_methods() {
	register_method("_ready", &BaseAI::_ready);
	register_method("_process", &BaseAI::_process);
	register_method("_physics_process", &BaseAI::_physics_process);
}

void BaseAI::_ready() {
	brain.set_state(this, &wanderState);
}

void BaseAI::_process(float delta) {
    //brain.update(this, delta);
}

void BaseAI::_physics_process(float delta) {
    
}

void BaseAI::_update_movement(Vector3 direction) {
}