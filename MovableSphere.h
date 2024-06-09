#ifndef MOVABLE_SPHERE_H
#define MOVABLE_SPHERE_H

#include "Robot_part.h"

class MovableSphere {
	public:
		Vector3 postion;
		float radious;

		MovableSphere(Vector3 sphere_position, float sphere_radious);
		void Draw();
		void FollowManipulator(Vector3 current_manipulator_cords);

	private:

};

#endif // MOVABLE_SPHERE_H