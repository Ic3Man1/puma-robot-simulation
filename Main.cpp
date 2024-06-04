#include "raylib.h"
#include "Robot_part.h"
#include "rlgl.h"

int main(void)
{
    const int screen_width = 1500;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "puma-robot");
    SetTargetFPS(60);     

    Camera3D camera = { 0 };
    camera.position = { 10.0f, 10.0f, 10.0f }; 
    camera.target = { 0.0f, 0.0f, 0.0f };     
    camera.up = { 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                      
    camera.projection = CAMERA_PERSPECTIVE;    

    Vector3 cubePosition1 = { 0.0f, 1.5f, 0.0f };
    Vector3 cubePosition2 = { 0.65f, 2.75f, 0.85f };
    Vector3 cubePosition3 = { 0.15f, 2.75f, 2.75f };

    Robot_part part1 = Robot_part(1, cubePosition1, 0.8f, 3.0f, 0.8f, GRAY);
    Robot_part part2 = Robot_part(2, cubePosition2, 0.5f, 0.5f, 2.5f, GRAY);
    Robot_part part3 = Robot_part(3, cubePosition3, 0.5f, 0.5f, 2.5f, GRAY);
    int i = 0;

    while (!WindowShouldClose())    
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        /*
        rlPushMatrix(); // rotation only applies until rlPopMatrix below
        rlRotatef(i, 1, 0, 0); // rotate 45 degrees along <1,0,0> x-axis
        Vector3 pos;
        pos.x = 0; pos.y = 0; pos.z = 0; // This works in C and C++
        DrawCube(pos, 1, 1, 1, BLUE); // set position 0, extents <1,1,1>
        rlPopMatrix();
        i++;
        */
        
        rlPushMatrix();
        
        /*
        part1.draw();
        part1.draw_wire(BLUE);
        part2.draw();
        part2.draw_wire(BLUE);
        part3.draw();
        part3.draw_wire(BLUE);
        */
        
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
        
        rlPopMatrix();
        DrawGrid(10, 1.0f);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();       

    return 0;
}