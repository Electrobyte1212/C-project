
### TEAM S PRESENTS
# THE ULTIMATE HANGMAN

## Introduction

 



This C program is a Hangman Game that supports both single-player and multiplayer modes. The game randomly selects a word from a file (words.txt) in single-player mode or allows Player 1 to input a word in multiplayer mode. The player(s) attempt to guess the word letter by letter or by guessing the entire word. The program keeps track of incorrect guesses and displays a Hangman ASCII art as an indication of remaining attempts. The game ends when the player guesses the word correctly or runs out of attempts. Additionally, users can add new words to the words file for an expanded word pool.

## Team Members

   1. Suman Baral
   2. Swaroop Ratna Shakya
   3. Sandesh Karki
   4. Suyog Limbu



## Features

1. Single and Multiplayer modes
2. Custom word selection
3. Visual hangman stages
4. Basic hint system


## Installation

$ git clone https://github.com/Suman0990/CProgramming082.git

$ cd CProgramming082

$ $ gcc hangman.c -o hangman

## Platform Used

OS: Windows 

IDE: Visual Studio Code

Compiler: MinGW
## How it Works
1. The game begins by selecting a random word and displaying it as(_ _ _ _ _).

2. The player guesses letters one by one.

3. If the letter is correct, it is revealed in the word; otherwise , an incorrect attempt is counted.

4. The game continues until the player either guesses the word correctly or exhausts all attempts.

5. In multiplayer mode, one player give a word and another player  guess that word before the hangman in drawn completely.

