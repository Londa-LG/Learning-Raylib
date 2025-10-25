#include <iostream> 
#include <raylib.h>
#include <cmath>


class Paddle{
    private:
        Rectangle rect;
        int speed = 800;
        int intel = 0;
        int diff = 4;
        float height = 150;
        float width = 30;

    public:
        Paddle(float x, float y){
            this->rect.x = x;
            this->rect.y = y;
            rect.width = width;
            rect.height = height;
        }
        Rectangle getRect(){
            return rect;
        }
        void increaseDificulty(){
            diff--;
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
        void followBall(Vector2 ball){
            if(intel > diff){
                if((rect.y > ball.y)){
                    moveUp();
                }
                if((rect.y < ball.y)){
                    moveDown();
                }
                intel = 0;
            }else{
             intel += GetRandomValue(1,100);
            }
        }
        void display(){
            DrawRectangleRec(rect, WHITE);
        }
};

class Ball{
    private:
        float radius = 20.0f;
        float dt = 1/60;
        int speed = 300;
        int playerScore = 0;
        int enemyScore = 0;
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
        int getPlayerScore(){
            return playerScore;
        }
        int getEnemyScore(){
            return enemyScore;
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
                // Increase your score
                playerScore++;
                resetPosition();
            }
            else if(pos.x <= 0){
                // Increase enemy score
                enemyScore++;
                resetPosition();
            }

            if(pos.y >= 600){
                toggleYDirection();
            }
            else if(pos.y <= 0){
                toggleYDirection();
            }
        }
        void resetScore(){
            playerScore = 0;
            enemyScore = 0;
        }
        void resetPosition(){
            pos.x = 450;
            pos.y = 300;
            direction.x *= -1;
            direction.y *= -1;
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
    Paddle player = Paddle(20,SCREEN_HEIGHT / 2);
    //Enemy
    Paddle enemy = Paddle(860,SCREEN_HEIGHT / 2);
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
            // Ball movement
        ball.borderDetection();
        ball.move();
            // Paddle collision
        if((CheckCollisionCircleRec(ball.getPos(),ball.getRadius(),player.getRect())) || (CheckCollisionCircleRec(ball.getPos(),ball.getRadius(),enemy.getRect()))){
            ball.toggleXDirection();
            ball.toggleYDirection();
        }

            // Enemy AI
        enemy.followBall(ball.getPos());

            // Score
        int scoreDiff = std::abs(ball.getPlayerScore() - ball.getEnemyScore());
        if(scoreDiff > 3){
            enemy.increaseDificulty();
            ball.resetScore();
            ball.resetPosition();
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
