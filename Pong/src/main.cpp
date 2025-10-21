#include <iostream> 
#include <raylib.h>
#include <cmath>


class Paddle{
    private:
        Rectangle rect;
        int speed = 10;

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

        void moveUp(){
            if(rect.y > 0){
                rect.y -= speed;
            }
        }

        void moveDown(){
            if(rect.y < (600 - rect.height)){
                rect.y += speed;
            }
        }

        void display(){
            DrawRectangleRec(this->rect, WHITE);
        }
};

class Ball{
    private:
        Vector2 speed;
        int radius = 10;
        Vector2 position;
        Vector2 destination;

    public:
        Ball(){
            position.x = 450;
            position.y = 300;
        }
        Ball(int par_x, int par_y, int par_radius){
            position.x = par_x;
            position.y = par_y;
            radius = par_radius;
        }
        void calcUnitVector(){
            int height = destination.y - position.y;
            int base = destination.x - destination.x;
            base = base * base;
            height = height * height;
            int hyp = base * height;
            hyp = sqrt(hyp);

            speed.x = (destination.x - position.x) / hyp;
            speed.y = (destination.y - position.y) / hyp;
        }
        void calculateDestination(bool horizDirection,bool vertDirection){
            if(horizDirection == true){
                destination.x = GetRandomValue(900, 920);
            }
            else{
                destination.x = GetRandomValue(20, -20);
            }

            if(vertDirection == true){
                destination.y = GetRandomValue(600, 620);
            }
            else{
                destination.y = GetRandomValue(0, -0);
            }
        }
        void reset(bool hDirection, bool vDirection){
          position.x = 450;
          position.y = 300;
          calculateDestination(hDirection,vDirection);
          calcUnitVector();
        }
        void update(){
            position.x += speed.x;
            position.y += speed.y;
        }
        void display(){
            DrawCircle(position.x, position.y, radius, WHITE);
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

        if(IsKeyDown(KEY_UP)){
            player.moveUp();
        }
        if(IsKeyDown(KEY_DOWN)){
            player.moveDown();
        }

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
