#include "MovableSphere.h"

MovableSphere::MovableSphere(Vector3 sphere_position, float sphere_radious) 
	:  postion(sphere_position), radious(sphere_radious) {
	
}

void MovableSphere::Draw() {
	DrawSphere(postion, radious, RED);
}

void MovableSphere::FollowManipulator(Vector3 current_manipulator_cords) {
	postion = current_manipulator_cords;
}