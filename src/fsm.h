#ifndef FSM_H
#define FSM_H
#include <Node2D.hpp>

namespace godot {
    class AbstractState {

    public:
        virtual void start(Node2D* parent) {}
        virtual void execute(Node2D* parent) {}
        virtual void end(Node2D* parent) {}
    };

    class FSM { 

    public:
        AbstractState* state = nullptr;
        void update(Node2D* parent);
        void set_state(Node2D* parent, AbstractState* new_state);
    };
}

#endif