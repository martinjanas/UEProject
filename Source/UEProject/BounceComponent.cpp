// Copyright Martin Janas (martinjanas) 2024
#include "BounceComponent.h"

UBounceComponent::UBounceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	m_flElapsedTime = 0.f;
}


// Called when the game starts
void UBounceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBounceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBounceComponent::BounceActor(float delta_time, float bounce_strength, float speed)
{
	const auto& owner = GetOwner();
	if (!owner)
		return;

	m_flElapsedTime += delta_time;

	const FVector& pos = owner->GetActorLocation();

	float sin = FMath::Sin(m_flElapsedTime * speed);

	float z_offset = bounce_strength * sin;

	float new_z = (pos.Z + z_offset);

	owner->SetActorLocation({ pos.X, pos.Y, new_z });
}

