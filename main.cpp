#include <stdio.h>
#include <math.h>

#include <SDL/SDL.h>

#include "renderer.hpp"
#include "vector.hpp"
#include "triangle.hpp"

#define RTS_X 640
#define RTS_Y 480

int main(){
	printf("\n\n\n");
    printf("[+] Welcome to 3DR\n\n");

    SDL_Surface* surface = NULL;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Set up screen
    surface = SDL_SetVideoMode( RTS_X, RTS_Y, 32, SDL_SWSURFACE );

    Scene s;
    RenderTarget t(RTS_X, RTS_Y);
    Renderer r(Vector(3,3,0), Vector(-1,-1,1), 30, &s, &t);
    //Renderer r(Vector(0,0,0), Vector(0,0,1), 30, &s, &t);

    s.lights.push_back(LightSource(Vector(0,0,-10), Color(1,1,1)));
    s.globalBr = LightSource(Vector(0,0,0),Color(0.01,0.01,0.01));

    //s.triags.push_back(Triangle(
    //    Vector( 1, 1,-3),
    //    Vector( 1,-1,-3),
    //    Vector(-1,-1,-3)
    //));

    //s.triags.push_back(Triangle(
    //    Vector( 1, 1,-3),
    //    Vector(-1, 1,-3),
    //    Vector(-1,-1,-3)
    //));

    s.triags.push_back(Triangle(
        Vector( 1, 1, 3),
        Vector( 1,-1, 3),
        Vector(-1,-1, 3),
        Color(1,0,0)
    ));

    s.triags.push_back(Triangle(
        Vector( 1, 1, 3),
        Vector(-1, 1, 3),
        Vector(-1,-1, 3),
        Color(1,0,0)
    ));

    s.triags.push_back(Triangle(
        Vector( 1, 1, 5),
        Vector( 1,-1, 5),
        Vector(-1,-1, 5),
        Color(1,1,0)
    ));

    s.triags.push_back(Triangle(
        Vector( 1, 1, 5),
        Vector(-1, 1, 5),
        Vector(-1,-1, 5),
        Color(1,1,0)
    ));

    s.triags.push_back(Triangle(
        Vector( 1, 1, 5),
        Vector( 1, 1, 3),
        Vector( 1,-1, 5),
        Color(0,1,0)
    ));

    s.triags.push_back(Triangle(
        Vector( 1,-1, 3),
        Vector( 1, 1, 3),
        Vector( 1,-1, 5),
        Color(0,1,0)
    ));

    s.triags.push_back(Triangle(
        Vector(-1, 1, 5),
        Vector(-1, 1, 3),
        Vector(-1,-1, 5),
        Color(0,1,1)
    ));

    s.triags.push_back(Triangle(
        Vector(-1,-1, 3),
        Vector(-1, 1, 3),
        Vector(-1,-1, 5),
        Color(0,1,1)
    ));

    int x = 6;
    char c='-';
    int Run=1;
    uint32_t startT = SDL_GetTicks();
    int framecnt = 0;
    SDL_Event Events;
    while(Run){
        //scanf("%c",&c);
        t.clear();
        r.renderScene();
        //r.createView(Vector((float)x/2,0,0), Vector((float)x*(-1.0f/6.0f),0,1), 30);
        r.createView(
            Vector(6*cos((float)x/10.0f), 3, 5+5*sin((float)x/10.0f)),
            Vector(-10*cos((float)x/10.0f),-1, -6*sin((float)x/10.0f)).normalize(),
            30);

        if(x==-100){
            c='+';
        }else if(x==100){
            c='-';
        }

        if(c=='+'){
            x++;
        }else if(c=='-'){
            x--;
        }

        SDL_LockSurface(surface);

        uint8_t * pxl = (uint8_t*)surface->pixels;
        memcpy((uint32_t*)pxl, t.fbadr(), RTS_X*RTS_Y*sizeof(uint32_t));

        SDL_UnlockSurface(surface);

        //Update Screen
        SDL_Flip( surface );

        //Pause
        SDL_Delay( 10 );

        framecnt++;
        float fps = ( framecnt/(float)(SDL_GetTicks() - startT) )*1000;
        printf("%.2f\n",fps);

        while (SDL_PollEvent(&Events)){
            if (Events.type == SDL_QUIT){
                Run = false;
            }
        }
    }

    //Quit SDL
    SDL_Quit();
}
