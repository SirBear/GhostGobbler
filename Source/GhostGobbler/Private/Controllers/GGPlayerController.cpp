#include "Controllers/GGPlayerController.h"
#include "GhostGobbler/Public/Characters/GGPlayerPawn.h"	// Include file for the PlayerPawn class (custom class)
#include "Cameras/GGCameraPawn.h"							// Include file for the CameraPawn class (custom class)


// Enhanced Input System
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"						
#include "Components/InputComponent.h"						// Needed for FloatingPawnMovementComponent?
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Debug
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"


void AGGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	LineTraceDistance = 6000.f; //Set initially to 60000

	APawn* PawnActor = GetPawn();   //Get the owner of this controller (Fetching the Camera Pawn)
	if (PawnActor)
	{
		CameraPawn = Cast<AGGCameraPawn>(PawnActor);
	}


	
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

void AGGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	ProcessMouseLocation();
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
	// const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	//PlayerPawn -> AddMovementInput(ControlRot.Vector(), AxisValue.Y);  // Code if using Control Rotation. Replaced with Fwd / RightVector calls since its a simple top-down
	
	
	//Only want the Player to move in one direction (either left or right) --- like the Original PacMan game as the player moves through the maze
	if (AxisValue.X != 0)
 	{
		//PlayerPawn -> AddMovementInput(PlayerPawn->GetActorRightVector(), AxisValue.X); 	// Move Right/Left strafe
		PlayerPawn -> AddMovementInput(FVector(0.0f, 1.0f, 0.0f),AxisValue.X );
	}
	else if (AxisValue.Y != 0) // If right/left input is non-zero and fwd/back input is zero
	{
		//PlayerPawn -> AddMovementInput(PlayerPawn->GetActorForwardVector(), AxisValue.Y);   // Move FWD/BACK
		PlayerPawn -> AddMovementInput(FVector(1.0f, 0.0f, 0.0f),AxisValue.Y );
	}


	PlayerPawn -> StartMovingMouth();
	
	UE_LOG(LogTemp,Warning, TEXT("AGGPlayerController::Move >>> Current AxisValue.X = %f, CurrentAxisValue.Y= %f"), AxisValue.X, AxisValue.Y);
	
	

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





void AGGPlayerController::ProcessMouseLocation()
{
	if (!PlayerPawn || !CameraPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AGGPlayerController::ProcessMouseLocation() >>> Cant find a PlayerPawn or a Camera Pawn"))
		if (!CameraPawn)
		{
			UE_LOG(LogTemp, Warning, TEXT("AGGPlayerController::ProcessMouseLocation() >>> Cant find a Camera Pawn"))
		}
		if (!PlayerPawn)
		{
			UE_LOG(LogTemp, Warning, TEXT("AGGPlayerController::ProcessMouseLocation() >>> Cant find a PlayerPawn"))
		}
		return; //If we dont control a valid Player or we dont control a valid Camera Pawn, early return (need both)
	}


	FVector Start;
	FVector End;
	FVector MouseWorldLocation = FVector(0.0f);		// Initialize to 0,0,0
	FVector MouseWorldDirection = FVector(0.0f);		// Initialize to 0,0,0

	FVector CameraLocation =  CameraPawn-> GetCameraComponent() -> GetComponentLocation();
	FRotator CameraRotation =  CameraPawn-> GetSpringArmComponent() -> GetComponentRotation();
	Start = CameraLocation;

	//Running this function will populate two OutParams with data
	DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
	End = CameraLocation + (MouseWorldDirection * LineTraceDistance);

	// Trace to a Single Point
	FHitResult OutHitResult = FHitResult(ForceInit);	// OutHitResult will be populated with data once the line trace completes
	FCollisionQueryParams TraceParams(FName(TEXT("LineTraceParams")), true, PlayerPawn); //Final Param (PlayerPawn) means we will ignore during the trace
	TraceParams.bTraceComplex = false;					// No Complex colliders, only trace against simple collision
	TraceParams.bReturnPhysicalMaterial = false;		// Dont return the physical material

	bool bIsHit = GetWorld()-> LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility, TraceParams);

	/* Debug Visualization */
	FColor LineTraceColor = bIsHit ? FColor::Green: FColor::Red; //Change color of trace depending on if we hit something
	//DrawDebugLine(GetWorld(), Start, End, LineTraceColor, true, 50.0f);
	DrawDebugSphere(GetWorld(), OutHitResult.ImpactPoint, 10.f, 12, FColor::Red, true, 50.f);
	
	if (bIsHit && OutHitResult.GetActor() != PlayerPawn)
	{
		FVector TargetLocation = OutHitResult.Location;
		FVector MovementVector  = UKismetMathLibrary::GetDirectionUnitVector(PlayerPawn-> GetActorLocation(), TargetLocation);
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(MovementVector);
		MovementRotation.Roll = 0.0f;
		MovementRotation.Pitch = 0.0f;
		PlayerPawn ->SetActorRotation(MovementRotation, ETeleportType::None);
	}

	
}



/* ----------- Getters and Setters ---------------------------- */



void AGGPlayerController::SetPlayerPawn(AGGPlayerPawn* InPlayerPawn)
{
	if (InPlayerPawn) PlayerPawn = InPlayerPawn; //If valid, set our Member variable
}

AGGPlayerPawn* AGGPlayerController::GetPlayerPawn()
{
	if (PlayerPawn) return PlayerPawn;
	return nullptr;
}

void AGGPlayerController::SetCameraPawn(AGGCameraPawn* InCameraPawn)
{
	if (InCameraPawn) CameraPawn = InCameraPawn;
}
AGGCameraPawn* AGGPlayerController::GetCameraPawn()
{
	if (CameraPawn) return CameraPawn;
	return nullptr;
}


