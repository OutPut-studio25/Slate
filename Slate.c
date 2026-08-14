#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/ssl.h>

#include "chickenRun.h"
#include "talkingTom.h"
#include "notesEdit.h"
#include "fred.h"
#include "dictionary.h"
#include "terminal.h"
#include "calendar.h"
#include "browser.h"
#include "mpvPlayer.h"

void errorScreen();
WINDOW *homeScreen();
void app1(bool selected);
void app2(bool selected);
void app3(bool selected);
void app4(bool selected);
void app5(bool selected);
void app6(bool selected);
void app7(bool selected);
void app8(bool selected);
void app9(bool selected);
void openApp(int yApp, int xApp, bool appOpen);

int main(int argc, char **argv)
{
   int xApp = 1,
       yApp = 1,
       highlight = 0;
   bool running = true,
        errorScreenShow,
        selected,
        appOpen = false;

   
   srand(time(NULL));
   initscr();
   curs_set(0);
   noecho();

   homeScreen();
   keypad(stdscr, true);
   timeout(1000);

   //Main loop
   while (running)
   {
      // Checks and resets app selected (AI condensed)
      if (!appOpen)
      {
         homeScreen();
         app1(yApp == 1 && xApp == 1);
         app2(yApp == 1 && xApp == 2);
         app3(yApp == 1 && xApp == 3);
         app4(yApp == 2 && xApp == 1);
         app5(yApp == 2 && xApp == 2);
         app6(yApp == 2 && xApp == 3);
         app7(yApp == 3 && xApp == 1);
         app8(yApp == 3 && xApp == 2);
         app9(yApp == 3 && xApp == 3);
      }

      //Menu
      switch (getch())
      {
      case 'q':
      case 'Q':
         endwin();
         return 0;
         break;
      case 'h':
      case 'H':
         homeScreen();
         appOpen = false;
         break;
      case KEY_UP:
         if (yApp > 1)
         {
            yApp -= 1;
         }
         break;
      case KEY_DOWN:
         if (yApp < 3)
         {
            yApp += 1;
         }
         break;
      case KEY_LEFT:
         if (xApp > 1)
         {
            xApp -= 1;
         }
         break;
      case KEY_RIGHT:
         if (xApp < 3)
         {
            xApp += 1;
         }
         break;
      case KEY_ENTER:
      case 10:
         openApp(yApp, xApp, appOpen);
         appOpen = false;
         break;
      default:
         break;
      }
   }

   curs_set(1);
   endwin();
   return 0;
}

/******************************************************************************
 Error screen (not used).
******************************************************************************/
void errorScreen()
{
   int yMax,
       xMax;
   getmaxyx(stdscr, yMax, xMax);

   WINDOW *errorScreen = newwin(yMax, xMax, 0, 0);
   refresh();

   box(errorScreen, 0, 0);
   mvwprintw(errorScreen, 1, 1, "Error");
   mvwprintw(errorScreen, 2, 1, "Press 'Control + C to exit at any time.");
   wrefresh(errorScreen);
}

/******************************************************************************
 Home screen window.
******************************************************************************/
WINDOW *homeScreen()
{
   int yMax = 0,
       xMax = 0;
   bool selected = false;
   getmaxyx(stdscr, yMax, xMax);

   WINDOW *homeScreen = newwin(yMax, xMax, 0, 0);
   refresh();

   box(homeScreen, 0, 0);
   for (int i = 1; i <= xMax - 2; i++)
   {
      mvwprintw(homeScreen, yMax - 4, i, "=");
   }

   mvwprintw(homeScreen, yMax - 3, 1, " Slate interface  'q' for quit 'h' for reload");

   // Tells the time (AI made)
   time_t now = time(NULL);
   struct tm *t = localtime(&now);
   char timebuf[32];
   strftime(timebuf, sizeof(timebuf), " Time: %I:%M:%S %p  Date: %m/%d", t);
   mvwprintw(homeScreen, yMax - 2, 1, "%s", timebuf);

   // App names
   mvwprintw(homeScreen, 7, 5, "Chicken");
   mvwprintw(homeScreen, 7, 17, "Tom Cat");
   mvwprintw(homeScreen, 7, 28, "Note edit");
   mvwprintw(homeScreen, 13, 4, "Fred Chat");
   mvwprintw(homeScreen, 13, 16, "Dictionary");
   mvwprintw(homeScreen, 13, 28, "Terminal");
   mvwprintw(homeScreen, 19, 4, "Calendar");
   mvwprintw(homeScreen, 19, 17, "GMI100");
   mvwprintw(homeScreen, 19, 28, "MPV Player");

   wrefresh(homeScreen);
   delwin(homeScreen);

   return homeScreen;
}

/******************************************************************************
 App 1 window.
******************************************************************************/
void app1(bool selected)
{
   int yMax = 5,
       xMax = 9,
       start_y = 2,
       start_x = 4;

   WINDOW *appScreen = newwin(yMax, xMax, start_y, start_x);
   refresh();

   if (selected)
   {
      wattron(appScreen, A_REVERSE);
      for (int y = 0; y < yMax; y++)
      {
         for (int x = 0; x < xMax; x++)
         {
            mvwaddch(appScreen, y, x, ' ');
         }
      }
   }
   box(appScreen, 0, 0);
   mvwprintw(appScreen, 1, 1, "   \\\\\\ ");
   mvwprintw(appScreen, 2, 1, "|\\__/'>");
   mvwprintw(appScreen, 3, 1, "\\_uU_/");
   wattroff(appScreen, A_REVERSE);

   wrefresh(appScreen);
   delwin(appScreen);
   return;
}

/******************************************************************************
 App 2 window.
******************************************************************************/
void app2(bool selected)
{
   int yMax = 5,
       xMax = 9,
       start_y = 2,
       start_x = 16;

   WINDOW *appScreen = newwin(yMax, xMax, start_y, start_x);
   refresh();

   if (selected)
   {
      wattron(appScreen, A_REVERSE);
      for (int y = 0; y < yMax; y++)
      {
         for (int x = 0; x < xMax; x++)
         {
            mvwaddch(appScreen, y, x, ' ');
         }
      }
   }
   box(appScreen, 0, 0);
   mvwprintw(appScreen, 1, 1, " _ _/| ");
   mvwprintw(appScreen, 2, 1, "\\'o.o'");
   mvwprintw(appScreen, 3, 1, " (___) ");
   wattroff(appScreen, A_REVERSE);

   wrefresh(appScreen);
   delwin(appScreen);
   return;
}

/******************************************************************************
 App 3 window
******************************************************************************/
void app3(bool selected)
{
   int yMax = 5,
       xMax = 9,
       start_y = 2,
       start_x = 28;

   WINDOW *appScreen = newwin(yMax, xMax, start_y, start_x);
   refresh();

   if (selected)
   {
      wattron(appScreen, A_REVERSE);
      for (int y = 0; y < yMax; y++)
      {
         for (int x = 0; x < xMax; x++)
         {
            mvwaddch(appScreen, y, x, ' ');
         }
      }
   }
   box(appScreen, 0, 0);
   mvwprintw(appScreen, 1, 1, "  /---)");
   mvwprintw(appScreen, 2, 1, " /~-~/");
   mvwprintw(appScreen, 3, 1, "(___/ ");
   wattroff(appScreen, A_REVERSE);

   wrefresh(appScreen);
   delwin(appScreen);
   return;
}

/******************************************************************************
 App 4 window.
******************************************************************************/
void app4(bool selected)
{
   int yMax = 5,
       xMax = 9,
       start_y = 8,
       start_x = 4;

   WINDOW *appScreen = newwin(yMax, xMax, start_y, start_x);
   refresh();

   if (selected)
   {
      wattron(appScreen, A_REVERSE);
      for (int y = 0; y < yMax; y++)
      {
         for (int x = 0; x < xMax; x++)
         {
            mvwaddch(appScreen, y, x, ' ');
         }
      }
   }
   box(appScreen, 0, 0);
   mvwprintw(appScreen, 1, 1, "  |---");
   mvwprintw(appScreen, 2, 1, "  |__");
   mvwprintw(appScreen, 3, 1, "  | ");
   wattroff(appScreen, A_REVERSE);

   wrefresh(appScreen);
   delwin(appScreen);
   return;
}

/******************************************************************************
 App 5 window.
******************************************************************************/
void app5(bool selected)
{
   int yMax = 5,
       xMax = 9,
       start_y = 8,
       start_x = 16;

   WINDOW *appScreen = newwin(yMax, xMax, start_y, start_x);
   refresh();

   if (selected)
   {
      wattron(appScreen, A_REVERSE);
      for (int y = 0; y < yMax; y++)
      {
         for (int x = 0; x < xMax; x++)
         {
            mvwaddch(appScreen, y, x, ' ');
         }
      }
   }
   box(appScreen, 0, 0);
   mvwprintw(appScreen, 1, 1, "/-\\ the");
   mvwprintw(appScreen, 2, 1, "\\-/word");
   mvwprintw(appScreen, 3, 1, "/search");
   wattroff(appScreen, A_REVERSE);

   wrefresh(appScreen);
   delwin(appScreen);
   return;
}

/******************************************************************************
 App 6 window.
******************************************************************************/
void app6(bool selected)
{
   int yMax = 5,
       xMax = 9,
       start_y = 8,
       start_x = 28;

   WINDOW *appScreen = newwin(yMax, xMax, start_y, start_x);
   refresh();

   if (selected)
   {
      wattron(appScreen, A_REVERSE);
      for (int y = 0; y < yMax; y++)
      {
         for (int x = 0; x < xMax; x++)
         {
            mvwaddch(appScreen, y, x, ' ');
         }
      }
   }
   box(appScreen, 0, 0);
   mvwprintw(appScreen, 1, 1, " >_    ");
   mvwprintw(appScreen, 2, 1, "");
   mvwprintw(appScreen, 3, 1, "");
   wattroff(appScreen, A_REVERSE);

   wrefresh(appScreen);
   delwin(appScreen);
   return;
}

/******************************************************************************
 App 7 window.
******************************************************************************/
void app7(bool selected)
{
   int yMax = 5,
       xMax = 9,
       start_y = 14,
       start_x = 4;

   WINDOW *appScreen = newwin(yMax, xMax, start_y, start_x);
   refresh();

   if (selected)
   {
      wattron(appScreen, A_REVERSE);
      for (int y = 0; y < yMax; y++)
      {
         for (int x = 0; x < xMax; x++)
         {
            mvwaddch(appScreen, y, x, ' ');
         }
      }
   }
   box(appScreen, 0, 0);
   wattron(appScreen, A_UNDERLINE);
   mvwprintw(appScreen, 1, 1, "__FEB__");
   wattroff(appScreen, A_UNDERLINE);
   mvwprintw(appScreen, 2, 1, "  |_|  ");
   mvwprintw(appScreen, 3, 1, "    |  ");
   wattroff(appScreen, A_REVERSE);

   wrefresh(appScreen);
   delwin(appScreen);
   return;
}

/******************************************************************************
 App 8 window.
******************************************************************************/
void app8(bool selected)
{
   int yMax = 5,
       xMax = 9,
       start_y = 14,
       start_x = 16;

   WINDOW *appScreen = newwin(yMax, xMax, start_y, start_x);
   refresh();

   if (selected)
   {
      wattron(appScreen, A_REVERSE);
      for (int y = 0; y < yMax; y++)
      {
         for (int x = 0; x < xMax; x++)
         {
            mvwaddch(appScreen, y, x, ' ');
         }
      }
   }
   box(appScreen, 0, 0);
   mvwprintw(appScreen, 1, 1, "  /^\\");
   mvwprintw(appScreen, 2, 1, "  |o|  ");
   mvwprintw(appScreen, 3, 1, " /|#|\\");
   wattroff(appScreen, A_REVERSE);

   wrefresh(appScreen);
   delwin(appScreen);
   return;
}

/******************************************************************************
 App 9 window.
******************************************************************************/
void app9(bool selected)
{
   int yMax = 5,
       xMax = 9,
       start_y = 14,
       start_x = 28;

   WINDOW *appScreen = newwin(yMax, xMax, start_y, start_x);
   refresh();

   if (selected)
   {
      wattron(appScreen, A_REVERSE);
      for (int y = 0; y < yMax; y++)
      {
         for (int x = 0; x < xMax; x++)
         {
            mvwaddch(appScreen, y, x, ' ');
         }
      }
   }
   box(appScreen, 0, 0);
   mvwprintw(appScreen, 1, 1, "  |'\\  ");
   mvwprintw(appScreen, 2, 1, "  |  }");   
   mvwprintw(appScreen, 3, 1, "  |,/  ");

   wattroff(appScreen, A_REVERSE);

   wrefresh(appScreen);
   delwin(appScreen);
   return;
}

/******************************************************************************
 Determines what app to open.
******************************************************************************/
void openApp(int yApp, int xApp, bool appOpen)
{
   if (yApp == 1 && xApp == 1)
   {
      runChickenRun();
   }
   else if (yApp == 1 && xApp == 2)
   {
      talkingTom();
   }
   else if (yApp == 1 && xApp == 3)
   {
      curs_set(1);
      notesEdit();
      curs_set(0);
   }
   else if (yApp == 2 && xApp == 1)
   {
      curs_set(1);
      fred();
      curs_set(0);
   }
   else if (yApp == 2 && xApp == 2)
   {
      curs_set(1);
      endwin();
      dictionary();
      curs_set(0);
      refresh();
   }
   else if (yApp == 2 && xApp == 3)
   {
      curs_set(1);
      endwin();
      terminal();
      curs_set(0);
      refresh();
   }
   else if (yApp == 3 && xApp == 1)
   {
      calendar();
   }
   else if (yApp == 3 && xApp == 2)
   {
      def_prog_mode();
      curs_set(1);
      endwin();
      browser(0, NULL);
      reset_prog_mode();
      curs_set(0);
      refresh();
   }
   else if (yApp == 3 && xApp == 3)
   {
      curs_set(1);
      endwin();
      mpvPlayer();
      curs_set(0);
      refresh();
   }
   return;
}