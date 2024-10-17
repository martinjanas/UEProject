#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "ItemRegistry.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(BlueprintReadWrite, Category = "UInventoryComponent")
	TArray<UItem*> m_Inventory;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="UInventoryComponent")
	void PrintData()
	{
		for (auto& x : m_Inventory)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, FString::Printf(L"%s - %d", *x->m_szName, x->m_iStack));
		}
	}

	UFUNCTION(BlueprintCallable, Category="UInventoryComponent", meta = (DisplayName = "AddItemToInventory"))
	void AddItem(UItem* item)
	{
		m_Inventory.Add(item);
	}

	UFUNCTION(BlueprintCallable, Category = "UInventoryComponent")
	UItem* FindItemInInventory()
	{
		unimplemented();

		return nullptr;
	}
};
