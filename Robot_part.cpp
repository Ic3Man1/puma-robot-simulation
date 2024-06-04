#include "Robot_part.h"
#include <string>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"



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

void Robot_part::rotate(string side, Vector3 man_cords)
{
	//rotating the arm while pressing the right button

	float r = 0.8 * sqrt(2) / 2;
	if(pow(man_cords.x,2)+pow(man_cords.z, 2) > r or man_cords.y > 3)
	{
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
				if (side == "+" and rot_pos_2 + 1 < 180 and (pow(man_cords.x, 2) + pow(man_cords.z, 2) + 1 > r or man_cords.y + 0.1 > 3))
				{
					rot_pos_2++;
				}
				else if (side == "-" and rot_pos_2 - 1 > -180 and (pow(man_cords.x, 2) + pow(man_cords.z, 2) - 1 > r or man_cords.y - 0.1 > 3))
				{
					rot_pos_2--;
				}
			}
		}
		else if (part_number == 3)
		{
			if (rot_pos_3 > -180 and rot_pos_3 < 180)
			{
				if (side == "+" and rot_pos_3 + 1 < 180 and (pow(man_cords.x, 2) + pow(man_cords.z, 2) + 1 > r or man_cords.y + 0.1 > 3))
				{
					rot_pos_3++;
				}
				else if (side == "-" and rot_pos_3 - 1 > -180 and (pow(man_cords.x, 2) + pow(man_cords.z, 2) - 1 > r or man_cords.y - 0.1 > 3))
				{
					rot_pos_3--;
				}
			}
		}
	}
}

void Robot_part::draw()
{
	// rotating cube 1
	rlRotatef(rot_pos_1, 0, 1, 0);

	// rotating cube 2
	rlTranslatef(0.0f, 2.75f, 0.0f);
	rlRotatef(rot_pos_2, 1, 0, 0);

	// rotating cube 3
	rlTranslatef(0.0f, 0.0f, 1.85f);
	rlRotatef(rot_pos_3, 1, 0, 0);
	
	// reseting centre of origin
	rlTranslatef(0.0f, -2.75f, -1.85f);

	DrawCube(cube_position, width, height, length, color);
}

void Robot_part::draw_wire(Color wire_color)
{
	DrawCubeWires(cube_position, width, height, length, wire_color);
}
