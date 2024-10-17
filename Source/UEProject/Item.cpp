#include "Item.h"

UItem* UItem::CreateItem(const FString& item_name)
{
	UItem* temp = NewObject<UItem>(); //MJ - I dont think this is a good idea
	temp->m_szName = item_name;
	temp->m_ItemGUID = FGuid::NewGuid();

	return temp;
}

void UItem::PrintData()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("%s - %d"), *m_szName, m_iStack));
}

void UItem::SetStack(int new_stack)
{
	m_iStack = new_stack;
}

int UItem::GetStack()
{
	return m_iStack;
}

void UItem::AddStackAmount(int amount)
{
	if (m_iStack >= 64)
		return;

	m_iStack += amount;
}

void UItem::RemoveStackAmount(int amount)
{
	if (m_iStack <= 0)
		return;

	m_iStack -= amount;
}

FString& UItem::GetName()
{
	return m_szName;
}