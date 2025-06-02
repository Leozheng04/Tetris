/*
Created and modification with the tutorial by 
Programming With Nick
*/
#include <raylib.h>

int playerScore;
int aiScore;

struct Ball{
    float x;
    float y;
    float radius;
    float speedX;
    float speedY;

    void draw(){
        DrawCircle(x,y,radius,WHITE);
    }
    void reset(){
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speedChoice[2] = {-1,1};
        speedX *= speedChoice[GetRandomValue(0,1)];
        speedY *= speedChoice[GetRandomValue(0,1)];

    }
    void update(){
        x += speedX;
        y += speedY;
        if (y >= GetScreenHeight() || y <= 0){
            speedY *= -1;
        }
        if (x >= GetScreenWidth()){
            playerScore ++;
            reset();
        }
        if (x <= 0){
            aiScore ++;
            reset();
        }
    }
};
struct paddle{
    float x;
    float y;
    float width;
    float height;
    float speed;

    void draw(){
        DrawRectangle(x,y,width,height,WHITE);
    }
    void update(){
        if (IsKeyDown(KEY_DOWN)){
            y += speed;
        }
        if (IsKeyDown(KEY_UP)){
            y -= speed;
        }
        if (y + speed <= 0){
            y = 0;
        }
        if (y + height >= GetScreenHeight()){
            y = GetScreenHeight() - height;
        }
    }
};
struct AI: public paddle{
    void update(float ballY){
        if(y + height/2 > ballY){
            y -= speed;
        }
        if(y + height/2 < ballY){
            y += speed;
        }

    }

};

Ball pingPongBall;
paddle player;
AI ai;

int main(){
    SetTargetFPS(60);

    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth,screenHeight, "Pong Video-Game");

    pingPongBall.x = screenWidth/2;
    pingPongBall.y = screenHeight/2;
    pingPongBall.radius = 20;
    pingPongBall.speedX = 7;
    pingPongBall.speedY = 7;

    player.x = 10;
    player.y = screenHeight/2 - 60;
    player.width = 25;
    player.height = 120;
    player.speed = 7;

    ai.x = screenWidth - 35;
    ai.y = screenHeight/2 - 60;
    ai.width = 25;
    ai.height = 120;
    ai.speed = 5;



    while(!WindowShouldClose()){
        BeginDrawing();

        DrawLine(screenWidth/2,0,screenWidth/2,screenHeight,WHITE);
        DrawCircleLines(screenWidth/2 ,screenHeight/2,120,WHITE);

        pingPongBall.draw();
        player.draw();
        ai.draw();

        pingPongBall.update();
        player.update();
        ai.update(pingPongBall.y);

         if(CheckCollisionCircleRec({pingPongBall.x,pingPongBall.y},pingPongBall.radius,{player.x,player.y,player.width,player.height})){
            pingPongBall.speedX *= -1;
         }
         if (CheckCollisionCircleRec({pingPongBall.x,pingPongBall.y},pingPongBall.radius,{ai.x,ai.y,ai.width,ai.height})){
            pingPongBall.speedX *= -1;
         }

        DrawText(TextFormat("%i",playerScore), screenWidth/4 , 20 , 80, WHITE);
        DrawText(TextFormat("%i",aiScore), 3* screenWidth/4 , 20 , 80, WHITE);

        ClearBackground(BLACK);
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}