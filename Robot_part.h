#pragma once
#include <string>
#include "raylib.h"
using namespace std;

class Robot_part {
private:
	int part_number, slices;
	float length, height, width;
	Vector3 cube_position;
	Color color;
public:
	int rot_pos_1 = 0, rot_pos_2 = 0, rot_pos_3 = 0;

	Robot_part(int part_number, Vector3 cube_position, float width, float height, float length , Color color);
	void rotate(string side);
	void draw();
	void draw_wire(Color wire_color);
};