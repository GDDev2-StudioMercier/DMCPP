#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ADMCPPProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DMCPP_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Fire();

protected:
	/** The Projectile Class to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TSubclassOf<ADMCPPProjectile> ProjectileClass;

	/** Offset from the camera to spawn the projectile */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	FVector MuzzleOffset;

	/** Sound to play when firing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	USoundBase* FireSound;

	/** Animation to play when firing */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* FireAnimation;
};
