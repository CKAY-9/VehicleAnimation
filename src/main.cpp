#include "raylib.h"
#include "car.h"
#include <iostream>
#include <string>
#include <vector>

const int windowWidth = 800;
const int windowHeight = 1000;

void drawBackground(Texture2D mountains, Texture2D sun, Texture2D clouds) 
{
    DrawTexture(mountains, windowWidth/2 - mountains.width/2, windowHeight - mountains.height/2, WHITE);
    DrawTexture(sun, 20, 20, RAYWHITE);
    for (int i = 0; i < 10; i++) {
        DrawTexture(clouds, (150 * i) - 60, -10, RAYWHITE);
    }
}

int main(int argc, char const *argv[])
{
    int trailLength = 75;

    InitWindow(windowWidth, windowHeight, "Vehicle Animation - Cameron Armstrong");
    SetTargetFPS(60);

    // Initialize cars
    std::vector<Car*> cars;
    int carCount = 50;
    for (int i = 0; i < carCount; i++) 
    {
        cars.push_back(new Car(0, (i + 1) * windowHeight / carCount + 1, i + 3, i + 2, windowWidth, windowHeight, &trailLength));
    }

    // Load Images for background
    Texture2D mountainsTexture = LoadTexture("./resources/mountains.png"); 
    std::cout << mountainsTexture.id << std::endl;
    Texture2D sunTexture = LoadTexture("./resources/sun.png"); 
    std::cout << sunTexture.id << std::endl;
    Texture2D cloudTexture = LoadTexture("./resources/clouds.png");
    std::cout << cloudTexture.id << std::endl;

    while (!WindowShouldClose()) 
    {
        // Clamp Trail Values
        if (IsKeyDown(KEY_UP)) 
        {
            if (trailLength <= 250) 
            {
                trailLength += 5;
            }
        }
        if (IsKeyDown(KEY_DOWN)) 
        {
            if (trailLength >= 5) 
            {
                trailLength -= 5;
            }  
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Background Elements
        drawBackground(mountainsTexture, sunTexture, cloudTexture);

        // Car Logic
        for (Car* car : cars) 
        {
            car->think();
            car->render();
        }

        // Car Trail Length
        std::string str = "Trail Length: " + std::to_string(trailLength);
        const char* c = str.c_str();
        DrawText(c, 0, 0, 20, BLACK);

        EndDrawing();
    }

    // Clear textures from memory
    UnloadTexture(mountainsTexture);
    UnloadTexture(sunTexture);
    UnloadTexture(cloudTexture);

    CloseWindow();

    return 0;
}