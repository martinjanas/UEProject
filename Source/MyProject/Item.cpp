// Fill out your copyright notice in the Description page of Project Settings.
#include "Item.h"

UItem::UItem()
{
}

UItem::UItem(const FString& name)
{
	this->m_szName = name;
}

UItem* UItem::CreateItem(FString name)
{
	UItem* temp = NewObject<UItem>();

	if (!temp)
		return nullptr;

	temp->m_szName = name;

	return temp;
}

void UItem::print_name()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, FString::Printf(TEXT("%d"), this->m_iStack));
}

void UItem::IncreaseStack(int stack)
{
	this->m_iStack += stack;
}
