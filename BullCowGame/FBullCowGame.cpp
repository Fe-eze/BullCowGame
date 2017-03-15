#include "FBullCowGame.h"
#include <map>
#include <ctype.h>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor, Reset() is defined below

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	return MyMaxTries; 
}

void FBullCowGame::Reset() // TODO get a more rich return value that catches non isograms
{
	constexpr int32 MAX_TRIES = 7;
	const FString HIDDEN_WORD = "project";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if the guess isnt an Isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength())// If the guess is too long or too short
	{
		return EGuessStatus::Wrong_Length; // TODO Write Function
	}
	else if (!IsLowercase(Guess)) // If the guess isnt Lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength();

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) // for all letters of our word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen.find(Letter) != LetterSeen.end()) { // if the letter is in the map break from the loop
			// alternative // if(LetterSeen[Letter])
			return false; // it isnt an isogram
		} else {
			LetterSeen.insert({ Letter, true });// add the letter to the map
			// alternative // LetterSeen[Letter] = true;
		}
	}
	return true; // weird cases like /0 always go through this test alive
}

bool FBullCowGame::IsLowercase(FString Worder) const
{
	// loop thru letters
	for (auto Letter : Worder) 
	{
		if (!islower(Letter)) { // check it's case
			return false; // once an uppercase letter is found, return false
		}
	}
	return true; // it's probably good
}

// Jokes: An Algorithm is not a Vice president's dance style, but a way of solving problems
// TShirt: Keep it Unreal