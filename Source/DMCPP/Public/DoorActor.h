#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

class UTimelineComponent;

UCLASS()
class DMCPP_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorActor();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ToggleDoor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> PivotComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	float TargetRotationYaw = 90.0f;

	bool bIsOpen = false;

	UFUNCTION(BlueprintImplementableEvent, Category = "Effects")
	void OnDoorStateChanged(bool bNewIsOpen);
};
