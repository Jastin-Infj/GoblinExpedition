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
# include <sstream>
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// <summary>
	/// 凹角のない四角形
	/// </summary>
	struct Quad
	{
#pragma warning(disable:4201)
		union
		{
			struct { Vec2 tl, tr, br, bl; };
			struct { Vec2 p[4]; };
		};
#pragma warning(default:4201)

		Quad() = default;

		explicit Quad(const String& pts)
		{
			std::wistringstream(pts.str()) >> *this;
		}

		Quad(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
			: tl(x0, y0)
			, tr(x1, y1)
			, br(x2, y2)
			, bl(x3, y3) {}

		Quad(const Vec2& _tl, const Vec2& _tr, const Vec2& _br, const Vec2& _bl)
			: tl(_tl)
			, tr(_tr)
			, br(_br)
			, bl(_bl) {}

		Quad& set(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
		{
			tl.set(x0, y0);
			tr.set(x1, y1);
			br.set(x2, y2);
			bl.set(x3, y3);
			return *this;
		}

		Quad& set(const Vec2& _tl, const Vec2& _tr, const Vec2& _br, const Vec2& _bl)
		{
			tl.set(_tl);
			tr.set(_tr);
			br.set(_br);
			bl.set(_bl);
			return *this;
		}

		Quad& set(const Quad& quad) { return *this = quad; }

		Quad movedBy(double x, double y) const { return movedBy({ x, y }); }

		Quad movedBy(const Vec2& v) const
		{
			return{ tl.movedBy(v), tr.movedBy(v), br.movedBy(v), bl.movedBy(v) };
		}

		Quad& moveBy(double x, double y) { return moveBy({ x, y }); }

		Quad& moveBy(const Vec2& v)
		{
			tl.moveBy(v);
			tr.moveBy(v);
			br.moveBy(v);
			bl.moveBy(v);
			return *this;
		}

		Quad rotatedAt(double x, double y, double angle) const
		{
			return rotatedAt({ x, y }, angle);
		}

		Quad rotatedAt(const Vec2& pos, double angle) const
		{
			const Vec2 a0 = p[0] - pos;
			const Vec2 a1 = p[1] - pos;
			const Vec2 a2 = p[2] - pos;
			const Vec2 a3 = p[3] - pos;
			const double s = std::sin(angle);
			const double c = std::cos(angle);
			const Vec2 x0{ a0.x*c - a0.y*s, a0.x*s + a0.y*c };
			const Vec2 x1{ a1.x*c - a1.y*s, a1.x*s + a1.y*c };
			const Vec2 x2{ a2.x*c - a2.y*s, a2.x*s + a2.y*c };
			const Vec2 x3{ a3.x*c - a3.y*s, a3.x*s + a3.y*c };

			return{ x0 + pos, x1 + pos, x2 + pos, x3 + pos };
		}

		Quad operator + (const Vec2& v) const { return{ tl + v, tr + v, br + v, bl + v }; }

		Quad operator - (const Vec2& v) const { return{ tl - v, tr - v, br - v, bl - v }; }

		double area() const;

		double perimeter() const;

		template <class Shape>
		bool intersects(const Shape& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template<typename Shape> bool contains(const Shape& shape) const
		{
			return Geometry2D::Within(shape, *this);
		}

		/// <summary>
		/// 四角形が左クリックされたかを示します。
		/// </summary>
		Property_Get(bool, leftClicked) const;

		/// <summary>
		/// 四角形がマウスの左ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, leftPressed) const;

		/// <summary>
		/// 四角形の上でマウスの左ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, leftReleased) const;

		/// <summary>
		/// 四角形が右クリックされたかを示します。
		/// </summary>
		Property_Get(bool, rightClicked) const;

		/// <summary>
		/// 四角形がマウスの右ボタンで押されているかを示します。
		/// </summary>
		Property_Get(bool, rightPressed) const;

		/// <summary>
		/// 四角形の上でマウスの右ボタンが離されたかを示します。
		/// </summary>
		Property_Get(bool, rightReleased) const;

		/// <summary>
		/// 四角形の上にマウスカーソルがあるかを示します。
		/// </summary>
		Property_Get(bool, mouseOver) const;

		void write(Image& image, const Color& color = Palette::Black) const;

		void overwrite(Image& image, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, const Color& color = Palette::Black) const;

		void writeFrame(Image& image, int thickness, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, const Color& color = Palette::Black) const;

		void overwriteFrame(Image& image, int thickness, const Color& color = Palette::Black) const;

		const Quad& draw(const Color& color = Palette::White) const;

		const Quad& draw(const Color(&colors)[4])const;

		const Quad& drawFrame(double thickness = 1.0, const Color& color = Palette::White) const;

		const Quad& drawFrame(double innerThickness, double outerThickness, const Color& color = Palette::White) const;

		TexturedQuad operator()(const Texture& texture) const;

		TexturedQuad operator()(const TextureRegion& textureRegion) const;

		Polygon asPolygon() const;
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const Quad& quad)
	{
		return	os << CharType('(')
			<< quad.p[0] << CharType(',')
			<< quad.p[1] << CharType(',')
			<< quad.p[2] << CharType(',')
			<< quad.p[3] << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, Quad& quad)
	{
		CharType unused;
		return	is >> unused
			>> quad.p[0] >> unused
			>> quad.p[1] >> unused
			>> quad.p[2] >> unused
			>> quad.p[3] >> unused;
	}
}
