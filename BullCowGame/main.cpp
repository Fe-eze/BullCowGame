/*	This is the console executable for our BullCow game, It makes use of the BullCow class.
	This acts as the view controller and is responsible for all user interaction. 
	For game logic, see the FBullCow class
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate a new game

// Starting point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while(bPlayAgain);
	return 0; // Exit the application
}

// Introduce the game
void PrintIntro() 
{
         //  ,/         \,
         // ((__,-"""-,__))
         //  `--)~   ~(--`
         // .-'(       )`-,
         // `~~`0\\   /0`~~`
         //     |     |
         //jgs  (6___6)
         //      `---`
	std::cout << "                __n__n__            ,/         \\," << std::endl;
	std::cout << "         .------`-\\00/-'           ((__,-\"\"\"-,__))" << std::endl;
	std::cout << "        / ##  ##  (oo)              `--)~   ~(--`" << std::endl;
	std::cout << "       / \\## __   . /              .-'(       )`-," << std::endl;
	std::cout << "          |//YY \\|/                `~~`0\\   /0`~~`" << std::endl;
	std::cout << "          |||   |||                    |     |" << std::endl;
	std::cout << "          |||   |||                    (6___6) "<< std::endl;
	std::cout << "          |_|   |_|                     `---`" << std::endl;
	std::cout << "\nWelcome to Bulls and Cows, a fun and interesting word game" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of? \n";
	return;
}

// Body of the game code
void PlayGame() 
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// Loop through GetValidGuess() as long as the player has guesses left and hasn't won the game
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit a valid guess for the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print the number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

// loop continually until user enters a valid guess
FText GetValidGuess() 
{
	FText  Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// Get a guess from the player,
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word that doesn't have repeating letters\n\n";
			break;

		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " Letter Word\n\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all Lowercase letters\n\n";
			break;

		default:
			// assume the guess is valid at this point
			break;
		}
		
	} while (Status != EGuessStatus::OK); // Keep looping until we get a good input, keep voting until we get our desired results, toe-mae-toe toh-mah-toh
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	FText Response = "";

	getline(std::cin, Response);
	// Force the player to either enter yes or no
	while (Response[0] != 'y' && Response[0] != 'Y' && Response[0] != 'n' && Response[0] != 'N') {
		std::cout << "Please answer with y or n: ";
		getline(std::cin, Response);
	}
	// while Loop breaks when Y or N is entered, and either starts a new game or quits repectively
	return (Response[0] == 'y' || Response[0] == 'Y');
	return false;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE. You Guessed right!\n" << std::endl;
	}
	else {
		std::cout << "You got it wrong, better luck next time!\n" << std::endl;
	}
}