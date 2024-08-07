// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

//DroppableItem actor - used when dropping instance of Item-(UI) class onto the ground.

UCLASS(Blueprintable)
class MYPROJECT_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();
	UItem(const FString& name);
	
	UFUNCTION(BlueprintCallable, Category = "UItem")
	static UItem* CreateItem(FString name);

	UFUNCTION(BlueprintCallable, Category = "UItem")
	void print_name();

	UFUNCTION(BlueprintCallable, Category = "UItem")
	void IncreaseStack(int stack);

private:
	FString m_szName;
	int m_iStack;
	int m_iMaxStack;
	/*UTexture2D* m_pIconTexture;
	UStaticMesh* m_pItem3DMesh;*/
};
