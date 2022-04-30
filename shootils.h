#ifndef _SHOOTILS_H_
#define _SHOOTILS_H_
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
typedef struct Bullet{
    float x, y;
    int w, h, vel[2];
    double angle;
    SDL_Texture* tex;
    struct Bullet* next;
}Bullet_t;
Bullet_t* CreateBulletHead(float x, float y, int w, int h, SDL_Texture* tex, int angle){
    Bullet_t* tmp=malloc(sizeof(Bullet_t));
    tmp->next=NULL;
    tmp->x=x;tmp->y=y;
    tmp->w=w;tmp->h=h;
    tmp->angle=angle;
    switch(angle){
        case 90:
            tmp->vel[1]=-1;
        break;
        case 270:
            tmp->vel[1]=1;
        break;
        case 0:
            tmp->vel[0]=1;
        break;
        case 180:
            tmp->vel[0]=-1;
        break;
        default:
            tmp->vel[0]=0;tmp->vel[1]=0;
        break;
    }
    tmp->tex=tex;
    return tmp;
}

void CreateBullet(Bullet_t* head,float x, float y, int w, int h, SDL_Texture* tex, int angle){
    Bullet_t* tmp=malloc(sizeof(Bullet_t));
    tmp->x=x;tmp->y=y;
    tmp->w=w;tmp->h=h;
    tmp->angle=angle;
    switch(angle){
        case 90:
            tmp->vel[1]=-1;
        break;
        case 270:
            tmp->vel[1]=1;
        break;
        case 0:
            tmp->vel[0]=1;
        break;
        case 180:
            tmp->vel[0]=-1;
        break;
        default:
            tmp->vel[0]=0;tmp->vel[1]=0;
        break;
    }
    printf("head->x: %.0f; tmp->x: %.0f\n", head->x, tmp->x);
    head->next=tmp;
}
#endif
