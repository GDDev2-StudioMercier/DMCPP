#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPickup.generated.h"

UCLASS()
class DMCPP_API AHealthPickup : public APickup
{
	GENERATED_BODY()
	
public:
	AHealthPickup();

protected:
	virtual bool ApplyEffect(AActor* TargetActor) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Config", meta = (AllowPrivateAccess = "true"))
	float HealthAmount;
};
