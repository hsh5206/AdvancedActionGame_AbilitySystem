// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/AG_GameInstance.h"
#include "AbilitySystemGlobals.h"

void UAG_GameInstance::Init()
{
	Super::Init();

	// ������Ʈ�� ����� �� �ѹ�, global data tables�� tags�� ���� ������Ƽ �¾�
	UAbilitySystemGlobals::Get().InitGlobalData();
}
