#include <raylib.h>

int main()
{

    int wind_x = 1280, wind_y = 720;
    int ball_x = wind_x/2, ball_y = wind_y/2;
    int ball_radius = 10;
    int ball_d = ball_radius/2;
    Color GreenF = {20, 160, 133, 255};

InitWindow(wind_x, wind_y, "My Game");
SetTargetFPS(60);

// Game Loop
while(WindowShouldClose() == false){

    // 1. Event Handling
    
    if(IsKeyDown(KEY_RIGHT) && ball_x < wind_x){
        ball_x += 3;
    } else if(IsKeyDown(KEY_LEFT) && ball_x > ball_d){
        ball_x -= 3;
    } else if (IsKeyDown(KEY_UP)){
        ball_y -= 3;
    } else if (IsKeyDown(KEY_DOWN)){
        ball_y += 3;
    }

    // 2. Updating positions


    // 3. Drawing
    BeginDrawing();
    ClearBackground(GreenF);
    DrawCircle(ball_x, ball_y, ball_radius, WHITE);
    EndDrawing();
}

CloseWindow();
    return 0;
}