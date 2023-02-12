// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/AG_AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

// GameplayEffect가 실행되기 직전에 호출
void UAG_AttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// 프로퍼티 게터를 사용하여 이 호출이 Health에 영향을 미치는지 확인
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Health의 값을 0~MaxHealth로
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

/** 멀티플레이에서 리플리케이트 설정 */
void UAG_AttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	// 디폴트 게임플레이 어트리뷰트 시스템의 repnotify 행동을 사용
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAG_AttributeSetBase, Health, OldHealth);
}

void UAG_AttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	// 디폴트 게임플레이 어트리뷰트 시스템의 repnotify 행동을 사용
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAG_AttributeSetBase, Health, OldMaxHealth);
}

//  어트리뷰트 세트에서 처음 리플리케이트되는 프로퍼티라면
void UAG_AttributeSetBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 리플리케이트 추가
	DOREPLIFETIME_CONDITION_NOTIFY(UAG_AttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAG_AttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
}