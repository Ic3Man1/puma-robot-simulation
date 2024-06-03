#include "raylib.h"
#include "Robot_part.h"
#include "rlgl.h"



int main(void)
{
    const int screen_width = 1000;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "puma-robot");
    SetTargetFPS(60);     

    Camera3D camera = { 0 };
    camera.position = { 10.0f, 10.0f, 10.0f }; 
    camera.target = { 0.0f, 0.0f, 0.0f };     
    camera.up = { 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                      
    camera.projection = CAMERA_PERSPECTIVE;    

    Vector3 cubePosition1 = { 0.0f, 1.0f, 0.0f };
    Vector3 cubePosition2 = { 0.0f, 2.25f, -0.25f };
    Vector3 cubePosition3 = { 0.5f, 2.25f, -1.0f };
    Vector3 cubePosition4 = { 1.25f, 1.75f, -0.5f };

    Robot_part part1 = Robot_part(0, cubePosition1, 0.5f, 2.0f, 0.5f, GRAY);
    Robot_part part2 = Robot_part(1, cubePosition2, 0.5f, 0.5f, 1.0f, GRAY);
    Robot_part part3 = Robot_part(2, cubePosition3, 2.0f, 0.5f, 0.5f, GRAY);
    Robot_part part4 = Robot_part(3, cubePosition4, 0.5f, 1.5f, 0.5f, GRAY);
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
        
       
        part1.draw();
        part1.draw_wire(BLUE);
        if (IsKeyDown(KEY_ONE))
        {
            part2.rotate("+");
        }
        else if (IsKeyDown(KEY_TWO))
        {
            part2.rotate("-");
        }
        part2.draw();
        part2.draw_wire(RED);
        if (IsKeyDown(KEY_THREE))
        {
            part3.rotate("+");
        }
        else if (IsKeyDown(KEY_FOUR))
        {
            part3.rotate("-");
        }
        part3.draw();
        part3.draw_wire(GREEN);
        if (IsKeyDown(KEY_FIVE))
        {
            part4.rotate("+");
        }
        else if (IsKeyDown(KEY_SIX))
        {
            part4.rotate("-");
        }
        part4.draw();
        part4.draw_wire(ORANGE);
        
        rlPopMatrix();
        DrawGrid(10, 1.0f);


        EndMode3D();

        EndDrawing();
    }

    CloseWindow();       

    return 0;
}