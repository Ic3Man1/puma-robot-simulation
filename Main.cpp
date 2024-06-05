#include <iostream>

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "Robot_part.h"
#include "GUI.h"

bool check_for_collision(int &rot_pos, char operation);

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

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // calculating current manipulator and rotational exis coordinates
        float x = DEG2RAD * (part1.rot_pos_1), y = DEG2RAD * (part2.rot_pos_2), z = DEG2RAD * (part3.rot_pos_3);

        Vector3 current_manipulator_cords = { 1.85 * sin(x) * cos(y) - 2.55 * sin(x) * sin(y) * sin(z) + 2.55 * sin(x) * cos(y) * cos(z),
                                        5.5 - (2.75 + 1.85 * sin(y) + 2.55 * sin(y) * cos(z) + 2.55 * cos(y) * sin(z)),
                                        1.85 * cos(x) * cos(y) + 2.55 * cos(x) * cos(y) * cos(z) - 2.55 * cos(x) * sin(y) * sin(z) };

        Vector3 current_rot_axis_coord = { 1.85 * sin(x) * cos(y),
                                        1.85 * cos(x) * cos(y),
                                        2.75 + 1.85 * sin(z) };


        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        // taking care of mouse inputs
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            GUI.CheckIfButtonPressed();
        }
        
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        // Draw 3D
        BeginMode3D(camera);

        rlPushMatrix();
        
        // taking care of keyboard inputs concerning robot movement
        if (IsKeyDown(KEY_ONE) and check_for_collision(part1.rot_pos_1, '+'))
        {
            part1.rotate("+", current_manipulator_cords, current_rot_axis_coord);
        }
        else if (IsKeyDown(KEY_TWO) and check_for_collision(part1.rot_pos_1, '-'))
        {
            part1.rotate("-", current_manipulator_cords, current_rot_axis_coord);
        }

        if (IsKeyDown(KEY_THREE) and check_for_collision(part2.rot_pos_2, '+'))
        {
            part2.rotate("+", current_manipulator_cords, current_rot_axis_coord);
        }
        else if (IsKeyDown(KEY_FOUR) and check_for_collision(part2.rot_pos_2, '-'))
        {
            part2.rotate("-", current_manipulator_cords, current_rot_axis_coord);
        }

        if (IsKeyDown(KEY_FIVE) and check_for_collision(part3.rot_pos_3, '+'))
        {
            part3.rotate("+", current_manipulator_cords, current_rot_axis_coord);
        }
        else if (IsKeyDown(KEY_SIX) and check_for_collision(part3.rot_pos_3, '-'))
        {
            part3.rotate("-", current_manipulator_cords, current_rot_axis_coord);
        }
     
        // drawing robot parts
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

        EndDrawing();
    }

    CloseWindow();       

    return 0;
}

bool check_for_collision(int &rot_pos, char operation) {
    // rotating to check if collision will happen
    if (operation == '+') {
        rot_pos++;
    }
    else {
        rot_pos--;
    }

    float x = DEG2RAD * (part1.rot_pos_1), y = DEG2RAD * (part2.rot_pos_2), z = DEG2RAD * (part3.rot_pos_3);

    // calculating coordinates localy
    Vector3 local_manipulator_cords = { 1.85 * sin(x) * cos(y) - 2.55 * sin(x) * sin(y) * sin(z) + 2.55 * sin(x) * cos(y) * cos(z),
                                        5.5 - (2.75 + 1.85 * sin(y) + 2.55 * sin(y) * cos(z) + 2.55 * cos(y) * sin(z)),
                                        1.85 * cos(x) * cos(y) + 2.55 * cos(x) * cos(y) * cos(z) - 2.55 * cos(x) * sin(y) * sin(z) };

    Vector3 local_rot_axis_coord = { 1.85 * sin(x) * cos(y),
                                    1.85 * cos(x) * cos(y),
                                    2.75 + 1.85 * sin(z) };

    // undoing the rotation after calculating local coordinates
    if (operation == '+') {
        rot_pos--;
    }
    else {
        rot_pos++;
    }


    float r = 0.8 * sqrt(2) / 2 + 0.2;

    // checking if the collison will happen or if the manipulator will hit the floor
    if (((pow(local_manipulator_cords.x, 2) + pow(local_manipulator_cords.z, 2) > pow(r, 2)) or (local_manipulator_cords.y > 3.5)) and (pow(local_rot_axis_coord.x, 2) + pow(local_rot_axis_coord.z, 2) > pow(r, 2)) and (local_manipulator_cords.y >= 0)) {
        return true;
    }
    
    return false;
}