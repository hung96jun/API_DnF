#include "Framework/Framework.h"
#include "Animation.h"


Animation::Animation(Actor* Owner)
	:Owner(Owner)
{
	HDC hdc = GetDC(hWnd);
	hMemDC = CreateCompatibleDC(hdc);
	hAlphaMemDC = CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);
}

Animation::~Animation()
{
	Destroy();

	DeleteObject(hAlphaMemDC);
	DeleteObject(hMemDC);
	DeleteObject(hBitMap);

	delete Info;
}

void Animation::Add(const WSTR& FileName, SpriteInfo Sprite)
{
	if (Animations.count(FileName) > 0) return;

	SpriteInfo* info = new SpriteInfo(Sprite);
	Animations[FileName] = info;
}

void Animation::SetFrame(const WSTR& FileName, const int& Key, const Vector2& Start, const Vector2& End, const LoopType::Type& Loop, const float& Speed)
{
	// 저장된 스프라이트 정보가 없을 경우
	if (Animations.count(FileName) == 0) return;
	// 입력된 행동 key값이 있을 경우
	if (KeySet.count(Key) > 0) return;

	if (Speed == 0.0f)
	{

	}

	SpriteInfo* sprite = Animations[FileName];
	KeySet[Key] = FileName;
	sprite->SetCutFrame(Key, Start, End, Loop, Speed);
}

void Animation::AddFrameFunction(const WSTR& FileName, const int& Key, const int& Frame, std::function<void()> Func)
{
	Animations[FileName]->SetFrameFunction(Key, Frame, Func);
}

void Animation::SetEndFunction(const WSTR& FileName, const int& Key, std::function<void()> Func)
{
	Animations[FileName]->SetEndFunction(Key, Func);
}

//void Animation::AddRangeFunction(const std::wstring& FileName, const int& Key, const int& Start, const int& End, std::function<void()> Func)
//{
//	Animations[FileName]->AddRangeFrameFunction(Key, Start, End, Func);
//}

void Animation::SetDelayTime(const WSTR& FileName, const int& Key, const float& DelayTime)
{
	Animations[FileName]->SetDelayTime(Key, DelayTime);
}

void Animation::Remove(const WSTR& FileName)
{
	if (Animations.count(FileName) == 0) return;

	delete Animations[FileName];
	Animations.erase(FileName);
}

void Animation::Destroy()
{
	for (pair<std::wstring, SpriteInfo*> Animation : Animations)
	{
		delete Animation.second;
	}
	Animations.clear();
}

void Animation::Play(const int& Key)
{
	//if (CurAnim != nullptr)
	//{
	//	if(CurAnim->GetCutInfo(SelectKey).EndFunction != nullptr)
	//		CurAnim->GetCutInfo(SelectKey).EndFunction();
	//}

	if (KeySet.count(Key) == 0) return;

	ResetAnimation();

	SelectKey = Key;
	std::wstring file = KeySet[Key];
	CurAnim = Animations[file];

	bPlay = true;
	SelectObject(hMemDC, CurAnim->GetTexture());
	CurFrame = CurAnim->GetCutInfo(SelectKey).Start;
}

void Animation::ReversePlay(const int& Key)
{
}

void Animation::Update()
{
	if (bPlay == false) return;

	CurAnim->SetLocation(Owner->GetLocation());

	// 단일 프레임 처리를 위한 조건문
	if (CurAnim->GetCutInfo(SelectKey).Start == CurAnim->GetCutInfo(SelectKey).End)
	{
		ResetFrame();
		return;
	}

	if (CurTime > CurAnim->GetCutInfo(SelectKey).Speed)
	{
		if (CurFrame == CurAnim->GetCutInfo(SelectKey).End)
		{
			if (CurAnim->GetCutInfo(SelectKey).Loop == LoopType::Delay)
			{
				if (DelayTime == 0.0f)
					DelayTime = CurTime;

				float testTime = CurTime - DelayTime;
				float testTime1 = CurAnim->GetCutInfo(SelectKey).DelayTime;

				if (CurTime - DelayTime < CurAnim->GetCutInfo(SelectKey).DelayTime)
				{
					CurTime += DELTA_TIME;
					return;
				}
			}

			ResetFrame();
		}

		++CurFrame.x;
		++CountFrame;

		if (CurFrame.x == CurAnim->GetMaxIndex().x)
		{
			if (CurFrame == CurAnim->GetMaxIndex() &&
				CurFrame.y == CurAnim->GetCutInfo(SelectKey).End.y)
			{
				ResetFrame();
			}

			else
			{
				++CurFrame.y;
			}

			CurFrame.x = 0;
		}

		if (CurAnim->GetCutInfo(SelectKey).FrameFunction.size() > 0)
		{
			CurAnim->CallFrameFunction(SelectKey, CountFrame);
		}

		//if (CurAnim->GetCutInfo(SelectKey).RangeFunction.size() > 0)
		//{
		//	CurAnim->CallRangeFrameFunction(SelectKey, CountFrame);
		//}

		CurTime = 0.0f;
	}

	CurTime += DELTA_TIME;
}

void Animation::Render(HDC hdc)
{
	if (bPlay == false) return;

	Vector2 location = CurAnim->GetLocation();
	Vector2 size = CurAnim->GetCutsize();

	bool check = GdiTransparentBlt(
		hdc,
		location.x, location.y,
		size.x, size.y,
		hMemDC,
		size.x * (CurFrame.x),
		size.y * (CurFrame.y),
		size.x, size.y,
		CurAnim->GetAlpha()
	);

<<<<<<< HEAD
	//wstring str;
	//if (check == true)
	//{
	//	str = L"Success";
	//	TextOut(hdc, WIN_CENTER_X, 0, str.c_str(), str.length());
	//}
	//else
	//{
	//	str = L"Failed";
	//	TextOut(hdc, WIN_CENTER_Y, 0, str.c_str(), str.length());
	//}
=======
	wstring str;
	if (check == true)
	{
		str = L"Success";
		TextOut(hdc, WIN_CENTER_X, 0, str.c_str(), str.length());
	}
	else
	{
		str = L"Failed";
		TextOut(hdc, WIN_CENTER_Y, 0, str.c_str(), str.length());
	}
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
}

void Animation::Render(HDC hdc, int Alpha)
{
	if (bPlay == false) return;

	Vector2 location = CurAnim->GetLocation();
	Vector2 size = CurAnim->GetCutsize();

	if (hAlphaBitMap == nullptr)
	{
		HDC tempHDC = GetDC(hWnd);

		BITMAP bitmap;
		GetObject(CurAnim->GetTexture(), sizeof(BITMAP), &bitmap);
		Vector2 imageSize = { (float)bitmap.bmWidth, (float)bitmap.bmHeight };
		Vector2 cutSize = { imageSize.x / CurAnim->GetMaxIndex().x, imageSize.y / CurAnim->GetMaxIndex().y};

		hAlphaBitMap = CreateCompatibleBitmap(hdc, cutSize.x, cutSize.y);
		ReleaseDC(hWnd, tempHDC);
	}

	BLENDFUNCTION blend;
	blend.SourceConstantAlpha = Alpha;

	SelectObject(hMemDC, CurAnim->GetTexture());
	SelectObject(hAlphaMemDC, hAlphaBitMap);

	bool check = BitBlt(
		hAlphaMemDC,
		0, 0, size.x, size.y,
		hdc,
		size.x * (CurFrame.x),
		size.y * (CurFrame.y),
		SRCCOPY
	);

	check = GdiTransparentBlt(
		hAlphaMemDC,
		0, 0,
		size.x, size.y,
		hMemDC,
		size.x * (CurFrame.x),
		size.y * (CurFrame.y),
		size.x, size.y,
		CurAnim->GetAlpha()
	);

	check = GdiAlphaBlend(
		hdc,
		0, 0,
		size.x, size.y,
		hAlphaMemDC,
		0, 0,
		size.x, size.y,
		blend
	);

	wstring str;
	if (check == true)
	{
		str = L"Success";
		TextOut(hdc, WIN_CENTER_X, 0, str.c_str(), str.length());
	}
	else
	{
		str = L"Failed";
		TextOut(hdc, WIN_CENTER_Y, 0, str.c_str(), str.length());
	}
}

void Animation::ResetAnimation()
{
	CurIndex = 0;
	CurFrame = {};
	CountFrame = 0;
	CurTime = 0.0f;
}

void Animation::ResetFrame()
{
	switch (CurAnim->GetCutInfo(SelectKey).Loop)
	{
	case LoopType::Loop:
	{
		CurFrame = CurAnim->GetCutInfo(SelectKey).Start;
		CountFrame = 0;
	}
	break;
	case LoopType::Delay:
	{
		if (CurAnim->GetCutInfo(SelectKey).EndFunction != nullptr)
			CurAnim->GetCutInfo(SelectKey).EndFunction();

		ResetAnimation();
	}
	break;
	case LoopType::Stop:
	{
		if (CurAnim->GetCutInfo(SelectKey).EndFunction != nullptr)
			CurAnim->GetCutInfo(SelectKey).EndFunction();

		bPlay = false;
		CountFrame = 0;
	}
	break;
	default:
		break;
	}
}