#include <stdio.h>
#include "window.h"
#include "entity.h"
#include "utils.h"
#include "shootils.h"

#define DELAY 1000/60
#define PLY_SPD 100
#define SQR(val1) (val1*val1)
enum DIR{UP=0,RIGHT=1,DOWN=2,LEFT=3};

/*globals that I couldn't avoid*/
int RUNNING=0;
double dT=0.0;
Entity_t player;
float camera[2]={0,0};
Timer_t animtimer={150,0,0};
SDL_Texture* bullet;
Bullet_t* head;

double DirToAng(int dir){
    double ang=0;
    switch(dir){
        case UP:
            ang=90;
        break;
        case DOWN:
            ang=270;
        break;
        case RIGHT:
            ang=0;
        break;
        case LEFT:
            ang=180;
        break;
    }
    return ang;
}
void Input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type==SDL_QUIT)
            RUNNING=0;
        if(e.type==SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_ESCAPE:
                    RUNNING=0;
                break;
                case SDLK_w:
                    player.vel[1]=-1;
                    player.dir=UP;
                break;
                case SDLK_s:
                    player.vel[1]=1;
                    player.dir=DOWN;
                break;
                case SDLK_a:
                    player.vel[0]=-1;
                    player.dir=LEFT;
                break;
                case SDLK_d:
                    player.vel[0]=1;
                    player.dir=RIGHT;
                break;
                case SDLK_SPACE:
                    CreateBullet(head, player.x, player.y, 8,8, bullet,DirToAng(player.dir));
                break;
            }
        }
        if(e.type==SDL_KEYUP){
            switch(e.key.keysym.sym){
                case SDLK_w:
                    if(player.vel[1]<0)
                        player.vel[1]=0;
                break;
                case SDLK_s:
                    if(player.vel[1]>0)
                        player.vel[1]=0;
                break;
                case SDLK_a:
                    if(player.vel[0]<0)
                        player.vel[0]=0;
                break;
                case SDLK_d:
                    if(player.vel[0]>0)
                        player.vel[0]=0;
                break;
            }
        }
    }
}
int main(){
    Window_t *win=CreateWindow("2DOOM", 800,600);
    SDL_RenderSetLogicalSize(win->ren,400,300);
    {
        SDL_Texture *player_tex=LoadImage(win,"src/img/player_spritesheet.png");
        int vel[2]={0,0};
        SDL_Rect src={0,0,64,64};
        player=CreateEntity(0,0,32,32,vel,player_tex,src);
    }
    bullet=LoadImage(win, "src/img/bullet.png");
    SDL_Texture* floor=LoadImage(win,"src/img/floor.png");
    head=CreateBulletHead(0,0,8,8,bullet,300);
    CreateBullet(head, 32, 86, 8,8, bullet, 300);
    RUNNING=1;
    /*game loop*/
    /*frame limiter variables*/
    uint32_t start=SDL_GetTicks(),time, last=0;
    while(RUNNING){
        /*dt/frame limit start*/
        last=start;
        start=SDL_GetTicks();
        dT=(double)(start-last)/1000;
        /*--Self Explanatory, comment only because of seperation--*/
        Input();
        /*rendering*/
        ClearWindow(win);
        DisplayImageS(win,floor,0,0,400,300);
        DisplayEntity(win,player);
        int num=0;
        for(Bullet_t* tmp=head;tmp!=NULL;tmp=tmp->next){
            DisplayImageS(win,tmp->tex,tmp->x,tmp->y,tmp->w,tmp->h);
            ++num;
        }
        printf("Iterations: %d\n",num);
        PresentWindow(win);
        /*update*/
        /*player movement*/
        float ply_mag=sqrt(SQR(player.vel[0]) + SQR(player.vel[1]));
        if(ply_mag>0){
            player.x+=((player.vel[0]*PLY_SPD)/ply_mag)*dT;
            player.y+=((player.vel[1]*PLY_SPD)/ply_mag)*dT;
        }

        /*anims*/
        switch(player.dir){
            case UP:
                player.src.y=64;
            break;
            case DOWN:
                player.src.y=0;
            break;
            case RIGHT:
                player.src.y=128;
            break;
            case LEFT:
                player.src.y=192;
            break;
        }
        if(player.vel[0] > 0 || player.vel[0]<0 || player.vel[1] > 0 || player.vel[1] < 0){
            TickTimer(&animtimer);
            if(animtimer.shot){
                if(player.src.x < 256)
                    player.src.x+=64;
                else
                    player.src.x=64;
            }
        }else
            player.src.x=0;

        /*frame limit end*/
        time=SDL_GetTicks()-start;
        if(DELAY>time)
            SDL_Delay(DELAY-time);
    }
    return 0;
}
