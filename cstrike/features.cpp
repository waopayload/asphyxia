#include "features.h"

// used: draw callbacks
#include "utilities/draw.h"
// used: notify
#include "utilities/notify.h"

// used: cheat variables
#include "core/variables.h"
// used: menu
#include "core/menu.h"

// used: features callbacks
#include "features/visuals.h"
#include "features/misc.h"

// used: interfaces
#include "core/interfaces.h"
#include "sdk/interfaces/iengineclient.h"
#include "sdk/interfaces/cgameentitysystem.h"
#include "sdk/datatypes/usercmd.h"
#include "sdk/entity.h"

void F::OnPresent()
{
	if (!D::bInitialized)
		return;

	D::NewFrame();
	{
		// render watermark
		MENU::RenderWatermark();

		// main window
		ImGui::PushFont(FONT::pMenu[C_GET(int, Vars.nDpiScale)]);
		// @note: here you can draw your stuff
		MENU::RenderMainWindow();
		// render notifications
		NOTIFY::Render();
		ImGui::PopFont();
	}
	D::Render();
}

void F::OnFrameStageNotify(int nStage)
{
	F::VISUALS::OnFrame(nStage);
}

void F::OnCreateMove(CUserCmd* pCmd, CCSPlayerController* pLocalController)
{
	C_CSPlayerPawn* pLocalPawn = I::GameResourceService->pGameEntitySystem->Get<C_CSPlayerPawn>(pLocalController->GetPawnHandle());
	if (pLocalPawn == nullptr)
		return;

	F::MISC::OnMove(pCmd, pLocalController, pLocalPawn);
}
