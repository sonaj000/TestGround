// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TestGroundCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

class UMyCharacterMovementComponent;
class ATestGroundGameMode;
class UMySaveGame;
UCLASS(config=Game)
class ATestGroundCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TestAction;

public:
	ATestGroundCharacter(const FObjectInitializer& ObjectInitializer);

	FCollisionQueryParams GetIgnoreCharacterParams() const;
	
	UFUNCTION(BlueprintPure) //only callable in bp
	FORCEINLINE UMyCharacterMovementComponent* GetTGCCharacterMovement() const { return TGCMovementComponent; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	UMyCharacterMovementComponent* TGCMovementComponent;

	UPROPERTY()
	bool bcanJump;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	virtual void Jump() override;

	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION()
	void Sprint();

	UFUNCTION()
	void StopSprinting();

	UFUNCTION()
	void TestFunction();

	UFUNCTION()
	void SpawnDebugBoxForCell(FString cell);
private:

	UFUNCTION()
	UMySaveGame* GetStateAsSave();

	UFUNCTION()
	void RestoreStateFromSave(UMySaveGame* Save);

	UPROPERTY()
	ATestGroundGameMode* CurrentGameMode;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	UFUNCTION()
	FString GetCellString();
public:

	TMap<FString, TArray<UMySaveGame*>>StatesForCells;

	void RememberCurrentState();

	void FastTick();

	void SlowTick();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
	virtual void Tick(float DeltaSeconds) override;

protected: //FSM stuff

	UFUNCTION()
	void RandomSeed();

	UFUNCTION()
	void RandomMovement();

	UPROPERTY()
	int RandSeed = 0;

	void NewSeed();
	bool bCanSeed = false;

	UPROPERTY()
	bool bCanGo = false;

	UPROPERTY()
	bool bCanRun = false;

};

