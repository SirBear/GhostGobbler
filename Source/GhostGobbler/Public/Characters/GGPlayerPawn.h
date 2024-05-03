#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GGPlayerPawn.generated.h"

class UGGPawnMovementComponent;

UCLASS()
class GHOSTGOBBLER_API AGGPlayerPawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Mesh")
	TObjectPtr<UStaticMeshComponent> BaseStaticMesh01;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Mesh")
	TObjectPtr<UStaticMeshComponent> BaseStaticMesh02;

	//Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Movement") 
	TObjectPtr<UGGPawnMovementComponent> PawnMovementComp; //Using my custom UPawnMovementComponent class
	
public:
	AGGPlayerPawn();
	virtual void Tick(float DeltaTime) override;

	
	//Return the PawnMovementComponent
	//    (will return the custom class...inherits from UPawnMovementComponent)
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	
protected:
	virtual void BeginPlay() override;
};













































