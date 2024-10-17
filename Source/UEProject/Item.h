#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

UCLASS(BlueprintType)
class UEPROJECT_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem()
	{
		m_iStack = 0;
		m_szName = "Empty";
	}

	UFUNCTION(BlueprintCallable, Category = "UItem")
	static UItem* CreateItem(const FString& item_name);

	UFUNCTION(BlueprintCallable, Category = "UItem")
	void PrintData();

	UFUNCTION(BlueprintCallable, Category = "UItem")
	void SetStack(int new_stack);

	UFUNCTION(BlueprintCallable, Category = "UItem")
	int GetStack();

	UFUNCTION(BlueprintCallable, Category = "UItem")
	void AddStackAmount(int amount);

	UFUNCTION(BlueprintCallable, Category = "UItem")
	void RemoveStackAmount(int amount);

	UFUNCTION(BlueprintCallable, Category = "UItem")
	FString& GetName();

	int m_iStack;
	FString m_szName;
	FGuid m_ItemGUID;
};
