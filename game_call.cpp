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

class kinematicBody{ //A very flexible class i love it
    public:
    int x; int y; 
    const int speed = 300; Vector2 direction = Vector2();
    void move_and_slide(){
        this->y += speed * direction.y * GetFrameTime(); // multiply the change of frame to make every frame proportional
        this->x += speed * direction.x * GetFrameTime();
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
        if(y < 0){//border at window y
            direction.y= 1;
        }
        if(y>get.maximum_sizey){
            direction.y = -1;
        }
        if(x < 0|| x > get.maximum_sizeX){ ///borders at window x, implement score? 
            //direction.x= 1;
           start();
        }
    }
    void hit(Rectangle rec){
        Vector2 center = Vector2();
        center.x = x;
        center.y = y;
        if(CheckCollisionCircleRec(center,size,rec)){
            if(direction.x == -1||direction.y == -1){
                direction.x = 1;
                direction.y = 1;
            } else{
                direction.x = -1;
                direction.y = 1;
            }
            DrawText("HIT",get.centerx-30,get.centery,55,WHITE);
        }
    }
    void start(){
        x = get.centerx; y=get.centery;
        direction.x = 1; direction.y = 1;
        DrawText("Score!",get.centerx-30,get.centery,55,WHITE);
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
    void assign_rect(Rectangle pad){
        hit(pad);
    }
    int get_shape(){
        return size;
    }
};

class player_paddle: public kinematicBody
{
    protected:
    int height;int width;
    private:
    public:
    Rectangle shape = Rectangle();
    player_paddle(int height,int width){
        shape.height = height;shape.width =width;
        this->height = height; this->width = width;
    }
    void controls(){
        this->direction.y = (int)IsKeyDown(KEY_RIGHT)+ (int)IsKeyDown(KEY_LEFT)*-1; // any bool that is true can be read as 1. BIG BRAIN?
    }
    void update(){
        //DrawRectangle(get.most_left,get.centery-50,10,100,WHITE);
        DrawRectangle(x,y,width,height,WHITE);
        move_and_slide();
        controls();
        limitY();
    }
    Rectangle getshape(){
        shape.x =x;shape.y=y;
         return shape;
    }
    void limitY(){
        
        if(y > get.maximum_sizey+20){
            y -= get.maximum_sizey+20;
        }
        if(y<20){
            y += 20;
        }
    }
};

class cpu_paddle: public player_paddle{
    int state = 0;
    using player_paddle::player_paddle;
    //DrawRectangle(get.most_right-20,get.centery-50,10,100,WHITE);//right, sub y with half of rec height to center pad
    public:void controls(int ballY){
        switch(state){
            case 0:
            y = ballY;
        }
    }
    
};


///WINDOW
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
        compad.controls(game_ball.y);
        game_ball.assign_rect(compad.getshape());
        game_ball.assign_rect(playerpad.getshape());
        EndDrawing();
    }

    CloseWindow();
};
void inputs(){
}
