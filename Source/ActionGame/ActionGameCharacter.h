// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemInterface.h"
#include "ActionGameCharacter.generated.h"

class UAG_AbilitySystemComponentBase;
class UAG_AttributeSetBase;
class UGameplayEffect;
class UGameplayAbility;

UCLASS(config=Game)
class AActionGameCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AActionGameCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/**
*
* Ability System
*
*/
public:
	// 스스로에게 GameplayEffect 적용
	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle InEffectContext);
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	void InitializeAttributes();
	void GiveAbilities();
	void ApplyStartupEffects();

	// 각각 클라이언트와 서버에서 위 함수를 이용해 초기화 해주기 위함
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> DefaultAttributeSet;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;
	UPROPERTY(EditDefaultsOnly)
	UAG_AbilitySystemComponentBase* AbilitySystemComponent;
	UPROPERTY(Transient)
	UAG_AttributeSetBase* AttributeSet;
};

