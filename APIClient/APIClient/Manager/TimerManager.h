#pragma once

struct TimerFunc;

class TimerManager : public Singleton<TimerManager>
{
private:
	const float EPSILON = 0.01f;

private:
	friend class Singleton;
	
	TimerManager();
	~TimerManager();

public:
	void Update();
	void Render(HDC hdc);

	void SetDeltaScale(float Value) { DeltaScale = Value; }
	void SetLockFPS(int Value) { LockFPS = Value; }

	float GetElapsedTime()
	{
		return ElapsedTime > EPSILON ? EPSILON : ElapsedTime * DeltaScale;
	}

	void AddFunction(TimerFunc Func);
	void CallFunction(std::wstring Func);

private:
	void LoopFunction();
	
private:
	float TimeScale = 0.0f;
	float ElapsedTime = 0.0f;
	float OneSecondCount = 0.0f;
	float DeltaScale = 1.0f;

	__int64 CurTime = 0;
	__int64 LastTime = 0;
	__int64 PeriodFrequency = 0;

	int FrameRate = 0;
	int FrameCount = 0;
	int LockFPS = 0;

	//std::map<std::wstring, TimerFunc*> TimerFunctions;
	//std::map<std::wstring, TimerFunc*> LoopFunctions;
	std::map<std::wstring, TimerFunc*> Functions;
};
