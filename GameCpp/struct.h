#pragma once

struct Vec2
{
	float x;
	float y;

public:
	Vec2()
		: x(0.f), y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x), y((float)_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x), y((float)_pt.y)
	{
		
	}

	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	float Length() { return sqrt(x * x + y * y); }

	// 자기자신을 반환
	Vec2& Normalize()
	{
		float fLen = Length();
		assert(fLen != 0.f); // 조건을 만족하지 않으면 경고
		x /= fLen;
		y /= fLen;
		return *this;
	}
};