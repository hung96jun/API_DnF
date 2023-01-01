#include "Framework/Framework.h"
#include "TimerManager.h"


TimerManager::TimerManager()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&PeriodFrequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&LastTime);

	TimeScale = 1.0f / (float)PeriodFrequency;
}

TimerManager::~TimerManager()
{
	for (pair<WSTR, TimerHandle*> pair : Functions)
	{
		delete pair.second;
		pair.second = nullptr;
	}
}

void TimerManager::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&CurTime);
	ElapsedTime = (float)(CurTime - LastTime) * TimeScale;

	if (LockFPS != 0)
	{
		while (ElapsedTime < (1.0f / LockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&CurTime);
			ElapsedTime = (float)(CurTime - LastTime) * TimeScale;
		}
	}

	LastTime = CurTime;

	FrameCount++;
	OneSecondCount += ElapsedTime;
	
	if (OneSecondCount >= 1.0f)
	{
		FrameRate = FrameCount;
		FrameCount = 0;
		OneSecondCount = 0.0f;
	}

	// 테스트
	for (std::pair<WSTR, bool> funcPair : CallFunctions)
	{
		if (funcPair.second == false) continue;

		Functions[funcPair.first]->CallFunction();
	}
}

void TimerManager::Render(HDC hdc)
{
	wstring str = L"FPS : " + to_wstring(FrameRate);
	TextOut(hdc, 0, 0, str.c_str(), (int)str.length());
	str = L"Delta : " + to_wstring(ElapsedTime);
	TextOut(hdc, 0, 20, str.c_str(), (int)str.length());
}

void TimerManager::AddFunction(TimerHandle Func)
{
	TimerHandle* function = new TimerHandle(Func);
	Functions[function->GetKey()] = function;
}

void TimerManager::CallFunction(WSTR Func)
{
	// 테스트
	if (Functions.count(Func) <= 0) return;
	CallFunctions[Func] = true;
}
