#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printMenu() {
    printf("======= Hangman Game =======\n");
    printf("1. Start Game\n");
    printf("2. Instructions\n");
    printf("3. Exit\n");
    printf("===========================\n");
    printf("Enter your choice: ");
}

void printInstructions() {
    printf("\nInstructions:\n");
    printf("1. The game will choose a random word.\n");
    printf("2. You need to guess the word one letter at a time.\n");
    printf("3. You have 2 wrong guesses before losing.\n");
    printf("4. If you guess all the letters correctly, you win.\n");
    printf("Press any key to return to the menu...\n");
    getch();
}

int main() {
    srand(time(NULL));
    const char words[15][20] = {
        "ALGORITHM",
        "BINARY",
        "COMPILER",
        "RECURSION",
        "HASHMAP",
        "ENCRYPTION",
        "PROTOCOL",
        "VARIABLE",
        "FUNCTION",
        "DATABASE",
        "ARRAY",
        "BOOLEAN",
        "ITERATION",
        "INHERITANCE",
        "FRAMEWORK"
    };
    char answer[15];
    char guesses[30] = "";
    int playing = 1;
    int wrong = 0;
    int right = 0;
    char current;
    int i = 0;
    int choice;

    while (1) {
        printMenu();
        scanf("%d", &choice);
        getchar();  // To consume the newline character after scanf

        switch (choice) {
            case 1:  // Start Game
                strcpy(answer, words[rand() % 15]);
                wrong = 0;
                right = 0;
                strcpy(guesses, "");
                playing = 1;

                do {
                    printf("\e[1;1H\e[2J"); // Non-platform specific, use system("cls") on Windows
                    right = 0;
                    for (i = 0; i < strlen(answer); i++) {
                        if (strchr(guesses, answer[i]) != NULL) {
                            printf("%c ", answer[i]);
                            ++right;
                        } else {
                            printf("_ ");
                        }
                    }
                    printf("\n +---+\n");
                    printf(" |   |\n");
                    printf(" |   O\n");
                    printf(" |  /|\\\n");
                    printf(" |  / \\\n");
                    printf(" |\n");
                    printf("=========\n");

                    for (i = 0; i < strlen(guesses); i++) {
                        if (strchr(answer, guesses[i]) == NULL) {
                            printf("%c ", guesses[i]);
                            ++wrong;
                        }
                    }

                    if (wrong >= 5 || right >= strlen(answer)) {
                        playing = 0;
                        break;
                    }
                    printf("\nEnter your next guess: ");
                    
                    current = toupper(getch());
                    if (strchr(answer, current) == NULL) {
                        ++wrong;
                    }
                    guesses[strlen(guesses)] = current;
                } while (playing);

                if (wrong >= 5) {
                    printf("\nYou Lose\n");
                    printf("The word was: %s\n", answer);
                }
                if (right >= strlen(answer)) {
                    printf("\nYou Win\n");
                }
                break;

            case 2:  // Instructions
                printInstructions();
                break;

            case 3:  // Exit
                printf("Thank you for playing!\n");
                return 0;

            default:
                printf("Invalid choice! Please choose a valid option.\n");
                break;
        }
    }

    return 0;
}

