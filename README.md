Spelling Game
=============

The game is an endless loop that does the following

Given a 2-4 letter prefix that has words in the provided wordlist, try to finish those words.
Words you get are displayed above the prompt.
3 bad guesses and some words you could have used are given and a letter is knocked off.
If there is only one letter left go to the top of the loop (pick a new prefix, clear the correct
guesses list)


Building and Running
====================

If you're on a system that supports Make you can use the included Makefile

    cd build
    make
    ...
    ./spelling_game ../ospd.txt

If you want to regenerate the Makefile or another build system you can use premake

    premake5 gmake
    cd build
    make
    ...
    ./spelling_game ../words_alpha.txt

There are 4 different word lists included in the repo, ospd.txt (the official scrabble player's dictionary)
is the smallest and strictest.  dictionary.txt and enable1.txt are much larger and almost the same; I can't
remember what/how I removed things from the former to create the latter.  words_alpha.txt is twice the size
of dictionary.txt and includes things like proper names so it's particularly easy to play.


