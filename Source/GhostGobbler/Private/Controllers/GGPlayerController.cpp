#include "Controllers/GGPlayerController.h"
#include "GhostGobbler/Public/Characters/GGPlayerPawn.h"  //Include file for the PlayerPawn class



// Enhanced Input System
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Components/InputComponent.h" //Needed for FloatingPawnMovementComponent?



void AGGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ---- REMOVE THIS CODE
	//Grab the Spawned Pawn
	//TObjectPtr<APawn> PawnActor = GetPawn();
	//if (PawnActor)
	//{
	//	PlayerPawn = Cast<AGGPlayerPawn>(PawnActor);
	//}
}


void AGGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	//Enhanced Input System: Adding Input Mapping Context
	const TObjectPtr<ULocalPlayer> LP = this -> GetLocalPlayer(); //Fetching from this, where 'this' is this PlayerController

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = LP -> GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);  //Assert to check that we have a valid pointer

	Subsystem -> ClearAllMappings(); //If respawning and have old mappings still set, clear all to remove old inputs

	Subsystem -> AddMappingContext(DefaultInputMappingContext, 0 );

	// New Enhanced Input System
	TObjectPtr<UEnhancedInputComponent> InputComp = Cast<UEnhancedInputComponent>(InputComponent);

	InputComp -> BindAction(Input_Move, ETriggerEvent::Triggered, this, &AGGPlayerController::Move);

	
}


void AGGPlayerController::Move(const FInputActionInstance& Instance)
{
	if (!PlayerPawn) return; //Early return if we dont have a valid PlayerPawn to move
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	// Get value from input (combined value from WASD keys or single Gamepad stick)
	// and convert to Vector (x,y)
	const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();

	// Move forward/back
	//PlayerPawn -> AddMovementInput(ControlRot.Vector(), AxisValue.Y);

	PlayerPawn -> AddMovementInput(PlayerPawn->GetActorForwardVector(), AxisValue.Y);
	
	// Move Right/Left strafe
	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	PlayerPawn -> AddMovementInput(RightVector, AxisValue.X);
	UE_LOG(LogTemp, Warning, TEXT("AGGPlayerController::Move"));
}



//Handling Possession
void AGGPlayerController::PossessPlayerPawn(AGGPlayerPawn* InPlayerPawn)
{
	if (InPlayerPawn)
	{
		PlayerPawn = InPlayerPawn;
		Possess(InPlayerPawn);
	}
}
void AGGPlayerController::UnPossessPlayerPawn(AGGPlayerPawn* InPlayerPawn)
{
	if (InPlayerPawn)
	{
		UnPossess();
		PlayerPawn = nullptr;
	}
}



void AGGPlayerController::StartControllingPlayerPawn(AGGPlayerPawn* InPlayerPawn)
{
	
}
void AGGPlayerController::StopControllingPlayerPawn(AGGPlayerPawn* InPlayerPawn)
{
	
}



void AGGPlayerController::SetPlayerPawn(AGGPlayerPawn* InPlayerPawn)
{
	if (InPlayerPawn)
	{
		PlayerPawn = InPlayerPawn; //If valid, set our Member variable
	}

}
AGGPlayerPawn* AGGPlayerController::GetPlayerPawn()
{
	if (PlayerPawn) return PlayerPawn;
	else return nullptr;
}
