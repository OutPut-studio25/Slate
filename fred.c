#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fred.h"

void fred()
{
   int  yMax,
        xMax, 
        fredsReplies,
        numFredQuestions = 0, 
        arrayPosition = 0;
   char userQuestion[58],
        answers[6][19] = {"Yes.", "No.", "Maybe.", "Ask again later.", "Definitely.", "Don't count on it."},
        byeBye[6][12]  = {";-)", "See ya.", ":)", "Bye bye now", "Goodbye", "Talk later"},
        fredMeans[]    = {"WHAT DOES FRED MEAN?"};

   getmaxyx(stdscr, yMax, xMax);
   WINDOW *fredChat     = newwin(yMax, xMax, 0,0),
          *fredMessage  = newwin(3, 62, 4, 1),
          *userMessage  = newwin(3, 62, 8, xMax - 63),
          *fredResponse = newwin(3, 62, 12, 1),
          *fredByeBye   = newwin(3, 16, 15, 1);

   clear();
   refresh();
   echo();

   box(fredChat, 0, 0);
   box(fredMessage, 0, 0);
   box(userMessage, 0, 0);
   wrefresh(fredChat);
   wrefresh(fredMessage);
   wrefresh(userMessage);

   mvwprintw(fredChat, 2, xMax / 2 - 10, "Welcome to Fred Chat!");
   mvwprintw(fredChat, yMax - 3, 1, "Asked Fred %d questions", numFredQuestions);
   mvwprintw(fredChat, yMax - 2, 1, "Fred is for entertainment use only. NOT FOR REAL DECISIONS.");
   mvwprintw(fredMessage, 1, 1, " Ask me a quick yes or no question and I'll answer it best.");
   mvwprintw(userMessage, 1, 1, " > ");

   wrefresh(fredChat);
   wrefresh(fredMessage);
   wrefresh(userMessage);
   wgetnstr(userMessage, userQuestion, 57);

   while(userQuestion[arrayPosition])
   {
      userQuestion[arrayPosition] = toupper(userQuestion[arrayPosition]);
      arrayPosition++;
   }

   numFredQuestions++;
   mvwprintw(fredChat, yMax - 3, 1, "Asked Fred %d questions (limit 1 at a time)", numFredQuestions);
   wrefresh(fredChat);

   noecho();
   fredsReplies = rand() % 6;

   if(strcmp(fredMeans, userQuestion) == 0)
   {
      mvwprintw(fredResponse, 1, 2, "Friendly Robotic Entertainment Device");
   }
   else
   {
      mvwprintw(fredResponse, 1, 2, "%s", answers[fredsReplies]);   
   }
   box(fredResponse, 0, 0);
   wrefresh(fredResponse);
   getch();

   box(fredByeBye, 0, 0);
   
   mvwprintw(fredByeBye, 1, 2, "%s", byeBye[fredsReplies]);
   wrefresh(fredByeBye);

   getch();

   delwin(fredChat);
   delwin(fredMessage);
   delwin(userMessage);
   delwin(fredResponse);
   delwin(fredByeBye);
   return;
}