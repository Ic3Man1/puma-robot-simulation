#ifndef ROBOT_PART_H
#define ROBOT_PART_H

#include <string>
#include "raylib.h"
#include "raymath.h"

using namespace std;

class Robot_part {
private:
	int part_number, slices;
	float length, height, width;
	Color color;
public:
	Vector3 cube_position;
	int rot_pos_1 = 0, rot_pos_2 = 0, rot_pos_3 = 0;

	Robot_part(int part_number, Vector3 cube_position, float width, float height, float length , Color color);
	void rotate(string side, Vector3 man_cords, Vector3 rot_axis_coord);
	void draw();
	void draw_wire(Color wire_color);
};

#endif // ROBOT_PART_H