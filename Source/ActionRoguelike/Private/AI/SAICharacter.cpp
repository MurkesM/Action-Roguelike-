// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

ASAICharacter::ASAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	AAIController* AIController = Cast<AAIController>(GetController());

	if (AIController)
	{
		UBlackboardComponent* BlackBoardComp = AIController->GetBlackboardComponent();

		BlackBoardComp->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER_SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}