// Fill out your copyright notice in the Description page of Project Settings.


#include "UsernameInput.h"

// Sets default values
AUsernameInput::AUsernameInput()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AUsernameInput::BeginPlay()
{
	Super::BeginPlay();



	Validation(Username);


}

// Called every frame
void AUsernameInput::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AUsernameInput::Validation(FString InputUsername) 
{
	 for (TCHAR Char : Username)
    {
        if (FChar::IsDigit(Char))
        {
            return true;
        }
    }
    return false;
}
