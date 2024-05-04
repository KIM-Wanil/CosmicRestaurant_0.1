
// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/CRCharacterBase.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"



//추가한 헤더_김완일
#include "Item/CRLevelTransferPortal.h"//포탈
#include "Kismet/GameplayStatics.h" // 레벨 이동 


//DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACRTestCharacter

ACRCharacterBase::ACRCharacterBase()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	/*bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;*/

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); 
	// Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));


	// Input
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ArenaBattle/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}


	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT(" / Script / EnhancedInput.InputAction'/Game/CosmicRestaurant/Input/Actions/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/CosmicRestaurant/Input/Actions/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionInteractionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/CosmicRestaurant/Input/Actions/IA_Interaction.IA_Interaction'"));
	if (nullptr != InputActionInteractionRef.Object)
	{
		InteractionAction = InputActionInteractionRef.Object;
	}

	//Inventory = CreateDefaultSubobject<UCRInventoryComponent>(TEXT("Inventory"));

}

void ACRCharacterBase::BeginPlay()
{
	//// Call the base class  
	Super::BeginPlay();

	////Add Input Mapping Context
	//if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	//{
	//	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//	{
	//		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	//	}
	//}
}

void ACRCharacterBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ACRLevelTransferPortal* Portal = Cast<ACRLevelTransferPortal>(OtherActor);
	if (Portal)
	{
		UE_LOG(LogTemp, Log, TEXT("Portal BeginOverlap"));

		bCanLevelTransfer = true;
		TransferLevelName = Portal->GetTransferLevelName();
		UE_LOG(LogTemp, Log, TEXT("name %s"), &TransferLevelName);
	}

}

void ACRCharacterBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	ACRLevelTransferPortal* Portal = Cast<ACRLevelTransferPortal>(OtherActor);
	if (Portal)
	{
		UE_LOG(LogTemp, Log, TEXT("Portal EndOverlap"));

		bCanLevelTransfer = false;
		TransferLevelName = TEXT("");
	}

}

//////////////////////////////////////////////////////////////////////////
// Input

void ACRCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACRCharacterBase::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACRCharacterBase::Look);

		////상호작용 키 바인딩_김완일_20240224
		// Interaction
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &ACRCharacterBase::Interaction);
	}
	/*else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}*/
}

void ACRCharacterBase::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACRCharacterBase::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.0f, FColor::Emerald, true, 5.0f);

}

void ACRCharacterBase::Interaction(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Press F key"));
	UE_LOG(LogTemp, Log, TEXT("name %s"), &TransferLevelName);
	UE_LOG(LogTemp, Log, TEXT("bool %d"), bCanLevelTransfer);

	if (bCanLevelTransfer)
	{
		UE_LOG(LogTemp, Log, TEXT("Transfer Level"));

		UGameplayStatics::OpenLevel(GetWorld(), FName(TransferLevelName));
		return;
	}
}
