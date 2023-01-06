#include "Framework/Framework.h"
#include "AIController.h"


AIController::AIController(Character* Owner, int* State)
	:Owner(Owner), OwnerState(State)
{
}

AIController::~AIController()
{
}

void AIController::Update()
{
	if (CurPattern.size() == 0)
		SelectAction();
	if (IsExcute == false)
		Excute();
}

void AIController::Excute()
{
	if (CurPattern.size() == 0) return;
	if (OwnerState == nullptr) return;

	IsExcute = true;
	(*OwnerState) = CurPattern.front();
	CurPattern.pop();
}

void AIController::CompliteAction()
{
	IsExcute = false;
}



