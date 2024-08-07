// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.h"
#include "TurretAIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UTurretAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurretAIComponent();

	float time;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsTargetVisible(AActor* target)
	{
		AActor* owner = this->GetOwner();

		if (!target || !owner)
			return false;

		FHitResult hit_result;

		const auto& forward = owner->GetActorForwardVector();
		const auto& start = owner->GetActorLocation();

		auto direction = target->GetActorLocation() - start;
		direction.Normalize();

		auto end = (direction * 1000.f) + start;

		FCollisionQueryParams params;
		params.AddIgnoredActor(owner);

		const auto& world = GetWorld();

		if (world->LineTraceSingleByChannel(hit_result, start, end, ECC_WorldStatic, params))
		{
			DrawDebugLine(world, start, end, FColor::Red);

			if (hit_result.GetActor() == target)
				return true;
		}

		return false;
	}
		
};
