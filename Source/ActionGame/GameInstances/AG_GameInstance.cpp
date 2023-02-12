// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/AG_GameInstance.h"
#include "AbilitySystemGlobals.h"

void UAG_GameInstance::Init()
{
	Super::Init();

	// 프로젝트가 실행될 때 한번, global data tables와 tags를 위한 프로젝티 셋업
	UAbilitySystemGlobals::Get().InitGlobalData();
}
