#include "raylib.h"
#include "Robot_part.h"

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

    Robot_part part1 = Robot_part("n", cubePosition1, 0.5f, 2.0f, 0.5f, GRAY);
    Robot_part part2 = Robot_part("z", cubePosition2, 0.5f, 0.5f, 1.0f, GRAY);
    Robot_part part3 = Robot_part("x", cubePosition3, 2.0f, 0.5f, 0.5f, GRAY);
    Robot_part part4 = Robot_part("x", cubePosition4, 0.5f, 1.5f, 0.5f, GRAY);

    while (!WindowShouldClose())    
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        part1.draw();
        part1.draw_wire(BLUE);

        part2.draw();
        part2.draw_wire(RED);

        part3.draw();
        part3.draw_wire(GREEN);

        part4.draw();
        part4.draw_wire(ORANGE);

        DrawGrid(10, 1.0f);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();       

    return 0;
}