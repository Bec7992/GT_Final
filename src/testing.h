#ifndef TESTING_H
#define TESTING_H

#include <Godot.hpp>
#include <Node.hpp>

namespace godot {

	class Testing : public Node {
		GODOT_CLASS(Testing, Node)

	private:

	public:

		static void _register_methods();

		Testing();
		~Testing();
		void _ready();
		void _process();
	};
}

#endif