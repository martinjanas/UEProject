#include "ItemRegistry.h"

UItemRegistry* UItemRegistry::GetItemRegistry()
{
	if (!m_pInstance)
	{
		m_pInstance = NewObject<UItemRegistry>();
		m_pInstance->AddToRoot();
	}

	return m_pInstance;
}

void UItemRegistry::RegisterItem(UItem* item)
{
	if (m_Items.FindOrAdd(item->GetName(), item))
		UE_LOG(LogTemp, Warning, L"Item Registered: %s", *item->GetName());
}

TMap<FString, UItem*>& UItemRegistry::GetRegisteredItems()
{
	return m_Items;
}

UItem* UItemRegistry::FindItem(const FString& key)
{
	UItem** item = m_Items.Find(key);

	if (item)
		return *item;

	return nullptr;
}

void UItemRegistry::ResetRegistry()
{
	m_Items.Empty();
}

void UItemRegistry::RegisterAndCreateItems()
{
	Items::wood = UItem::CreateItem("Wood");
	Items::stone = UItem::CreateItem("Stone");

	this->RegisterItem(Items::wood); //Move this into UItem::CreateItem?
	this->RegisterItem(Items::stone);
}
