#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DMCPP_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();
	virtual void BeginPlay() override;

protected:
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmo;

public:
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta); 

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void AddAmmo(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool TryConsumeAmmo(int32 Amount); 

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChanged;
};
