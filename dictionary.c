#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "dictionary.h"

static char buffer[65536];
static int bufferLen = 0;

//AI made and added to the bare bones I made
size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
   size_t realsize = size * nmemb;
   memcpy(buffer + bufferLen, contents, realsize);
   bufferLen += realsize;
   buffer[bufferLen] = '\0';
   return realsize;
}

/******************************************************************************
 Dictionary.
******************************************************************************/
void dictionary()
{
   char input[45], url[512], definition[1024];
   char *pos;
   int index = 0;
   CURL *curl;

   //Determines the OS.
   #ifdef _WIN32
      system("cls");
   #else
      system("clear");
   #endif

   // Clear buffer from any previous call.
   memset(buffer, 0, sizeof(buffer));
   bufferLen = 0;

   //Gets definition
   printf("Enter one word you want to define: ");
   scanf("%44s", input);
   printf("\n");

   //Looks it up
   snprintf(url, sizeof(url), "https://api.dictionaryapi.dev/api/v2/entries/en/%s", input);

   //Receives package
   curl = curl_easy_init();
   curl_easy_setopt(curl, CURLOPT_URL, url);
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
   curl_easy_perform(curl);
   curl_easy_cleanup(curl);

   //Look for similar to definition
   pos = strstr(buffer, "\"definition\":\"");
   if (pos == NULL)
   {
      printf("Word not found, sorry.\n");
      getchar();
      getchar();
      return;
   }
   pos += strlen("\"definition\":\"");

   while (pos[index] != '"')
   {
      definition[index] = pos[index];
      index++;
   }
   definition[index] = '\0';

   //Prints definition
   printf("%s\n", definition);

   getchar();
   getchar();
}