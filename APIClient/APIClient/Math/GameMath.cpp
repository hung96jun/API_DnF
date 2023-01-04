#include "Framework/Framework.h"
#include "GameMath.h"

int GameMath::Random(const int& Min, const int& Max)
{
    return rand() % (Max - Min) + Min;
}

float GameMath::Random(const float& Min, const float& Max)
{
    float normal = rand() / (float)RAND_MAX;

    return (Max - Min) * normal + Min;
}

float GameMath::Clamp(const float& Min, const float& Max, float Value)
{
    if (Value < Min)
        Value = Min;

    if (Value > Max)
        Value = Max;

    return Value;
}

float GameMath::Lerp(const float& Start, const float& End, float T)
{
    T = Clamp(0.0f, 1.0f, T);

    return Start + (End - Start) * T;
}

Vector2 GameMath::Lerp(const Vector2& Start, const Vector2& End, float T)
{
    T = Clamp(0.0f, 1.0f, T);

    return Start + (End - Start) * T;
}

Vector2 GameMath::SLerp(const Vector2& Start, const Vector2& End, float T)
{
    T = Clamp(0.0f, 1.0f, T);

    return Start + (End - Start) * (T * T);
}
