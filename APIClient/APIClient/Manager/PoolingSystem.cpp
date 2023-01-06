#include "Framework/Framework.h"
#include "PoolingSystem.h"

<<<<<<< HEAD
PollingSystem::PollingSystem(const UINT& MaxCount)
	:MAX_SIZE(MaxCount)
{
	TotalObjects.reserve(MaxCount);
=======

PollingSystem::PollingSystem(const UINT& MaxCount)
{
	TotalObject.reserve(MaxCount);
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
}

PollingSystem::~PollingSystem()
{
<<<<<<< HEAD
	for (int i = 0; i < TotalObjects.size(); ++i)
	{
		if (TotalObjects[i] != nullptr)
			delete TotalObjects[i];
	}

	TotalObjects.clear();
}
=======
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

>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
