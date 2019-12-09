#ifndef BASE_AI_H
#define BASE_AI_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <SceneTree.hpp>
#include <Node.hpp>
#include <Node2D.hpp>
#include <Viewport.hpp>
#include <AStar.hpp>
#include <Area2D.hpp>
#include <string>
#include "fsm.h"
#include "health_bar.h"
#include "ability.h"

//class MapHandler;

namespace godot {

	class WanderState : public AbstractState {
	public:
        PoolVector3Array path;
        int path_index = 1;
        int tile_size = 16;

		void start(Node2D* parent) override;
		void execute(Node2D* parent) override;
		void end(Node2D* parent) override;
	};

	class AttackState : public AbstractState {
	public:
		PoolVector3Array path;
		int path_index = 0;
		int tile_size = 16;

		void start(Node2D* parent) override;
		void execute(Node2D* parent) override;
		void end(Node2D* parent) override;
	};

	class RunAwayState : public AbstractState {
		public:
		Array path = Array{};
		NodePath current_waypoint = "";

		void start(Node2D* parent) override;
		void execute(Node2D* parent) override;
		void end(Node2D* parent) override;
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

		Ability abil1;

		int health = 100;

		static void _register_methods();
        
        BaseAI();
        ~BaseAI();

        void _init();
        void _ready();
        void _process(float delta);
        void _physics_process(float delta);
        void _update_movement();
        void change_health(int change);
        void death();
        void recieve_ability(Ability ability);
        void _area_entered(Area2D* area);
        void _area_exited(Area2D* area);
	};
}

#endif