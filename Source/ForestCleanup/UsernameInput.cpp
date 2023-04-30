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

	
}

// nothing above this point has been added by me

// Called when the game starts or when spawned 
void AUsernameInput::BeginPlay()
{	
	Super::BeginPlay();

	UsernameSet = false;
	
	Validation(Username);
}



// Called every frame
void AUsernameInput::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// this if statement checks if the Validation function has returned true and that the username has not already been added to the array, to prevent having multiple instance of the same name on the array.
	if (Validation(Username) && UsernameSet == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Your message"));
		UsernameSet = true;
		Usernames.Add(Username);
	}

	UserLength = Username.Len();
	UE_LOG(LogTemp, Error, TEXT("Your message: %d"), UserLength);
}


// This function checks if a string has any numeric digits
bool AUsernameInput::Validation(FString InputUsername) 
{	
	 for (TCHAR Char : Username)
    {	
        if (FChar::IsDigit(Char))
        {
            return false;
        }
    }
    return true;
}
