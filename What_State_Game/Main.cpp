
#include<iostream>
#include<string>
#include"EZLevel.h"
#include<ctime>
EZLevel Game;

void PlayGameIntro();
void PlayGame();
std::string ChosenSecretWordList();
std::string getValidGuess();
void PrintResults();
bool AskToPlayAgain();

int main()
{
	bool bPlayAgain = true;
	while (bPlayAgain)
	{
		PlayGameIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	};
	return 0;
}

void PlayGameIntro()
{
	Game.SetSecretWord(ChosenSecretWordList());

	std::cout << "	*******************************\n";
	std::cout << "	* Welcome to my Guessing Game *\n";
	std::cout << "	*******************************\n\n";
	std::cout << "Can you think of a U.S. State I am thinking of?\n";
	std::cout << "I'll give you a hint, it's a " << Game.GetSecretWordLength();
	std::cout << " letter word\n" << std::endl;
}

void PlayGame()
{
	//Resets game to default values when played again
	Game.ResetGame();
	int MaxTries = Game.GetMaxTries();

	//Allow player to guess while game is not won
	while (!Game.IsGameWon() && Game.GetCurrentTry() <= MaxTries)
	{
		std::string guess = getValidGuess();
		CorrectIncorrectCount CIWordCount = Game.SubmitValidGuess(guess);
		int GoodGuess = CIWordCount.CorrectlyPlacedWords;
		int AlmostGoodGuess = CIWordCount.IncorrectlyPlacedWords;

		std::cout << Game.SecretWordPadding(guess) << std::endl;
		std::cout << "You guessed " << GoodGuess << " words in the right place" << std::endl;
		std::cout << "You got " << AlmostGoodGuess << " words placed in the wrong place";
		std::cout << std::endl << std::endl;
	}
	PrintResults();
	return;
}

std::string ChosenSecretWordList()
{
	//Secret Word must not conatin a repeated word
	std::string WordList[9] =
	{ "arizona","florida","idaho","iowa","maine","texas","uttah","vermont","wyoming" };
	srand(time(NULL));
	std::string RandomWord = "";
	int s = rand() % 9;
	RandomWord = WordList[s];
	return RandomWord;
}

//Loop continually until player has a valid guess
std::string getValidGuess()
{
	std::string Guess;
	Wordtype Status = Wordtype::Invalid_Status;
	do {

		int PlayerCurrentTurn = Game.GetCurrentTry();
		int PlayerTries = Game.GetMaxTries();

		std::cout << "Turn. " << PlayerCurrentTurn << " out of " << PlayerTries << std::endl;
		std::cout << "Enter your guess" << std::endl;
		std::getline(std::cin, Guess);

		Status = Game.ValidateGuess(Guess);
		switch (Status)
		{
		case Wordtype::Wrong_Length:
			std::cout << "\nPlease enter a " << Game.GetSecretWordLength() << " letter word.\n";
			break;
			//Assume guess is valid
		default:
			break;
		}
		std::cout << std::endl;
	}
	//Loops until there are no errors
	while (Status != Wordtype::Valid_Guess);
	return Guess;
}

void PrintResults()
{
	if (Game.IsGameWon())
	{
		std::cout << "Awsome You Win!!\n";
		std::cout << "\nThe state I was thinking of was indeed: " << Game.GetSecretWord() << std::endl;
	}
	else
	{
		std::cout << "Sorry you Lost!\n";
		std::cout << "\nThe state I was thinking of was: " << Game.GetSecretWord() << std::endl;
	}
}

bool AskToPlayAgain()
{
	std::cout << "\nWould you like to try to guess the same word again? (y/yes or n/no)" << std::endl;
	std::string tryAgain = " ";
	getline(std::cin, tryAgain);
	return(tryAgain[0] == 'y') || (tryAgain[0] == 'Y');
}