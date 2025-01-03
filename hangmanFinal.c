#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

//Deklarasi array untuk menampung nama dan score leaderboard
char ldbNames[4][50];
int ldbScores[4];

//Fungsi untuk menampilkan menu
void printMenu() {
    printf("======= Hangman Game =======\n");
    printf("1. Start Game\n");
    printf("2. Instructions\n");
    printf("3. Leaderboard\n");
    printf("4. Exit\n");
    printf("===========================\n");
    printf("Enter your choice: ");
}

//Fungsi untuk menampilkan instruksi
void printInstructions() {
    printf("\nInstructions:\n");
    printf("1. The game will choose a random word.\n");
    printf("2. You need to guess the word one letter at a time.\n");
    printf("3. You have 5 wrong guesses before losing.\n");
    printf("4. If you guess all the letters correctly, you win.\n");
    printf("Press any key to return to the menu...\n");
    getch();
}

//Fungsi untuk mengurutkan nama dan score pada leaderboard
void insertionSort(int arr[], char names[][50]) {

    for (int i = 1; i < 4; i++) {
        int temp = arr[i];
        char tempName[50];
        strcpy(tempName, names[i]);
        int j = i - 1;

        while (j >= 0 && arr[j] < temp) {
            arr[j + 1] = arr[j];
            strcpy(names[j+1], names[j]);
            j = j - 1;
        }

        arr[j + 1] = temp;
        strcpy(names[j+1], tempName);
    }
}

//Fungsi untuk membaca data leaderboard
void readFile(int currentScore){
	FILE *fp = fopen("leaderboard.txt", "r");
	if(fp == NULL){
		printf("File not exist");
	}else{
		int i=0;
		while(!feof(fp)){
			fscanf(fp, "%[^#]#%d\n", ldbNames[i], &ldbScores[i]);
			i++;
		}
	}
	fclose(fp);
	insertionSort(ldbScores, ldbNames);
}

//Fungsi untuk memperbarui leaderboard
void writeFile(int currentScore, char currentName[50]){
	if(currentScore > ldbScores[2]){
		strcpy(ldbNames[2], currentName);
		ldbScores[2] = currentScore;
	}
	
	FILE *fp = fopen("leaderboard.txt", "w");
	if(fp == NULL){
		printf("File not exist");
	}else{
		for(int i=0; i<3; i++){
			fprintf(fp, "%s#%d\n", ldbNames[i], ldbScores[i]);
		}
	}
	fclose(fp);
	insertionSort(ldbScores, ldbNames);
}

//Fungsi untuk menampilkan leaderboard
void printLeaderboard(char names[4][50], int scores[4]){
	printf("Leaderboard:\n");
	for(int i=0; i<3; i++){
		printf("%d. %-20s%5d\n", i+1, names[i], scores[i]);
	}
	printf("*Lose player isn't added to leaderboard\n\n");
	printf("Press any key to return to the menu...\n");
    getch();
}

//Fungsi untuk menampilkan gambar hangman
void gantungDiri(int wrong){
	switch(wrong){
		case 1:
			printf("\n\n +---+\n");
			printf(" |\n");
			printf(" |\n");
			printf(" |\n");
			printf(" |\n");
			printf(" |\n");
			printf("=========\n");
			break;
		case 2:
			printf("\n\n +---+\n");
			printf(" |   |\n");
			printf(" |\n");
			printf(" |\n");
			printf(" |\n");
			printf(" |\n");
			printf("=========\n");
			break;
		case 3:
			printf("\n\n +---+\n");
			printf(" |   |\n");
			printf(" |   O\n");
			printf(" |\n");
			printf(" |\n");
			printf(" |\n");
			printf("=========\n");
			break;
		case 4:
			printf("\n\n +---+\n");
			printf(" |   |\n");
			printf(" |   O\n");
			printf(" |  /|\\\n");
			printf(" |\n");
			printf(" |\n");
			printf("=========\n");
			break;
		case 5:
			printf("\n\n +---+\n");
			printf(" |   |\n");
			printf(" |   O\n");
			printf(" |  /|\\\n");
			printf(" |  / \\\n");
			printf(" |\n");
			printf("=========\n");
			break;
		default:
			printf("");
			break;
	}
}

//Fungsi untuk menghitung score
int scoring(int wrong){
	int score = 100 - (wrong*20);
	return score;
}

int main() {
	//Mendapatkan index kata secara acak untuk setiap permainan
    srand(time(NULL));
    
    //List kata yang harus ditebak
    char words[15][20] = {
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
    
    //Deklarasi dan inisialisasi variable yang dibutuhkan
    char answer[15];
    char guesses[30] = "";
    int playing = 1;
    int wrong = 0;
    int right = 0;
    char current;
    int i = 0;
    int choice;
    
	//Loop untuk menampilkan menu dan memulai permainan
    while (1) {
    	system("cls"); //Mengosongkan konsol
        printMenu();
        scanf("%d", &choice); //Mengambil pilihan user
        getchar(); //Mengonsumsi garis baru

        switch (choice) {
            case 1:  // Memulai permainan
            	//Mengambil kata secara acak
                strcpy(answer, words[rand() % 15]);
                char guesses[30] = "";
                strcpy(guesses, "");
                playing = 1;
            	char playerName[50];
            	
            	//Mengambil nama pemain
            	printf("Enter your name: ");
            	scanf("%[^\n]", playerName);
				
                do {
                    system("cls"); // Non platform specific. Use system("cls") if confirmed will be run on windows.
                    wrong = 0;
                	right = 0;
                	
                	//Menampilkan update huruf yang sudah tertebak
					for (i = 0; i < strlen(answer); i++){
						if (strchr(guesses, answer[i]) != NULL){
							printf("%c ", answer[i]);
							++right;
						}else{
							printf("_ ");
						}
					}
					
					//Menampilkan huruf yang pernah ditebak dan salah
					printf("\n\nWrong Letters History: ");
			    	
			    	//Memeriksa jawaban pemain
					for (i = 0; i < strlen(guesses); i++){
						if (strchr(answer, guesses[i]) == NULL){
							printf("%c ", guesses[i]);
							++wrong;
						}
					}
					
					//Menampilkan hangman jika pemian salah
					gantungDiri(wrong);
					
					//Menampilkan jumlah kesalahan
			    	printf("\nWrong Guesses: %d\n", wrong);
			    	
			    	//Memeriksa keberlanjutan permainan
					if (wrong >= 5 || right >= strlen(answer)){
						playing = 0;
						break;
					}
					
					//Mengambil tebakan pemain
					printf("\nEnter Your Guess: ");
					current = toupper(getch());
					
					//Memeriksa kesamaan jawaban pemain dengan tebakan sebelumnya
                    if (strchr(guesses, current) == NULL) {
                        guesses[strlen(guesses)] = current;

                        if (strchr(answer, current) == NULL) {
                            ++wrong;
                        }
                    } else {
                        printf("You already guessed that letter!\n");
                        Sleep(1000);
                    }
                } while (playing);
				
				//Penentuan kemenagnan/kekalahan pemain
                if (wrong >= 5) {
                    printf("\nYou Lose\n");
                    printf("The word was: %s\n", answer);
                }
                if (right >= strlen(answer)) {
                    printf("\nYou Win\n");
                }
                
                //Memperbarui leaderboard
                readFile(scoring(wrong));
                writeFile(scoring(wrong), playerName);
                
                //Menampilkan score pemain
                printf("Your Score: %d\n", scoring(wrong));
                system("pause");
                break;

            case 2:  // Menampilkan instruksi
            	system("cls");
                printInstructions();
                break;

            case 3:  // Menampilkan Leaderboard
            	system("cls");
            	readFile(scoring(wrong));
                printLeaderboard(ldbNames, ldbScores);
                break;

            case 4:  // Exit
            	system("cls");
                printf("Thank you for playing!\n");
                return 0;

            default: //Penanganan input yang tidak sesuai
            	system("cls");
                printf("Invalid choice! Please choose a valid option.\n");
                Sleep(2000);
                break;
        }
    }

    return 0;
}
