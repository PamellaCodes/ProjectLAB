#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
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
	strcpy(answer, words[rand()%15]);
	char guesses[30] = "";
	int playing = 1;
	int wrong = 0;
	int right = 0;
	char current;
	int i = 0;
	
	do {
		printf("\e[1;1H\e[2J"); // Non platform specific. Use system("cls") if confirmed will be run on windows.
		right = 0;
		wrong = 0;
		for (i = 0; i < strlen(answer); i++){
			if (strchr(guesses, answer[i]) != NULL){
				printf("%c ", answer[i]);
				++right;
			}else{
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
		for (i = 0; i < strlen(guesses); i++){
			if (strchr(answer, guesses[i]) == NULL){
				printf("%c ", guesses[i]);
				++wrong;
			}
		}
		if (wrong >= 5 || right >= strlen(answer)){
			playing = 0;
			break;
		}
		printf("\nEnter Your next Guess: ");
		
		current = toupper(getch());
		if (strchr(answer, current) == NULL){
			++wrong;
		}
		guesses[strlen(guesses)] = current;
	} while (playing);
	
	if (wrong >= 5){
		printf("\nYou Lose\n");
		printf("The word was: %s", answer);
	}
	if (right >= strlen(answer)){
		printf("\nYou Win\n");
	}

	return 0;
}

