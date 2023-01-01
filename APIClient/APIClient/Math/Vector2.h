#pragma once

struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2() = default;
	Vector2(float x, float y) : x(x), y(y) {};

    Vector2 operator+(const Vector2& value) const
    {
        return Vector2(x + value.x, y + value.y);
    }
    Vector2 operator-(const Vector2& value) const
    {
        return Vector2(x - value.x, y - value.y);
    }
    Vector2 operator*(const float& value) const
    {
        return Vector2(x * value, y * value);
    }
    Vector2 operator/(const float& value) const
    {
        return Vector2(x / value, y / value);
    }

    bool operator==(const Vector2& value) const
    {
        return (x == value.x) && (y == value.y);
    }

    void operator+=(const Vector2& value)
    {
        x += value.x;
        y += value.y;
    }
    void operator-=(const Vector2& value)
    {
        x -= value.x;
        y -= value.y;
    }
    void operator*=(const float& value)
    {
        x *= value;
        y *= value;
    }
    void operator/=(const float& value)
    {
        x /= value;
        y /= value;
    }

    float Length() const
    {
        return sqrt(x * x + y * y);
    }

    void Normalize()
    {
        float length = Length();
        x /= length;
        y /= length;
    }

    Vector2 GetNormalized() const
    {
        float length = Length();
        return Vector2(x / length, y / length);
    }
};