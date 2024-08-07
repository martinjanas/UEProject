// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretAIComponent.h"

// Sets default values for this component's properties
UTurretAIComponent::UTurretAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTurretAIComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTurretAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* turret = this->GetOwner();

	if (!turret)
		return;

	UStaticMeshComponent* head_mesh_comp = Cast<UStaticMeshComponent>(turret->GetDefaultSubobjectByName(TEXT("HeadMesh")));

	if (!head_mesh_comp)
		return;

	APlayerController* player = GetWorld()->GetFirstPlayerController();

	if (!player)
		return;

	APawn* player_pawn = player->GetPawn();

	if (!player_pawn)
		return;

	if (IsTargetVisible(player_pawn))
	{
		time += GetWorld()->GetDeltaSeconds();

		UHealthComponent* health_comp = Cast<UHealthComponent>(player_pawn->GetDefaultSubobjectByName(TEXT("HealthComponent")));

		if (health_comp && time >= 2.5f)
		{
			health_comp->ApplyDamage(25, 33);
			health_comp->TryDestroyTarget(player_pawn);

			//UE_LOG(LogTemp, Warning, TEXT("HP: %d"), health_comp->health);

			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("HP: %d"), health_comp->health));

			time = 0;
		}
	}

	FRotator cur_rotation = head_mesh_comp->GetRelativeRotation();

	FVector turret_location = turret->GetActorLocation();
	FVector player_location = player_pawn->GetActorLocation();

	FVector delta = player_location - turret_location;
	delta.Z = 0;
	delta.Normalize();

	FRotator new_rotation = FRotationMatrix::MakeFromX(delta).Rotator();

	new_rotation.Yaw -= 90;

	head_mesh_comp->SetRelativeRotation(new_rotation);
}

