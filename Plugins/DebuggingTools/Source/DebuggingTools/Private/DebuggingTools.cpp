#include "DebuggingTools.h"
#include "GameplayDebugger.h"
#include "DebuggerCategory.h"

// 현지화(Localization)를 위한 네임스페이스 정의
#define LOCTEXT_NAMESPACE "FDebuggingToolsModule"

// 클래스가 'DebuggingTools'라는 이름의 모듈임을 엔진에 알리는 매크로
IMPLEMENT_MODULE(FDebuggingToolsModule, DebuggingTools)

// 플러그인이 메모리에 로드되고 초기화될 때 엔진에 의해 호출
void FDebuggingToolsModule::StartupModule()
{
	// 카테고리 생성 델리게이트(Delegate) 준비
	// 엔진이 "이 카테고리가 필요하다"고 요청할 때, 누구를 호출해서 객체를 만들지 설정
	IGameplayDebugger::FOnGetCategory Category;

	// DebuggerCategory 클래스의 정적 함수 MakeInstance를 연결
	// 엔진은 필요할 때 MakeInstance()를 호출하여 새 디버거 객체 로드
	Category.BindStatic(DebuggerCategory::MakeInstance);

	// 게임플레이 디버거에 카테고리 등록
	// - "PlayerPawn": 카테고리 이름 (화면 상단 표시)
	// - category: 객체 생성 델리게이트
	// - EnabledInGameAndSimulate: 게임 플레이 중 및 시뮬레이션 모드에서도 사용 가능
	// - 5: 단축키 NumPad 5번 키로 설정 (토글 방식)
	IGameplayDebugger::Get().RegisterCategory("PlayerPawn", Category, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
	
	// 카테고리가 변경되었음을 디버거 시스템에 알려 즉시 반영
	IGameplayDebugger::Get().NotifyCategoriesChanged();
}

// 플러그인이 언로드되거나 에디터가 종료될 때 호출
void FDebuggingToolsModule::ShutdownModule()
{
	// 게임플레이 디버거 시스템이 여전히 유효한지 확인
	if (IGameplayDebugger::IsAvailable())
	{
		// 등록했던 "PlayerPawn" 카테고리를 제거
		// 이미 사라진 객체를 참조하려는 시도를 막기 위한 절차
		IGameplayDebugger::Get().UnregisterCategory("PlayerPawn");
	}
}

#undef LOCTEXT_NAMESPACE
