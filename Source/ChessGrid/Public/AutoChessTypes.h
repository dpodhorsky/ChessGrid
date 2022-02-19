// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// ----------------------------------------------------------------------------------------------------------------
// This header is for enums and structs used by classes and blueprints accross the game
// Collecting these in a single header helps avoid problems with recursive header includes
// It's also a good place to put things like data table row structs
// ----------------------------------------------------------------------------------------------------------------

#include "Engine/DataTable.h"
#include "AutoChessTypes.generated.h"


/** XpToLevel Data table struct */
USTRUCT(BlueprintType)
struct CHESSGRID_API FAutoChessXpTable : public FTableRowBase
{
	GENERATED_BODY()

	/** Constructor */
	FAutoChessXpTable(){}

	/** The amount of xp needed to level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	int32 XpToNextLevel;

	/** Returns true if slot is valid */
	bool IsValid() const
	{
		return XpToNextLevel > 0;
	}
};

/** Delegate called when the player's currency changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrencyUpdated);
DECLARE_MULTICAST_DELEGATE(FOnCurrencyUpdatedNative);

/** Delegate called when the player's xp amount changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnXpUpdated);
DECLARE_MULTICAST_DELEGATE(FOnXpUpdatedNative);

/** Delegate called when the player's level changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpdated);
DECLARE_MULTICAST_DELEGATE(FOnLevelUpdatedNative);