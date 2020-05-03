#include "zMath.h"



Matrix Matrix::tmps[64];
Transform Transform::tmps[64];

Quaternion rotationQuat(float p, float y, float r) {
	return yawQuat(y)*pitchQuat(p)*rollQuat(r);
}