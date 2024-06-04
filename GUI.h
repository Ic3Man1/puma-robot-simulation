#ifndef GUI_CLASS_H
#define GUI_CLASS_H

#include "raylib.h"

class GUI {
	public:
		GUI(int screenWidth, int screenHeight);
		void DrawGUI(int screenWidth, int screenHeight);
		void CheckIfButtonPressed();

	private:
		Rectangle guiRectangle, acceptRectangle, startRectangle, finishRectangle, executeRectangle, manualRectangle;
		Color guiColor, buttonColor;
};

#endif // GUI_CLASS_H