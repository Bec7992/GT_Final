#include "fsm.h"

using namespace godot;

void FSM::update(Node2D* parent) {
    if (state != nullptr) {
        state->execute(parent);
    }
}


void FSM::set_state(Node2D* parent, AbstractState* new_state) {
    if (state != nullptr) {
        state->end(parent);
    }

    state = new_state;

    if (state != nullptr) {
        state->start(parent);
    }
}
