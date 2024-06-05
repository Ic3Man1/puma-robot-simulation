#include "raylib.h"
#include "raymath.h"

int main(void) {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib - transformations");

    // Camera setup
    Camera camera = { 0 };
    camera.position = { 4.0f, 4.0f, 4.0f };
    camera.target = { 0.0f, 1.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Initial position of the object
    Vector3 objectPosition = { 0.0f, 0.0f, 0.0f };

    // Size of the object (a cube)
    float cubeSize = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Apply transformations
        Matrix transform = MatrixIdentity();
        transform = MatrixMultiply(transform, MatrixTranslate(1.0f, 0.0f, 0.0f));  // Translate
        transform = MatrixMultiply(transform, MatrixRotate({ 0.0f, 1.0f, 0.0f }, DEG2RAD * 45.0f));  // Rotate 45 degrees around Y-axis
        transform = MatrixMultiply(transform, MatrixTranslate(0.0f, 1.0f, 0.0f));  // Translate again

        // Apply transformation to object position
        Vector3 transformedPosition = Vector3Transform(objectPosition, transform);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        // Draw original and transformed cubes
        DrawCube(objectPosition, cubeSize, cubeSize, cubeSize, BLUE);  // Original position
        DrawCube(transformedPosition, cubeSize, cubeSize, cubeSize, RED);  // Transformed position

        // Draw axes for reference
        DrawGrid(10, 1.0f);
        EndMode3D();

        // Display transformed position
        DrawText(TextFormat("Transformed Position: (%.2f, %.2f, %.2f)", transformedPosition.x, transformedPosition.y, transformedPosition.z), 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}