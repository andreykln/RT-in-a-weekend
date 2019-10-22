#pragma once
#include <random>
inline double random_double() {
	return rand() / (RAND_MAX + 1.0);
}