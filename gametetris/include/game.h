#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;
const int M=20;
const int N=10;
const int SIZE=20;
const int THUTU[]={1,2,3,4,5,6,7};

enum GAMEPHASE
{
   GAMEPLAY,GAMEOVER
};


struct color
{
   int r,g,b,a;
};
color GetColor(int r,int g,int b,int a);
const color COLORS[]=
{
   GetColor(255,0,0,0),
   GetColor(0,255,0,0),
   GetColor(0,0,255,0),
   GetColor(255,255,0,0),
   GetColor(255,0,255,0),
   GetColor(0,255,255,0),
   GetColor(255,127,64,0)
};
struct tetrino
{
   int x,y;
   color mau;
};
const int SetTetrino[7][4]=
{
   0,4,8,12,   //I
   1,4,5,9,    //T
   0,4,8,9,   //L
   0,1,4,5,   //O
   0,4,5,9,    //S
   1,4,5,8,   //Z
   1,5,8,9    //J
};
void GetTetrino(tetrino a[4],int &random,int &restorerandom);
void MoveTetrino(tetrino a[4],tetrino b[4],int &dx);
void RotateTetrino(tetrino a[4],int &rotation);
void DrawTetrino(SDL_Renderer *renderer,tetrino a[4]);
void SoftTetrino(SDL_Renderer *renderer,tetrino a[4],tetrino b[4]);
bool Check(tetrino a[4],int BOARD[M][N]);
void DrawBoard(SDL_Renderer *renderer,int BOARD[M][N]);
void EraseBoard(int BOARD[M][N]);
void DrawNext(SDL_Renderer *renderer,tetrino a[4],int &random);
bool GameLose(int BOARD[M][N]);

void DrawFrame(SDL_Renderer *renderer);
void DrawPointNext(SDL_Renderer *renderer);
#endif // GAME_H
