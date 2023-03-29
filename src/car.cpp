#include "car.h"

Car::Car(int x, int y, int speedX, int speedY, int windowWidth, int windowHeight, int* trailLength) 
{
    this->x = x;
    this->y = y;
    this->speedX = speedX;
    this->speedY = speedY;
    this->wWidth = windowWidth;
    this->wHeight = windowHeight;
    this->trailLength = trailLength;
}

Vector2 Car::carPos() 
{
    return Vector2{(float)this->x, (float)this->y};
}

// Used for calculations or non-drawing
void Car::think() 
{
    // Collision checking with window bounds
    x += 1 * speedX;
    y += 1 * speedY;
    if (x >= this->wWidth || x <= 0) 
    {
        this->speedX *= -1;
    } 
    if (y >= this->wHeight || y <= 0) 
    {
        this->speedY *= -1;
    } 

    // For drawing car trail
    previousPositions.push_back(new Vector2{(float) x, (float) y});
    if (previousPositions.size() >= *trailLength) 
    {
        previousPositions.erase(previousPositions.begin());
    }
    // Clear unused positions
    if (*trailLength <= 0) 
    {
        previousPositions.clear();
    }
}

void Car::drawCar() 
{
    // Render Car
    DrawCircle(this->x - 50, this->y - 10, 20, RED);
    DrawCircle(this->x + 50, this->y - 10, 20, RED);
    DrawRectangle(this->x - 80, this->y - 40, 160, 30, BLACK);
    DrawLine(this->x - 60, this->y - 30, this->x, this->y - 60, BLACK);
    DrawLine(this->x, this->y - 60, this->x + 60, this->y - 30, BLACK);
}

void Car::drawTrails()
{
    // Render car trail
    for (int i = 0; i < previousPositions.size(); i++) 
    {
        if (i + 1 != previousPositions.size()) 
        {
            unsigned char opacity = (unsigned char) i * (255 / *trailLength);
            DrawLine(previousPositions[i]->x, previousPositions[i]->y, previousPositions[i + 1]->x, previousPositions[i + 1]->y, Color{255, 0, 0, opacity});
        }
    }
}

void Car::drawPos() 
{
    std::string pos = "X: " + std::to_string((int)this->carPos().x) + ", Y: " + std::to_string((int)this->carPos().y);
    DrawText(pos.c_str(), this->x - 60, this->y - 30, 15, RAYWHITE);
}

void Car::render() 
{
    drawTrails();
    drawCar();
    drawPos();
}

Car::~Car() 
{

}