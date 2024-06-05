#include "raylib.h"
#include "rlgl.h"
#include <iostream>
#include "raymath.h"

#include "Robot_part.h"
#include "GUI.h"
#include "InverseKinematicsCalc.h"


BoundingBox create_bounding_box(Vector3 position, Vector3 size);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    const int screen_width = 1500;
    const int screen_height = 800;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    // Window configuration flags

    InitWindow(screen_width, screen_height, "PUMA robot");

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
    GUI GUI(screen_width, screen_height);

    Vector3 cubePosition1 = { 0.0f, 1.5f, 0.0f };
    Vector3 cubePosition2 = { 0.65f, 2.75f, 0.85f };
    Vector3 cubePosition3 = { 0.15f, 2.75f, 2.75f };
    Vector3 cubePosition4 = { 0.15f, 2.75f, 4.15f };

    Vector3 cubeSize1 = { 0.8f, 3.0f, 0.8f };
    Vector3 cubeSize2 = { 0.5f, 0.5f, 2.5f };
    Vector3 cubeSize3 = { 0.5f, 0.5f, 2.5f };
    Vector3 cubeSize4 = { 0.3f, 0.3f, 0.3f };

    Robot_part part1 = Robot_part(1, cubePosition1, 0.8f, 3.0f, 0.8f, GRAY);
    Robot_part part2 = Robot_part(2, cubePosition2, 0.5f, 0.5f, 2.5f, GRAY);
    Robot_part part3 = Robot_part(3, cubePosition3, 0.5f, 0.5f, 2.5f, GRAY);
    Robot_part part4 = Robot_part(4, cubePosition4, 0.3f, 0.3f, 0.3f, DARKGRAY);

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        float x = DEG2RAD * (part1.rot_pos_1), y = DEG2RAD * (part2.rot_pos_2), z = DEG2RAD * (part3.rot_pos_3);
        Vector3 current_manipulator_cords = { 1.85 * sin(x) * cos(y) - 2.55 * sin(x) * sin(y) * sin(z) + 2.55 * sin(x) * cos(y) * cos(z),
                                5.5 - (2.75 + 1.85 * sin(y) + 2.55 * sin(y) * cos(z) + 2.55 * cos(y) * sin(z)),
                                1.85 * cos(x) * cos(y) + 2.55 * cos(x) * cos(y) * cos(z) - 2.55 * cos(x) * sin(y) * sin(z) };
        //current_manipulator_cords.y = 5.5 - current_manipulator_cords.y;
        //cout << current_manipulator_cords.x << "; " << current_manipulator_cords.y << "; " << current_manipulator_cords.z << endl;
        //cout << part1.rot_pos_1 << "  " << part2.rot_pos_2 << "  " << part3.rot_pos_3 << "     " << endl;

        //a = 1.85 * sin(x) * cos(y) - 2.45 * sin(x) * sin(y) * sin(z) + 2.45 * sin(x) * cos(y) * cos(z); //x
        //b = 1.85 * cos(x) * cos(y) + 2.45 * cos(x) * cos(y) * cos(z) - 2.45 * cos(x) * sin(y) * sin(z); //y
        //c = 2.75 + 1.85 * sin(y) + 2.45 * sin(y) * cos(z) + 2.45 * cos(y) * sin(z); // z
        
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            GUI.CheckIfButtonPressed();
        }
        
        
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        // Draw 3d
        BeginMode3D(camera);
        DrawSphere({ 2, 0, 0 }, 0.5f, RED);
        DrawSphere({ -2, 0, 0 }, 0.5f, BLUE);
        DrawSphere({ 0, 0, 3 }, 0.5f, RED);
        DrawSphere({ 0, 0, -3 }, 0.5f, BLUE);
        rlPushMatrix();

        if (IsKeyDown(KEY_ONE))
        {
            part1.rotate("+", current_manipulator_cords);
        }
        else if (IsKeyDown(KEY_TWO))
        {
            part1.rotate("-", current_manipulator_cords);
        }

        if (IsKeyDown(KEY_THREE))
        {
            part2.rotate("+", current_manipulator_cords);
        }
        else if (IsKeyDown(KEY_FOUR))
        {
            part2.rotate("-", current_manipulator_cords);
        }

        if (IsKeyDown(KEY_FIVE))
        {
            part3.rotate("+", current_manipulator_cords);
        }
        else if (IsKeyDown(KEY_SIX))
        {
            part3.rotate("-", current_manipulator_cords);
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

        
        
        GUI.DrawGUI(screen_width, screen_height, current_manipulator_cords);
        GUI.CheckIfMouseOnButton();
        EndDrawing();
    }

    CloseWindow();       

    return 0;
}

BoundingBox create_bounding_box(Vector3 position, Vector3 size) 
{
    Vector3 min = { position.x - size.x / 2, position.y - size.y / 2, position.z - size.z / 2 };
    Vector3 max = { position.x + size.x / 2, position.y + size.y / 2, position.z + size.z / 2 };
    return {min, max};
}