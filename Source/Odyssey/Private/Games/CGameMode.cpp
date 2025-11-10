#include "Games/CGameMode.h"
#include "Characters/CPlayerController.h"
#include "Characters/Misthios/CMisthios.h"

ACGameMode::ACGameMode()
{
	DefaultPawnClass = ACMisthios::StaticClass();
	PlayerControllerClass = ACPlayerController::StaticClass();
}
