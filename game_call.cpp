///all calls are coded here

#include "raylib.h"

struct navigation
{
   int maximum_sizeX = 1000;
   int maximum_sizey = 600;
   int centery = maximum_sizey/2;
   int centerx = maximum_sizeX/2;
   int most_left = 10; int most_right = maximum_sizeX-10;
   int most_top = 20; int most_floor = maximum_sizey-20;
}; navigation get;

class kinematicBody{ //very fexible class
    public:
    int x; int y; 
    const int speed = 10; Vector2 direction = Vector2();
    void move_and_slide(){
        this->y += speed * direction.y;
        this->x += speed * direction.x;
    }
    void set_x(int x){
       this->x = x;
    }
    void set_y(int y){
    this->y = y;
    }
};

class ball: public kinematicBody{
    private:
    int size;
    void check_borders(){
        if(y < 0){
            direction.y= 1;
        }
        if(y>get.maximum_sizey){
            direction.y = -1;
        }
        if(x < 0){
            direction.x= 1;
        }
        if(x > get.maximum_sizeX){
            direction.x = -1;
        }
    }
    public:
    ball(int rad_size){
        this->size = rad_size;
        direction.x = 1; direction.y = 1;
    }
     void update(){
        //DrawCircle(get.centerx,get.centery,(float)10,WHITE);
        DrawCircle(x,y,size,WHITE);
        move_and_slide();
        check_borders();
     }
    void set_dir(Vector2 direction){
        this->direction = direction;
    }
};

class player_paddle: public kinematicBody
{
    protected:
    //int x;int y;
    int height;int width;
    private:
    void controls(){
        
    }
    public:

    player_paddle(int height,int width){
        this->height = height; this->width = width;
    }
    void update(){
        //DrawRectangle(get.most_left,get.centery-50,10,100,WHITE);
        DrawRectangle(x,y,width,height,WHITE);
    }
};
class cpu_paddle: public player_paddle{
    using player_paddle::player_paddle;
    //DrawRectangle(get.most_right-20,get.centery-50,10,100,WHITE);//right, sub y with half of rec height to center pad
};
player_paddle playerpad(50,10);
cpu_paddle compad(50,10);
ball game_ball(10);

void Swindows(){

InitWindow(get.maximum_sizeX,get.maximum_sizey,"My first c++ game pingpong"); //initialize the window
SetTargetFPS(60);

game_ball.set_x(get.centerx); game_ball.set_y(get.centery);/// draw first
playerpad.set_x(get.most_left);playerpad.set_y(get.centery);
compad.set_x(get.most_right-10);compad.set_y(get.centery);
while (!WindowShouldClose())//update
    {
        ClearBackground(BLACK);
        BeginDrawing();
        game_ball.update();playerpad.update();compad.update();
        EndDrawing();
    }

    CloseWindow();
};
void inputs(){
}
