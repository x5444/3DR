#include <stdio.h>

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

    //s.triags.push_back(Triangle(
    //    Vector( 1, 1, 3),
    //    Vector( 1,-1, 3),
    //    Vector(-1,-1, 3),
    //    Color(1,0,0)
    //));

    //s.triags.push_back(Triangle(
    //    Vector( 1, 1, 3),
    //    Vector(-1, 1, 3),
    //    Vector(-1,-1, 3),
    //    Color(1,0,0)
    //));

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
    SDL_Event Events;
    while(Run){
        t.clear();
        r.renderScene();
        r.createView(Vector((float)x/2,3,0), Vector((float)x*(-1.0f/6.0f),-1,1), 30);

        if(x==-20){
            c='+';
        }else if(x==20){
            c='-';
        }

        if(c=='+'){
            x++;
        }else if(c=='-'){
            x--;
        }

        SDL_LockSurface(surface);

        for(int y=RTS_Y-1; y>=0;y--){
            for(int x=0; x<RTS_X; x++){

                //c = SDL_MapRGB( screen->format, r, g, b );
                uint8_t * pxl = (uint8_t*)surface->pixels;
                pxl += (y * surface->pitch) + (x * sizeof(uint32_t));
                *((uint32_t*)pxl) = t.fb(x,RTS_Y-y-1);

                //printf("%c", t.fb(x,y)?'X':' ');
            }
            //printf("\n");
        }

        SDL_UnlockSurface(surface);

        //Apply image to screen
        // SDL_BlitSurface( hello, NULL, screen, NULL );

        //Update Screen
        SDL_Flip( surface );

        //Pause
        SDL_Delay( 50 );

        while (SDL_PollEvent(&Events)){
            if (Events.type == SDL_QUIT){
                Run = false;
            }
        }
    }

    //Quit SDL
    SDL_Quit();
}
