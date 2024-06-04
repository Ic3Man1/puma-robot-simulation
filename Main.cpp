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
#include "rlgl.h"

#include "Robot_part.h"
#include "GUI.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    const int screen_width = 1500;
    const int screen_height = 800;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    // Window configuration flags

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

    Vector3 cubePosition1 = { 0.0f, 1.5f, 0.0f };
    Vector3 cubePosition2 = { 0.65f, 2.75f, 0.85f };
    Vector3 cubePosition3 = { 0.15f, 2.75f, 2.75f };
    Vector3 cubePosition4 = { 0.15f, 2.75f, 4.15f };

    Robot_part part1 = Robot_part(1, cubePosition1, 0.8f, 3.0f, 0.8f, GRAY);
    Robot_part part2 = Robot_part(2, cubePosition2, 0.5f, 0.5f, 2.5f, GRAY);
    Robot_part part3 = Robot_part(3, cubePosition3, 0.5f, 0.5f, 2.5f, GRAY);
    Robot_part part4 = Robot_part(4, cubePosition4, 0.3f, 0.3f, 0.3f, DARKGRAY);

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            GUI.CheckIfButtonPressed();
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
      
        // Draw 3D
      
        BeginMode3D(camera);
        
        rlPushMatrix();
        
        if (IsKeyDown(KEY_ONE))
        {
            part1.rotate("+");
        }
        else if (IsKeyDown(KEY_TWO))
        {
            part1.rotate("-");
        }   

        if (IsKeyDown(KEY_THREE))
        {
            part2.rotate("+");
        }
        else if (IsKeyDown(KEY_FOUR))
        {
            part2.rotate("-");
        }

        if (IsKeyDown(KEY_FIVE))
        {
            part3.rotate("+");
        }
        else if (IsKeyDown(KEY_SIX))
        {
            part3.rotate("-");
        }

        part1.draw();
        part1.draw_wire(BLUE);
        part2.draw();
        part2.draw_wire(RED);
        part3.draw();
        part3.draw_wire(GREEN);
        part4.draw();
        part4.draw_wire(PURPLE);
        
        rlPopMatrix();
        DrawGrid(10, 1.0f);

        EndMode3D();
        
        // Draw 2D
      
        GUI.DrawGUI(screenWidth, screenHeight);

        EndDrawing();
    }

    CloseWindow();       

    return 0;
}
