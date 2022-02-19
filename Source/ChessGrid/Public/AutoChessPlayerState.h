// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Engine/DataTable.h"
#include "AutoChessTypes.h"
#include "AutoChessPlayerState.generated.h"

UCLASS()
class CHESSGRID_API AAutoChessPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	// Constructor and overrides
	AAutoChessPlayerState();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Returns current currency amount */
	UFUNCTION(BlueprintCallable)
		virtual int32 GetCurrencyAmount() const;

	/** Adds currency to player, can be negative to remove */
	UFUNCTION(BlueprintCallable)
		virtual void AddCurrency(int32 AddedAmount);

	/** Sets current currency amount */
	UFUNCTION(BlueprintCallable)
		virtual void SetCurrency(int32 NewAmount);

	/** Returns current XP */
	UFUNCTION(BlueprintCallable)
		virtual int32 GetXp() const;

	/** Adds XP to player */
	UFUNCTION(BlueprintCallable)
		virtual void AddXp(int32 AddedXp);

	void NewFunction();

	/** Returns current Level */
	UFUNCTION(BlueprintCallable)
		virtual int32 GetPlayerLevel() const;

	/** Delegate called when the currency amount has changed */
	UPROPERTY(BlueprintAssignable, Category = Currency)
		FOnCurrencyUpdated OnCurrencyUpdated;

	/** Delegate called when player xp has changed */
	UPROPERTY(BlueprintAssignable, Category = Level)
		FOnXpUpdated OnXpUpdated;

	/** Delegate called when player level has changed */
	UPROPERTY(BlueprintAssignable, Category = Level)
		FOnLevelUpdated OnLevelUpdated;

	/** Called after currency has updated and we notified all delegates */
	UFUNCTION(BlueprintImplementableEvent, Category = Currency)
		void CurrencyUpdated();

	/** Called after player xp has changed and we notified all delegates */
	UFUNCTION(BlueprintImplementableEvent, Category = Level)
		void XpUpdated();

	/** Called after level has changed and we notified all delegates */
	UFUNCTION(BlueprintImplementableEvent, Category = Level)
		void LevelUpdated();

protected:
	/** Returns required xp to level for level */
	UFUNCTION(BlueprintCallable)
		int32 GetXpToLevel() const;

	/** The currency amount of this player */
	UPROPERTY(EditAnywhere, Replicated, Category = Currency)
		int32 CurrencyAmount;

	/** The xp amount of this player */
	UPROPERTY(EditAnywhere, Replicated, Category = Level)
		int32 XpAmount;

	/** The xp amount required to level */
	UPROPERTY(EditAnywhere, Replicated, Category = Level)
		int32 XpToNextLevel;

	/** The level of this player */
	UPROPERTY(EditAnywhere, Replicated, Category = Level)
		int32 PlayerLevel;

	/** The data table containing XpToNextLevel info */
	UPROPERTY(EditAnywhere, Category = Level)
		UDataTable* XpDataTable;
};
