#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GGPlayerPawn.generated.h"

class USphereComponent;
class UGGPawnMovementComponent;

UCLASS()
class GHOSTGOBBLER_API AGGPlayerPawn : public APawn
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Component")
	TObjectPtr<USphereComponent> RootComp;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Mesh")
	TObjectPtr<UStaticMeshComponent> Mesh_TopMouth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Mesh")
	TObjectPtr<UStaticMeshComponent> Mesh_BottomMouth;

	//Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Movement") 
	TObjectPtr<UGGPawnMovementComponent> PawnMovementComp; //Using my custom UPawnMovementComponent class


	// For moving/stop-moving mouth
	FTimerHandle TimerHandle_MoveMouth;
	UPROPERTY(EditDefaultsOnly, Category = "PlayerPawn|Timers")
	float Delay_StopMovingMouth;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|MouthRotation")
	float MouthRotationRate;    //How fast should the jaws open and close?
	
	bool bMoveMouth;           //Turn on and off during movement / stop-movement in order to make the Pacman look like its opening/closing its jaws
	bool bOpeningJaws;         // Which direction should the jaws be moving in
	
	
public:
	void MoveMouth();
	void StopMovingMouth();
	void StartMovingMouth();

	
	AGGPlayerPawn();
	virtual void Tick(float DeltaTime) override;

	
	//Return the PawnMovementComponent
	//    (will return the custom class...inherits from UPawnMovementComponent)
	virtual UPawnMovementComponent* GetMovementComponent() const override;



	
protected:
	virtual void BeginPlay() override;
};













































