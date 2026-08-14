#include <ncurses.h>

//made from calendar tutorial
void calendar()
{
   int back,
       daysInMonth,
       dayOfWeek,
       month,
       startingDay,
       trueFalse = 1,
       xMax,
       yMax,
       year;

   getmaxyx(stdscr, yMax, xMax);
   WINDOW *calendar = newwin(yMax, xMax, 0, 0);

   clear();
   refresh();
   echo();

   //Input year and month
   wprintw(calendar, "Enter year: ");
   wrefresh(calendar);
   wscanw(calendar, "%d", &year);
   wprintw(calendar, "Enter month (1 - 12): ");
   wrefresh(calendar);
   wscanw(calendar, "%d", &month);

   //Calculate number of days in the month
   if(month == 2)
   {
      //Check for leap year
      if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
      {
         daysInMonth = 29;
      }
      else
      {
         daysInMonth = 28;
      }
   }
   else if(month == 4 || month == 6 || month == 9 || month == 11)
   {
      daysInMonth = 30;
   }
   else
   {
      daysInMonth = 31;
   }
   
   //Calculate the starting day of the month
   startingDay = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
   for (int i = 1; i < month; ++i)
   {
      if(i == 2)
      {
         if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
         {
            startingDay += 29;
         }
         else 
         {
            startingDay += 28;
         }
      }
      else if( i == 4 || i == 6 || i == 9 || i == 11)
      {
         startingDay += 30;
      }
      else
      {
         startingDay += 31;
      }
   } 
   dayOfWeek = (startingDay + 1) % 7; //Incrementing teh starting day by 1
   
   //Display the calendar
   wprintw(calendar, "\n==============================\n");
   wprintw(calendar, "           %d - %02d\n", year, month);
   wprintw(calendar, "==============================\n");
   wprintw(calendar, " Sun Mon Tue Wed Thu Fri Sat\n");
   wrefresh(calendar);

   //Print spaces for the days 
   for(int i = 0; i < dayOfWeek; ++i)
   {
      wprintw(calendar, "    ");
   }
   //Print the days and month
   for(int day = 1; day <= daysInMonth; ++day)
   {
      wprintw(calendar, "%4d", day);
      if((day + dayOfWeek) % 7 == 0)
      {
         wprintw(calendar, "\n");
      }
   }

   wprintw(calendar, "\n");

   wrefresh(calendar);
   noecho();
   do 
   {
      if((back = getch()) == 'q' || back == 'Q')
      {
         trueFalse = 0;
      }
   }while(trueFalse);

   delwin(calendar);
   return;
}