#pragma once

#include "Manager/TimerManager.h"

struct TimerFunc
{
public:
	TimerFunc(WSTR Key, std::function<void()> Func, float Time, bool Loop = false, bool Active = true)
		: Key(Key), Function(Func), EndTime(Time), bLoop(Loop), bActive(Active) {}

	void SetStartTime(const float& Start) { StartTime = Start; }

	const float GetStartTime() const { return StartTime; }
	const float GetEndTime() const { return EndTime; }
	const WSTR GetKey() const { return Key; }

	void CallFunction()
	{
		if (StartTime == 0.0f)
			StartTime = ELAPSED_TIME;

		CurTime += DELTA_TIME;
		
		if (bLoop == true)
		{
			if ((CurTime - StartTime) < EndTime)
				Function();

			else
				bActive = false;
		}

		else if (bLoop == false)
		{
			if (Function != nullptr && (CurTime - StartTime) > EndTime)
			{
				Function();
				bActive = false;
			}
		}
	}

	const bool IsLoop() const { return bLoop; }
	const bool IsActive() const { return bActive; }
	void ResetFunction()
	{
		StartTime = 0.0f;
		bActive = true;
	}

private:
	WSTR Key = L"";
	std::function<void()> Function = nullptr;
	float StartTime = 0.0f;
	float EndTime = 0.0f;
	float CurTime = 0.0f;
	bool bLoop = false;
	bool bActive = false;
};
