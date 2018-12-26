
#include "node.hpp"

float node::minLength;
void node::set_minLength(float l) { minLength = l; }


int random(const int begin, const int end) {
	int num = rand() % (end - begin);
	return num + begin;
};

int myrandom() {
	return random(1, 5);
}