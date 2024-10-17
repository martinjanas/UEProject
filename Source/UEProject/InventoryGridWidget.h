#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/GridPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Engine/Texture.h"
#include "Materials/MaterialInterface.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Slate/SlateBrushAsset.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotWidget.h"
#include "ItemRegistry.h"
#include "InventoryGridWidget.generated.h"

UCLASS()
class UEPROJECT_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UInventoryGridWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
    {
        ConstructorHelpers::FObjectFinder<USlateBrushAsset> brush(L"SlateBrushAsset'/Game/Assets/M_SlateBrush.M_SlateBrush'");
        if (brush.Succeeded() && brush.Object)
        {
            BoxBrush = brush.Object->Brush;
            BoxBrush.ImageSize = FVector2D(25.f, 25.f);
        }

        ConstructorHelpers::FClassFinder<UUserWidget> widget_finder(L"/Game/Blueprints/UI_Blueprints/WBP_ItemSlot.WBP_ItemSlot_C");

        if (widget_finder.Succeeded())
            widget_class = widget_finder.Class;
    }

    virtual void NativeTick(const FGeometry& geo, float deltatime) override
    {
        Super::NativeTick(geo, deltatime);

        static auto item_reg = UItemRegistry::GetItemRegistry();

        time += deltatime;

        if (time >= 2.5f)
        {
            const auto& wood = item_reg->FindItem("Wood");
            if (wood)
            {
                wood->RemoveStackAmount(1);
            }
            time = 0.f;
        }
    }

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* image;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UGridPanel* gridpanel;

    UPROPERTY()
	FSlateBrush BoxBrush;

    UPROPERTY()
    UClass* widget_class;

    float time;

    void DrawBoard(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const
    {
        FVector2D slot_size(75.f, 75.f);
        FMargin padding{ 10.f, 35.f, 10.f, 10.f };

        const auto& grid_geo = gridpanel->GetPaintSpaceGeometry();
        FVector2D grid_size = grid_geo.GetLocalSize();
        FVector2D grid_abs_pos = grid_geo.GetAbsolutePosition();
        FVector2D grid_local_pos = AllottedGeometry.AbsoluteToLocal(grid_abs_pos);

        float availableWidth = grid_size.X - (padding.Left + padding.Right);
        float availableHeight = grid_size.Y - (padding.Top + padding.Bottom);

        int32 slots_x = FMath::FloorToInt(availableWidth / slot_size.X);
        int32 slots_y = FMath::FloorToInt(availableHeight / slot_size.Y);

        static auto item_reg = UItemRegistry::GetItemRegistry();

        const auto& inventory_items = item_reg->GetRegisteredItems();
       
        UItemSlotWidget* widget = nullptr;

        for (int32 row = 0; row < slots_y; ++row)
        {
            for (int32 col = 0; col < slots_x; ++col)
            {
                auto slot_pos = FVector2D(grid_local_pos.X + padding.Left + col * slot_size.X, grid_local_pos.Y + padding.Top + row * slot_size.Y);
                auto geo = AllottedGeometry.ToPaintGeometry(slot_pos, slot_size);
                
                for (const auto& x : inventory_items)
                {
                    static int i = 0;

                    if (i < inventory_items.Num())
                    {
                        widget = CreateWidget<UItemSlotWidget>(GetWorld(), widget_class);
                        if (!widget)
                            continue;
                        
                        i++;
                    }

                    if (!widget)
                        continue;

                    widget->SetupSlotEx(x.Value->GetName(), x.Value->GetStack());

                    widget->SetPositionInViewport(slot_pos);
                    widget->SetDesiredSizeInViewport(slot_size);
                    widget->AddToViewport(1);
                }

                FSlateDrawElement::MakeBox(OutDrawElements, LayerId, geo, &BoxBrush, ESlateDrawEffect::None, FLinearColor::White);
            }
        }
    }

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override
	{
		int32 layer = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

        DrawBoard(AllottedGeometry, OutDrawElements, layer);

		return layer + 1;
	}
};
