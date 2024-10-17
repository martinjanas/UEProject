#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemSlotWidget.generated.h"

UCLASS()
class UEPROJECT_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override
	{
		Super::NativeConstruct();
	}

public:

	UFUNCTION(BlueprintCallable, Category = "UItemSlotWidget")
	void SetupSlot(UTexture2D* item_icon, const FString& item_name, int item_stack)
	{
		if (m_pIconImage)
			m_pIconImage->SetBrushFromTexture(item_icon);

		if (m_pItemName)
			m_pItemName->SetText(FText::FromString(item_name));

		if (m_pItemStackText)
			m_pItemStackText->SetText(FText::AsNumber(item_stack));
	}

	UFUNCTION(BlueprintCallable, Category = "UItemSlotWidget")
	void SetupSlotEx(const FString& item_name, int item_stack)
	{
		if (m_pItemName)
			m_pItemName->SetText(FText::FromString(item_name));

		if (m_pItemStackText)
			m_pItemStackText->SetText(FText::AsNumber(item_stack));
	}

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* m_pIconImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_pItemName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* m_pItemStackText;
};
