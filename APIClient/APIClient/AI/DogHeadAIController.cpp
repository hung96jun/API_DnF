#include "Framework/Framework.h"
#include "DogHeadAIController.h"


DogHeadAIController::DogHeadAIController(Character* Owner, int* State)
	:AIController(Owner, State)
{
}

DogHeadAIController::~DogHeadAIController()
{
}

void DogHeadAIController::Update()
{
	Super::Update();

}

void DogHeadAIController::Excute()
{
	Super::Excute();

}

void DogHeadAIController::CompliteAction()
{
	Super::CompliteAction();

}

void DogHeadAIController::SelectAction()
{
	if (IsPattern == true) return;
	if (MaxPatterns.size() == 0) return;

	for (std::vector<int> tempVector : MaxPatterns)
	{
		int maxCount = GameMath::Random(0, tempVector.size());
		//for (int i = 0; i < maxCount; ++i)
		for(int i =0; i < tempVector.size(); ++i)
		{
			int index = 0;
			while (true)
			{
				index = GameMath::Random(0, tempVector.size());
				if (tempVector[index] == -1)
					continue;
				else
					break;
			}

			CurPattern.push(tempVector[index]);
			tempVector[index] = -1;
		}
	}
}
