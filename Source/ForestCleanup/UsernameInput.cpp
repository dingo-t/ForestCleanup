// Fill out your copyright notice in the Description page of Project Settings.


#include "UsernameInput.h"

/* This program takes the username input that is given by the user and checks if it contains any numeric digits. 
If it doesn't the users input is saved into the Usernames Array. 
If the users name does contain numeric digits the IsNumeric function will return false and the user will be asked to give a username that contains no numeric characters. */



// Sets default values
AUsernameInput::AUsernameInput()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
}

// nothing above this point has been added by me

// Called when the game starts or when spawned 
void AUsernameInput::BeginPlay()
{   	
	Super::BeginPlay();
}

// Called every frame
void AUsernameInput::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  // This block checks if the username has already been set and then validates the Username and adds it to the Map if it passes
  if (is_username_Set == false)
  {
    if (CheckUsername(Username))
	  {
	    SetUsername(Username);
	  }
	}

	// Every tick the DeltaTime is added to the variable once the username is set
	if (is_username_Set)
	{
	  time_elapsed_milliseconds += DeltaTime;
	}

	// once the game has ended the current time will be saved to a key in the Usernames map
	if (game_ended && GotTime == false)
	{
	  usernames_.Add(Username, time_elapsed_milliseconds);
	  GotTime = true;
	}

	if (game_ended)
	{
	  // Gets the values of the Usernames TMap
	  usernames_.GenerateValueArray(ScoreValues);
	
	  // This sorts the values in descending order
      ScoreValues.Sort([](float A, float B) { return A < B; });

	  // Adds the top 5 values to the scorevalues TMap
	  // Starts a counter variable to keep track of how many scores have been added
	  int32 Count = 0;

	  // This line loops through the Scorevalues array until 5 scores have been added 
	  for (float i = 0; i < score_values_.Num() && Count < 5; ++i)
	{		
      // This loops through each key and value pair in the Usernames Tmap using a range-based for loop
      for (auto& Pair : usernames_)
   	  {	
        // This code checks if the value of the current key and value pair matches the score value being checked 
        if (Pair.Value == score_values_[i])
          {
            // If there is a match the corresponding key and value pair are added to the Scoreboard TMap 
            scoreboard_.Add(Pair.Key, Pair.Value);

           // keeps track of how many scores have been added
            ++Count;

            // Exits the loop
            break;
        	}
    	  }
	    }		
   }

	/* this if statement checks if the IsNumeric function has returned true 
	and that the username has not already been added to the array, to prevent having multiple instances of the same name on the array. 
	It also runs the boundary check function to make sure the username isnt longer than 20 characters. If these conditions are met */

}



// These Functions check to make sure that the Username that the user has entered is a suitable length, uses the right characters and isnt already in use

// This function checks if a string has any numeric digits
bool AUsernameInput::IsNumeric(FString InputUsername) 
{	
  //this is a range based loop that iterates through each character in the username 
	
  for (TCHAR Char : Username)
    {	
	  // The FChar::IsDigit function checks if the Char is a digit 
      if (FChar::IsDigit(Char))
      // if a character is found to be a digit the function will return true otherwise it returns false once it has gone through the entire string
	  {
        return true;
      }
    }
      return false;
}



// this function makes sure that the Username is shorter than a certain length that is controlled by a variable
int32 AUsernameInput::IsUsernameValidLength(FString InputUsername) 
{
  username_length = Username.Len();
  // if statement comparing the length of the username with the MaxUserLength that has been set
  if (username_length > kMaxUserLength)
  {
	return 1;
  }
  else if (username_length < kMinUserLength)
  {
	return 2;
  }
  else 
  {
	return 0;
  }
	
}



// this function checks the TMap to make sure that an Inputted Username is not already in use
bool AUsernameInput::IsUsernameTaken(FString InputUsername)
{
  // searchs the Usernames Map for the username that has been selected by the player
  float* Pointer = usernames_.Find(Username);
  // If the Username is not found the function will return nullptr and the function will return true
  // If it is found it will send a valid pointer and the function will return false
  if (Pointer != nullptr)
  {
	return true;
  }
  else
  {
	return false;
  }
}



// This incorporates all of the previous functions into a single function so that checking a username is easier to implement

bool AUsernameInput::CheckUsername(FString InputUsername)
{
  // checking every IsNumeric function to make sure the username fits all the criteria
  if (IsUsernameTaken(Username) || IsUsernameValidLength(Username) != 0 || IsNumeric(Username))
  {
	return false;
  }
  else;
  {
	return true;
  }
}


void AUsernameInput::SetUsername(FString InputUsername)
{
  // Adds the Username to the MTap
  // When you add a key to a TMap without a value the value is set to nothing 
  usernames_.Add(Username);
  // setting this ensures that the username wont be set again until the game restarts 
  is_username_Set = true;
  time_at_user_set = GetTimeElapsedSinceUserSet(time_at_user_set);
  for (auto& Pair : usernames_);
}



// This function gets the time since the level was created

int AUsernameInput::GetTimeElapsedSinceUserSet(int32 UserSetTime)
{
  int32 PlayerTime = GetWorld()->GetTimeSeconds();
  PlayerTime -= UserSetTime;
  return PlayerTime;
}




