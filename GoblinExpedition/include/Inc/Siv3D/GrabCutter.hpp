//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2015 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Image.hpp"

namespace s3d
{
	class GrabCutter
	{
	private:

		class CGrabCutter;

		std::shared_ptr<CGrabCutter> pImpl;

	public:

		GrabCutter();

		GrabCutter(const Image& image);

		GrabCutter(const Image& image, const Rect& backgroundRect, int32 iteration = 2);

		void setForegroundMask(const Point& pos);

		void setBackgroundMask(const Point& pos);

		void setMask(const Image& image, const Color& foregroundPixel = Color(255,0,0), const Color& backgroundPixel = Color(0,255,0));

		static Color DefaultColoring(Color color, bool foreground)
		{
			if (!foreground)
			{
				color.a = 0;
			}

			return color;
		}

		void getResult(Image& image, std::function<Color(Color, bool)> coloring = DefaultColoring, int32 iteration = 2);

		void getResult(Grid<bool>& image, int32 iteration = 2);
	};
}
