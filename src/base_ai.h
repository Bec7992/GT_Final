#ifndef BASE_AI_H
#define BASE_AI_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <SceneTree.hpp>
#include <Node.hpp>
#include <Viewport.hpp>
#include <AStar.hpp>
#include <Area.hpp>
#include <string>
#include "fsm.h"
//#include "map_handler.h"

namespace godot {

	class WanderState : public AbstractState {
	public:
        PoolVector3Array path;

		void start(Node* parent) override;
		void execute(Node* parent) override;
		void end(Node* parent) override;
	};

	class AttackState : public AbstractState {
	public:
		NodePath current_target = "";
		NodePath current_target_rotation = "";

		void start(Node* parent) override;
		void execute(Node* parent) override;
		void end(Node* parent) override;
	};

	class RunAwayState : public AbstractState {
		public:
		Array path = Array{};
		NodePath current_waypoint = "";

		void start(Node* parent) override;
		void execute(Node* parent) override;
		void end(Node* parent) override;
	};

	class BaseAI : public KinematicBody2D {
		GODOT_CLASS(BaseAI, KinematicBody2D)
	private:
		Vector2 motion = Vector2(0, 0);

	public:
		FSM brain;
		WanderState wanderState;
		AttackState attackState;
		RunAwayState runAwayState;

		static void _register_methods();
        
        void _ready();
        void _process(float delta);
        void _physics_process(float delta);
        void _update_movement(Vector3 direction);
	};
}

#endif