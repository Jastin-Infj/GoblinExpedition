//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

namespace s3d
{
	inline constexpr bool LineInt::operator == (const LineInt& line) const
	{
		return begin == line.begin && end == line.end;
	}

	inline constexpr bool LineInt::operator != (const LineInt& line) const
	{
		return begin != line.begin || end != line.end;
	}

	inline LineInt& LineInt::set(int32 x0, int32 y0, int32 x1, int32 y1)
	{
		begin.set(x0, y0);
		end.set(x1, y1);
		return *this;
	}

	inline LineInt& LineInt::set(const Point& p0, int32 x1, int32 y1)
	{
		begin.set(p0);
		end.set(x1, y1);
		return *this;
	}

	inline LineInt& LineInt::set(int32 x0, int32 y0, const Point& p1)
	{
		begin.set(x0, y0);
		end.set(p1);
		return *this;
	}

	inline LineInt& LineInt::set(const Point& p0, const Point& p1)
	{
		begin.set(p0);
		end.set(p1);
		return *this;
	}

	inline LineInt& LineInt::set(const LineInt& line)
	{
		return *this = line;
	}

	inline constexpr LineInt LineInt::movedBy(int x, int y) const
	{
		return{ begin.movedBy(x, y), end.movedBy(x, y) };
	}

	inline constexpr LineInt LineInt::movedBy(const Point& v) const
	{
		return{ begin.movedBy(v), end.movedBy(v) };
	}

	inline LineInt& LineInt::moveBy(int x, int y)
	{
		begin.moveBy(x, y);
		end.moveBy(x, y);
		return *this;
	}

	inline LineInt& LineInt::moveBy(const Point& v)
	{
		begin.moveBy(v);
		end.moveBy(v);
		return *this;
	}

	inline constexpr LineInt LineInt::operator + (const Point& v) const
	{
		return{ begin + v, end + v };
	}

	inline constexpr LineInt LineInt::operator - (const Point& v) const
	{
		return{ begin - v, end - v };
	}

	inline constexpr Point LineInt::vector() const
	{
		return end - begin;
	}

	inline constexpr LineInt LineInt::reversed() const
	{
		return{ end, begin };
	}

	inline double LineInt::length() const
	{
		return begin.distanceFrom(end);
	}

	inline constexpr double LineInt::lengthSq() const
	{
		return begin.distanceFromSq(end);
	}

	inline Line& Line::set(double x0, double y0, double x1, double y1)
	{
		begin.set(x0, y0);
		end.set(x1, y1);
		return *this;
	}

	inline Line& Line::set(const Vec2& p0, double x1, double y1)
	{
		begin.set(p0);
		end.set(x1, y1);
		return *this;
	}

	inline Line& Line::set(double x0, double y0, const Vec2& p1)
	{
		begin.set(x0, y0);
		end.set(p1);
		return *this;
	}

	inline Line& Line::set(const Vec2& p0, const Vec2& p1)
	{
		begin.set(p0);
		end.set(p1);
		return *this;
	}

	inline Line& Line::set(const Line& line)
	{
		return *this = line;
	}

	inline constexpr Line Line::movedBy(double x, double y) const
	{
		return{ begin.movedBy(x, y), end.movedBy(x, y) };
	}

	inline constexpr Line Line::movedBy(const Vec2& v) const
	{
		return{ begin.movedBy(v), end.movedBy(v) };
	}

	inline Line& Line::moveBy(double x, double y)
	{
		begin.moveBy(x, y);
		end.moveBy(x, y);
		return *this;
	}

	inline Line& Line::moveBy(const Vec2& v)
	{
		begin.moveBy(v);
		end.moveBy(v);
		return *this;
	}

	inline constexpr Line Line::operator + (const Vec2& v) const
	{
		return{ begin + v, end + v };
	}

	inline constexpr Line Line::operator - (const Vec2& v) const
	{
		return{ begin - v, end - v };
	}

	inline constexpr Vec2 Line::vector() const
	{
		return{ end.x - begin.x, end.y - begin.y };
	}

	inline constexpr Line Line::reversed() const
	{
		return{ end, begin };
	}

	inline double Line::length() const
	{
		return begin.distanceFrom(end);
	}

	inline constexpr double Line::lengthSq() const
	{
		return begin.distanceFromSq(end);
	}
}
