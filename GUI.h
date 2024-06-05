#ifndef GUI_CLASS_H
#define GUI_CLASS_H

#include <string>

#include "raylib.h"

class GUI {
	public:
		GUI(int screenWidth, int screenHeight);
		void DrawGUI(int screenWidth, int screenHeight, Vector3 cords);
		void CheckIfButtonPressed();
		void CheckIfMouseOnButton(bool &writing);

	private:
		Rectangle guiRectangle, acceptRectangle, startRectangle, finishRectangle, executeRectangle, manualRectangle, xRectangle, yRectangle, zRectangle;
		Color guiColor, buttonColor;
		char x_input[3] = "\0", y_input[3] = "\0", z_input[3] = "\0";
};

#endif // GUI_CLASS_H