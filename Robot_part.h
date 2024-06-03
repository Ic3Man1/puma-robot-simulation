#pragma once
#include <string>
#include "raylib.h"
using namespace std;

class Robot_part {
private:
	string rotation_axis;
	Vector3 cube_position;
	float length, height, width;
	int slices;
	Color color;
public:
	int rot_pos = 0;
	Robot_part(string rotation_axis, Vector3 cube_position, float width, float height, float length , Color color);
	int rotation();
	void draw();
	void draw_wire(Color wire_color);
};