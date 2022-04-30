#ifndef _UTILS_H_
#define _UTILS_H_
#include <math.h>
#include <stdint.h>
typedef struct Timer{
    uint32_t delay, last;
    int shot;
}Timer_t;
void TickTimer(Timer_t* timer){
    timer->shot=0;
    uint64_t curr=SDL_GetTicks();
    if(curr>timer->last+timer->delay){
        timer->shot=1;
        timer->last=curr;
    }
}
int CircleCollision(int cx, int cy, int r, int rx, int ry, int rw, int rh){
    float tx=cx;
    float ty=cy;
    //check which to test against
    if(cx<rx)
        tx=rx;
    else if(cx>rx+rw)
        tx=rx+rw;
    if(cy<ry)
        ty=ry;
    else if(cy>ry+rh)
        ty=ry+rh;
    //distance
    float dx=cx-tx;
    float dy=cy-ty;
    float dist=sqrt((dx*dx) + (dy*dy));
    //compare if it's bigger than radius
    if(dist <= r)
        return 1;
    return 0;
}
int RectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
    return (x1 < x2 + w2 &&
            y1 < y2 + h2 &&
            x2 < x1 + w1 &&
            y2 < y1 + h1);
}
#endif
