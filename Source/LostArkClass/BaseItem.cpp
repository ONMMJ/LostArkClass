// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"

void UBaseItem::UseItem_Implementation()
{

}

void UBaseItem::SetIconTexture()
{
	FString TexturePath = "/Game/Textures/Item/" + FileName;
	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(*TexturePath);
	if (IconTexture.Succeeded())
	{
		ItemIcon = IconTexture.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load texture from path: %s"), *TexturePath);
	}
}
