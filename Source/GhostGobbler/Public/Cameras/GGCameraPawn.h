#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GGCameraPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GHOSTGOBBLER_API AGGCameraPawn : public APawn
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComp;





	
public:
	AGGCameraPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Getters and Setters
	USpringArmComponent* GetSpringArmComponent();
	void SetSpringArmComponent(USpringArmComponent* InSpringArmComponent);

	UCameraComponent* GetCameraComponent();
	void SetCameraComponent(UCameraComponent* InCameraComponent);
	
protected:
	virtual void BeginPlay() override;



};
