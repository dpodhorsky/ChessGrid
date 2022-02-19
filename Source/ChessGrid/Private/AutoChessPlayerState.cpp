// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoChessPlayerState.h"
#include "AutoChessTypes.h"

AAutoChessPlayerState::AAutoChessPlayerState()
{
	PlayerLevel = 1;
}

void AAutoChessPlayerState::BeginPlay()
{
	Super::BeginPlay();

	XpToNextLevel = GetXpToLevel();
}

void AAutoChessPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

int32 AAutoChessPlayerState::GetCurrencyAmount() const
{
	return CurrencyAmount;
}

void AAutoChessPlayerState::AddCurrency(int32 AddedAmount)
{
	CurrencyAmount = FMath::Clamp(CurrencyAmount + AddedAmount, 0, MAX_int32);
	OnCurrencyUpdated.Broadcast();
	CurrencyUpdated();
}

void AAutoChessPlayerState::SetCurrency(int32 NewAmount)
{
	CurrencyAmount = FMath::Clamp(NewAmount, 0, MAX_int32);
	OnCurrencyUpdated.Broadcast();
	CurrencyUpdated();
}

int32 AAutoChessPlayerState::GetXp() const
{
	return XpAmount;
}

void AAutoChessPlayerState::AddXp(int32 AddedXp)
{
	XpAmount += AddedXp;

	if (XpAmount >= XpToNextLevel)
	{
		int32 RemainingXp = XpToNextLevel - XpAmount;

		XpAmount = RemainingXp;

		PlayerLevel++;

		XpToNextLevel = GetXpToLevel();

		OnLevelUpdated.Broadcast();
		LevelUpdated();
	}

	OnXpUpdated.Broadcast();
	XpUpdated();
}

int32 AAutoChessPlayerState::GetPlayerLevel() const
{
	return PlayerLevel;
}

int32 AAutoChessPlayerState::GetXpToLevel() const
{
	if (!XpDataTable)
	{
		UE_LOG(LogTemp, Fatal, TEXT("Could not find Xp to next level data table. Make sure it is assigned in the AutoChessPlayerState blueprint"));
	}

	FAutoChessXpTable* XpData = XpDataTable->FindRow<FAutoChessXpTable>(FName(FString::FromInt(PlayerLevel)), "");

	if (XpData->IsValid())
	{
		return XpData->XpToNextLevel;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find Xp to next level data for level: %d for player: %s "), PlayerLevel, *GetPlayerName());
		return XpToNextLevel;
	}
}