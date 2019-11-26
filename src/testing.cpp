#include "testing.h"

using namespace godot;

void Testing::_register_methods() {
	register_method("_ready", &Testing::_ready);
    register_method("_process", &Testing::_process);
}

Testing::Testing() {
}

Testing::~Testing() {
}

void Testing::_ready() {

}

void Testing::_process() {
	
}