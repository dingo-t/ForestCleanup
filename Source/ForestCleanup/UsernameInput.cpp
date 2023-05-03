// Fill out your copyright notice in the Description page of Project Settings.


#include "UsernameInput.h"

/* This program takes the username input that is given by the user and checks if it contains any numeric digits. 
If it doesn't the users input is saved into the Usernames Array. 
If the users name does contain numeric digits the Validation function will return false and the user will be asked to give a username that contains no numeric characters. */



// Sets default values
AUsernameInput::AUsernameInput()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// adding keys and values for testing
	
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

	if (UserSet == false)
	{
		if (VerifyUsername(Username))
		{
			SetUsername(Username);
		}
	}
	// UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), ( GameEnded ? TEXT("true") : TEXT("false") ));

	ReturnedTime = GetTime(TimeAtUserSet);
	if (GameEnded && GotTime == false)
	{
		Usernames.Add(Username, ReturnedTime);
		
		if (Usernames.Contains(Username))
		{
			MapInt = *Usernames.Find(Username);
		}
		UE_LOG(LogTemp, Warning, TEXT("The time for %s is %d"), *Username, MapInt);
		GotTime = true;
	}

	if (GameEnded)
	{
		// gets the values of the Usernames TMap
		Usernames.GenerateValueArray(ScoreValues);
	
		// this sorts the values in descending order
		ScoreValues.Sort([](int32 A, int32 B) { return A < B; });

		// adds the top 5 values to the scorevalues TMap
		int32 Count = 0;
		for (int32 i = 0; i < ScoreValues.Num() && Count < 5; ++i)
		{
    		for (auto& Pair : Usernames)
    		{	
        		if (Pair.Value == ScoreValues[i])
        		{
            		Scoreboard.Add(Pair.Key, Pair.Value);
            		++Count;
           	   	 break;
       			}
    		}
		}

		// Print the contents of the scoreboard map
		for (auto& Pair : Scoreboard)
		{
   		UE_LOG(LogTemp, Warning, TEXT("%s: %d"), *Pair.Key, Pair.Value);
		}
		UE_LOG(LogTemp, Warning, TEXT("Usernames"),);
	
	}

	/* this if statement checks if the Validation function has returned true 
	and that the username has not already been added to the array, to prevent having multiple instances of the same name on the array. 
	It also runs the boundary check function to make sure the username isnt longer than 20 characters. If these conditions are met */

}


// These Functions check to make sure that the Username that the user has entered is a suitable length, uses the right characters and isnt already in use

// This function checks if a string has any numeric digits
bool AUsernameInput::Validation(FString InputUsername) 
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
bool AUsernameInput::IsUsernameValidLength(FString InputUsername) 
{
	UserLength = Username.Len();
	// if statement comparing the length of the username with the MaxUserLength that has been set
	if (UserLength < MaxUserLength)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// this function checks the TMap to make sure that an Inputted Username is not already in use
bool AUsernameInput::IsUsernameTaken(FString InputUsername)
{
	// searchs the Usernames Map for the username that has been selected by the player
	int32* Pointer = Usernames.Find(Username);
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

bool AUsernameInput::VerifyUsername(FString InputUsername)
{
	// checking every validation function to make sure the username fits all the criteria
	if (IsUsernameTaken(Username) || IsUsernameValidLength(Username) || Validation(Username))
	{
		return false;
	}
	else;
	{
		return true;
	}
}

// this simple function adds the Username to the Usernames TMap if it passes all the checks

void AUsernameInput::SetUsername(FString InputUsername)
{
	// Adds the Username to the MTap
	// When you add a key to a TMap without a value the value is set to nothing 
	Usernames.Add(InputUsername);
	// setting this ensures that the username wont be set again until the game restarts 
	UserSet = true;
	// UE_LOG(LogTemp, Error, TEXT("Username valid"));
	TimeAtUserSet = GetTime(TimeAtUserSet);
	UE_LOG(LogTemp, Error, TEXT("%s"), *InputUsername);
	for (auto& Pair : Usernames)
	{
    UE_LOG(LogTemp, Warning, TEXT("%s: %d"), *Pair.Key, Pair.Value);
	}
}

// This function gets the time since the level was created

int AUsernameInput::GetTime(int32 UserSetTime)
{
	int32 PlayerTime = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), PlayerTime);
	PlayerTime -= UserSetTime;
	return PlayerTime;
}



TMap<FString, int32> GetTop5Users(TMap<FString, int32> Usernames)
{
    TMap<FString, int32> Top5Users;

    // Sort the values in descending order
    Usernames.ValueSort(TGreater<int32>());

    // Extract the top 5 values and add them to the new map
    int32 i = 0;
    for (const auto& Pair : Usernames)
    {
        if (i >= 5) break;

        Top5Users.Add(Pair.Key, Pair.Value);
        ++i;
    }

    return Top5Users;
}



