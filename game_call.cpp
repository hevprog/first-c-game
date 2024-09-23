///all calls are coded here

#include "raylib.h"

/// i regret defining navigation this in .cpp file!
struct navigation //is this allowed?
{
   int maximum_sizeX = 1000;
   int maximum_sizey = 600;
   int centery = maximum_sizey/2;
   int centerx = maximum_sizeX/2;
   int most_left = 10; int most_right = maximum_sizeX-10;
   int most_top = 20; int most_floor = maximum_sizey-20;
}; navigation get;



//GLOBAL CLASS----------------------------------------------
class kinematicBody{ //A very flexible class i love it
    public:
    int x; int y;
    const int speed = 300; Vector2 direction = Vector2();
    void move_and_slide(){
        this->y += speed * direction.y * GetFrameTime(); // multiply the change of frame to make every frame proportional,
        this->x += speed * direction.x * GetFrameTime(); //  so no matter the fps was, the change in framerate is constant 
    }
    void set_x(int x){
       this->x = x;
    }
    void set_y(int y){
    this->y = y;
    }
};





class ball: public kinematicBody{ /// Ping Pong must have a BALL
    private:
    int size;
    void check_borders(){
        if(y < 5){//border at window y
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
            if(direction.x == -1){
                direction.x = 1;
                x += size/2;
            } else{
                direction.x = -1;
                x -= size/2;
            }
            
        }
    }
    void start(){ // when i lose this function is called!,the name, its very deceiving
        x = get.centerx; y=get.centery;
        direction.x = 1; direction.y = 1;
    }
    public:
    
    ball(int rad_size){
        this->size = rad_size;
        direction.x = 1; direction.y = 1;
    }
     void update(){
        DrawCircle(x,y,size,WHITE);
        move_and_slide();
        check_borders();
     }
    void set_dir(Vector2 direction){
        this->direction = direction;
    }
    void assign_rect(Rectangle pad){ /// provide a rectangle object to properly call hit function, else? this ball is flat.
        hit(pad);
    }
    int get_shape(){ // this is for any class or functions requesting its size, hoy!
        return size;
    }
};





class player_paddle: public kinematicBody // this is Your pad, it has up and down control (Key bindings are left key and right key)
{
    protected:
    int height;int width;
    public:
    Rectangle shape = Rectangle();
    player_paddle(int height,int width){
        shape.height = height;shape.width =width;
        this->height = height; this->width = width;
    }
    void controls(){ //You need this,(fixed key bindigs do not change!)
        
        this->direction.y = (int)IsKeyDown(KEY_RIGHT)- (int)IsKeyDown(KEY_LEFT); 
        // any bool that is true can be read as 1. BIG BRAIN?
    }
    void update(){
        DrawRectangle(x,y,width,height,WHITE);
        move_and_slide();
        controls();
        limitY();
    }
    Rectangle getshape(){ // are you in good shape?, returns Vector2
        shape.x =x;shape.y=y;
         return shape;
    }
    void limitY(){ //
        if(y >= get.maximum_sizey-height){
            y = y - 5;
        }
        if(y < 0){
            y = 1;
        }
    }
}; 



class cpu_paddle: public player_paddle{
    int state = 0;
    float rand = 1;
    using player_paddle::player_paddle;

    public:void controls(int ballY){
        int magnitude = ballY;
        switch(state){
            case 0:
            y = magnitude- height/2 * rand; /// CPU is too OP!!!! i cant beat it, nerf CPU with randomized values?
            if(y<0){
                y=1;
            }
            if(y > get.maximum_sizey -height){
                y = get.maximum_sizey - height + 1;
            }
            default:
                state=0; // reserved for future feature such as multiplayer, current version 1.0.1
        }
    } 
    private:void giveRandom(float min,float max){ /// maybe i can make use of this to nerf CPU soon
        rand = GetRandomValue(min,max)/10; /// minimum of 1 to maximum of 10 to return value between 0 and 1

    }
    public:void set_state(int set){ // set state, this is for future features
        state = set;
    }
};


///OBJECTS------------------------------------------------------------------------------------------
player_paddle playerpad(100,10);
cpu_paddle compad(100,10);
ball game_ball(20);
Color colors;
//-------------------------------------------------------------------------------------------------


//game states-----------------------------------------------------------
// I need to know more about data structure like linked list to better implement this part 
//DO NOT DEFINE THESE IN .h file!!
void background_clear(Color color){
    ClearBackground(color);
}

//DESKTOP----------------------------------------------------------------
void Swindows(){
InitWindow(get.maximum_sizeX,get.maximum_sizey,"My first c++ game pingpong"); //initialize the window
SetTargetFPS(60);
game_ball.set_x(get.centerx); game_ball.set_y(get.centery);/// draw first
playerpad.set_x(get.most_left);playerpad.set_y(get.centery-playerpad.getshape().height);
compad.set_x(get.most_right-10);compad.set_y(get.centery-compad.getshape().height);
};
/// all 
void game_init(){ 
    ClearBackground(BLACK);
    game_ball.update();playerpad.update();compad.update();
    compad.controls(game_ball.y);
    game_ball.assign_rect(compad.getshape());
    game_ball.assign_rect(playerpad.getshape());
}

bool game_loop(){
    return !WindowShouldClose();
}
void game_close(){
    CloseWindow();
}
void begindraw(bool begin){
    if(begin){
        BeginDrawing();}
    else
    {
        EndDrawing();
    }
}
void gameDesignTable(){
    DrawLine(get.centerx,0,get.centerx,get.maximum_sizey,WHITE);   
}