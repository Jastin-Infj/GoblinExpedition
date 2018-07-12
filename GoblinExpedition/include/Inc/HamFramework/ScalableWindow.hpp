//-----------------------------------------------
//
//	This file is part of the HamFramework for Siv3D.
//
//	Copyright (C) 2014-2016 Hamukun
//	Copyright (C) 2014-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "../Siv3D.hpp"

namespace ham
{
	namespace ScalableWindow
	{
		inline void Setup(const s3d::Size& baseSize = s3d::Size(640, 480))
		{
			s3d::Window::SetStyle(s3d::WindowStyle::Sizeable);

			s3d::Window::SetBaseSize(baseSize);
		}

		inline void Setup(s3d::int32 width, s3d::int32 height)
		{
			return Setup({ width, height });
		}

		inline s3d::Transformer2D CreateTransformer(const s3d::Size& baseSize = s3d::Window::BaseSize())
		{
			const double sx = static_cast<double>(s3d::Window::Width()) / baseSize.x;

			const double sy = static_cast<double>(s3d::Window::Height()) / baseSize.y;

			const double s = s3d::Min(sx, sy);

			if (sx <= sy)
			{
				return s3d::Transformer2D(s3d::Mat3x2::Scale(s).translate(0, (s3d::Window::Height() - baseSize.y * s) * 0.5), true);
			}
			else
			{
				return s3d::Transformer2D(s3d::Mat3x2::Scale(s).translate((s3d::Window::Width() - baseSize.x * s) * 0.5, 0), true);
			}
		}

		inline s3d::Transformer2D CreateTransformer(s3d::int32 width, s3d::int32 height)
		{
			return CreateTransformer({ width, height });
		}

		inline s3d::RectF GetVirtualWindowArea(const s3d::Size& baseSize = s3d::Window::BaseSize())
		{
			const double sx = static_cast<double>(s3d::Window::Width()) / baseSize.x;

			const double sy = static_cast<double>(s3d::Window::Height()) / baseSize.y;

			const double s = s3d::Min(sx, sy);

			if (sx <= sy)
			{
				return s3d::RectF(baseSize * s).moveBy(0, (s3d::Window::Height() - baseSize.y * s) * 0.5);
			}
			else
			{
				return s3d::RectF(baseSize * s).moveBy((s3d::Window::Width() - baseSize.x * s) * 0.5, 0);
			}
		}

		inline s3d::Array<s3d::RectF> GetBlackBars(const s3d::Size& baseSize = s3d::Window::BaseSize())
		{
			const double sx = static_cast<double>(s3d::Window::Width()) / baseSize.x;

			const double sy = static_cast<double>(s3d::Window::Height()) / baseSize.y;

			const double s = s3d::Min(sx, sy);

			if (sx < sy)
			{
				const double h = (s3d::Window::Height() - baseSize.y * s) * 0.5;

				return{ s3d::RectF(0, 0, s3d::Window::Width(), h), s3d::RectF(0, s3d::Window::Height() - h,s3d::Window::Width(), h) };
			}
			else if (sx > sy)
			{
				const double w = (s3d::Window::Width() - baseSize.x * s) * 0.5;

				return{ s3d::RectF(0, 0, w, s3d::Window::Height()), s3d::RectF(s3d::Window::Width() - w, 0, w, s3d::Window::Height()) };
			}
			else
			{
				return{};
			}
		}

		inline s3d::Array<s3d::RectF> GetBlackBars(s3d::int32 width, s3d::int32 height)
		{
			return GetBlackBars({ width, height });
		}

		inline void DrawBlackBars(const s3d::Color& color = s3d::Palette::Black, const s3d::Size& baseSize = s3d::Window::BaseSize())
		{
			for (const auto& bar : GetBlackBars(baseSize))
			{
				bar.draw(color);
			}
		}

		inline void DrawBlackBars(const s3d::Color& color, s3d::int32 width, s3d::int32 height)
		{
			return DrawBlackBars(color, { width, height });
		}
	}
}
