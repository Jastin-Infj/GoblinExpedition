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
# include "Array.hpp"
# include "Mat3x2.hpp"

namespace s3d
{
	struct Mat3x2Stack
	{
		Array<Mat3x2> m_stack;

		Mat3x2 m_current = Mat3x2::Identity();

		const Mat3x2& push(const Mat3x2& mat)
		{
			m_stack.push_back(mat);

			return m_current = m_current * mat;
		}

		const Mat3x2& pop()
		{
			if (!m_stack.empty())
			{
				m_stack.pop_back();

				m_current = Mat3x2::Identity();

				for (const auto& mat : m_stack)
				{
					m_current = m_current * mat;
				}
			}

			return m_current;
		}

		const Mat3x2& set(const Mat3x2& mat)
		{
			m_stack.clear();

			return m_current = mat;
		}

		const Mat3x2& get() const
		{
			return m_current;
		}
	};
}
