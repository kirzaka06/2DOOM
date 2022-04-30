#ifndef _WINDOW_H_
#define _WINDOW_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "entity.h"

typedef struct Window{
    SDL_Window* win;
    SDL_Renderer* ren;
}Window_t;
Window_t* CreateWindow(const char* title, int w, int h){
    Window_t* tmp=malloc(sizeof(Window_t));
    tmp->win=SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w,h,SDL_WINDOW_SHOWN);
    tmp->ren=SDL_CreateRenderer(tmp->win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return tmp;
}
void ClearWindow(Window_t* win){
    SDL_SetRenderDrawColor(win->ren,255,255,255,255);
    SDL_RenderClear(win->ren);
}
void PresentWindow(Window_t* win){
    SDL_RenderPresent(win->ren);
}
void DisplayRect(Window_t* win, float x, float y, int w, int h, SDL_Color col){
	SDL_SetRenderDrawColor(win->ren,col.r,col.g,col.b,255);
	SDL_Rect rect={x, y, w, h};
	SDL_RenderDrawRect(win->ren, &rect);
	SDL_SetRenderDrawColor(win->ren,255,255,255,255);
}
void DisplayText(Window_t* win, TTF_Font* font, const char* text, float x, float y, SDL_Color col){
	SDL_Surface* s=TTF_RenderText_Solid(font, text, col);
	SDL_Texture* tex=SDL_CreateTextureFromSurface(win->ren, s);
	SDL_Rect tmp={x,y,s->w,s->h};
	SDL_RenderCopy(win->ren,tex,NULL,&tmp);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(s);
}
SDL_Texture* LoadImage(Window_t* win, const char* src){
    return (SDL_Texture*)IMG_LoadTexture(win->ren, src);
}
void DisplayImage(Window_t* win, SDL_Texture* tex, SDL_Rect* src, SDL_Rect* dst, double angle, SDL_RendererFlip flip){
    SDL_RenderCopyEx(win->ren,tex,src,dst,angle,NULL,flip);
}
void DisplayImageS(Window_t* win, SDL_Texture* tex, int x, int y, int w, int h){
    SDL_Rect dst={x,y,w,h};
    SDL_RenderCopy(win->ren,tex,NULL,&dst);
}
void DisplayEntity(Window_t* win, Entity_t ent, float cam[2]){
    SDL_Rect dst={ent.x-cam[0],ent.y-cam[1],ent.w,ent.h};
    SDL_RenderCopy(win->ren,ent.tex,&ent.src,&dst);
}
#endif 
