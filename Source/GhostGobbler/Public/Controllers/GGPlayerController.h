#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"						// Included for struct FInputActionInstance (Enhanced Input)
#include "GGPlayerController.generated.h"

class UInputMappingContext;
class AGGPlayerPawn;
class AGGCameraPawn;

UCLASS()
class GHOSTGOBBLER_API AGGPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerController|Player")
	TObjectPtr<AGGPlayerPawn> PlayerPawn;  //Hold reference to PlayerPawn to move it around

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerController|Camera")
	TObjectPtr<AGGCameraPawn> CameraPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerController|Trace")
	float LineTraceDistance;

	

	//Enhanced Input Subsystem: Input Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|MappingContext")
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|InputAction")
	TObjectPtr<UInputAction> Input_Move;








	
protected:
	UFUNCTION()
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	//Enhanced Input System
	void Move(const FInputActionInstance& Instance);


	// Fetching Mouse Location on screen -- using this for determining rotation of the player
	void ProcessMouseLocation();



	
public:

	virtual void PlayerTick(float DeltaTime) override;
	
	//Handling Possession
	void PossessPlayerPawn(AGGPlayerPawn* InPlayerPawn);
	void UnPossessPlayerPawn(AGGPlayerPawn* InPlayerPawn);

	void StartControllingPlayerPawn(AGGPlayerPawn* InPlayerPawn);
	void StopControllingPlayerPawn(AGGPlayerPawn* InPlayerPawn);


	//Getters and Setters
	void SetPlayerPawn(AGGPlayerPawn* InPlayerPawn);
	AGGPlayerPawn* GetPlayerPawn();

	void SetCameraPawn(AGGCameraPawn* InCameraPawn);
	AGGCameraPawn* GetCameraPawn();

	
};
