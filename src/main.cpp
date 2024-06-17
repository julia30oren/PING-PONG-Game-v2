#include <iostream>
#include <raylib.h>

using namespace std;

const int /*window width*/ wind_x = 1280, /*window height*/ wind_y = 720;
Color LightGreen = Color{107, 142, 35, 255}; /*rgb + 255 - transparency value*/
Color DarkGreen = Color{85, 107, 47, 255};
Color TransparentWhite = Color{127,255,212, 150};
int playre_1_score = 0, playre_1_ai_score = 0, playre_2_score = 0;

class Ball
{
public:
    const int radius = 10;
    int speed_x = 8, speed_y = 8;
    float x = wind_x / 2, y = wind_y / 2;
    int top, bottom = y + radius, right, left;

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    };

    void ResetBall()
    {
        x = wind_x / 2;
        y = wind_y / 2;
    };

    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= wind_y || y - radius <= 0)
        {
            speed_y *= -1; /*changing the direction of a ball*/
        }
        // if (x + radius >= wind_x || x - radius <= 0) /* to hit the wall */
        // {
        //     speed_x *= -1; /*changing the direction of a ball*/
        // }

        if (x + radius >= wind_x)
        {
            playre_1_ai_score = playre_1_score += 1;
            ResetBall();
        }
        if (x - radius <= 0)
        {
            playre_2_score += 1;
            ResetBall();
        }
    };
};

class Player_1
{
public:
    const int width = 20, height = 150;
    int speed = 6;
    const float x = width * 2;             /*position of top left corner of rectangle*/
    float y = (wind_y / 2) - (height / 2); /*position of top left corner of rectangle*/

    void Draw()
    {
        DrawRectangle(x, y, width, height, BLACK);
    };

    void Update()
    {
        if (IsKeyDown(KEY_W) && y > 0)
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_S) && y + height < wind_y)
        {
            y += speed;
        }
    };
};

class CpuPlayer_1 : public Player_1
{
public:
    void Update(int ball_y)
    {
        if (y + height / 2 > ball_y)
        {
            y -= speed;
        }
        if (y + height / 2 <= ball_y)
        {
            y += speed;
        }
    };
};

class Player_2
{
public:
    const int width = 20, height = 150;
    int speed = 6;
    const float x = wind_x - width * 3;    /*position of top left corner of rectangle*/
    float y = (wind_y / 2) - (height / 2); /*position of top left corner of rectangle*/

    void Draw()
    {
        DrawRectangle(x, y, width, height, BLACK);
    };

    void Update()
    {
        if (IsKeyDown(KEY_UP) && y > 0)
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN) && y + height < wind_y)
        {
            y += speed;
        }
    };
};

Ball ball;
Player_1 player_1;
CpuPlayer_1 player_1_ai;
Player_2 player_2;

int main()
{
    InitWindow(wind_x, wind_y, "My Game"); /*create a window "My Game"*/
    SetTargetFPS(60);                      /*set speed ( 60 frames per seconds)*/

    // Game Loop
    while (/*this function check if "x" or "ESC" was clicked*/ !WindowShouldClose())
    {
        // 1. Event Handling
        BeginDrawing(); /*start drawing canvas*/
        ClearBackground(LightGreen);
        DrawRectangle(0, 0, wind_x / 2, wind_y, DarkGreen);
        DrawCircle(wind_x / 2, wind_y / 2, wind_y / 5, TransparentWhite);

        // 2. Updating positions
        ball.Update();
        player_2.Update();
        player_1_ai.Update(ball.y);

        // 3. Checking for collisions
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player_1_ai.x, player_1_ai.y, player_1_ai.width, player_1_ai.height}) ||
            CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player_2.x, player_2.y, player_2.width, player_2.height}))
        {
            ball.speed_x *= -1;
        }

        // 4. Drawing
        DrawLine(wind_x / 2, 0, wind_x / 2, wind_y, WHITE);
        // DrawText(text,x_pos,y_pos,font_size, color);
        DrawText(TextFormat("%i", playre_1_score), wind_x / 5, 50, 80, WHITE);
        DrawText(TextFormat("%i", playre_2_score), wind_x - wind_x / 5, 50, 80, WHITE);
        ball.Draw();
        player_1_ai.Draw();
        player_2.Draw();

        EndDrawing(); /*ends drawing canvas*/
    }

    CloseWindow();
    return 0;
}