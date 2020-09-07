#pragma once
/*
Just a Simple Game where a player needs to guess the U.S. State I am thinking of
*/
#pragma once
#include<string>

enum class Wordtype
{
	Invalid_Status,
	Not_A_Letter,
	Wrong_Length,
	Valid_Guess,
	Not_Capital_Word,
	Not_Lowercase
};

struct CorrectIncorrectCount
{
	int CorrectlyPlacedWords = 0;
	int IncorrectlyPlacedWords = 0;
};

class EZLevel
{
private:
	std::string SecretWord;
	int CurrentTry;
	bool DidPlayerWin;

public:
	//Constructor
	EZLevel();
	void ResetGame();

	std::string SecretWordPadding(std::string guess);

	void SetSecretWord(std::string SW);
	int GetSecretWordLength() const;
	int GetMaxTries() const;
	int GetCurrentTry() const;
	std::string GetSecretWord();

	CorrectIncorrectCount SubmitValidGuess(std::string);
	Wordtype ValidateGuess(std::string) const;
	bool IsGameWon();
};

