// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/AG_AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "AG_AttributeSetBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// GameplayEffect�� ����Ǳ� ������ ȣ��
void UAG_AttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// ������Ƽ ���͸� ����Ͽ� �� ȣ���� Health�� ������ ��ġ���� Ȯ��
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Health�� ���� 0~MaxHealth��
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxMovementSpeedAttribute())
	{
		ACharacter* OwningCharacter = Cast<ACharacter>(GetOwningActor());
		UCharacterMovementComponent* CharacterMovement = OwningCharacter ? OwningCharacter->GetCharacterMovement() : nullptr;
		if (CharacterMovement)
		{
			const float MaxSpeed = GetMaxMovementSpeed();
			CharacterMovement->MaxWalkSpeed = MaxSpeed;
		}
	}
}

/** ��Ƽ�÷��̿��� ���ø�����Ʈ ���� */
void UAG_AttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	// ����Ʈ �����÷��� ��Ʈ����Ʈ �ý����� repnotify �ൿ�� ���
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAG_AttributeSetBase, Health, OldHealth);
}

void UAG_AttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	// ����Ʈ �����÷��� ��Ʈ����Ʈ �ý����� repnotify �ൿ�� ���
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAG_AttributeSetBase, Health, OldMaxHealth);
}

void UAG_AttributeSetBase::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAG_AttributeSetBase, Health, OldStamina);
}

void UAG_AttributeSetBase::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAG_AttributeSetBase, Health, OldMaxStamina);
}

void UAG_AttributeSetBase::OnRep_MaxMovementSpeed(const FGameplayAttributeData& OldMaxMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAG_AttributeSetBase, Health, OldMaxMovementSpeed);
}

//  ��Ʈ����Ʈ ��Ʈ���� ó�� ���ø�����Ʈ�Ǵ� ������Ƽ���
void UAG_AttributeSetBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// ���ø�����Ʈ �߰�
	DOREPLIFETIME_CONDITION_NOTIFY(UAG_AttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAG_AttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAG_AttributeSetBase, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAG_AttributeSetBase, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAG_AttributeSetBase, MaxMovementSpeed, COND_None, REPNOTIFY_Always);
}