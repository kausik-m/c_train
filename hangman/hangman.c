#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAXNUMWORDS 2048
#define MAXWORDLENGTH 32

int main() {

	srand(time(NULL));

	char guessWords[MAXNUMWORDS][MAXWORDLENGTH];
	int wordsRead = 0;

	FILE *filePtr = fopen("hangman.txt","r");

	if(filePtr == NULL) {
		printf("Failed To Open File\n");
		return 0;
	}

	char input[MAXWORDLENGTH];

	while(fgets(input, MAXWORDLENGTH-1, filePtr) && wordsRead <MAXNUMWORDS) {
		sscanf(input, "%s", guessWords[wordsRead]);
		//printf("Scanned: input:%s guessWords[%d]:%s\n",input,wordsRead,guessWords[wordsRead]);
		wordsRead++;
	}

	printf("Total Words Read In:%d\n",wordsRead);

	if(wordsRead == 0){
		printf("No Word in file\n");
		return 0;
	}

	fclose(filePtr);

	// index for random word
	int randomIndex = rand() % wordsRead;

	int numLives = 5;
	int numCorrect = 0;
	int oldCorrect = 0;

	int lengthOfWord = strlen(guessWords[randomIndex]);

	int letterGuessed[lengthOfWord];

	memset(letterGuessed, 0, sizeof(letterGuessed));

	bool quit = false;

	int loopIndex = 0;
	bool reguessed = false; // EDIT

	char guess[MAXWORDLENGTH];
	char letterEntered;

    // game loop
    while (true)
    {
    	printf("\n\nNew Game....");
		while ( numCorrect < lengthOfWord ) {

			printf("\nNew Turn....\nHangman Word:");
			printf("\nEnter quit to exit game");
			printf("\nHangman Word:");

			for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {

				if(letterGuessed[loopIndex] == 1) {
					printf("%c",guessWords[randomIndex][loopIndex]);
				}
				else {
					printf("*");
				}

			}

			printf("\n");

			printf("Number Correct So Far:%d\n",numCorrect);
			printf("Enter a guess letter:");
			fgets(guess, MAXWORDLENGTH, stdin);

			for(int i = 0; i < strlen(guess); i++){
				guess[i] = tolower(guess[i]);
			}

			printf("guess letter: %s\n", guess);

			if( strncmp(guess, "quit", 4) == 0) {
				quit = true;
				break;
			}

			letterEntered = guess[0];
			reguessed = false;

			printf("letterEntered:%c\n",letterEntered);

			oldCorrect = numCorrect;

			for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {

				if(letterGuessed[loopIndex] == 1) {
					if(guessWords[randomIndex][loopIndex] == letterEntered) {
						reguessed = true;
						break;
					}
					continue;
				}

				if( letterEntered == guessWords[randomIndex][loopIndex] ) {
					letterGuessed[loopIndex] = 1;
					numCorrect++;
				}

			}

			if( oldCorrect == numCorrect && reguessed == false) {
				numLives--;
				printf("Sorry, wrong guess. Lives remaining: %d\n", numLives);
				if (numLives == 0) {
					break;
				}
			}
			else if( reguessed == true) {
				printf("Already Guessed!!\n");
			}
			else {
				printf("Correct guess :)\n");
			}

		} // while loop

		if( quit == true ) {
			printf("\nthe user quit early\n");
			return 0;
		}
		else if (numLives == 0) {
			printf("\nSorry you lose, the word was: %s\n",
			guessWords[randomIndex]);
		}
		else  {
			printf("\nYOU WIN!!! :)\n");
		}
    }
	return 0;
}
