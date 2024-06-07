#ifndef GUI_CLASS_H
#define GUI_CLASS_H

#include <string>

#include "raylib.h"

class GUI {
	public:
		GUI(int screenWidth, int screenHeight);
		void DrawGUI(int screenWidth, int screenHeight, Vector3 cords, int game_state);
		void CheckIfMouseOnButton(bool& writing);
		Vector3 ReturnFinalCoordinates();
		void CheckIfButtonPressed(int &game_state);

	private:
		Rectangle guiRectangle, acceptRectangle, startRectangle, finishRectangle, executeRectangle, manualRectangle, xRectangle, yRectangle, zRectangle;
		Color guiColor, buttonColor;
		char x_input[6] = "\0", y_input[6] = "\0", z_input[6] = "\0";
		int letter_count_x = 0, letter_count_y = 0, letter_count_z = 0;
};

#endif // GUI_CLASS_H