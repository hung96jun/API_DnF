#include "Framework/Framework.h"
#include "PoolingSystem.h"


PollingSystem::PollingSystem(const UINT& MaxCount)
{
	TotalObject.reserve(MaxCount);
}

PollingSystem::~PollingSystem()
{
	for (int i = 0; i < TotalObject.size(); ++i)
	{
		delete TotalObject[i];
	}

	TotalObject.clear();
}

void PollingSystem::Update()
{
	for (Actor* object : TotalObject)
	{
		if (object->GetIsActive() == false) continue;

		object->Update();
	}
}

void PollingSystem::Render(HDC hdc)
{
	for (Actor* object : TotalObject)
	{
		if (object->GetIsActive() == false) continue;

		object->Render(hdc);
	}
}

