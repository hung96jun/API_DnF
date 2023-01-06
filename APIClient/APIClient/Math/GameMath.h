#pragma once

namespace GameMath
{
    enum class Direction
    {
        UP, DOWN, LEFT, RIGHT, NONE
    };

    int Random(const int& Min, const int& Max);
    float Random(const float& Min, const float& Max);

    float Clamp(const float& Min, const float& Max, float Value);

    float Lerp(const float& Start, const float& End, float T);
    Vector2 Lerp(const Vector2& Start, const Vector2& End, float T);
    Vector2 SLerp(const Vector2& Start, const Vector2& End, float T);

}