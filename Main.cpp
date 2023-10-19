#define SDL_MAIN_HANDLED

#include "Bot.h"
#include "Params.h"
#include "Vector2.h"
#include "Matrix.h"
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>

enum class eBEHAVIOUR
{
   WANDER,
   FLEE,
   WANDER_AND_SEEK
};

void drawBot(SDL_Renderer *renderer, const Bot &bot, int r, int g, int b)
{
   Vector2f pos = bot.getPosition();
   Vector2f facing = bot.getFacing();
   Matrix2 mat;
   float rot = atan2(facing.y, facing.x);

   mat.setRotation(rot);
   mat.setTranslation(pos);
   Vector2f tri[4];
   tri[0].x = -5;
   tri[0].y = 5;
   tri[1].x = -5;
   tri[1].y = -5;
   tri[2].x = 10;
   tri[2].y = 0;
   tri[3].x = -5;
   tri[3].y = 5;

   tri[0] = mat.transform(tri[0]);
   tri[1] = mat.transform(tri[1]);
   tri[2] = mat.transform(tri[2]);
   tri[3] = mat.transform(tri[3]);

   SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
   SDL_Point SDLtri[4];
   SDLtri[0].x = tri[0].x;
   SDLtri[0].y = tri[0].y;
   SDLtri[1].x = tri[1].x;
   SDLtri[1].y = tri[1].y;
   SDLtri[2].x = tri[2].x;
   SDLtri[2].y = tri[2].y;
   SDLtri[3].x = tri[3].x;
   SDLtri[3].y = tri[3].y;
   SDL_RenderDrawLines(renderer, &SDLtri[0], 4);
}

void main()
{
   if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
   {
      SDL_Log("SDL_Init failed (%s)", SDL_GetError());
      return;
   }

   SDL_Window *window = NULL;
   SDL_Renderer *renderer = NULL;

   if (SDL_CreateWindowAndRenderer(Params::getInstance()->windowX, Params::getInstance()->windowY,
      0, &window, &renderer) < 0) 
   {
      SDL_Log("SDL_CreateWindowAndRenderer failed (%s)", SDL_GetError());
      SDL_Quit();
      return;
   }

   SDL_SetWindowTitle(window, "App");

   srand (time(NULL));

   //create bots
   Vector2f startPosA(rand() % Params::getInstance()->windowX,
                      rand() % Params::getInstance()->windowY);
   
   Vector2f startPosB(rand() % Params::getInstance()->windowX,
                      rand() % Params::getInstance()->windowY);

   Bot botA(startPosA, 40.0f);
   Bot botB(startPosB, 50.0f);

   auto now = std::chrono::steady_clock::now();
   auto last = now;

   eBEHAVIOUR behaviour = eBEHAVIOUR::WANDER; 

   while (1) 
   {
      last = now;
      now = std::chrono::steady_clock::now();
      double dt = std::chrono::duration<double>(now-last).count();

      int finished = 0;
      SDL_Event event;
      while (SDL_PollEvent(&event)) 
      {
         if (event.type == SDL_QUIT) 
         {
               finished = 1;
               break;
         }
         else if (event.type == SDL_KEYDOWN)
         {
            switch(event.key.keysym.sym)
            {
               case SDLK_ESCAPE:
               {
                  finished = 1;
                  break;
               }
               case SDLK_1:
               {
                  behaviour = eBEHAVIOUR::WANDER;
                  break;
               }
               case SDLK_2:
               {
                  behaviour = eBEHAVIOUR::FLEE;
                  break;
               }
               case SDLK_3:
               {
                  behaviour = eBEHAVIOUR::WANDER_AND_SEEK;
                  break;
               }
            }
         }
      }

      if (finished) 
      {
         break;
      }

      //do game logic 
      switch(behaviour)
      {
         case eBEHAVIOUR::WANDER:
         {
            botA.wander();
            botB.wander();
            break;
         }
         case eBEHAVIOUR::FLEE:
         {
            botA.seek(botB.getPosition());
            botB.flee(botA.getPosition());
            break;
         }
         case eBEHAVIOUR::WANDER_AND_SEEK:
         {
            botA.seek(botB.getPosition());
            botB.wander();
            break;
         }
      }

      botA.update(dt);
      botB.update(dt);

      //render to screen
      SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      drawBot(renderer, botA, 255, 0, 0);
      drawBot(renderer, botB, 0, 0, 255);

      SDL_RenderPresent(renderer);
   }

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);

   SDL_Quit();
}