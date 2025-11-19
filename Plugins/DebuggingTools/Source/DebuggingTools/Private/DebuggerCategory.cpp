#include "DebuggerCategory.h"
#include "GameFramework/PlayerController.h"
#include "Characters/CCharacter.h"
#include "CanvasItem.h"
#include "DrawDebugHelpers.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/CStatusComponent.h"

// 엔진이 디버그 카테고리를 활성화할 때 최초 1회 호출하는 팩토리 함수
TSharedRef<FGameplayDebuggerCategory> DebuggerCategory::MakeInstance()
{
	// 실제 DebuggerCategory 객체를 생성(new) 
	// 메모리 관리를 위해 공유 레퍼런스(TSharedRef)로 감싸서 반환
	return MakeShareable(new DebuggerCategory());
}

// 디버깅할 데이터를 실제 게임 객체로부터 읽어와서 구조체(PlayerPawnData)에 저장하는 함수
void DebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	// 정보를 가져올 대상 캐릭터(OwnerPC가 빙의 중인 캐릭터) 로드
	if (ACCharacter* character = OwnerPC->GetPawn<ACCharacter>())
	{
		// 데이터를 성공적으로 가져왔으므로 그리기를 활성화
		{ // PlayerPawnData
			PlayerPawnData.bDraw = true;

			PlayerPawnData.ActorName = character->GetName();
			PlayerPawnData.ActorLocation = character->GetActorLocation();
			PlayerPawnData.Speed = character->GetVelocity().Size2D();

			// UCStateComponent를 로드하여 현재 상태를 문자열로 변환
			if (const UEnum* enumPtr = StaticEnum<EStateType>())
			{
				if (UCStateComponent* stateComponent = character->GetComponentByClass<UCStateComponent>())
				{
					FString stateType = enumPtr->GetNameStringByValue((int32)stateComponent->GetStateType());

					PlayerPawnData.StateType = stateType;
				}
			}

			// UCWeaponComponent를 가져와서 현재 무기를 문자열로 변환
			if (const UEnum* enumPtr = StaticEnum<EWeaponType>())
			{
				if (UCWeaponComponent* weaponComponent = character->GetComponentByClass<UCWeaponComponent>())
				{
					FString weaponType = enumPtr->GetNameStringByValue((int32)weaponComponent->GetWeaponType());

					PlayerPawnData.WeaponType = weaponType;
				}
			}

			if (UCStatusComponent* status = character->GetComponentByClass<UCStatusComponent>())
			{
				PlayerPawnData.CurHealth = status->GetCurHealth();
				PlayerPawnData.CurStamina = status->GetCurStamina();
			}
		}
	}
}

// CollectData에서 수집된 PlayerPawnData를 바탕으로 화면에 텍스트와 도형을 표시
void DebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	// 검은색 반투명(Alpha 0.5) 배경 박스 그리기
	FCanvasTileItem item(FVector2D(10, 10), FVector2D(300, 200), FLinearColor(0, 0, 0, 0.5f));
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);

	CanvasContext.Printf(FColor::White, TEXT("ActorName : %s"), *PlayerPawnData.ActorName);
	CanvasContext.Printf(FColor::White, TEXT("Location : %s"), *PlayerPawnData.ActorLocation.ToString());
	CanvasContext.Printf(FColor::White, TEXT("Speed : %f"), PlayerPawnData.Speed);
	CanvasContext.Printf(FColor::White, TEXT("StateType : %s"), *PlayerPawnData.StateType);
	CanvasContext.Printf(FColor::White, TEXT("WeaponType : %s"), *PlayerPawnData.WeaponType);
	CanvasContext.Printf(FColor::White, TEXT("CurHealth : %f"), PlayerPawnData.CurHealth);
	CanvasContext.Printf(FColor::White, TEXT("CurStamina : %f"), PlayerPawnData.CurStamina);
}

DebuggerCategory::DebuggerCategory()
{
	// 디버깅 대상 액터(DebugActor)가 선택되었을 때만 이 카테고리를 표시할지 여부
	// false로 설정하면 대상이 없어도(예: 로컬 플레이어) 정보를 표시할 수 있도록 시도
	bShowOnlyWithDebugActor = false;
}
