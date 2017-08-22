#pragma once
#include <string>

//to make syntax Unreal friendly
typedef std::string FString;
typedef int int32;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus{	
	
	Invalid_status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase	
};

class FBullCowGame{
	
	public:
		
		FBullCowGame(); //constructor
		
		int32 GetMaxTries() const; //const here makes sure that the function cant change any member variables in the function ( read only function )
		int32 GetCurrentTry() const;		
		int32 GetHiddenWordLength() const;
		
		bool IsGameWon() const;
		bool IsIsogram(FString) const;
		bool IsLowercase(FString) const;
		EWordStatus CheckGuessValidity(FString) const;
		
		void Reset(); //TODO make a more rich return value.		
		FBullCowCount SubmitValidGuess(FString);
		
	private:
		int32 MyCurrentTry;
		FString MyHiddenWord;
		bool bGameIsWon;
	
};
