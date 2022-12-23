#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define EASY 20
#define MODERATE 15
#define HARD 10
#define CRAZY ((rand()%25)+5)
#define FALSE 0
#define TRUE !0
#define NUM_OF_DIGITS 4

enum { Easy = 1, Moderate, Hard, Crazy };

void gameProgress(int rounds);
void numToGuess(int* targetNum);
int isNumValid(int* num);
void checkHitsOrMisses(int* counter, int* targetNum, int* userGuess);
void cleanBuffer();
void lose();
void win();

int main() {
	srand((unsigned)time((time_t)NULL));
	int userChoice = 0;
	char playAgain = 'y';
	printf("Welcome to the Guessing Game! \n\nRules:\n1.You need to guess 4 digits in some order.\n2.You have limited number of rounds.\n3.after each guess you will get a hint.\n\nHITS : The number of digits in your guess which were exactly right.\nMISSES : The number of digits in your guess which belongs to the password but were miss - placed.\n\nYou can only use the numbers  1-6 to guess and the numbers cant be repeated\n i.e:\n 1234 is good\n 1233 is bad (because 3 is repeated)\n 1237 is bad (because you can only use the numbers 1-6)\n\n)");

	while (playAgain == 'y')
	{
		printf("Please choose the game level:  \n");
		printf("1 - Easy(20 rounds)\n");
		printf("2 - Moderate(15 rounds)\n");
		printf("3 - Hard(10 rounds)\n");
		printf("4 - Crazy(random number of rounds 5-25)\n\n");

		cleanBuffer();
		do {
			printf("Make a choice (1-4): ");
			scanf_s("%d", &userChoice);
		} while ((userChoice < Easy) || (userChoice > Crazy));

		if (userChoice == Easy) {
			printf("You are in EASY mode\n");
			gameProgress(EASY);
		}
		else if (userChoice == Moderate) {
			printf("You are in MODERATE mode\n");
			gameProgress(MODERATE);
		}
		else if (userChoice == Hard) {
			printf("You are in HARD mode\n");
			gameProgress(HARD);
		}
		else if (userChoice == Crazy) {
			printf("You are in CRAZY mode  \n");
			gameProgress(CRAZY);
		}
		do
		{
			printf("Would you like to play again? (y/n): ");
			playAgain = _getch();
			_putch(playAgain);
			_putch('\n');
		} while (playAgain != 'y' && playAgain != 'n');

		if (playAgain == 'y')
			system("cls");
	}
	printf("\nGoodbye!\n");
	system("pause");
	
	return 0;
}

void gameProgress(int rounds) 
{
	int targetNum[NUM_OF_DIGITS] = { 0 }; 
	int userGuess[NUM_OF_DIGITS] = { 0 };
	int hitOrMiss[2] = { 0 };
	int round = rounds;

	numToGuess(targetNum); //make a number to guess
	printf("\n");
	for (; round > 0; round--)
	{
		printf("You have %d Guesses Left\n", round);
		printf("Make a Guess: ");
		cleanBuffer();
		for (int i = 0; i < NUM_OF_DIGITS; i++)
		{
			int choice = _getch();
			_putch(choice);
			userGuess[i] = choice;
		}
		if (!isNumValid(userGuess))
		{
			printf("\nYou Cant use this number, try again\n\n");
			round++;
		}
		else
		{
			checkHitsOrMisses(hitOrMiss, targetNum, userGuess);
			printf("\nHits: %d \nMisses: %d \n\n", hitOrMiss[0], hitOrMiss[1]);
		}
		if (hitOrMiss[0] == NUM_OF_DIGITS)
		{
			printf("\n\nYou did it!!!\n\n");
			win();
			printf("You won!!! It took you %d guesses\n", rounds-round);
			return;
		}
	}
	if (!round) //lost
	{
		lose();
		printf("\nyou lost! The number was\n");
		for (int i = 0; i < NUM_OF_DIGITS; i++)
			printf("%d", targetNum[i]);
		_putch('\n');
	}
}

void numToGuess(int* targetNum)
{
	int new_random;
	int unique = FALSE;
	for (int i = 0; i < NUM_OF_DIGITS; i++)
	{
		do
		{
			new_random = ((rand() % 6) + 1);
			unique = TRUE;
			for (int j = 0; j < i; j++) {
				if (targetNum[j] == new_random)
					unique = FALSE;
			}
		} while (!unique);
		targetNum[i] = new_random;
	}
}

int isNumValid(int* num)
{
	for (int i = 0; i < NUM_OF_DIGITS; i++) //if not between 1-6
	{
		if (!(num[i] >= 49 && num[i] <= 54))
			return FALSE;
	}
	for (int i = 0; i < NUM_OF_DIGITS; i++) //Turn from ASCII to num
	{
		num[i] = num[i] - 48;
	}
	for (int i = 0; i < NUM_OF_DIGITS; i++) // if the same digit is more then once in the choice
	{
		for (int j = 0; j < NUM_OF_DIGITS; j++)
		{
			if (i != j && num[i] == num[j])
				return FALSE;
		}
	}
	return TRUE;
}

void checkHitsOrMisses(int* counter, int* targetNum, int* userGuess)
{
	counter[0] = 0;
	counter[1] = 0;
	for (int i = 0; i < NUM_OF_DIGITS; i++)
	{
		if (targetNum[i] == userGuess[i])
			counter[0]++; //HIT!
		for (int j = 0; j < NUM_OF_DIGITS; j++)
		{
			if (i != j && targetNum[i] == userGuess[j])
				counter[1]++; //MISS!
		}
	}
}

void cleanBuffer()
{
	fflush(stdin);
}

void lose()
{
	printf("                                                        =--_\n");
	printf("                                         .-\"\"\"\"\"\"-.     |* _)\n");
	printf("                                        /          \\   /  /\n");
	printf("                                       /            \\_/  /\n");
	printf("           _                          /|                /\n");
	printf("       _-'\" / \\                        / |    ____    _. - \"            _\n");
	printf("    _-'   (  '-_            _       (   \\  |\\  /\\  ||           .-'\".\".\n");
	printf("_.-'       '.   `'-._   .-'\" / '.      \"   | |/ /  | |/        _-\"   (   ' - _\n");
	printf("             '.      _-\"   ('-_       \\ | /   \\ |     _.-')     \"-._\n");
	printf("           _.'   _.-'       )     \" - ._ || \\\\ | \\\\  '\"'        . - '\n");
	printf("         '               .-'          `'  || \\\\  ||))\n");
	printf("ari__el_za___ke_n____________ _____  ___ _|\\ _|\\_|\\\\/ _______________  ___   _\n");
	printf("                       c  c  \" c C \"\"C  \" \"\"  \"\" \"\"\n");
	printf("                   c       C\n");
	printf("              C        C\n");
	printf("                   C\n");
	printf("    C     c\n");
}

void win()
{
	printf("                           ___\n");
	printf("                          ( ((\n");
	printf("                           ) ))\n");
	printf("  .::.                    / /(\n");
	printf(" 'M .-;-.-.-.-.-.-.-.-.-/| ((::::::::::::::::::::::::::::::::::::::::::::::.._\n");
	printf("(J ( ( ( ( ( ( ( ( ( ( ( |  ))   -====================================-      _.>\n");
	printf(" `P `-;-`-`-`-`-`-`-`-`-\\| ((::::::::::::::::::::::::::::::::::::::::::::::''\n");
	printf("  `::'                    \\ \\(\n");
	printf("                           ) ))\n");
	printf("                          (_((\n\n\n");
}