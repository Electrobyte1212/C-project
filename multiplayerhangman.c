#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORD_LENGTH 20
#define MAX_ATTEMPTS 6

typedef struct {
    char word[MAX_WORD_LENGTH];
} Word;

// ASCII Art for Hangman Stages
const char *HANGMAN_STAGES[] = {
    "   +---+\n"
    "   |   |\n"
    "       |\n"
    "       |\n"
    "       |\n"
    "       |\n"
    "=========\n",  // 0 wrong guesses

    "   +---+\n"
    "   |   |\n"
    "   O   |\n"
    "       |\n"
    "       |\n"
    "       |\n"
    "=========\n",  // 1 wrong guess

    "   +---+\n"
    "   |   |\n"
    "   O   |\n"
    "   |   |\n"
    "       |\n"
    "       |\n"
    "=========\n",  // 2 wrong guesses

    "   +---+\n"
    "   |   |\n"
    "   O   |\n"
    "  /|   |\n"
    "       |\n"
    "       |\n"
    "=========\n",  // 3 wrong guesses

    "   +---+\n"
    "   |   |\n"
    "   O   |\n"
    "  /|\\  |\n"
    "       |\n"
    "       |\n"
    "=========\n",  // 4 wrong guesses

    "   +---+\n"
    "   |   |\n"
    "   O   |\n"
    "  /|\\  |\n"
    "  /    |\n"
    "       |\n"
    "=========\n",  // 5 wrong guesses

    " \t\t\t\t  +---+\n"
    " \t\t\t\t  |   |\n"
    " \t\t\t\t  O   |\n"
    " \t\t\t\t /|\\  |\n"
    " \t\t\t\t / \\  |\n"
    " \t\t\t\t      |\n"
    "\t\t\t\t ========\n"  // 6 wrong guesses (Game Over)
};

// Function to get a random word from file
int getRandomWord(char *selectedWord) {
    FILE *file = fopen("words.txt", "r");
    if (!file) {
        printf("Error: Could not open file.\n");
        return 0;
    }

    Word words[100];  
    int count = 0;
    
    while (fscanf(file, "%s", words[count].word) != EOF && count < 100) {
        count++;
    }
    
    fclose(file);

    if (count == 0) {
        printf("Error: No words found in file.\n");
        return 0;
    }

    srand(time(0));
    int randomIndex = rand() % count;
    strcpy(selectedWord, words[randomIndex].word);
    return 1;
}

// Function to display the word with guessed letters
void displayWordState(const char *word, const int *guessedLetters) {
    for (int i = 0; i < strlen(word); i++) {
        if (guessedLetters[i] == 1)
            printf("%c ", word[i]);
        else
            printf("_ ");
    }
    printf("\n");
}

// Function to play Hangman (for both modes)
void playHangman(int isMultiplayer) {
    char word[MAX_WORD_LENGTH];

    if (isMultiplayer) {
        printf("Player 1, enter a word for Player 2 to guess: ");
        scanf("%s", word);
        system("clear"); // Clear the screen to prevent Player 2 from seeing the word
        
    } else {
        if (!getRandomWord(word)) return;
    }

    int wordLength = strlen(word);
    int guessedLetters[wordLength];
    memset(guessedLetters, 0, sizeof(guessedLetters));

    int attemptsLeft = MAX_ATTEMPTS;
    char guessedLettersList[26] = {0};
    int guessedCount = 0;

    system("clear");
    printf("\n start guessing!...\n");
    printf("\nHint: The word starts with '%c'\n", word[0]);

    while (attemptsLeft > 0) {
        printf("\n%s", HANGMAN_STAGES[MAX_ATTEMPTS - attemptsLeft]); 
        displayWordState(word, guessedLetters);
        printf("Attempts left: %d\n", attemptsLeft);
        printf("Guessed letters: %s\n", guessedLettersList);
        
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (strchr(guessedLettersList, guess)) {
            printf("You already guessed '%c'. Try another letter.\n", guess);
            continue;
        }

        guessedLettersList[guessedCount++] = guess;
        guessedLettersList[guessedCount] = '\0';

        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guess) {
                guessedLetters[i] = 1;
                found = 1;
            }
        }

        if (!found) {
            printf("Wrong guess! '%c' is not in the word.\n", guess);
            attemptsLeft--;
        } else {
            printf("Good guess!\n");
        }

        int allGuessed = 1;
        for (int i = 0; i < wordLength; i++) {
            if (!guessedLetters[i]) {
                allGuessed = 0;
                break;
            }
        }

        if (allGuessed) {
            printf("\n%s", HANGMAN_STAGES[MAX_ATTEMPTS - attemptsLeft]);
            displayWordState(word, guessedLetters);
            printf("\nCongratulations! You guessed the word: %s\n", word);
            return;
        }
    }

    printf("\n%s", HANGMAN_STAGES[MAX_ATTEMPTS]);
    printf("Out of attempts! The word was: %s\n", word);
}

// Function to add words to the file
void addWordsToFile() {
    FILE *file = fopen("words.txt", "a"); 
    if (!file) {
        printf("Error: Could not open file.\n");
        return;
    }

    int n;
    printf("How many words do you want to add? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Word newWord;
        printf("Enter word %d: ", i + 1);
        scanf("%s", newWord.word);
        fprintf(file, "%s\n", newWord.word);
    }

    fclose(file);
    printf("Words added successfully!\n");
}

int main() {
    int choice;
    char x;

    printf("\t\t=== THE ULTIMATE HANGMAN ===\n\n%s\t\t", HANGMAN_STAGES[6]);
    printf("\nPress any key to continue\n");
    scanf("%c", &x);
    system("clear");

    while (1) {
        printf("\n1. Add words to the file\n");
        printf("2. Play Hangman\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("clear");
                addWordsToFile();
                break;
            case 2:
                system("clear");
                // Now choose between Single-player and Multiplayer Hangman
                printf("\n1. Single-player Hangman\n");
                printf("2. Multiplayer Hangman\n");
                printf("Enter your choice: ");
                int modeChoice;
                scanf("%d", &modeChoice);
                if (modeChoice == 1) {
                    playHangman(0); // Single-player mode
                } else if (modeChoice == 2) {
                    playHangman(1); // Multiplayer mode
                } else {
                    printf("Invalid choice! Returning to main menu.\n");
                }
                break;
            case 3:
                printf("Thanks for playing! Exiting now...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
