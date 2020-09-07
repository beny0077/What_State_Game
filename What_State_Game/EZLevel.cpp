#pragma once
#include "EZLevel.h"
#include<ctime>
#include<map>

#define Map std::map 
EZLevel object;

//Non-parameterized constructor to set default values when game is played again
EZLevel::EZLevel()
{
	ResetGame();
}

void EZLevel::ResetGame()
{
	SecretWord;
	CurrentTry = 1;
	DidPlayerWin = false;
	return;
}

void EZLevel::SetSecretWord(std::string SW)
{
	SecretWord = SW;
}

int EZLevel::GetSecretWordLength() const
{
	return SecretWord.length();
}

std::string EZLevel::GetSecretWord()
{
	return SecretWord;
}

int EZLevel::GetCurrentTry() const
{
	return CurrentTry;
}

int EZLevel::GetMaxTries() const
{
	Map<int, int> WordLengthtoMaxTries
	{ {4,3},{5,4},{6,4},{7,5},{8,6},{9,6},{10,6},{11,6},{12,7},{13,7},{14,8}, };
	return WordLengthtoMaxTries[SecretWord.length()];
	return 0;
}

Wordtype EZLevel::ValidateGuess(std::string Guess) const
{
	if (Guess.length() != GetSecretWordLength())
	{
		return Wordtype::Wrong_Length;
	}
	else
	{
		return Wordtype::Valid_Guess;
	}
	return Wordtype::Valid_Guess;
}

CorrectIncorrectCount EZLevel::SubmitValidGuess(std::string Guess)
{
	CurrentTry++;
	CorrectIncorrectCount CIWordCount;

	//Count the number of correct and incoreect words and increment them
	int HiddenWordLength = SecretWord.length();
	for (int MyChar = 0; MyChar < HiddenWordLength; MyChar++)
	{
		for (int GameChar = 0; GameChar < HiddenWordLength; GameChar++)
		{
			//if they match
			if (Guess[GameChar] == SecretWord[MyChar])
			{
				if (MyChar == GameChar)
				{
					CIWordCount.CorrectlyPlacedWords++;
				}
				else
				{
					CIWordCount.IncorrectlyPlacedWords++;
				}
			}
		}
	}
	if (CIWordCount.CorrectlyPlacedWords == HiddenWordLength)
	{
		DidPlayerWin = true;
	}
	else
	{
		DidPlayerWin = false;
	}
	return CIWordCount;
}

bool EZLevel::IsGameWon()
{
	return DidPlayerWin;
}

//Displays secret word with padding
std::string EZLevel::SecretWordPadding(std::string Guess)
{
	//Initialize secretword length with padding
	std::string SecretWordPadded(GetSecretWordLength(), '*');

	for (int i = 0; i < GetSecretWordLength(); i++)
	{
		//If guess is in the correct place reveal the correctly guessed word
		if (Guess[i] == GetSecretWord()[i])
		{
			SecretWordPadded[i] = Guess[i];
		}
	}
	return SecretWordPadded;
}

