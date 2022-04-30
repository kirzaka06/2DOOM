#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
typedef struct Entity{
    float x,y;
    int w,h,vel[2],dir;
    SDL_Texture *tex;
    SDL_Rect src;
}Entity_t;
Entity_t CreateEntity(float x, float y, int w, int h, int vel[2], SDL_Texture* tex, SDL_Rect src){
    Entity_t tmp={x,y,w,h,{vel[0], vel[1]},2,tex,src};
    return tmp;
}
#endif
