#pragma once

#include "Manager/TimerManager.h"

struct TimerHandle
{
public:
	TimerHandle(WSTR Key, std::function<void()> Func, float Time, bool Loop = false)
		: Key(Key), Function(Func), EndTime(Time), bLoop(Loop) {}

	void SetStartTime(const float& Start) { StartTime = Start; }

	const float GetStartTime() const { return StartTime; }
	const float GetEndTime() const { return EndTime; }
	const WSTR GetKey() const { return Key; }

	void CallFunction()
	{
		if (StartTime == 0.0f)
			StartTime = ELAPSED_TIME;

		CurTime += DELTA_TIME;

		if (Function != nullptr && (CurTime - StartTime) > EndTime)
		{
			Function();
			StartTime = 0.0f;

			if (bLoop == false)
				bLoop = false;
		}
	}

	const bool IsLoop() const { return bLoop; }

private:
	WSTR Key = L"";
	std::function<void()> Function = nullptr;
	float StartTime = 0.0f;
	float EndTime = 0.0f;
	float CurTime = 0.0f;
	bool bLoop = false;
};
