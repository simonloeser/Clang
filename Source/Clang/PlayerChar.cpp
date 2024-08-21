// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerChar::APlayerChar(): IAJumpAction(nullptr), IAMoveAction(nullptr), MoveActionBinding(nullptr)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IAJumpAction)
		{
			EnhancedInputComponent->BindAction(IAJumpAction, ETriggerEvent::Started, this, &APlayerChar::Jump);
			EnhancedInputComponent->BindAction(IAJumpAction, ETriggerEvent::Completed, this, &APlayerChar::StopJumping);
		}

		if (IAMoveAction)
		{
			EnhancedInputComponent->BindAction(IAMoveAction, ETriggerEvent::Triggered, this, &APlayerChar::Move);
			MoveActionBinding = &EnhancedInputComponent->BindActionValue(IAMoveAction);
		}
	}
}

void APlayerChar::Move()
{
	const FVector2D InputValue = MoveActionBinding->GetValue().Get<FVector2D>();
	
}

void APlayerChar::SpawnActor()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector ForwardVectorPosition = GetActorLocation() + GetActorForwardVector() * 250.0f;
	
	//USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnComp"));
	//SceneComp->SetupAttachment(RootComponent);

	FTransform SpawnTransform = GetActorTransform();
	SpawnTransform.SetLocation(ForwardVectorPosition);
	
	if (GetWorld()->SpawnActor<AActor>(ActorBPToSpawn, SpawnTransform, SpawnParams))
	{
		UE_LOG(LogTemp, Log, TEXT("Actor spawned successfully at location: %s"), *ForwardVectorPosition.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn actor."));
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, this->GetActorLocation().ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, this->GetActorForwardVector().ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, SpawnTransform.GetLocation().ToString());
}
