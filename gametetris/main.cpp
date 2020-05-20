#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "game.h"
#include <ctime>
using namespace std;

SDL_Window *window=NULL;
SDL_Renderer *renderer=NULL;
int BOARD[M][N]={0};

int dx=0,rotation=0;float curren,last=0,delay=0.3f;

int main(int argc,char** argv)
{
   srand(time(NULL));
   SDL_Init(SDL_INIT_VIDEO);
   window=SDL_CreateWindow("GAME TETRIS",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,400,600,SDL_WINDOW_SHOWN);
   renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
   bool run=true;
   tetrino a[4],b[4];
   GAMEPHASE game=GAMEPLAY;
   int random,restorerandom=-1;int soft=0;
   GetTetrino(a,random,restorerandom);

   while(run)
   {
      curren=SDL_GetTicks()/1000.0f;
      SDL_Event e;
      while(SDL_PollEvent(&e))
      {
         if(e.type==SDL_QUIT) run=false;
         if(e.type==SDL_KEYDOWN)
         {
            if(e.key.keysym.sym==SDLK_RIGHT) dx=1;
            else if(e.key.keysym.sym==SDLK_LEFT) dx=-1;
            else if(e.key.keysym.sym==SDLK_UP) rotation=1;
            else if(e.key.keysym.sym==SDLK_DOWN) delay=0.05f;
            else if(e.key.keysym.sym==SDLK_SPACE) soft=1;

         }
      }
      SDL_SetRenderDrawColor(renderer,0,0,0,0);

      if(game==GAMEPLAY)
      {
          SDL_RenderClear(renderer);

         DrawFrame(renderer);
         EraseBoard(BOARD);
         DrawBoard(renderer,BOARD);
         if(curren>last+delay)
         {
            last=curren;
            SoftTetrino(renderer,a,b);
            if(!Check(a,BOARD))
            {
               if(BOARD[b[0].y][b[0].x]==0)
               {
                  for(int i=0;i<4;i++)
                  {
                     BOARD[b[i].y][b[i].x]=THUTU[restorerandom];
                  }
                  GetTetrino(a,random,restorerandom);

               }
            }
         }

         MoveTetrino(a,b,dx);
         if(!Check(a,BOARD))
         {
            for(int i=0;i<4;i++)
            a[i]=b[i];
         }

         if(soft==1)
         {
             while(Check(a,BOARD)) SoftTetrino(renderer,a,b);
             soft=0;
         }
         RotateTetrino(a,rotation);
         if(!Check(a,BOARD))
         {
            for(int i=0;i<4;i++)
            a[i]=b[i];
         }
         DrawTetrino(renderer,a);
         DrawPointNext(renderer);
         DrawNext(renderer,a,random);

         delay=0.3f;
         SDL_RenderPresent(renderer);
         if(GameLose(BOARD)==true) game=GAMEOVER;
      }
      else if(game==GAMEOVER)
      {

         run=false;
      }

   }
   SDL_DestroyWindow(window);
   window=NULL;
   SDL_DestroyRenderer(renderer);
   renderer=NULL;
   SDL_Quit();
   return 0;
}


