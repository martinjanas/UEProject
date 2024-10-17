#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "ItemRegistry.generated.h"

namespace Items //Switch to UDataAsset
{
	inline static UItem* wood;
	inline static UItem* stone;
}

UCLASS()
class UEPROJECT_API UItemRegistry : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "UItemRegistry")
	TMap<FString, UItem*> m_Items; //Not clearing once exiting play mode

	UFUNCTION(BlueprintCallable, Category = "UItemRegistry")
	static UItemRegistry* GetItemRegistry();

	UFUNCTION(BlueprintCallable, Category = "UItemRegistry")
	void RegisterItem(UItem* item);

	UFUNCTION(BlueprintCallable, Category = "UItemRegistry")
	TMap<FString, UItem*>& GetRegisteredItems();

	UFUNCTION(BlueprintCallable, Category = "UItemRegistry")
	UItem* FindItem(const FString& key);

	UFUNCTION(BlueprintCallable, Category = "UItemRegistry")
	void ResetRegistry();

	UFUNCTION(BlueprintCallable, Category = "UItemRegistry")
	void RegisterAndCreateItems();

private:
	inline static UItemRegistry* m_pInstance;
};
