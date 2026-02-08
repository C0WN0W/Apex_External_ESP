#include "Structs.hpp"

Vector3::Vector3(void) {
	x = y = z = 0.0f;
}

Vector3::Vector3(float fx, float fy, float fz) {
	x = fx;
	y = fy;
	z = fz;
}

Vector3::~Vector3(void) {
};