#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SwitchInteractable.generated.h"

class ADoorActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DMCPP_API USwitchInteractable : public UActorComponent
{
	GENERATED_BODY()

public:	
	USwitchInteractable();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void Interact();

protected:
	// Direct reference to the door this switch controls
	// EditInstanceOnly allows selecting the door in the Level Viewport
	UPROPERTY(EditInstanceOnly, Category = "Linkage")
	TObjectPtr<ADoorActor> LinkedDoor;
};
