#include "Robot_part.h"
#include <string>
#include "raylib.h"
using namespace std;

Robot_part::Robot_part(string rotation_axis, Vector3 cube_position, float width, float height, float length, Color color)
{
	this->rotation_axis = rotation_axis;
	this->cube_position = cube_position;
	this->length = length;
	this->width = width;
	this->height = height;
	this->color = color;
}

int Robot_part::rotation()
{
	//rotating the arm while pressing the right button
	return rot_pos;
}

void Robot_part::draw()
{
	DrawCube(cube_position, width, height, length, color);
}

void Robot_part::draw_wire(Color wire_color)
{
	DrawCubeWires(cube_position, width, height, length, wire_color);
}