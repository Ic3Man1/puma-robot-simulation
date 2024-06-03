#include "raylib.h"

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

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    while (!WindowShouldClose())    
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        DrawCube(cubePosition, 2, 2, 2, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, BLUE);
        DrawGrid(10, 1.0f);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();       

    return 0;
}