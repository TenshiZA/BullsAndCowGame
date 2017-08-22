#include "FBullCowGame.h"
#include <map>
#define TMap std::map //to make syntax Unreal friendly

FBullCowGame::FBullCowGame(){ Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const {	return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; };

void  FBullCowGame::Reset()
{
	
	const FString HIDDEN_WORD = "planet"; //this MUST be an isogram
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return;
}; 

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32,int32> WordLengthMaxTries {{3,4}, {4,7}, {5,10}, {6,15}, {7,20}};	
	return WordLengthMaxTries[MyHiddenWord.length()];	
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if ( !IsIsogram(Guess) ){
		return EWordStatus::Not_Isogram; //if the guess ins't an isogram return an error
	}
	else if ( !IsLowercase(Guess) ){
		return EWordStatus::Not_Lowercase; //if the guess isn't all lowercase
	}
	else if ( Guess.length() != GetHiddenWordLength() ){
		return EWordStatus::Wrong_Length;//if the guess length is wrong
	}else{	
		
		//otherwise return ok
		return EWordStatus::OK;
	}
};

//receives a VALID guess, increments turns 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
	
	MyCurrentTry++;
	FBullCowCount aBullCowCount;
	
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	
	for ( int32 i = 0; i < WordLength ; i++ ){
		for ( int32 j = 0; j < WordLength ; j++ ){
			if ( Guess[i] == MyHiddenWord[j] && j==i ) {
				aBullCowCount.Bulls++;
			}else if(Guess[i] == MyHiddenWord[j] && j!=i){
				aBullCowCount.Cows++;
			}
		}		
	}
	
	if ( Guess == MyHiddenWord ) {
		bGameIsWon = true;
	}
	
	return aBullCowCount;
	
};

bool FBullCowGame::IsLowercase(FString Word) const {
	
	for ( auto Letter : Word ){ //auto here compiler checks the type -- we could have made it char
		
		if ( !islower(Letter) ){
			return false;
		}		
	}
	
	return true;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	
	if ( Word.length() <= 1 ) { return true; }
	
	//setup our map
	TMap <char, bool> LetterSeen;
	
	for ( auto Letter : Word ){ //auto here compiler checks the type -- we could have made it char
		Letter = tolower(Letter);
		
		if ( LetterSeen[Letter] )
		{
			return false; //we do not have an isogram
		} else {			
			LetterSeen[Letter] = true;			
		}		
		
	}
	
	
	return true; //for example in cases where /0 is entered
}

