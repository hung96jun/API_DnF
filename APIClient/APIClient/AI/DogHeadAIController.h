#pragma once

class DogHeadAIController : public AIController
{
private:
	const int MAX_THROW_PATTERN = 2;
	const int MAX_ATTACK_PATTERN = 3;

public:
	DogHeadAIController() = default;
	DogHeadAIController(Character* Owner, int* State);
	~DogHeadAIController();

	virtual void Update() override;

	virtual void Excute() override;
	virtual void CompliteAction() override;

	virtual void SelectAction() override;

private:
	bool IsPattern = false;
	int CurThrowMax = 0;
	int CurAttackMax = 0;
};