#include "Games/CGameMode.h"
#include "Characters/CPlayerController.h"
#include "Characters/Misthios/CCharacter_Misthios.h"

ACGameMode::ACGameMode()
{
	DefaultPawnClass = ACCharacter_Misthios::StaticClass();
	PlayerControllerClass = ACPlayerController::StaticClass();
}
