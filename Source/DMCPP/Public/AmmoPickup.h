#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "AmmoPickup.generated.h"

UCLASS()
class DMCPP_API AAmmoPickup : public APickup
{
	GENERATED_BODY()
	
public:
	AAmmoPickup();

protected:
	virtual bool ApplyEffect(AActor* TargetActor) override;

private:
	UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowPrivateAccess = "true"))
	int32 AmmoAmount;
};
