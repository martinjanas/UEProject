// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int health;

	UFUNCTION(BlueprintCallable)
	void SetHealth()
	{
		health = 100;
	}

	void ApplyDamage(int min_damage, int max_damage)
	{
		health -= rand() % (max_damage - min_damage + 1) + min_damage;
		health = std::clamp<int>(health, 0, 100);
	}

	void TryDestroyTarget(AActor* target)
	{
		if (health <= 0 && target)
			target->Destroy();
	}
};
