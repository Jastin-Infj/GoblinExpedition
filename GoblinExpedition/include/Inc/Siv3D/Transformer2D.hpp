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
# include "Fwd.hpp"
# include "Mat3x2.hpp"
# include "Mouse.hpp"
# include "Graphics2D.hpp"

namespace s3d
{
	struct Transformer2D
	{
		bool m_transformMouse = false;

		Transformer2D(const Mat3x2& mat, bool transformMouse = false)
			: m_transformMouse(transformMouse)
		{
			Graphics2D::PushTransform(mat);

			if (m_transformMouse)
			{
				Mouse::PushTransform(mat);
			}
		}

		~Transformer2D()
		{
			Graphics2D::PopTransform();

			if (m_transformMouse)
			{
				Mouse::PopTransform();
			}
		}
	};
}
