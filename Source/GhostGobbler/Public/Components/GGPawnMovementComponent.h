#pragma once

//#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GGPawnMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GHOSTGOBBLER_API UGGPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float PawnBaseMoveSpeed;




	
public:
	UGGPawnMovementComponent();

	// virtual override function from class UMovementComponent
	virtual void TickComponent(
		float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;
	
};
