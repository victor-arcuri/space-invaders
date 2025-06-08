#include <math.h>
#include "utilidades.h"

float ease_in_out_sine(float t) {
    return -(cos(M_PI * t) - 1) / 2;
}

float ease_in_quad(float t) {
    return t * t;
}