

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
//using FText = std::string;  doesnt work in linux so using the typedef. just note the typedef is not compatible with templates
typedef std::string Ftext;
typedef int int32;


void PrintIntro();
void PlayGame();
void PrintGameSummary();
Ftext GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; //intantiate class

int main()
{ 
	
	do {	
		PrintIntro();  	
		PlayGame();		
	} while (AskToPlayAgain());
	
	return 0; //exit the application
}

void PrintIntro()
{	
  
  //introduce the game
  std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << std::endl;
  std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
  std::cout << std::endl;
  return;
}


void PrintGameSummary(){
	
	if ( BCGame.IsGameWon() )
	{
		std::cout << "Well done!" << std::endl;
	}
	else{
		std::cout << "Better luck next time." << std::endl;
	}
	
	
	return;
}

void PlayGame(){
	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	//loop while game is not won and there are still turns remaining
	while ( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries )
	{
		Ftext myGuess = GetValidGuess(); //TODO check valid guess		
		
		//submit guess
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(myGuess);
		
		//print number of bulls and cows
		std::cout << "Bull = " << BullCowCount.Bulls << " ";
		std::cout << "Cows = " << BullCowCount.Cows << " ";
		
		std::cout << "You guessed " + myGuess << std::endl << std::endl; 
	}
	
	PrintGameSummary();
	
	return;
}

Ftext GetValidGuess()
{  
	
	EWordStatus Status = EWordStatus::Invalid_status;
	Ftext Guess = "";
	
	do {
		//get a guess from the player		
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() <<  " .Enter your guess: ";
		getline(std::cin,Guess);		
		
		Status = BCGame.CheckGuessValidity(Guess);
			
			switch (Status) {
				case EWordStatus::Not_Isogram : { 
					std::cout << "Please enter an isogram word only" << std::endl << std::endl;
					break;
				}
				case EWordStatus::Wrong_Length : { 
					std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word only" << std::endl << std::endl;
					break;
				}
				case EWordStatus::Not_Lowercase : { 
					std::cout << "Please enter all your words as lowercase only" << std::endl << std::endl;
					break;
				}
				default : break;
			}
			
			
			
		} while ( Status != EWordStatus::OK );
		
		return Guess; 
	
}

bool AskToPlayAgain(){
	std::cout << "Do you want to play again? (y/n) ";
	Ftext yes_no = "";
	getline(std::cin,yes_no);
	
	if ( yes_no[0] == 'y' || yes_no[0] == 'Y' ) {
		return true;
	}else{
		return false;
	}
}


/*to compile 
g++ first.cpp -o first
* 
g++ main.cpp FBullCowGame.cpp -std=c++11 -o test
* */
