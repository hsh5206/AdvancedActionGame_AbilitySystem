// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/AG_AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

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

//  ��Ʈ����Ʈ ��Ʈ���� ó�� ���ø�����Ʈ�Ǵ� ������Ƽ���
void UAG_AttributeSetBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// ���ø�����Ʈ �߰�
	DOREPLIFETIME_CONDITION_NOTIFY(UAG_AttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAG_AttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
}