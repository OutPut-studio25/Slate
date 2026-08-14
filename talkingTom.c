#include <ncurses.h>
#include "talkingTom.h"

void drawTom(WINDOW *tomScreen, int yMax, int xMax);

void helpInfo(WINDOW *tomsScreen, int yMax, int xMax);

void printUI(WINDOW *tomsScreen, int tomHappiness, int tomFeeding, int tomBathroom, int tomSleep, int yMax, int xMax);

void talkingTom()
{
   int yMax,
       xMax,
       input, 
       gameRan       = 0,
       tomHappiness  = 0,
       tomFeeding    = 50,
       tomSleep      = 50,
       tomBathroom   = 50;

   bool isGameRunning = true;

   clear();
   refresh();

   getmaxyx(stdscr, yMax, xMax);
   WINDOW *tomsScreen = newwin(yMax, xMax, 0, 0);

   while (isGameRunning)
   {
      input = getch();
      box(tomsScreen, 0, 0);

      drawTom(tomsScreen, yMax, xMax);
      printUI(tomsScreen, tomHappiness, tomFeeding, tomBathroom, tomSleep, yMax, xMax);
      wrefresh(tomsScreen);

      switch (input)
      {
         // Checks resize
         case KEY_RESIZE:
            getmaxyx(stdscr, yMax, xMax);
            wresize(tomsScreen, yMax, xMax);
            wclear(tomsScreen);

            // Here to pause screen so user can read message
            getch();
            break;

         // Happy logic
         case 'h':
            wclear(tomsScreen);
            mvwprintw(tomsScreen, yMax * 0.5 - 1, xMax * 0.5 - 20, "Tom loves the scratches behind the ear.");
            wrefresh(tomsScreen);
            tomHappiness += 10;
            tomFeeding -= 10;
            tomBathroom -= 5;
            tomSleep -=20;

            gameRan++;
            box(tomsScreen, 0, 0);
            refresh();

            // Here to pause screen so user can read message
            getch();
            break;

         // Feeding logic
         case 'f':
            wclear(tomsScreen);
            mvwprintw(tomsScreen, yMax * 0.5 - 1, xMax * 0.5 - 12, "Tom loves a good cookie.");
            wrefresh(tomsScreen);
            tomHappiness += 5;
            tomFeeding += 10;
            tomBathroom -= 10;
            tomSleep -=10;

            gameRan++;
            box(tomsScreen, 0, 0);
            refresh();

            // Here to pause screen so user can read message
            getch();
            break;

         // Bathroom logic
         case 'b':
            wclear(tomsScreen);
            mvwprintw(tomsScreen, yMax * 0.5 - 1, xMax * 0.5 - 23, "Tom's a kid and doesn't waste time showering.");
            wrefresh(tomsScreen);
            tomHappiness -= 5;
            tomFeeding -= 5;
            tomBathroom += 10;
            tomSleep +=5;

            gameRan++;
            box(tomsScreen, 0, 0);
            refresh();

            // Here to pause screen so user can read message
            getch();
            break;

         // Sleepy logic
         case 's':
            wclear(tomsScreen);
            mvwprintw(tomsScreen, yMax * 0.5 - 1, xMax * 0.5 - 25, "'Zzz' shhh 'Zzz' Tom's getting his beauty sleep.");
            wrefresh(tomsScreen);
            tomHappiness +=25;
            tomFeeding -= 15;
            tomBathroom -=10;
            tomSleep +=10;

            gameRan++;
            box(tomsScreen, 0, 0);
            refresh();

            // Here to pause screen so user can read message
            getch();
            break;

         // Help print
         case 'H':
            wclear(tomsScreen);
            helpInfo(tomsScreen, yMax, xMax);
            wrefresh(tomsScreen);
            box(tomsScreen, 0, 0);
            refresh();

            // Here to pause screen so user can read message
            getch();
            getch();
            break;

         // Quit logic
         case 'q':
            wclear(tomsScreen);
            isGameRunning = false;
            mvwprintw(tomsScreen, yMax / 2, xMax * 0.5 - 25, "Thanks for playing with Tom. Have a beautiful day!");
            wrefresh(tomsScreen);
            box(tomsScreen, 0, 0);
            refresh();

            // Here to pause screen so user can read message
            getch();
            break;

         // Error
         default:
            break;
      }

      //Checks if player had a perfect day????
      if (tomFeeding >= 100 && tomBathroom >= 100 && tomSleep >= 100 && 
                  tomHappiness >=100)
      {
         wclear(tomsScreen);

         printUI(tomsScreen, tomHappiness, tomFeeding, tomBathroom, tomSleep, yMax, xMax);
         mvwprintw(tomsScreen, yMax * 0.5 - 1, xMax * 0.5 - 20, "A perfect day!!! WOW, what a lucky cat.");
         mvwprintw(tomsScreen, yMax / 2, xMax * 0.5 - 17, "You finished the game in %d moves", gameRan);
         wrefresh(tomsScreen);
         box(tomsScreen, 0, 0);
         refresh();

         // Here to pause screen so user can read message
         getch();
         getch();
         isGameRunning = false;
      }
      //Checks if player has won
      else if (tomHappiness >= 100)
      {
         wclear(tomsScreen);

         printUI(tomsScreen, tomHappiness, tomFeeding, tomBathroom, tomSleep, yMax, xMax);
         mvwprintw(tomsScreen, yMax * 0.5 - 1, xMax * 0.5 - 4, "You won!");
         mvwprintw(tomsScreen, yMax / 2, xMax * 0.5 - 17, "You finished the game in %d moves", gameRan);
         wrefresh(tomsScreen);
         box(tomsScreen, 0, 0);
         refresh();

         // Here to pause screen so user can read message
         getch();
         getch();
         isGameRunning = false;
      }  
      //Checks if player has lost
      else if (tomFeeding <= 0 || tomBathroom <= 0 || tomSleep <= 0 || 
      tomHappiness < 0)
      {
         wclear(tomsScreen);

         printUI(tomsScreen, tomHappiness, tomFeeding, tomBathroom, tomSleep, yMax, xMax);
         mvwprintw(tomsScreen, yMax * 0.5 - 1, xMax * 0.5 - 13, "You made Tom sad today :(");
         mvwprintw(tomsScreen, yMax / 2, xMax * 0.5 - 16, "Run the program again to retry.");
         mvwprintw(tomsScreen, yMax * 0.5 + 1, xMax * 0.5 - 12, "You failed in %d moves", gameRan);
         wrefresh(tomsScreen);
         box(tomsScreen, 0, 0);
         refresh();

         // Here to pause screen so user can read message
         getch();
         getch();
         isGameRunning = false;
      }
   }

   delwin(tomsScreen);
   return;
}

/******************************************************************************
 Prints Talking Tom.
******************************************************************************/
void drawTom(WINDOW *tomScreen, int yMax, int xMax)
{
   mvwprintw(tomScreen, yMax - 43 - 7, xMax * 0.5 - 33, "               .+=. . ++--.   .......   .+..-.                  ");
   mvwprintw(tomScreen, yMax - 42 - 7, xMax * 0.5 - 33, "                -  .-.  ..  -+      .-.. . -..--+++-.-          ");
   mvwprintw(tomScreen, yMax - 41 - 7, xMax * 0.5 - 33, "                -.    -...--           .-. ..  .---  -.         ");
   mvwprintw(tomScreen, yMax - 40 - 7, xMax * 0.5 - 33, "                -.     +..    .           .  -+.    ..          ");
   mvwprintw(tomScreen, yMax - 39 - 7, xMax * 0.5 - 33, "                .-     # --...#.    .+. .-.  -      -.          ");
   mvwprintw(tomScreen, yMax - 38 - 7, xMax * 0.5 - 33, "     .-.         .-   -+--.##.+-   .--...-.. -     ..           ");
   mvwprintw(tomScreen, yMax - 37 - 7, xMax * 0.5 - 33, "    .-  -.         -.-- .-###++.   .-.##+ ++ .-   +.            ");
   mvwprintw(tomScreen, yMax - 36 - 7, xMax * 0.5 - 33, "  .  -  ..-..+      --  .+ .+--    --.### ++   ++-              ");
   mvwprintw(tomScreen, yMax - 35 - 7, xMax * 0.5 - 33, "--  --   .-  +     -+--.    .-      --..---    .-               ");
   mvwprintw(tomScreen, yMax - 34 - 7, xMax * 0.5 - 33, ".-..        .-     +..-..  ..--....---    ....-.-.              ");
   mvwprintw(tomScreen, yMax - 33 - 7, xMax * 0.5 - 33, " -++.       -.    .-...      .-- .+-.  .....-.   +              ");
   mvwprintw(tomScreen, yMax - 32 - 7, xMax * 0.5 - 33, "-.           .+.   +  -   +-           --.    --.+..            ");
   mvwprintw(tomScreen, yMax - 31 - 7, xMax * 0.5 - 33, ".--+--++--     --  .-...    -++-.-+#+-+     ....-.              ");
   mvwprintw(tomScreen, yMax - 30 - 7, xMax * 0.5 - 33, "          --     -- .- .     -......--      ...-                ");
   mvwprintw(tomScreen, yMax - 29 - 7, xMax * 0.5 - 33, "           .-      .-..--.    .#-.--.     +.-.                  ");
   mvwprintw(tomScreen, yMax - 28 - 7, xMax * 0.5 - 33, "            .-         -+-#-            .-.                     ");
   mvwprintw(tomScreen, yMax - 27 - 7, xMax * 0.5 - 33, "              +-            .-...---..-...                      ");
   mvwprintw(tomScreen, yMax - 26 - 7, xMax * 0.5 - 33, "               .-.                        ...                   ");
   mvwprintw(tomScreen, yMax - 25 - 7, xMax * 0.5 - 33, "                    ..        .-+--+-.         .-               ");
   mvwprintw(tomScreen, yMax - 24 - 7, xMax * 0.5 - 33, "                       +    .-        ..         --             ");
   mvwprintw(tomScreen, yMax - 23 - 7, xMax * 0.5 - 33, "                       #   +.           .          -.           ");
   mvwprintw(tomScreen, yMax - 22 - 7, xMax * 0.5 - 33, "                      +   +              .            +.        ");
   mvwprintw(tomScreen, yMax - 21 - 7, xMax * 0.5 - 33, "                      #  ..              -   -. .-.    ..-..    ");
   mvwprintw(tomScreen, yMax - 20 - 7, xMax * 0.5 - 33, "                     .-  ..              -   ..   .-        .-. ");
   mvwprintw(tomScreen, yMax - 19 - 7, xMax * 0.5 - 33, "                     +.  ..              ..   -     -.      -+. ");
   mvwprintw(tomScreen, yMax - 18 - 7, xMax * 0.5 - 33, "                     +   ..               -   +     -.     . .- ");
   mvwprintw(tomScreen, yMax - 17 - 7, xMax * 0.5 - 33, "                     +   ..               -   +    .- .+-  ---- ");
   mvwprintw(tomScreen, yMax - 16 - 7, xMax * 0.5 - 33, "                    .-   -                -   ..    +++--. -    ");
   mvwprintw(tomScreen, yMax - 15 - 7, xMax * 0.5 - 33, "                    ..   -                -    -         --     ");
   mvwprintw(tomScreen, yMax - 14 - 7, xMax * 0.5 - 33, "                    ..   ..               +    ..               ");
   mvwprintw(tomScreen, yMax - 13 - 7, xMax * 0.5 - 33, "                    -.     .           .+.     .- - .+-.        ");
   mvwprintw(tomScreen, yMax - 12 - 7, xMax * 0.5 - 33, "                    -.       ........--         -.-  ...-.      ");
   mvwprintw(tomScreen, yMax - 11 - 7, xMax * 0.5 - 33, "                   .-        -...---...-        -.   .. +.      ");
   mvwprintw(tomScreen, yMax - 10 - 7, xMax * 0.5 - 33, "                   .-        +         -        --     +-       ");
   mvwprintw(tomScreen, yMax - 9 - 7, xMax * 0.5 - 33, "                   .-       ..         .-       -. .--.         ");
   mvwprintw(tomScreen, yMax - 8 - 7, xMax * 0.5 - 33, "                   .-       -.          -.      ..              ");
   mvwprintw(tomScreen, yMax - 7 - 7, xMax * 0.5 - 33, "                    .       -.          -.       -              ");
   mvwprintw(tomScreen, yMax - 6 - 7, xMax * 0.5 - 33, "                .---       .-            -.       .-..          ");
   mvwprintw(tomScreen, yMax - 5 - 7, xMax * 0.5 - 33, "             .-..   .      .-             #         ..+.        ");
   mvwprintw(tomScreen, yMax - 4 - 7, xMax * 0.5 - 33, "             ++-.  +       +               +.     #. +-+        ");
   mvwprintw(tomScreen, yMax - 3 - 7, xMax * 0.5 - 33, "             .++#-.#+...-+.                 .-.  -+-.-.         ");
   mvwprintw(tomScreen, yMax - 2 - 7, xMax * 0.5 - 33, "                                              .---.             ");
   return;  
}

/******************************************************************************
 Help screen.
******************************************************************************/
void helpInfo(WINDOW *tomsScreen, int yMax, int xMax)
{
   mvwprintw(tomsScreen, yMax * 0.5 - 17, xMax * 0.5 - 17, "Here are all the usable commands:");
   mvwprintw(tomsScreen, yMax * 0.5 - 16, xMax * 0.5 - 17, "1. 'h' for happy");
   mvwprintw(tomsScreen, yMax * 0.5 - 15, xMax * 0.5 - 17, "    -  Giving Tom a good scratch around the ear");
   mvwprintw(tomsScreen, yMax * 0.5 - 14, xMax * 0.5 - 17, "    -  Adds 10 to the Happiness stat");
   mvwprintw(tomsScreen, yMax * 0.5 - 13, xMax * 0.5 - 17, "2. 'f' for feed");
   mvwprintw(tomsScreen, yMax * 0.5 - 12, xMax * 0.5 - 17, "    -  Give Tom grandmas famous cookies");
   mvwprintw(tomsScreen, yMax * 0.5 - 11, xMax * 0.5 - 17, "    -  Adds 10 to the Feeding stat");
   mvwprintw(tomsScreen, yMax * 0.5 - 10, xMax * 0.5 - 17, "3. 'b' for bathroom");
   mvwprintw(tomsScreen, yMax * 0.5 - 9, xMax * 0.5 - 17, "    -  Tom is stinky, give him a bath");
   mvwprintw(tomsScreen, yMax * 0.5 - 8, xMax * 0.5 - 17, "    -  Adds 10 to the Bathroom stat");
   mvwprintw(tomsScreen, yMax * 0.5 - 7, xMax * 0.5 - 17, "4. 's' for sleep");
   mvwprintw(tomsScreen, yMax * 0.5 - 6, xMax * 0.5 - 17, "    -  After a long day Tom needs some rest");
   mvwprintw(tomsScreen, yMax * 0.5 - 5, xMax * 0.5 - 17, "    -  Adds 10 to the Sleepy stat");
   mvwprintw(tomsScreen, yMax * 0.5 - 4, xMax * 0.5 - 17, "5. 'q' for quit");
   mvwprintw(tomsScreen, yMax * 0.5 - 3, xMax * 0.5 - 17, "    -  You don't want to play with Tom :(");
   mvwprintw(tomsScreen, yMax * 0.5 - 2, xMax * 0.5 - 17, "    -  Ends playing with Tom");
   return;
}

/******************************************************************************
 UI element.
******************************************************************************/
void printUI(WINDOW *tomsScreen, int tomHappiness, int tomFeeding, int tomBathroom, int tomSleep, int yMax, int xMax)
{
   mvwprintw(tomsScreen, yMax - 8, xMax * 0.5 - 27, "======================================================            ");
   mvwprintw(tomsScreen, yMax - 7, xMax * 0.5 - 27, " type |   ____       ____      ____      ____  |                  ");
   mvwprintw(tomsScreen, yMax - 6, xMax * 0.5 - 27, " 'H'  |  /    \\     /    \\    /    \\    /    \\ |GOAL:         ");
   mvwprintw(tomsScreen, yMax - 5, xMax * 0.5 - 27, "if you|  |%3d%%|     |%3d%%|    |%3d%%|    |%3d%%| |make          ",
               tomHappiness, tomFeeding, tomBathroom, tomSleep);
   mvwprintw(tomsScreen, yMax - 4, xMax * 0.5 - 27, " need |  \\____/     \\____/    \\____/    \\____/ |happy         ");
   mvwprintw(tomsScreen, yMax - 3, xMax * 0.5 - 27, " help | Happiness  Feeding   Bathroom   Sleepy |                  ");
   mvwprintw(tomsScreen, yMax - 2, xMax * 0.5 - 27, "======================================================            ");

   return;
}