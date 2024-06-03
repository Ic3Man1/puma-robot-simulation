#include "Robot_part.h"
#include <string>
#include "raylib.h"
#include "rlgl.h"


using namespace std;

Robot_part::Robot_part(int part_number, Vector3 cube_position, float width, float height, float length, Color color)
{
	this->part_number = part_number;
	this->cube_position = cube_position;
	this->length = length;
	this->width = width;
	this->height = height;
	this->color = color;
}

void Robot_part::rotate(string side)
{
	//rotating the arm while pressing the right button
	if (part_number == 1)
	{
		if (rot_pos_1 > -180 and rot_pos_1 < 180)
		{
			if (side == "+" and rot_pos_1 + 1 < 180)
			{
				rot_pos_1++;
			}
			else if (side == "-" and rot_pos_1 - 1 > -180)
			{
				rot_pos_1--;
			}
		}
	}
	else if (part_number == 2)
	{
		if (rot_pos_2 > -180 and rot_pos_2 < 180)
		{
			if (side == "+" and rot_pos_2 + 1 < 180)
			{
				rot_pos_2++;
			}
			else if (side == "-" and rot_pos_2 - 1 > -180)
			{
				rot_pos_2--;
			}
		}
	}
	else if (part_number == 3)
	{
		if (rot_pos_3 > -180 and rot_pos_3 < 180)
		{
			if (side == "+" and rot_pos_3 + 1 < 180)
			{
				rot_pos_3++;
			}
			else if (side == "-" and rot_pos_3 - 1 > -180)
			{
				rot_pos_3--;
			}
		}
	}
}

void Robot_part::draw()
{
	rlRotatef(rot_pos_1, 0, 1, 0);
	rlRotatef(rot_pos_2, 0, 0, 1);
	rlRotatef(rot_pos_3, 0, 0, 1);
	DrawCube(cube_position, width, height, length, color);
}

void Robot_part::draw_wire(Color wire_color)
{
	DrawCubeWires(cube_position, width, height, length, wire_color);
}