#include "GUI.h"
#include "Robot_part.h"
#include "stateNames.h"

#include <iostream>

GUI::GUI(int screenWidth, int screenHeight) {
	guiRectangle = { 0, (float)(screenHeight - screenHeight * 0.3), (float)(screenWidth), (float)(screenHeight * 0.3) };
    acceptRectangle = { 10, (float)(screenHeight - screenHeight * 0.3 + 130),  (float)(screenWidth / 6), (float)(screenHeight * 0.1) };
    startRectangle = { (float)(screenWidth / 5), (float)(screenHeight - screenHeight * 0.3 + 30),  (float)(screenWidth / 5), (float)(screenHeight * 0.1)};
    finishRectangle = { (float)(screenWidth / 5), (float)(screenHeight - screenHeight * 0.3 + 130),  (float)(screenWidth / 5), (float)(screenHeight * 0.1) };
    executeRectangle = { (float)(screenWidth / 2 - 120), (float)(screenHeight - screenHeight * 0.3 + 30),  (float)(screenWidth / 5 - 30), (float)(screenHeight * 0.1 + 100) };
    manualRectangle = { (float)(screenWidth / 5 * 3 + 30), (float)(screenHeight - screenHeight * 0.3 + 30),  (float)(screenWidth / 5), (float)(screenHeight * 0.07) };
    xRectangle = { 40, (float)(screenHeight - screenHeight * 0.3 + 30),  (float)(screenWidth / 6)-30, (float)(screenHeight * 0.03) };
    yRectangle = { 40, (float)(screenHeight - screenHeight * 0.3 + 62),  (float)(screenWidth / 6) - 30, (float)(screenHeight * 0.03) };
    zRectangle = { 40, (float)(screenHeight - screenHeight * 0.3 + 100),  (float)(screenWidth / 6) - 30, (float)(screenHeight * 0.03) };

    guiColor = GRAY;
    buttonColor = DARKGRAY;
}

void GUI::DrawGUI(int screenWidth, int screenHeight, Vector3 cords) {
    DrawRectangleRec(guiRectangle, guiColor);

    const unsigned int fontSize = 25;

    DrawText("x: ", 20, screenHeight - screenHeight * 0.3 + 30, fontSize, BLACK);
    DrawText("y: ", 20, screenHeight - screenHeight * 0.3 + 60, fontSize, BLACK);
    DrawText("z: ", 20, screenHeight - screenHeight * 0.3 + 100, fontSize, BLACK);

    //Drawing coordinates that will be set for robot to reach
    DrawRectangleRec(xRectangle, LIGHTGRAY);
    DrawText(x_input, xRectangle.x+3, xRectangle.y + 3, 20, BLACK);
    DrawRectangleRec(yRectangle, LIGHTGRAY);
    DrawText(y_input, yRectangle.x + 3, yRectangle.y + 3, 20, BLACK);
    DrawRectangleRec(zRectangle, LIGHTGRAY);
    DrawText(z_input, zRectangle.x + 3, zRectangle.y + 3, 20, BLACK);

    // drawing the accept button
    DrawRectangleRec(acceptRectangle, buttonColor);
    DrawText("ACCEPT", 30, screenHeight - screenHeight * 0.3 + 150, fontSize * 1.5, BLACK);

    // drawing the start learning button
    DrawRectangleRec(startRectangle, buttonColor);
    DrawText("Start learing", screenWidth / 4 - 40, screenHeight - screenHeight * 0.3 + 50, fontSize * 1.5, BLACK);

    // drawing the finish learning button
    DrawRectangleRec(finishRectangle, buttonColor);
    DrawText("Finish learing", screenWidth / 4 - 40, screenHeight - screenHeight * 0.3 + 150, fontSize * 1.5, BLACK);

    // drawing the execute learing button
    DrawRectangleRec(executeRectangle, buttonColor);
    DrawText("Execute", screenWidth / 2 - 60, screenHeight - screenHeight * 0.3 + 110, fontSize * 1.5, BLACK);

    // drawing the manual mode button
    DrawRectangleRec(manualRectangle, buttonColor);
    DrawText("Manual mode", screenWidth / 5 * 3 + 50, screenHeight - screenHeight * 0.3 + 40, fontSize * 1.5, BLACK);

    // drawing button info text
    DrawText("Button 1/2 - Axis 1", screenWidth / 5 * 3 + 50, screenHeight - screenHeight * 0.3 + 100, fontSize, BLACK);
    DrawText("Button 1/2 - Axis 2", screenWidth / 5 * 3 + 50, screenHeight - screenHeight * 0.3 + 140, fontSize, BLACK);
    DrawText("Button 1/2 - Axis 3", screenWidth / 5 * 3 + 50, screenHeight - screenHeight * 0.3 + 180, fontSize, BLACK);

    // drawing manipulator coordinates text
    DrawText("Manipulator", screenWidth / 5 * 4 + 80, screenHeight - screenHeight * 0.3 + 30, fontSize, BLACK);
    DrawText("coordinates:", screenWidth / 5 * 4 + 80, screenHeight - screenHeight * 0.3 + 70, fontSize, BLACK);
    DrawText(TextFormat("X: %.2f", cords.x), screenWidth / 5 * 4 + 80, screenHeight - screenHeight * 0.3 + 110, fontSize, BLACK);
    DrawText(TextFormat("Y: %.2f", cords.z), screenWidth / 5 * 4 + 80, screenHeight - screenHeight * 0.3 + 150, fontSize, BLACK);
    DrawText(TextFormat("Z: %.2f", cords.y), screenWidth / 5 * 4 + 80, screenHeight - screenHeight * 0.3 + 180, fontSize, BLACK);
}

void GUI::CheckIfMouseOnButton(bool &writing)
{   
    if (CheckCollisionPointRec(GetMousePosition(), xRectangle)) { // saves and displays input written by user
        writing = true;
        DrawRectangleLines(xRectangle.x, xRectangle.y, xRectangle.width, xRectangle.height, BLUE);
        //cout << "on x" << endl;
        int key_x = GetCharPressed();
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        while (key_x > 0)
        {
            // NOTE: Only allow numbers
            if ((((key_x >= 48) and (key_x <= 57)) or key_x == 46 or key_x == 45) and (letter_count_x < 5))
            {
                x_input[letter_count_x] = (char)key_x;
                x_input[letter_count_x + 1] = '\0';
                letter_count_x++;
            }

            key_x = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letter_count_x--;
            if (letter_count_x < 0) letter_count_x = 0;
            x_input[letter_count_x] = '\0';
        }
    }
    else if (CheckCollisionPointRec(GetMousePosition(), yRectangle)) {
        writing = true;
        DrawRectangleLines(yRectangle.x, yRectangle.y, yRectangle.width, yRectangle.height, BLUE);
        //cout << "on y" << endl;
        int key_y = GetCharPressed();
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        while (key_y > 0)
        {
            // NOTE: Only allow numbers
            if ((((key_y >= 48) and (key_y <= 57)) or key_y == 46 or key_y == 45) and (letter_count_y < 5))
            {
                y_input[letter_count_y] = (char)key_y;
                y_input[letter_count_y + 1] = '\0';
                letter_count_y++;
            }

            key_y = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letter_count_y--;
            if (letter_count_y < 0) letter_count_y = 0;
            y_input[letter_count_y] = '\0';
        }
    }
    else if (CheckCollisionPointRec(GetMousePosition(), zRectangle)) {
        writing = true;
        DrawRectangleLines(zRectangle.x, zRectangle.y, zRectangle.width, zRectangle.height, BLUE);
        //cout << "on z" << endl;
        int key_z = GetCharPressed();
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        while (key_z > 0)
        {
            // NOTE: Only allow numbers
            if ((((key_z >= 48) and (key_z <= 57)) or key_z == 46) and (letter_count_z < 5))
            {
                z_input[letter_count_z] = (char)key_z;
                z_input[letter_count_z + 1] = '\0';
                letter_count_z++;
            }

            key_z = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letter_count_z--;
            if (letter_count_z < 0) letter_count_z = 0;
            z_input[letter_count_z] = '\0';
        }
    }
    else
    {
        writing = false;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

Vector3 GUI::ReturnFinalCoordinates() // converts input given by user into float and sends it to program to know where it wants to go
{
    float x, y, z;
    x = atof(x_input);
    y = atof(y_input);
    z = atof(z_input);
  
    for (int i = 0; i <= 5; i++)
    {
        x_input[i] = '\0';
        y_input[i] = '\0';
        z_input[i] = '\0';
    }
    letter_count_x = 0;
    letter_count_y = 0;
    letter_count_z = 0;
  
    return {x,y,z};
}

void GUI::CheckIfButtonPressed(int &game_state) {
    // checking if accept button was pressed
    if (CheckCollisionPointRec(GetMousePosition(), acceptRectangle)) {
        // accept button callback function
        if (game_state == MANUAL) {
            game_state = INVERSE;
        }
    }
    if (CheckCollisionPointRec(GetMousePosition(), startRectangle)) {
        // start learning button callback function
        if (game_state == MANUAL) {
            game_state = LEARNING;
        }
    }
    if (CheckCollisionPointRec(GetMousePosition(), finishRectangle)) {
        // finish learing button callback function
        if (game_state == LEARNING) {
            game_state = FINISHED_LEARING;
        }
    }
    if (CheckCollisionPointRec(GetMousePosition(), executeRectangle)) {
        // execute button callback function
        if (game_state == FINISHED_LEARING) {
            game_state = EXECUTE;
        }
    }
    if (CheckCollisionPointRec(GetMousePosition(), manualRectangle)) {
        // manual mode button callback function
        game_state = MANUAL;
    }
}