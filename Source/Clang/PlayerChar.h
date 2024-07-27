// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Character.h"
#include "PlayerChar.generated.h"

UCLASS()
class CLANG_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

    UFUNCTION(BlueprintCallable, Category = "Spawning")
        void SpawnActor();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> ActorBPToSpawn;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
