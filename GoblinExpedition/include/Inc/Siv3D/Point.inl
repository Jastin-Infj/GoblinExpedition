//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cassert>

namespace s3d
{
	inline constexpr Point Point::operator + () const
	{
		return *this;
	}

	inline constexpr Point Point::operator - () const
	{
		return{ -x, -y };
	}

	inline constexpr Point Point::operator + (const Point& p) const
	{
		return{ x + p.x, y + p.y };
	}

	inline constexpr Point Point::operator - (const Point& p) const
	{
		return{ x - p.x, y - p.y };
	}

	inline constexpr Point Point::operator * (int32 s) const
	{
		return{ x*s, y*s };
	}

	inline constexpr Float2 Point::operator * (float s) const
	{
		return{ x*s, y*s };
	}

	inline constexpr Vec2 Point::operator * (double s) const
	{
		return{ x*s, y*s };
	}

	inline constexpr Point Point::operator * (const Point& p) const
	{
		return{ x*p.x, y*p.y };
	}

	inline constexpr Point Point::operator / (int32 s) const
	{
		return{ x / s, y / s };
	}

	inline constexpr Float2 Point::operator / (float s) const
	{
		return{ x / s, y / s };
	}

	inline constexpr Vec2 Point::operator / (double s) const
	{
		return{ x / s, y / s };
	}

	inline Point& Point::operator += (const Point& p)
	{
		x += p.x;
		y += p.y;
		return *this;
	}

	inline Point& Point::operator -= (const Point& p)
	{
		x -= p.x;
		y -= p.y;
		return *this;
	}

	inline Point& Point::operator *= (int32 s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	inline Point& Point::operator /= (int32 s)
	{
		assert(s != 0);
		x /= s;
		y /= s;
		return *this;
	}

	inline constexpr bool Point::operator == (const Point& p) const
	{
		return x == p.x && y == p.y;
	}

	inline constexpr bool Point::operator != (const Point& p) const
	{
		return x != p.x || y != p.y;
	}

	inline double Point::distanceFrom(const Vec2& p) const
	{
		return std::sqrt(distanceFromSq(p));
	}

	inline constexpr double Point::distanceFromSq(const Vec2& p) const
	{
		return (p.x - x)*(p.x - x) + (p.y - y)*(p.y - y);
	}

	inline double Point::length() const
	{
		return std::sqrt(lengthSq());
	}

	inline constexpr double Point::lengthSq() const
	{
		return x * x + y * y;
	}

	inline constexpr Vec2 Point::lerp(const Vec2& other, double f) const
	{
		return{ x + (other.x - x) * f, y + (other.y - y) * f };
	}

	inline constexpr Point operator * (int32 s, const Point& p)
	{
		return p*s;
	}

	inline constexpr Float2 operator * (float s, const Point& p)
	{
		return p*s;
	}

	inline constexpr Vec2 operator * (double s, const Point& p)
	{
		return p*s;
	}
}
