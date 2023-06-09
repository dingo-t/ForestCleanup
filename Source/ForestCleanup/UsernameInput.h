// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UsernameInput.generated.h"

/* This is the header file where all of the variables, collections and functions are declared 
so that they can be implemented in the cpp file. 
I have not used any local variables or collections so these are all of the variables and collections that are being used in the program */


UCLASS()
class FORESTCLEANUP_API AUsernameInput : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUsernameInput();

protected:
	// Called when the game starts or when spawned 
	virtual void BeginPlay() override;


	// Everything under public is the functions and collections that i have added
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* I have set all of the collections functions and variables under the Public class 
	so that i can use the functions and collections in other files if i need to+. */

	/* Setting the variable as a UPROPERTY allows Enreal Engine to access the variable so that it can be used in blueprints and in the engine.
	the EditAnywhere and BlueprintReadWrite tags tell Unreal that the variable can be read and edited by blueprints */
	
	// Variables
	
	// The default value is set to "5" so that the function returns false by default 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Username = "5";

	// I need to prevent the same username from being set multiple times so this boolean variable will dictate if a new Username can be added to the Array or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool is_username_Set = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool game_ended = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool got_time = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 username_length;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    const int32 kMaxUserLength = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	const int32 kMinUserLength = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 time_at_user_set;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float time_elapsed_milliseconds;
	
	// Collections

	// A TMap is an Unreal engine dynamically sized Dictionary
	// Here you can see that the Dictionary has been set to use a string as the key and an integer as the value
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, float> usernames_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, float> scoreboard_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> score_values_;

	// Functions

	// UFUNCTION also allows Unreal to use the function in blueprints
	// The function is set to return a boolean value and takes the parameter of the String InputUsername 
	UFUNCTION(BlueprintCallable)
	bool  IsNumeric(FString InputUsername); 

	// This function checks if a Username is not outside the max boundary of 20 characters 
	UFUNCTION(BlueprintCallable)
	int32 IsUsernameValidLength(FString InputUsername); 

	UFUNCTION(BlueprintCallable)
	bool IsUsernameTaken(FString InputUsername);

	UFUNCTION(BlueprintCallable)
	bool CheckUsername(FString InputUsername);

	UFUNCTION(BlueprintCallable)
	void SetUsername(FString InputUsername);

	UFUNCTION(BlueprintCallable)
	int32 GetTimeElapsedSinceUserSet(int32 UserSetTime);

	
};