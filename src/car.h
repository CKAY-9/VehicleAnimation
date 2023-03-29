#include <vector>
#include "raylib.h"
#include <string>

class Car 
{
    public: 
        int x = 0; // X Location
        int y = 0; // Y Location
        int speedX = 1;
        int speedY = 1;
        int wHeight; // Window Height
        int wWidth; // Window Width
        int* trailLength;
        std::vector<Vector2*> previousPositions;
        Car(int x, int y, int speedX, int speedY, int windowWidth, int windowHeight, int* trailLength);
        void think();
        void render();
        void drawTrails();
        void drawCar();
        void drawPos();
        Vector2 carPos();
        ~Car();
};