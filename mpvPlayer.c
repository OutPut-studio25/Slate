#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

   #ifdef _WIN32
      #include <windows.h>
   #endif

#include "mpvPlayer.h"

void mpvPlayer()
{
   char fileName[100],
        findCommand[128],
        filePath[512];
   FILE *filePointer;

   //Checks OS running
   #ifdef _WIN32
      system("cls");

   #else 
      system("clear");
      
   #endif

   //Prints instructions
   printf("Welcome to the terminal video player through MPV!\n");
   printf("=====================================================================\n");
   printf("This program will play any video type in the terminal,\n");
   printf("but MPV MUST be installed!\n\n");
   printf("'q' to quit before search\n");
   printf("=====================================================================\n");
   printf("Enter your video file name: ");

   scanf("%99s", fileName);

   //Quits function
   if(strcmp(fileName, "q") == 0)
   {
      return;
   }
   
   printf("\nFinding file now...\n");
   printf("Please be patient.\n");
   printf("Also the smaller the terminal the better the video is.\n");
   printf("'q' to quit during movie.\n");

   #ifdef _WIN32
      snprintf(findCommand, sizeof(findCommand), "where /r %%USERPROFILE%% %s", fileName);
      #define sleep_ms(ms) Sleep(ms)
   #else
      snprintf(findCommand, sizeof(findCommand), "find ~ -name \"%s\" 2>/dev/null", fileName);
      #define sleep_ms(ms) usleep((ms) * 1000)
   #endif

   filePointer = popen(findCommand, "r");

   if (filePointer == NULL) 
   {
      perror("Search failed");
      return;
   }

   if (fgets(filePath, sizeof(filePath), filePointer) == NULL) 
   {
      printf("File not found: %s\n", fileName);
      pclose(filePointer);
      return;
   }

   pclose(filePointer);
   filePath[strcspn(filePath, "\n")] = 0;

   //Runs the mpv through terminal
   //MPV MUST BE INSTALLED
   char mpvCommand[600];
   snprintf(mpvCommand, sizeof(mpvCommand), "mpv --vo=tct \"%s\"", filePath);
   system(mpvCommand);
   return;
}
