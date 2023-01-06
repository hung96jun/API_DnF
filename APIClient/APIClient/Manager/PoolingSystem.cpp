#include "Framework/Framework.h"
#include "PoolingSystem.h"

PollingSystem::PollingSystem(const UINT& MaxCount)
	:MAX_SIZE(MaxCount)
{
	TotalObjects.reserve(MaxCount);
}

PollingSystem::~PollingSystem()
{
	for (int i = 0; i < TotalObjects.size(); ++i)
	{
		if (TotalObjects[i] != nullptr)
			delete TotalObjects[i];
	}

	TotalObjects.clear();
}
