/*******************************************************************************************
*
*   raylib [core] example - Picking in 3d mode
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "GUI.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    // Window configuration flags

    int screenWidth = 1500;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "PUMA robot");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = { 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };

    Ray ray = { 0 };                    // Picking line ray
    RayCollision collision = { 0 };     // Ray collision hit info

    // Set up 2D GUI
    GUI GUI(screenWidth, screenHeight);

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            GUI.CheckIfButtonPressed();
        }
        //----------------------------------------------------------------------------------

        // Draw 3D
        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        DrawCube(cubePosition, 2, 2, 2, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, BLUE);
        DrawGrid(10, 1.0f);

        EndMode3D();

        // Draw 2D
        //----------------------------------------------------------------------------------

        GUI.DrawGUI(screenWidth, screenHeight);

        EndDrawing();
    }

    CloseWindow();       

    return 0;
}
