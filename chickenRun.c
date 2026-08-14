#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "chickenRun.h"

void chicken    (WINDOW *chickenRun, int yMax, int chickenHair, int chickenHead, 
        int chickenBody1, int chickenBody2, int chickenBody3, int chickenLegs);

void rock       (WINDOW *chickenRun, int yMax, int rockX);
bool physics    (int *chickenHair, int *chickenHead, int *chickenBody1,
                 int *chickenBody2, int *chickenBody3, int *chickenLegs);
bool checkCollision(int rockX, int chickenBody3, int yMax);

void runChickenRun()
{
   int yMax, 
       xMax,
       input,
       rockSpeed    = 2,
       score        = 0,
       frameCount   = 0,
       chickenHair  = 10,
       chickenHead  = 9,
       chickenBody1 = 8,
       chickenBody2 = 7,
       chickenBody3 = 6,
       chickenLegs  = 5;
   bool touchingGround = true,
        gameOver     = false;

   clear();
   refresh();

   getmaxyx(stdscr, yMax, xMax);
   int rockX = xMax - 1;

   WINDOW *chickenRun = newwin(yMax, xMax, 0, 0);
   keypad(chickenRun, TRUE);
   nodelay(chickenRun, TRUE);
   refresh();
   wrefresh(chickenRun);

   while (1)
   {
      input = wgetch(chickenRun);

      // Exit to OS
      if (input == 'q' || input == 'Q') 
      {
         break;
      }
      // Checks resize
      if (input == KEY_RESIZE)
      {
         getmaxyx(stdscr, yMax, xMax);
         wresize(chickenRun, yMax, xMax);
         wclear(chickenRun);
      }

      // Game over screen
      if (gameOver)
      {
         wclear(chickenRun);
         box(chickenRun, 0, 0);
         mvwprintw(chickenRun, yMax / 2 - 2, xMax / 2 - 4, "GAME OVER");
         mvwprintw(chickenRun, yMax / 2,     xMax / 2 - 4, "Score:  %d", score);
         mvwprintw(chickenRun, yMax / 2 + 2, xMax / 2 - 10, "R to restart, Q to quit");
         wrefresh(chickenRun);

         nodelay(chickenRun, FALSE);
         input = wgetch(chickenRun);
         nodelay(chickenRun, TRUE);

         // Reload
         if (input == 'r' || input == 'R')
         {
            getmaxyx(stdscr, yMax, xMax);
            rockX        = xMax - 1;
            rockSpeed    = 2;
            score        = 0;
            frameCount   = 0;
            chickenHair  = 10;
            chickenHead  = 9;
            chickenBody1 = 8;
            chickenBody2 = 7;
            chickenBody3 = 6;
            chickenLegs  = 5;
            touchingGround = true;
            gameOver     = false;
            wclear(chickenRun);
            continue;
         }
         else if (input == 'q' || input == 'Q')
            break;
         continue;
      }

      // Jump mechanic
      if (input == ' ' && touchingGround)
      {
         touchingGround = false;
         chickenHair  += 11;
         chickenHead  += 11;
         chickenBody1 += 11;
         chickenBody2 += 11;
         chickenBody3 += 11;
         chickenLegs  += 11;
      }

      // Jump physics
      if (!touchingGround)
         touchingGround = physics(&chickenHair, &chickenHead, &chickenBody1,
                                  &chickenBody2, &chickenBody3, &chickenLegs);

      // Rock movement
      rockX -= rockSpeed;
      if (rockX < -10)
      {
         getmaxyx(stdscr, yMax, xMax);
         rockX = xMax - 1;
         score++;
         if (score % 5 == 0 && rockSpeed < 5)
         {
            rockSpeed++;
         }
      }
   
      // Collision check
      if (checkCollision(rockX, chickenBody3, yMax))
      {
         gameOver = true;
         continue;
      }

      // Draw the GUI
      getmaxyx(stdscr, yMax, xMax);
      wresize(chickenRun, yMax, xMax);
      wclear(chickenRun);

      chicken(chickenRun, yMax, chickenHair, chickenHead, chickenBody1,
              chickenBody2, chickenBody3, chickenLegs);

      rock(chickenRun, yMax, rockX);

      mvwhline(chickenRun, yMax - 2, 1, '=', xMax - 2);
      mvwhline(chickenRun, yMax - 3, 1, '=', xMax - 2);
      mvwhline(chickenRun, yMax - 4, 1, '=', xMax - 2);

      box(chickenRun, 0, 0);
      mvwprintw(chickenRun, 1, xMax / 2 - 6,  " chicken run");
      mvwprintw(chickenRun, 1, xMax - 14,     " Score: %d", score);
      mvwprintw(chickenRun, yMax - 2, 2,      " SPACE = jump  Q = quit ");

      wrefresh(chickenRun);
      napms(75);
      frameCount++;
   }

   delwin(chickenRun);
   clear();
   refresh();
   return;
}

/******************************************************************************
 Chicken art.
******************************************************************************/
void chicken(WINDOW *chickenRun, int yMax, int chickenHair, int chickenHead,
             int chickenBody1, int chickenBody2, int chickenBody3, int chickenLegs)
{
   mvwprintw(chickenRun, yMax - chickenHair - 1, 7, "              ");
   mvwprintw(chickenRun, yMax - chickenHair,     7, "         ,.+-_");
   mvwprintw(chickenRun, yMax - chickenHead,     7, " .     +/(0)>");
   mvwprintw(chickenRun, yMax - chickenBody1,    7, " | \\---'   \\");
   mvwprintw(chickenRun, yMax - chickenBody2,    7, "  \\,  |_/  |");
   mvwprintw(chickenRun, yMax - chickenBody3,    7, "    \\_____/ ");
   mvwprintw(chickenRun, yMax - chickenLegs,     7, "    _|_ _|_");
}

/******************************************************************************
 Rock logic.
******************************************************************************/
void rock(WINDOW *chickenRun, int yMax, int rockX)
{
   if (rockX < 1) return;
   mvwprintw(chickenRun, yMax - 6, rockX, " ,___,  ");
   mvwprintw(chickenRun, yMax - 5, rockX, "/     \\");
}

/******************************************************************************
 Chicken physics.
******************************************************************************/
bool physics(int *chickenHair, int *chickenHead, int *chickenBody1,
             int *chickenBody2, int *chickenBody3, int *chickenLegs)
{
   *chickenHair  -= 1;
   *chickenHead  -= 1;
   *chickenBody1 -= 1;
   *chickenBody2 -= 1;
   *chickenBody3 -= 1;
   *chickenLegs  -= 1;

   return (*chickenLegs <= 5);
}

/******************************************************************************
 Checks for collisions.
******************************************************************************/
bool checkCollision(int rockX, int chickenBody3, int yMax)
{
   int rockLeft   = rockX;
   int rockRight  = rockX + 7;
   int rockTop    = yMax - 6;
   int rockBottom = yMax - 5;

   int chickenLeft   = 9;
   int chickenRight  = 20;
   int chickenBottom = yMax - chickenBody3;  
   int chickenTop    = chickenBottom - 3;    

   if (chickenRight < rockLeft || chickenLeft > rockRight)
      return false;

   if (chickenBottom < rockTop || chickenTop > rockBottom)
      return false;

   return true;
}