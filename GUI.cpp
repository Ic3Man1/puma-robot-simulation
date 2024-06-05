#include "GUI.h"
#include "Robot_part.h"
#include "stateNames.h"

GUI::GUI(int screenWidth, int screenHeight) {
	guiRectangle = { 0, (float)(screenHeight - screenHeight * 0.3), (float)(screenWidth), (float)(screenHeight * 0.3) };
    acceptRectangle = { 10, (float)(screenHeight - screenHeight * 0.3 + 130),  (float)(screenWidth / 6), (float)(screenHeight * 0.1) };
    startRectangle = { (float)(screenWidth / 5), (float)(screenHeight - screenHeight * 0.3 + 30),  (float)(screenWidth / 5), (float)(screenHeight * 0.1)};
    finishRectangle = { (float)(screenWidth / 5), (float)(screenHeight - screenHeight * 0.3 + 130),  (float)(screenWidth / 5), (float)(screenHeight * 0.1) };
    executeRectangle = { (float)(screenWidth / 2 - 120), (float)(screenHeight - screenHeight * 0.3 + 30),  (float)(screenWidth / 5 - 30), (float)(screenHeight * 0.1 + 100) };
    manualRectangle = { (float)(screenWidth / 5 * 3 + 30), (float)(screenHeight - screenHeight * 0.3 + 30),  (float)(screenWidth / 5), (float)(screenHeight * 0.07) };

    guiColor = GRAY;
    buttonColor = DARKGRAY;
}

void GUI::DrawGUI(int screenWidth, int screenHeight, Vector3 cords) {
    DrawRectangleRec(guiRectangle, guiColor);

    const unsigned int fontSize = 25;

    DrawText("x: ", 20, screenHeight - screenHeight * 0.3 + 30, fontSize, BLACK);
    DrawText("y: ", 20, screenHeight - screenHeight * 0.3 + 60, fontSize, BLACK);
    DrawText("z: ", 20, screenHeight - screenHeight * 0.3 + 100, fontSize, BLACK);

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
    DrawText("Button 1/2 - Axis 1", screenWidth / 5 * 3 + 50, screenHeight - screenHeight * 0.3 + 140, fontSize, BLACK);
    DrawText("Button 1/2 - Axis 1", screenWidth / 5 * 3 + 50, screenHeight - screenHeight * 0.3 + 180, fontSize, BLACK);

    // drawing manipulator coordinates text
    DrawText("Manipulator", screenWidth / 5 * 4 + 80, screenHeight - screenHeight * 0.3 + 30, fontSize, BLACK);
    DrawText("coordinates:", screenWidth / 5 * 4 + 80, screenHeight - screenHeight * 0.3 + 70, fontSize, BLACK);
    DrawText(TextFormat("X: %.2f", cords.x), screenWidth / 5 * 4 + 80, screenHeight - screenHeight * 0.3 + 110, fontSize, BLACK);
    DrawText(TextFormat("Y: %.2f", cords.z), screenWidth / 5 * 4 + 80, screenHeight - screenHeight * 0.3 + 150, fontSize, BLACK);
    DrawText(TextFormat("Z: %.2f", cords.y), screenWidth / 5 * 4 + 80, screenHeight - screenHeight * 0.3 + 180, fontSize, BLACK);
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