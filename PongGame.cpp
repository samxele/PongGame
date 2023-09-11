#include <iostream>
#include <raylib.h>

using namespace std;

class Ball
{
public:
    float x, y;
    int speedx,speedy;
    int radius; 

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update()
    {
        x += speedx; 
        y += speedy;
    }
};

Ball ball; 

int main() 
{
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screenWidth / 2; 
    ball.y = screenHeight / 2;
    ball.speedx = 10; 
    ball.speedy = 10; 

    while(WindowShouldClose() == false) 
    {
        BeginDrawing();
        ball.Update();
        
        ClearBackground(BLACK);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        ball.Draw(); 
        DrawRectangle(10, screenHeight/2 - 60, 25, 120, WHITE);
        DrawRectangle(screenWidth - 35, screenHeight / 2 - 60, 25, 120, WHITE);
        EndDrawing(); 
    }

    CloseWindow(); 
    return 0;
}