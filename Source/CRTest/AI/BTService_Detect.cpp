// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "AIController.h"
#include "Interface/CRCharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");

	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World)
	{
		return;
	}

	ICRCharacterAIInterface* AIPawn = Cast<ICRCharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}

	TArray<FOverlapResult> OverlapResults;

	FCollisionQueryParams CollisionQuerayParams(SCENE_QUERY_STAT(Detect), false, ControllingPawn);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		ControllingPawn->GetActorLocation() - FVector(0.0f,0.0f, ControllingPawn->GetActorScale3D().Z / 2.0f),
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AIPawn->GetAIDetectRange()),
		CollisionQuerayParams
	);

	FVector FootPos = ControllingPawn->GetActorLocation() - FVector(0.0f,0.0f, ControllingPawn->GetActorScale3D().Z/2.0f);
	DrawDebugSphere(World, FootPos, AIPawn->GetAIDetectRange(), 26, FColor::Blue, false , 3, 0, 1);
	DrawDebugLine(World, FootPos, FootPos + ControllingPawn->GetActorForwardVector().RotateAngleAxis(-45.0f, FVector::UpVector) * AIPawn->GetAIDetectRange(), FColor::Red, false, 3, 0, 1);
	DrawDebugLine(World, FootPos, FootPos + ControllingPawn->GetActorForwardVector().RotateAngleAxis(45.0f, FVector::UpVector) * AIPawn->GetAIDetectRange(), FColor::Red, false, 3, 0, 1);

	if (bResult)
	{

		for (auto OverlapResult : OverlapResults)
		{
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{

				FVector Forward = ControllingPawn->GetActorForwardVector();
				Forward.Z = 0.0f;
				Forward.Normalize();
				FVector ToPlayer = Pawn->GetActorLocation() - ControllingPawn->GetActorLocation();
				ToPlayer.Z = 0.0f;
				ToPlayer.Normalize();

				float Dot = FVector::DotProduct(Forward, ToPlayer);
				float AcosAngle = FMath::Acos(Dot);
				float AngleDegree = FMath::RadiansToDegrees(AcosAngle);



				if (abs(AngleDegree) <= 45.0f)
				{
					DrawDebugLine(World, FootPos, FootPos + ToPlayer * AIPawn->GetAIDetectRange(), FColor::Green, false, 3, 0, 1);
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Pawn);
					return;
				}
			}
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);

}
