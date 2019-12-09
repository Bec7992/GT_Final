#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include <Godot.hpp>
#include <Control.hpp>
#include <TextureProgress.hpp>

namespace godot {

	class HealthBar : public Control {
		GODOT_CLASS(HealthBar, Control)

	private:

	public:

		static void _register_methods();

		HealthBar();
		~HealthBar();

		void _init();
		void _ready();
		void on_health_update(int health);
	};
}

#endif