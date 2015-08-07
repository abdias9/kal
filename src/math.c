#include "math.h"

size_t ceil(float value) {
	size_t iv = (size_t) value;
	if (value > (float) iv)
		iv++;
	return iv;
}
