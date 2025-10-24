#include <iostream> 
#include <raylib.h>
#include <cmath>


class Paddle{
    private:
        Rectangle rect;
        int speed = 800;

    public:
        Paddle(float x, float y){
            this->rect.x = x;
            this->rect.y = y;
            this->rect.width = 20;
            this->rect.height = 100;
        }

        Paddle(float x, float y, float width, float height){
            this->rect.x = x;
            this->rect.y = y;
            this->rect.width = width;
            this->rect.height = height;
        }
        Rectangle getRect(){
            return rect;
        }
        void moveUp(){
            if(rect.y > 0){
                rect.y -= GetFrameTime() * speed;
            }
        }

        void moveDown(){
            if(rect.y < (600 - rect.height)){
                rect.y += GetFrameTime() * speed;
            }
        }

        void display(){
            DrawRectangleRec(this->rect, WHITE);
        }
};

class Ball{
    private:
        float radius = 10;
        float dt = 1/60;
        int speed = 250;
        Vector2 pos;
        Vector2 direction;

    public:
        Ball(){
            pos.x = 450;
            pos.y = 300;
            direction.x = 1;
            direction.y = 1;
        }
        Vector2 getPos(){
            return pos;
        }
        float getRadius(){
            return radius;
        }
        void toggleXDirection(){
            if(direction.x > 0){
                direction.x = -1;
            }
            else{
                direction.x = 1;
            }
        }
        void toggleYDirection(){
            if(direction.y > 0){
                direction.y = -1;
            }
            else{
                direction.y = 1;
            }
        }
        void borderDetection(){
            if(pos.x >= 900){
                toggleXDirection();
            }
            else if(pos.x <= 0){
                toggleXDirection();
            }

            if(pos.y >= 600){
                toggleYDirection();
            }
            else if(pos.y <= 0){
                toggleYDirection();
            }
        }
        void move(){
            pos.x += GetFrameTime() * speed * direction.x;
            pos.y += GetFrameTime() * speed * direction.y;
        }
        void display(){
            DrawCircle(pos.x, pos.y, radius, WHITE);
        }
};


int main(){
    const float SCREEN_WIDTH = 900;
    const float SCREEN_HEIGHT = 600;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);


    //Player
    Paddle player = Paddle(20,20);
    //Enemy
    Paddle enemy = Paddle(860,480);
    //Ball
    Ball ball = Ball();

    while(WindowShouldClose() == false){

        // Process user input
        if(IsKeyDown(KEY_UP)){
            player.moveUp();
        }
        if(IsKeyDown(KEY_DOWN)){
            player.moveDown();
        }

        // update world
        ball.borderDetection();
        ball.move();
        if((CheckCollisionCircleRec(ball.getPos(),ball.getRadius(),player.getRect())) || (CheckCollisionCircleRec(ball.getPos(),ball.getRadius(),enemy.getRect()))){
            ball.toggleXDirection();
            ball.toggleYDirection();
        }


        // Draw updated world
        BeginDrawing();
        
            ClearBackground(GREEN);
            player.display();
            enemy.display();
            ball.display();

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}
