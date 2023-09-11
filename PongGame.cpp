#include <iostream>
#include <raylib.h>

using namespace std;

int playerScore = 0;
int cpuScore = 0; 

class Ball
{
public:
    float x, y;
    int speedx,speedy;
    int radius; 

    void Draw()
    {
        DrawCircle(x, y, radius, YELLOW);
    }

    void Update()
    {
        x += speedx; 
        y += speedy;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speedy *= -1; 
        }
        if (x + radius >= GetScreenWidth())
        {
            cpuScore++;
            ResetBall();
        } 
        if (x - radius <= 0)
        {
            playerScore++;
            ResetBall();
        }
    }

    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2; 

        int speedChoices[2] = { -1,1 };
        speedx *= speedChoices[GetRandomValue(0, 1)];
        speedy *= speedChoices[GetRandomValue(0, 1)];
    }
};

class Paddle
{
protected: 
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height; 
        }
    }

public: 
    float x, y;
    float width, height;
    int speed; 

    void Draw()
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, LIGHTGRAY);
    }

    void Update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }
        LimitMovement(); 
    }
};

class CpuPaddle: public Paddle
{
public:
    void Update(int bally)
    {
        if (y + height / 2 > bally)
        {
            y = y - speed; 
        }
        if (y + height / 2 <= bally)
        {
            y = y + speed; 
        }
        LimitMovement();
    }
};

Ball ball; 
Paddle player; 
CpuPaddle cpu; 

int main() 
{
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    ball.radius = 15;
    ball.x = screenWidth / 2; 
    ball.y = screenHeight / 2;
    ball.speedx = 8; 
    ball.speedy = 8; 
    
    player.width = 25;
    player.height = 120; 
    player.x = screenWidth - player.width - 10; 
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 6;

    while(WindowShouldClose() == false) 
    {
        BeginDrawing();
        
        ball.Update();
        player.Update(); 
        cpu.Update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speedx *= -1; 
        }
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speedx *= -1;
        }

        ClearBackground(BLACK);
        DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, BLACK);
        DrawCircle(screenWidth / 2, screenHeight / 2, 150, GRAY);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        ball.Draw(); 
        cpu.Draw(); 
        player.Draw();
        DrawText(TextFormat("%i", cpuScore), screenWidth / 4 - 20, 20, 80, GRAY);
        DrawText(TextFormat("%i", playerScore), 3 * screenWidth / 4 - 20, 20, 80, GRAY);

        EndDrawing(); 
    }

    CloseWindow(); 
    return 0;
}
