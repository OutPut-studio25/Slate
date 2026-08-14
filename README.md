===============================================================================
This is a terminal based desktop environment called Slate.

Description 
===============================================================================

This environment is designed for people who want a change up. It's not a daily
   drive utility; it is more of something that is cool to say "I can do this."
   You can watch movies, that you have acquired (I must say) legally, in your
   terminal. You can take notes. You can use a Gemini protocol browser. You
   can see what past days looked like using the calendar app. You can look up
   definitions to words, and so much more.

Set up (for Mac mainly, more Linux support will come)
===============================================================================
*  Things you need

   *  MPV to be installed for the video player
      *  brew install mpv

   *  ncurses library installed for C programming 
      *  brew install ncurses (best to install even though mac ships with a version)

   *  libcurl needs to be installed (different than normal curl in most scenarios)
      *  brew install curl

Directions
===============================================================================

*  If you get the source code compile with:
   *  for Mac:
      ```gcc Slate.c chickenRun.c talkingTom.c notesEdit.c fred.c dictionary.c terminal.c calendar.c browser.c mpvPlayer.c -lncurses -lcurl -I$(brew --prefix openssl)/include -L$(brew --prefix openssl)/lib -lssl -lcrypto -o Slate```

   *  for Linux try:
      ```gcc Slate.c chickenRun.c talkingTom.c notesEdit.c fred.c dictionary.c terminal.c calendar.c browser.c mpvPlayer.c -lncurses -lcurl -lssl -lcrypto -o Slate```

   *  for Windows:
      ```gcc give up the ghost dude, I'm just a freshman, it ain't working brother```

   *  Run with:
      *  ./Slate

Licensing 
===============================================================================

*  No official licensing for this project, just make sure you change the program at least 30% before you call it your own thank you.

*  GMI100 not made by me, read more to learn more
   *  Is in public domain
   *  https://unlicense.org

*  Talking Tom 
   *  All rights are to Outfit7
   *  App made for fun (no monetary value so don't sue me Outfit7)

Final notes
===============================================================================

*  Slate may look better if you up the font size of terminal

*  Talking Tom is going to need a larger area so you can actually see him

*  Look up how to use a Gemini Protocol browser before trying

*  'q' is the universal quit in the program

*  MUST install MPV from the makers of MPV for MPV player to work!

Credits
===============================================================================

*  Slate made by Owen Giles and Cole Stanley 
   *  With minimal help from AI 
         *  30% AI
*  Gemini browser made by ir33k 
   *  https://github.com/ir33k/gmi100/tree/master
   *  This is free and unencumbered software released into the public domain.  
         *  Read more: https://unlicense.org
*  MPV player uses the open source program allowing a user to play their video
   *  https://mpv.io/
*  Dictionary uses
   *  https://api.dictionaryapi.dev/api/v2/entries/en/
   *  At the very end it adds users word
*  Talking Tom
   *  Does not belong to me in anyway and Outfit7 has full control so be careful