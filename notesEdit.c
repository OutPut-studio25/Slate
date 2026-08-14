#include <ncurses.h>
#include <string.h>
#include "notesEdit.h"

void appendNotes();
void writeNotes();
void readNotes();

void notesEdit()
{
   int  yMax,
        xMax,
        input;
   bool noteTaking = true;

   clear();
   getmaxyx(stdscr, yMax, xMax);
   WINDOW *notes = newwin(yMax, xMax, 0, 0);

   //Main loop
   while (noteTaking)
   {
      input = getch();

      box(notes, 0, 0);
      refresh();

      //Prints selection section
      mvwprintw(notes, 2, xMax / 2 - 6, "Notes Edit app");
      mvwprintw(notes, 6, xMax / 2 - 36, "[o] open note   [r] read note  [n] delete and write new note   [q] quit");

      //Menu selection
      switch (input)
      {
         case KEY_RESIZE:
            getmaxyx(stdscr, yMax, xMax);
            wresize(notes, yMax, xMax);
            wclear(notes);
            box(notes, 0, 0);
            refresh();
            break;
         case 'o':
         case 'O':
            wclear(notes);
            appendNotes();
            break;
         case 'n':
         case 'N': 
            wclear(notes);
            writeNotes();
            break;
         case 'q':
         case 'Q':
            noteTaking = false;
            return;
            break;
         case 'r':
         case 'R':
            wclear(notes);
            readNotes();
         default:
            break;
      }

      wrefresh(notes);
   }

   delwin(notes);
   return;
}

/******************************************************************************
 Append to notes.
******************************************************************************/
void appendNotes()
{
   int  yMax,
        xMax,
        fileCharacter;
   FILE *notesFile;
   char note[81];

   getmaxyx(stdscr, yMax, xMax);
   WINDOW *notesScreen = newwin(yMax, xMax, 0, 0);

   clear();
   refresh();
   echo();

   if ((notesFile = fopen("notes.txt", "r")) == NULL)
   {
      printw("Error opening file!");
      getch();
      return;
   }

   while ((fileCharacter = fgetc(notesFile)) != EOF)
      {
         wprintw(notesScreen, "%c", fileCharacter);
         wrefresh(notesScreen);
      }

   if ((notesFile = fopen("notes.txt", "a")) == NULL)
   {
      printw("Error opening file!");
      getch();
      return;
   }

   wprintw(notesScreen, "\n");
   whline(notesScreen, '=', xMax);
   wprintw(notesScreen, "\nAdd to your note (80 characters max at a time):\n");
   wrefresh(notesScreen);
   wgetnstr(notesScreen, note, 80);

   fprintf(notesFile, "%s\n", note);
   fclose(notesFile);

   wattron(notesScreen, A_BOLD);
   wprintw(notesScreen, "\nNote saved.");
   wattroff(notesScreen, A_BOLD);

   wrefresh(notesScreen);
   getch();
   return;
}

/******************************************************************************
 Write notes.
******************************************************************************/
void writeNotes()
{
      int yMax,
          xMax;
   FILE *notesFile;
   char note[81];

   getmaxyx(stdscr, yMax, xMax);
   WINDOW *notesScreen = newwin(yMax, xMax, 0, 0);

   clear();
   refresh();
   echo();

   if ((notesFile = fopen("notes.txt", "w")) == NULL)
   {
      printw("Error opening file!");
      getch();
      return;
   }

   wprintw(notesScreen, "Type your note (80 characters max at a time):\n");

   wgetnstr(notesScreen, note, 80);

   fprintf(notesFile, "%s\n", note);
   fclose(notesFile);

   wattron(notesScreen, A_BOLD);
   wprintw(notesScreen, "\nNote saved.");
   wattroff(notesScreen, A_BOLD);

   wrefresh(notesScreen);
   getch();
   return;
}

/******************************************************************************
 Read notes
******************************************************************************/
void readNotes()
{
   int yMax,
       xMax,
       fileCharacters;
   char endReadingCharacter;
   FILE *notesFile = fopen("notes.txt", "r");

   clear();
   refresh();

   getmaxyx(stdscr, yMax, xMax);
   WINDOW *notesScreen = newwin(yMax, xMax, 0, 0);

   if ((notesFile = fopen("notes.txt", "r")) == NULL)
   {
      printw("Error opening file!");
      getch();
      return;
   }

   wprintw(notesScreen, "Here is your note: \n");

   while ((fileCharacters = fgetc(notesFile)) != EOF)
   {
      wprintw(notesScreen, "%c", fileCharacters);
      wrefresh(notesScreen);
   }

   wprintw(notesScreen, "\n\nPress 'b' to go back");
   wrefresh(notesScreen);
   fclose(notesFile);

   while(1)
   {
      endReadingCharacter = getch();
      if(endReadingCharacter == 'b' || endReadingCharacter == 'B')
      {
         return;
      }
   }
   return;
}